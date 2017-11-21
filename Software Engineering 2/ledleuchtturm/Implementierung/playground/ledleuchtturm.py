# -*- coding: utf-8 -*-
import RPi.GPIO as GPIO #@UnresolvedImport
import threading
import paho.mqtt.client as mqtt #@UnresolvedImport
import sys
import time
from cgitb import reset

GREEN_PORT, ORANGE_PORT, RED_PORT = 26, 19, 13
#GREEN_PORT, ORANGE_PORT, RED_PORT = 21, 20, 16
BLINK_PERIOD = 0.5
DEBUG = 1 # 0: kein Debug, 1: grobes Debug, 2: feines Debug, 3: alle Meldungen
TOPIC_PREFIX = "ledleuchtturm/"
BROKER = "cougcv5yvgvitijp.myfritz.net"
PORT = 1883
TOOL = "#"
topic = ""
status = 0 # 0: aus, 1: grün, 2: orange, 3: rot, 4: rot blinkend, 5: error
threadEvent = threading.Event()
threadActive = True
resetLED = False

def debug(string, mode):
    if DEBUG == 3:
        printDebugMessage(string, mode)
    elif DEBUG == 2:
        if mode <= 2:
            printDebugMessage(string, mode)
    elif DEBUG == 1:
        if mode <= 1:
            printDebugMessage(string, mode)
    
def printDebugMessage(string, mode):
    if mode == 1:
        print('\t'+string)
    elif mode == 2:
        print('\t\t'+string)
    elif mode == 3:
        print('\t\t\t'+string)

def _toggleLED (portnumber):
    if GPIO.input(portnumber) == GPIO.LOW:
        GPIO.output(portnumber, GPIO.HIGH)
    else:
        GPIO.output(portnumber, GPIO.LOW)

def _switchAllOff():
    GPIO.output(GREEN_PORT, GPIO.LOW)
    GPIO.output(ORANGE_PORT, GPIO.LOW)
    GPIO.output(RED_PORT, GPIO.LOW)
        
def _changeLED():
    global resetLED
    while threadActive:
        _switchAllOff()
        if status == 1:
            GPIO.output(GREEN_PORT, GPIO.HIGH)
        elif status == 2:
            GPIO.output(ORANGE_PORT, GPIO.HIGH)
        elif status == 3:
            GPIO.output(RED_PORT, GPIO.HIGH)
        elif status == 4:
            while (status == 4) and not(resetLED):
                debug("blinked",3)
                _toggleLED(RED_PORT)
                threadEvent.wait(BLINK_PERIOD)                
        elif status == 5:
            while (status == 5) and not(resetLED):
                debug("signal",3)
                _toggleLED(RED_PORT)
                threadEvent.wait(BLINK_PERIOD)
                _toggleLED(RED_PORT)
                _toggleLED(ORANGE_PORT)
                threadEvent.wait(BLINK_PERIOD)
                _toggleLED(ORANGE_PORT)
                _toggleLED(GREEN_PORT)
                threadEvent.wait(BLINK_PERIOD)
                _toggleLED(GREEN_PORT)
        threadEvent.wait()
        #debug("changeLED",3)
        threadEvent.clear()
        # Einsatz Semaphor?
        resetLED = False

def _getInput():
    '''
    Statuswechsel durch Nutzereingabe.
    '''
    global status
    global resetLED
    while True:
        lamp = raw_input("d / g / o / r / b / e - ");
        if len(lamp) == 0 or lamp[0] == 'q':
            break
        if (lamp[0] == 'd'):
            changeStatus(0)
        if (lamp[0] == 'g'):
            changeStatus(1)
        if (lamp[0] == 'o'):
            changeStatus(2)
        if (lamp[0] == 'r'):
            changeStatus(3)
        if (lamp[0] == 'b'):
            changeStatus(4)
        if (lamp[0] == 'e'):
            changeStatus(5)
        # Einsatz Semaphor?
        resetLED = True
        threadEvent.set()

def _justWait():
    while True:
        time.sleep(5)
        debug("waiting with status "+str(status), 3)
        
def changeStatus(newStatus):
    global status
    debug("Changing Status from "+str(status)+" to "+str(newStatus)+".",3)
    status = newStatus

def on_connect(client, userdata, flags, rc):
    debug("Connected with result code "+str(rc), 3)
    client.subscribe(topic)

def on_message(client, userdata, msg):
    global status
    global resetLED
    debug(msg.topic+": "+str(msg.payload),1)
    if (str(msg.payload) == 'PROC'):
        changeStatus(1)
    if (str(msg.payload) == 'IDLE'):
        changeStatus(2)
    if (str(msg.payload) == 'MAINT'):
        changeStatus(3)
    if (str(msg.payload) == 'DOWN'):
        changeStatus(4)
    # Bonus-Zustand :-)
    if (str(msg.payload) == 'ERR'):
        changeStatus(1)
    if (str(msg.payload) not in ['PROC', 'IDLE', 'MAINT', 'DOWN', 'ERR']):
        changeStatus(0)
    # Einsatz Semaphor?
    resetLED = True
    threadEvent.set()
    
if __name__ == '__main__':
    if len(sys.argv) >2:
        GREEN_PORT, ORANGE_PORT, RED_PORT = 21, 20, 16
    GPIO.setmode(GPIO.BCM)
    GPIO.setwarnings(False)
    GPIO.setup(GREEN_PORT, GPIO.OUT)
    GPIO.setup(ORANGE_PORT, GPIO.OUT)
    GPIO.setup(RED_PORT, GPIO.OUT)
    
    if len(sys.argv) < 2:
        print("No tool name given!")
    else:
        # setup MQTT details:
        TOOL = sys.argv[1]
        topic = TOPIC_PREFIX + TOOL
        # setup subscription:
        client = mqtt.Client()
        client.on_connect = on_connect
        client.on_message = on_message      
        client.connect(BROKER, PORT, 60)
        client.loop_start()
        # setup LED Thread
        thread = threading.Thread(target=_changeLED)
        thread.start()
        try:
            #_getInput()
            _justWait()
        except:
            print
        client.loop_stop()
    if thread.isAlive():
        status = 0
        threadActive=False
        threadEvent.set()
        thread.join()
    _switchAllOff()
    GPIO.cleanup();
