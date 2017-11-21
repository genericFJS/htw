# -*- coding: utf-8 -*-
import threading

BLINK_PERIOD = 0.5

def _toggleLED (portnumber):
    print "toggle " + str(portnumber)  # siehe plaground.ledleuchtturm

def _switchAllOff():
    print "alle LEDs aus\r"  # siehe playground.ledleuchtturm
      
def changeStatus(status, newStatus):
    print("Changing Status from " + status[0] + " to " + str(newStatus) + ".")
    status[0] = newStatus
        
def _changeLED(status, threadEvents):
    while not(threadEvents[1].is_set()):    # Während das DisableThread-Event nicht aktiv ist:
        _switchAllOff()
        if status[0] == 'PROC':
            print("grün\r")
        elif status[0] == 'IDLE':
            print("orange\r")
        elif status[0] == 'MAINT':
            print("rot\r")
        elif status[0] == 'DOWN':
            while status[0] == 'DOWN':
                _toggleLED("rot\r")
                threadEvents[0].wait(BLINK_PERIOD)
                if threadEvents[1].is_set() or threadEvents[0].is_set():    # bei neuem Status oder Thread-beenden aus loop raus gehen
                    break;
                threadEvents[0].clear()
        # kann hier ggf. was schief gehen, wenn der Thread und das Hauptprogramm gleichzeitig den Event bearbeiten. Vielleicht alle .wait() und .clear() [auch im Hautpogramm] in einen Lock setzen?!
        threadEvents[0].wait()
        threadEvents[0].clear()
        
def _getInput(status, threadEvents):
    while True:
        lamp = raw_input("[q]uit, [d]isable, [g]rün, [o]range, [r]ot, [b]linkend \r");
        if len(lamp) == 0 or lamp[0] == 'q':
            break
        if (lamp[0] == 'd'):
            changeStatus(status, 'N/A')
        if (lamp[0] == 'g'):
            changeStatus(status, 'PROC')
        if (lamp[0] == 'o'):
            changeStatus(status, 'IDLE')
        if (lamp[0] == 'r'):
            changeStatus(status, 'MAINT')
        if (lamp[0] == 'b'):
            changeStatus(status, 'DOWN')
        threadEvents[0].set()
    
if __name__ == '__main__':       
    # globale Variablen jetzt lokal:
    status = ['N/A']    # nur Listen sind auch bei Übergabe zu Funktionen veränderlich (mutable). Deswegen status und threadEvents als Listen!
    threadEvents = [threading.Event(), threading.Event()]  # 0: Event für neusetzen des Status, 1: Event für beenden des Threads
    
    # setup LED Thread
    thread = threading.Thread(target=_changeLED, args=[status, threadEvents])
    thread.start()
    try:    # versuche Input zu bekommen (hier: durch Konsole, sonst: durch Socket)
        _getInput(status, threadEvents)
    except Exception, e:
        print "INTERRUPT " + str(e)
    finally:    # bei Interrupt (oder anderer Exception):
        try:    # versuche Thread zu beenden
            if thread.isAlive():
                threadEvents[1].set()  # Thread nicht mehr aktiv
                threadEvents[0].set()  # Letzte Thread-Schleife durchlaufen lassen (Event neu setzen)
                thread.join()  # Thread beenden
        except:
            print
        _switchAllOff() # alle ausschalten
        # und natürlich GPIO.cleanup(), siehe playground.ledleuchtturm
