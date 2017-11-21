# -*- coding: utf-8 -*-
'''
    Funktionen zur Arbeit mit Dateien.

    @type globalFileOpen: File object
    @var globalFileOpen: Dateiobjekt einer geöffneten Datei.
    @author: Simon Retsch
'''

import time
import json
import os


# global Variables
globalFileOpen = -1


def checkArgumentForConfigFile(argv):
    '''
        Überprüft ob dem Programm ein Pfad einer Konfigurationsdatei mit der
        Endung .json als Argument übergeben wurde.

        @type argv: string[]
        @param argv: Programm Übergabeparameter.
        @rtype: int / string
        @return: Pfad der Konfigurationsdatei falls es erfolgreich ist,
        -1 falls nicht die richtige Anzahl von Argumenten mitgegeben wurde.
        @author: Raphael Pour
    '''

    # Check count of arguments
    if len(argv) != 2:
        return -1

    return argv[1]


def configFileExists(configFile):
    '''
        Überprüft ob die Konfigurationsdatei existiert.

        @type configFile: string
        @param configFile: Pfad der Konfigurationsdatei.
        @rtype: int
        @return: 1 falls die Datei existiert, -1 falls die Datei nicht
        existiert.
        @author: Raphael Pour
    '''

    if os.path.exists(configFile):
        return 1
    return -1


def configFileValidJsonFile(configFile):
    '''
        Überprüft ob es sich bei configFile wirklich um eine json Datei
        handelt.

        @type configFile: string
        @param configFile: Pfad der Konfigurationsdatei.
        @rtype: int
        @return: 1 falls configFile eine Json Datei ist, -1 falls configFile
        keine Json Datei ist.
        @author: Raphael Pour
    '''

    # Check if file name has the right extension
    if '.json' not in configFile:
        return -1

    try:
        json.load(open(configFile, 'r'))
        return 1
    except ValueError as e:
        return -1


def createStdConf():
    '''
        Schreibt ein Python Objekt in eine Datei mit dem Namen
        Std-Conf-Ledleuchtturm.json. In dem Objekt befinden sich
        Standartwerte.

        @rtype: int
        @return: 1, falls das Objekt in die Datei geschrieben werden kann,
        -1 falls es dabei Probleme gibt.
        @author: Simon Retsch
    '''

    defaultJsonConfig = """
        {
            \"ledleuchtturm\":{

                \"machine\":{
                    \"name\":\"default\"
                },

                \"database\":{
                    \"server\":\"default\",
                    \"port\":-1,
                    \"socketport\":-1,
                    \"interface\":\"default\",
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

    global globalFileOpen

    try:
        globalFileOpen = open('Std-Conf-LedLeuchtturm.json', 'w')
        file = globalFileOpen
        file.write(defaultJsonConfig)
        file.close()

    except IOError as e:
        return -1

    return 1


def getJsonFileObject(fileName):
    '''
        Lädt die Struktur einer Json Datei in ein Objekt.

        @type fileName: string
        @param fileName: Pfad der Json Datei.
        @rtype: Json Object
        @return: Objekt welches aus einer Json Datei geladen wurde.
        @author: Simon Retsch
    '''

    fileData = open(fileName).read()

    # decode json content into data object
    jsonFileObject = json.loads(fileData)
    return jsonFileObject

