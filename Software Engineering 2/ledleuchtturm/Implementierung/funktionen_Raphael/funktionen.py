import os
import json
from sys import argv

def checkArgumentForConfigFile():

    # Check count of arguments
    if len(argv) != 2:
        return -1

    # Check if file name has the right extension
    if '.json' not in argv[1]:
        return -1

    return argv[1]

# function: Ueberprueft ob dem Programm ein configFile Name (Pfad) uebergeben wurde
# in:   Kein Uebergabe, es existiert jedoch ein Objekt 'argv' das die Uebergabeparameter enthaelt (from sys import argv)
# out:  configFile Name (Pfad), oder -1 falls kein File angehaengt wurde


def configFileExists(configFile):
    if os.path.exists(configFile):
        return 1
    return -1

# function: Ueberprueft ob das confiFile existiert und gelesen werden kann
# in:   Pfad oder Name des configFiles
# out:  1 falls es existiert, -1 falls es nicht existiert


def configFileValidJsonFile(configFile):
    try:
        json.load(open(configFile, 'r'))
        return 1
    except ValueError as e:
        return -1

# function: Ueberprueft ob das angegebene configFile das Jsonformat hat
# in:   Pfad oder Name des configFiles
# out:  1 falls es valid ist, -1 falls es nicht valid ist


if __name__ == '__main__':

    if len(argv) < 2:
        print "usage: %s <path to config>" % (argv[0])
        exit(1)

    print checkArgumentForConfigFile()
    print configFileExists(argv[1])
    print configFileValidJsonFile(argv[1])

# Beispielaufrufe:
# $>funktionen.py
# $>funktionen.py ..\json\readInJson.py
# $>funktionen.py ..\json\config.json