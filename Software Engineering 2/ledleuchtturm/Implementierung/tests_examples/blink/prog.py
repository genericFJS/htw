# -*- coding: utf-8 -*-

# ---imports
import time
#import RPi.GPIO as GPIO
import json
import threading


class blinkThread(threading.Thread):
    def run(self):
        global threadRun
        while threadRun == 1:
            print "1"
            #GPIO.setup(pins[2], True)
            time.sleep(0.25)

            print "0"
            #GPIO.setup(pins[2], False)
            time.sleep(0.25)


# --- define threads
class newblinkThread(threading.Thread):
#class newblinkThread(threading.Thread, pin):
    def __init__(self, pin):
        # first call constructor
        super(newblinkThread,self).__init__()

        # create own variable
        self.stop_event = threading.Event()
        self.pin = pin


    def run(self):
        while not self.stop_event.is_set():
            print "1"
            #GPIO.setup(pin, True)
            time.sleep(0.25)

            print "0"
            #GPIO.setup(pin, False)
            time.sleep(0.25)


    def stop(self):
        # stop thread with thread run
        print "stop thread"
        self.stop_event.set()


# --- define functions
def checkArgumentForConfigFile():
    return configFile


def configFileExists(configFile):
    return -1


def configFileValidJsonFile(configFile):
    return -1


def getDBinfo(configFile):
    return dbInfo


def testDBconnection(dbInfo):
    return -1


def checkForDBmessage(trigger):
    return -1


def loadCurrentMaschineState():
    return state


def compareMaschineNames(maschineName):
    return -1


def setState(state, pins):
    color = ''

    # stop running Threads
    blinkThread().stop()

    # set all lights false
    #GPIO.setup(pins[0], False)
    #GPIO.setup(pins[1], False)
    #GPIO.setup(pins[2], False)

    # check which state it is
    if state is 'PROC':

        # light up led
        #GPIO.setup(pins[0], True)
        color = 'Grün'

    elif state is 'IDLE':
        #GPIO.setup(pins[1], True)
        # light up led
        color = 'Gelb'

    elif state is 'MAINT':
        #GPIO.setup(pins[2], True)
        # light up led
        color = 'Rot'

    elif state is 'DOWN':
        # start thread
        blinkThread().start()u
        color = 'Rot blinkend'

    else:
        color = 'Keine'

    tm = time.localtime()
    print "Statusänderung: %s, %s:%s:%s" %(color, tm.tm_hour, tm.tm_min, tm.tm_sec)
    return state


def checkForExitCommand(exitCommand):
    # print "Programm wird beendet"
    return -1


def createStdConf():
    defaultJsonConfig = """
        {
            \"ledleuchtturm\":{

                \"maschine\":{
                    \"name\":\"default\"
                },

                \"database\":{
                    \"server\":\"default\",
                    \"port\":\"default\",
                    \"dbname\":\"default\",
                    \"username\":\"default\",
                    \"password\":\"default\",
                    \"table\":\"default\",
                    \"column\":\"default\"
                },

                \"hardware\":{
                    \"green\":-1,
                    \"yellow\":-1,
                    \"red\":-1
                }
            }
        }
        """

    file = open('Std-Conf-LedLeuchtturm.json', 'w')
    file.write(defaultJsonConfig)
    file.close()
    return -1


def getJsonFileObject(fileName):
    fileData = open(fileName).read()

    # decode json content into data object
    jsonFileObject = json.loads(fileData)
    return jsonFileObject


def printConfigSettings(jsonFileObject):
    print "\nMaschine ---"
    print "     Name: %s" % jsonFileObject["ledleuchtturm"]["maschine"]["name"]
    print "\nDatabase ---"
    print "     Server:     %s" % jsonFileObject["ledleuchtturm"]["database"]["server"]
    print "     Port:       %s" % jsonFileObject["ledleuchtturm"]["database"]["port"]
    print "     Name:       %s" % jsonFileObject["ledleuchtturm"]["database"]["dbname"]
    print "     Username:   %s" % jsonFileObject["ledleuchtturm"]["database"]["username"]
    print "     Password:   %s" % jsonFileObject["ledleuchtturm"]["database"]["password"]
    print "     Table:      %s" % jsonFileObject["ledleuchtturm"]["database"]["table"]
    print "     Column:     %s" % jsonFileObject["ledleuchtturm"]["database"]["column"]
    print "\nHardware ---"
    print "     Pin Green LED:  %d" % jsonFileObject["ledleuchtturm"]["hardware"]["green"]
    print "     Pin Yellow LED: %d" % jsonFileObject["ledleuchtturm"]["hardware"]["yellow"]
    print "     Pin Red LED:    %d" % jsonFileObject["ledleuchtturm"]["hardware"]["red"]


# --- main
if __name__ == "__main__":
     # --- variables
    configFile = ""
    state = ""
    pins = [-1,-1,-1]

    # switch state example
    #jsonFileObject = getJsonFileObject("Test-Conf-LedLeuchtturm.json")
    #printConfigSettings(jsonFileObject)

    #pins[0] = jsonFileObject["ledleuchtturm"]["hardware"]["green"]
    #pins[1] = jsonFileObject["ledleuchtturm"]["hardware"]["yellow"]
    #pins[2] = jsonFileObject["ledleuchtturm"]["hardware"]["red"]

    #setState('PROC', pins)
    #time.sleep(1)
    #setState('IDLE', pins)
    #time.sleep(1)
    #setState('MAINT', pins)
    #time.sleep(1)
    #setState('DOWN', pins)
    #time.sleep(1)
    #setState('PROC', pins)

    blink = newblinkThread()

    blink.start()
    time.sleep(1)
    blink.stop()















#configFile = checkArgumentsForConfigFile()

#ret = configFileExists(configFile)
# No
    # exit program

#configFileValid(configFile)
# No
    # exit program

#dbinfo = getDBinfo(configFile)

#testDBconnection(dbInfo)

# No
    # exit program

#state = loadCurrentMaschineState()

#setState(state)

#while true:
#while true:
        #checkForExitCommand()
        # Yes
            # exit program

        #checkForDBtrigger()

    #compareMaschineNames(maschineName)
    # Yes
        #setState(state)

# close DB Connection
