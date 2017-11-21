# -*- coding: utf-8 -*-
'''
    Funktionen zur Arbeit mit LEDs.

    @type GREEN_PORT: int
    @var GREEN_PORT: Port der grünen LED auf dem Raspberry Pi.
    @type YELLOW_PORT: int
    @var YELLOW_PORT: Port der gelben LED auf dem Raspberry Pi.
    @type RED_PORT: int
    @var RED_PORT: Port der roten LED auf dem Raspberry Pi.
    @type blinkThread: Thread object
    @var blinkThread: Objekt des Threads der das Blinken einer LED
    realisiert.
    @type blinkThreadStopEvent: Thread event object
    @var blinkThreadStopEvent: Objekt eines Thread Events, welches den
    Thread beendet.
    @author: Simon Retsch
'''
import RPi.GPIO as GPIO  # @UnresolvedImport
import threading
import datetime

# global variables
GREEN_PORT = -1
YELLOW_PORT = -1
RED_PORT = -1
blinkThread = threading.Thread()
blinkThreadStopEvent = threading.Event()


def toggleLED(portnumber):
    '''
        Wechselt die den Zustand (an/aus) der LED am angegebenen Port.

        @type portnumber: int
        @param portnumber: Nummer des Ports am Rasperry Pi.
        @rtype: int
        @return: 1 bei Erfolg, -1 bei Misserfolg.
        @author: Falk-Jonatan Strube
    '''

    try:
        if GPIO.input(portnumber) == GPIO.LOW:
            GPIO.output(portnumber, GPIO.HIGH)
        else:
            GPIO.output(portnumber, GPIO.LOW)
        return 1
    except:
        return -1


def enableLED(portnumber):
    '''
        Schaltet die LED am angegeben Port an.

        @type portnumber: int
        @param portnumber: Nummer des Ports am Rasperry Pi.
        @rtype: int
        @return: 1 bei Erfolg, -1 bei Misserfolg.
        @author: Falk-Jonatan Strube
    '''

    try:
        switchAllOff()
        GPIO.output(portnumber, GPIO.HIGH)
        return 1
    except:
        return -1


def switchAllOff():
    '''
        Schaltet alle LEDs (definiert durch die globale Variablen der
        entsprechenden Ports) aus.

        @rtype: int
        @return: 1 bei Erfolg, -1 bei Misserfolg.
        @author: Falk-Jonatan Strube
    '''

    try:
        GPIO.output(GREEN_PORT, GPIO.LOW)
        GPIO.output(YELLOW_PORT, GPIO.LOW)
        GPIO.output(RED_PORT, GPIO.LOW)
        return 1
    except:
        return -1


def blink(portnumber):
    '''
        Lässt die LED am angegebenen Port blinken, indem der ein Thread
        in der globalen Variabel L{blinkThread} als L{blinkThreadFunction}
        gestartet wird.

        @type portnumber: int
        @param portnumber: Nummer des Ports am Rasperry Pi.
        @rtype: int
        @return: 1 bei Erfolg, -1 bei Misserfolg.
        @author: Falk-Jonatan Strube
    '''
    global blinkThread
    try:
        switchAllOff()
        blinkThread = threading.Thread(
                target=blinkThreadFunction, args=[portnumber])
        blinkThread.start()
        return 1
    except:
        return -1


def blinkThreadFunction(portnumber):
    '''
        Diese Funktion wird als Thread genutzt und lässt die LED am angegeben
        Port blinken:
        Das Warten zwischen dem Wechseln des LED-Zustands wird über das
        globale L{blinkThreadStopEvent} realisiert.
        Dadurch kann der Zustand des Blinkens jederzeit beendet werden.

        @type portnumber: int
        @param portnumber: Nummer des Ports am Rasperry Pi.
        @rtype: int
        @return: 1 bei Erfolg, -1 bei Misserfolg.
        @author: Falk-Jonatan Strube
    '''
    try:
        while not(blinkThreadStopEvent.is_set()):
            toggleLED(portnumber)
            blinkThreadStopEvent.wait(0.5)
        blinkThreadStopEvent.clear()
        return 1
    except:
        return -1


def killBlinkThread():
    '''
        Beendet den für das Blinken verantwortliche Thread L{blinkThread}.
        Es wird zuerst das L{blinkThreadStopEvent} aktiviert und der Thread
        dann zusammengeführt.

        @rtype: int
        @return: 1 bei Erfolg, -1 bei Misserfolg.
        @author: Falk-Jonatan Strube
    '''
    returnCode = -1
    if blinkThread.isAlive():
        blinkThreadStopEvent.set()
        returnCode = blinkThread.join()
    return returnCode


def changeState(status):
    '''
        Wechselt den Status der LED-Anzeige.
        Dabei werden zuerst Blink-Threads beendet (falls vorhanden).
        Dann wird die dem übergebenen Status entsprechende LED
        eingeschaltet oder das Blinken gestartet.
        Wenn der übergebene Status unbekannt ist, werden alle LEDs
        ausgeschaltet.

        @type status: string
        @param status: Status, zu dem gewechselt werden soll
        (bekannte Stati: PROC/IDLE/MAINT/DOWN).
        @rtype: int
        @return: 1 bei Erfolg, -1 bei Misserfolg.
        @author: Falk-Jonatan Strube
    '''

    returnCode = -1

    # Try to stop active threads,in case that the blink thread was used before
    try:
        returnCode = killBlinkThread()
    except:
        return returnCode

    # change into the given state
    if status == 'PROC':
        returnCode = enableLED(GREEN_PORT)
    elif status == 'IDLE':
        returnCode = enableLED(YELLOW_PORT)
    elif status == 'MAINT':
        returnCode = enableLED(RED_PORT)
    elif status == 'DOWN':
        returnCode = blink(RED_PORT)
    else:  # unknown state
        returnCode = switchAllOff()
        returnCode = -1

    # print status change
    if returnCode == -1:
        print("\nIllegal state! All LEDs are switched off!")
    else:
        now = datetime.datetime.now()
        currentTime = " %s:%s:%s %s-%s-%s" %(now.hour, now.minute, now.second,
            now.day, now.month, now.year)
        print("\nChanging Status to " + str(status) + str(currentTime) + ".")

    return returnCode


def setLEDsGlobal(configData):
    '''
        Setzt die Globalen Variablen für die LED Pins mit Hilfe der Daten
        aus der Konfigurationsdatei.

        @type configData: Json Object
        @param configData: Beinhaltet die Daten aus der Konfigurationsdatei
        der Konfigurationsdatei.
        @author: Simon Retsch
    '''

    global GREEN_PORT
    global YELLOW_PORT
    global RED_PORT

    GREEN_PORT = configData["ledleuchtturm"]["hardware"]["green"]
    YELLOW_PORT = configData["ledleuchtturm"]["hardware"]["yellow"]
    RED_PORT = configData["ledleuchtturm"]["hardware"]["red"]


def initLEDs():
    '''
        Initialisiert die LEDs des Raspberry Pi:
        Setzen des Pinning-Layouts und Pins als Output definieren

        @rtype: int
        @return: 1 falls das Initialisieren erfolgreich war, -1 wenn nicht.
        @author: Simon Retsch
    '''

    try:
        GPIO.setmode(GPIO.BCM)
        GPIO.setwarnings(False)
        GPIO.setup(GREEN_PORT, GPIO.OUT)
        GPIO.setup(YELLOW_PORT, GPIO.OUT)
        GPIO.setup(RED_PORT, GPIO.OUT)

    except:
        return -1

    return 1

