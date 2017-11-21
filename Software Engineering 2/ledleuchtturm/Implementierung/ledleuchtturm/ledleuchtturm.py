# -*- coding: utf-8 -*-
'''
    Main-Funktion des Paketes ledleuchtturm. Sie repräsentiert den
    Ablauf des Programms. Sie beschränkt sich auf das Aufrufen
    von Funktionen aus den Modulen L{stdFunc}, L{fileFunc}, L{dbFunc} oder
    L{ledFunc}. Des Weiteren behandelt  sie die Auswertung von Rückgabewerten
    und das Schreiben von Meldungen auf der Konsole.

    @type DEBUG: int
    @var DEBUG: Entscheidung über Ausgabe der debug-Nachrichten.
    @author: Simon Retsch
'''
# ---imports
from sys import argv
import sys
import psycopg2
import signal
import threading
import RPi.GPIO as GPIO

import stdFunc
import fileFunc
import dbFunc
import ledFunc


# global variables
DEBUG = 1


def signal_handler(signal, frame):
    '''
        Behandelt das Signal welches durch Strg+C ausgelöst wird (SIGINT)
        und beendet alle Verbindungen oder schließt alle offenen Dateien damit
        das Programm ordnungsgemäß beendet wird.

        @type signal: int
        @param signal: Signalnummer
        @type frame: stack frame
        @param frame: Unterbrochener Stack Frame
        @author: Simon Retsch
    '''

    print """\n---\nSie haben Ctrl+C gedrückt!\n\nAlle Verbindungen und offenen
Dateien werden nun zurückgebaut!\n"""

    # clean up File
    try:
        fileFunc.globalFileOpen.close()
    except:
        stdFunc.debug("Keine Dateien geöffnet", DEBUG)

    # clean up DB
    try:
        dbFunc.globalDBcursor.close()
    except:
        stdFunc.debug("Keine Cursor geöffnet", DEBUG)

    try:
        dbFunc.globalDBsocket.close()
    except:
        stdFunc.debug("Keine Sockets geöffnet", DEBUG)

    try:
        dbFunc.globalDBconnection.close()
    except:
        stdFunc.debug("Keine Verbindungen zu Datenbanken geöffnet", DEBUG)

    # clean up LEDs
    ledFunc.switchAllOff()
    GPIO.cleanup()

    # clean up threads
    ledFunc.killBlinkThread()

    print "Alles erfolgreich zurückgebaut.\nDas Programm wird beendet!"

    sys.exit(-1)


# --- main
if __name__ == "__main__":
    # --- variables
    # return variable for functions
    ret = 0

    # enable own signal_handler
    signal.signal(signal.SIGINT, signal_handler)

    # read in configFile (path) from Arguments
    configFile = fileFunc.checkArgumentForConfigFile(argv)

    if configFile == -1:
        configFile = "Std-Conf-LedLeuchtturm.json"
        stdFunc.debug("""Keine Konfigurationsdatei als Argument übergeben!\n
Standart Konfigurationsdatei wird benutzt!\n""", DEBUG)

        ret = fileFunc.configFileExists(configFile)

        if ret != 1:
            fileFunc.createStdConf()
            print """Konfigurationsdatei wurde nicht gefunden.\n
Muster-Konfigurationsdatei wurde erstellt!\n
Editieren Sie die Muster-Konfiguration
und starten sie das Programm neu!\n
Das Programm wird beendet!"""

            sys.exit(-1)

    else:
        stdFunc.debug("""Konfigurationsdatei wurde als Argument
übergeben!""", DEBUG)
        ret = fileFunc.configFileExists(configFile)

        if ret != 1:
            print """Konfigurationsdatei nicht gefunden!\n
Das Programm wird beendet!"""

            sys.exit(-1)

    stdFunc.debug("Konfigurationsdatei gefunden!\n", DEBUG)

    # check if configFile is valid
    ret = fileFunc.configFileValidJsonFile(configFile)
    if ret != 1:
        print """Bei der Konfigurationsdatei handelt es sich
nicht um eine JSON Datei!\n
Das Programm wird beendet!"""

        sys.exit(-1)

    # get the data out of the json file
    configData = fileFunc.getJsonFileObject(configFile)

    # set the LED pins
    ret = ledFunc.setLEDsGlobal(configData)

    # test connection to the database
    dbConnection = dbFunc.testDBconnection(configData)
    if dbConnection == -1:
        print """Verbindung zur Datenbank fehlgeschlagen.\n
Das Programm wird beendet!"""
        sys.exit(-1)

    stdFunc.debug("Verbindung zur Datenbank Erfolgreich", 1)

    # read out the current state of the machine
    state = dbFunc.getCurrentDBstate(dbConnection, configData)
    if state == -1:
        print """Es konnte kein legaler erster Status für die aktuelle Maschine
abgefragt werden.\n
Das Programm wird beendet!"""
        # cleanup
        dbConnection.close()
        sys.exit(-1)

    # initialize the Raspi for controling the LEDs
    ret = ledFunc.initLEDs()
    if ret == -1:
        print """Raspberry Pi konnte nicht initialisiert werden.\n
Das Programm wird beendet!"""
        dbConnection.close()

    while True:
        stateChange = ledFunc.changeState(state)

        if stateChange == -1:
            print """Probleme mit dem setzten des letzten Updates.\n
Neuer Status wurde nicht übernommen!"""

        state = dbFunc.waitForDBupdate(configData)
        if state == -1:
            print "\n Das Programm wird beendet!"
            break

    # clean up
    dbConnection.close()
    dbFunc.globalDBconnection = -1

    ledFunc.killBlinkThread()
    ledFunc.switchAllOff()
    GPIO.cleanup()
    ledFunc.globalLEDinit = -1

