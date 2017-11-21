# -*- coding: utf-8 -*-
# import RPi.GPIO as GPIO  # @UnresolvedImport
import threading


# global variables ---
# LED Ports
GREEN_PORT, YELLOW_PORT, RED_PORT = -1, -1, -1
# Thread, that realises the blinking
blinkThread = threading.Thread()
# Event, that tells the thread to stop
blinkThreadStopEvent = threading.Event()


def toggleLED (portnumber):
    '''
        Wechselt die den Zustand (an/aus) der LED am angegebenen Port.
        @param portnumber: Nummer des Ports am Rasperry Pi.
        @type portnumber: int.
        @rtype: int.
        @return: 1 bei Erfolg, -1 bei Misserfolg.
    '''
    try:
        if GPIO.input(portnumber) == GPIO.LOW:
            GPIO.output(portnumber, GPIO.HIGH)
        else:
            GPIO.output(portnumber, GPIO.LOW)
        return 1
    except:
        return -1


def enableLED (portnumber):
    '''
        Schaltet die LED am angegeben Port an.
        @param portnumber: Nummer des Ports am Rasperry Pi.
        @type portnumber: int.
        @rtype: int.
        @return: 1 bei Erfolg, -1 bei Misserfolg.
    '''
    try:
        switchAllOff()
        GPIO.output(portnumber, GPIO.HIGH)
        return 1
    except:
        return -1


def switchAllOff():
    '''
        Schaltet alle LEDs aus.
        @rtype: int.
        @return: 1 bei Erfolg, -1 bei Misserfolg.
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
        Lässt die LED am angegebenen Port (in einem Thread) blinken.
        @param portnumber: Nummer des Ports am Rasperry Pi.
        @type portnumber: int.
    @rtype: int.
        @return: 1 bei Erfolg, -1 bei Misserfolg.
    '''
    global blinkThread
    try:
        switchAllOff()
        blinkThread = threading.Thread(target=blinkThreadFunction, args=[portnumber])
        blinkThread.start()
        return 1
    except:
        return -1


def blinkThreadFunction(portnumber):
    '''
        Diese Funktion wird als Thread genutzt und lässt die LED am
            angegeben Port blinken.
        @param portnumber: Nummer des Ports am Rasperry Pi.
        @type portnumber: int.
    @rtype: int.
        @return: 1 bei Erfolg, -1 bei Misserfolg.
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
        Beendet den für das Blinken verantwortliche Thread.
    @rtype: int.
        @return: 1 bei Erfolg, -1 bei Misserfolg.
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
            Wenn der übergeben Status unbekannt ist, werden alle LEDs
            ausgeschaltet.

        @param status: Status, zu dem gewechselt werden soll
            (bekannte Stati: PROC/IDLE/MAINT/DOWN).
        @type status: string.
    @rtype: int.
        @return: 1 bei Erfolg, -1 bei Misserfolg.
    '''

    returnCode = -1
    success = 1

    # Try to stop active threads (in case that the blink thread was used before
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
        success = -1

    # print status change
    if success == -1:
        print("\nIllegal state! All LEDs are switched off!")
    else:
        print("\nChanging Status to " + str(status) + ".")

    return returnCode


def setLEDsGlobal(configData):
    '''
        Setzt die Globalen Variablen für die LED Pins mit Hilfe der Daten
            aus der Konfigurationsdatei

        @type configData: Json Objekt
        @param configData: Beinhaltet die Daten aus der Konfigurationsdatei
            der Konfigurationsdatei
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
            setzen des Pinning-Layouts und Pins als Output definieren

        @rtype: int
        @return: 1 falls das Initialisieren erfolgreich war, -1 wenn nicht
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

