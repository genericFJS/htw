# -*- coding: utf-8 -*-
import RPi.GPIO as GPIO  # @UnresolvedImport
import threading

# diese globalen Variablen funktionieren vielmehr als DEFs
BLINK_PERIOD = 0.5
# diese globalen Variablen sind sinnvoll (nach dem starten und ersten Belegen sind sie fest, wie DEFs):
GREEN_PORT, ORANGE_PORT, RED_PORT = 26, 19, 13  #: Ports, an denen die LEDs anliegen.
# diese globalen Variablen sind für das sinnvolle Nutzen der Threads unablässlich:
blinkThread = threading.Thread()    #: Thread, der für das Blinken verantwortlich ist.
blinkThreadStopEvent = threading.Event()    #: Event, der dem Thread signalisiert, dass er beendet werden soll.

def toggleLED (portnumber):
    '''
        Wechselt die den Zustand (an/aus) der LED am angegebenen Port.
        @param portnumber: Nummer des Ports am Rasperry Pi.
        @type portnumber: Zahl.
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
        @type portnumber: Zahl.
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
        @return: 1 bei Erfolg, -1 bei Misserfolg.
    '''
    try:
        GPIO.output(GREEN_PORT, GPIO.LOW)
        GPIO.output(ORANGE_PORT, GPIO.LOW)
        GPIO.output(RED_PORT, GPIO.LOW)
        return 1
    except: 
        return -1
    
def blink(portnumber):
    '''
        Lässt die LED am angegebenen Port (in einem Thread) blinken.
        @param portnumber: Nummer des Ports am Rasperry Pi.
        @type portnumber: Zahl.
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
        Diese Funktion wird als Thread genutzt und lässt die LED am angegeben Port blinken.
        @param portnumber: Nummer des Ports am Rasperry Pi.
        @type portnumber: Zahl.
        @return: 1 bei Erfolg, -1 bei Misserfolg.
    '''
    try:
        while not(blinkThreadStopEvent.is_set()):
            toggleLED(portnumber)
            blinkThreadStopEvent.wait(BLINK_PERIOD)
        blinkThreadStopEvent.clear()
        return 1
    except:
        return -1

def killBlinkThread():
    '''
        Beendet den für das Blinken verantwortliche Thread.
        @return: 1 bei Erfolg, -1 bei Misserfolg.
    '''
    returnCode = -1
    if blinkThread.isAlive():
        blinkThreadStopEvent.set()
        returnCode = blinkThread.join()
    return returnCode

def changeStatus(status):
    '''
        Wechselt den Status der LED-Anzeige. 
            Dabei werden zuerst Blink-Threads beendet (falls vorhanden). 
            Dann wird die dem übergebenen Status entsprechende LED eingeschaltet oder das Blinken gestartet.
            Wenn der übergeben Status unbekannt ist, werden alle LEDs ausgeschaltet.
        @param status: Status, zu dem gewechselt werden soll (bekannte Stati: PROC/IDLE/MAINT/DOWN).
        @type status: Zeichenkette.
        @return: 1 bei Erfolg, -1 bei Misserfolg.
    '''
    print("Changing Status to " + str(status) + ".")
    returnCode = -1
    # Versuche aktive Threads zu beenden (falls zuvor blinkender Zustand war)
    try:
        returnCode = killBlinkThread()
    except:
        return returnCode
    # Wechsele in entsprechenden Zustand:
    if status == 'PROC':
        returnCode = enableLED(GREEN_PORT)
    elif status == 'IDLE':
        returnCode = enableLED(ORANGE_PORT)
    elif status == 'MAINT':
        returnCode = enableLED(RED_PORT)
    elif status == 'DOWN':
        returnCode = blink(RED_PORT)
    else:  # status unbekannt (Maschine nicht gefunden)
        returnCode = switchAllOff()
    return returnCode
        
if __name__ == '__main__':
    GPIO.setmode(GPIO.BCM)
    GPIO.setwarnings(False)
    GPIO.setup(GREEN_PORT, GPIO.OUT)
    GPIO.setup(ORANGE_PORT, GPIO.OUT)
    GPIO.setup(RED_PORT, GPIO.OUT)
    try:  # versuche Input zu bekommen (hier: durch Konsole, sonst: durch Socket)
        while True:
            lamp = raw_input("[q]uit, [n]ot active, [p]roc, [i]dle, [m]aint, [d]own ");
            if len(lamp) == 0 or lamp[0] == 'q':
                break
            if (lamp[0] == 'n'):
                changeStatus('N/A')  # 
            if (lamp[0] == 'p'):
                changeStatus('PROC')
            if (lamp[0] == 'i'):
                changeStatus('IDLE')
            if (lamp[0] == 'm'):
                changeStatus('MAINT')
            if (lamp[0] == 'd'):
                changeStatus('DOWN')
    except:
        print "\nINTERRUPT"
    finally:
        print("Shutting down.")
        killBlinkThread()
        switchAllOff()
        GPIO.cleanup()
