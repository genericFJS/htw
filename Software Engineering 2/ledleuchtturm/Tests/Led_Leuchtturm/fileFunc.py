# -*- coding: utf-8 -*-

import time
import json
import os


def checkArgumentForConfigFile(argv):
    '''
    Überprüft ob dem Programm ein Pfad einer Konfigurationsdatei mit der
        Endung .json als Argument übergeben wurde

    @type argv: string[]
    @param argv: Programm Übergabeparameter
    @rtype: int oder string
    @return: Pfad der Konfigurationsdatei oder -1 falls keine Datei mit der
        Endung .json übergeben wurde
    '''

    # Check count of arguments
    if len(argv) != 2:
        return -1

    # Check if file name has the right extension
    if '.json' not in argv[1]:
        return -1

    return argv[1]


def configFileExists(configFile):
    '''
    Überprüft ob die Konfigurationsdatei existiert

    @type configFile: string
    @param configFile: Pfad der Konfigurationsdatei
    @rtype: int
    @return: 1 falls die Datei existiert, -1 falls die Datei nicht existiert
    '''

    if os.path.exists(configFile):
        return 1
    return -1


def configFileValidJsonFile(configFile):
    '''
    Überprüft ob es sich bei configFile wirklich um eine json Datei handelt

    @type configFile: string
    @param configFile: Pfad der Konfigurationsdatei
    @rtype: int
    @return: 1 falls configFile eine Json Datei ist, -1 falls configFile
        keine Json Datei ist
    '''

    try:
        json.load(open(configFile, 'r'))
        return 1
    except ValueError as e:
        return -1


def createStdConf():
    '''
    Schreibt ein Python Objekt in eine Datei mit dem Name
        Std-Conf-Ledleuchtturm.json. In dem Objekt befinden sich
        Standartwerte

    @rtype: int
    @return: 1, falls das Objekt in die Datei geschrieben werden kann,
        -1 falls es dabei Probleme gibt
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
                    \"Socketport\":-1,
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

    try:
        file = open('Std-Conf-LedLeuchtturm.json', 'w')
        file.write(defaultJsonConfig)
        file.close()

    except IOError as e:
        return -1

    return 1


def getJsonFileObject(fileName):
    '''
    Läd die Struktur einer Json Datei in ein Objekt.

    @type fileName: string
    @param fileName: Pfad der Json Datei
    @rtype: Json Objekt
    @return: Objekt welches aus einer Json Datei geladen wurde
    '''

    fileData = open(fileName).read()

    # decode json content into data object
    jsonFileObject = json.loads(fileData)
    return jsonFileObject

