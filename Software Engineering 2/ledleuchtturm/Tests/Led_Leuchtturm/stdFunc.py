# -*- coding: utf-8 -*-


def printConfigSettings(jsonFileObject):
    '''
    Gibt den Inhalt des jsonFileObjects auf der Konsole aus

    @type jsonFileObject: Json Objekt
    @param jsonFileObject: Objekt welches Daten der Konfigurationsdatei enthält
    '''

    print "\nMachine ---"
    print "     Name:   %s" % (
            jsonFileObject["ledleuchtturm"]["machine"]["name"])

    print "\nDatabase ---"
    print "     Server:   %s" % (
            jsonFileObject["ledleuchtturm"]["database"]["server"])
    print "     Port:   %d" % (
            jsonFileObject["ledleuchtturm"]["database"]["port"])
    print "     Socketport:   %d" % (
            jsonFileObject["ledleuchtturm"]["database"]["Socketport"])
    print "     Name:   %s" % (
            jsonFileObject["ledleuchtturm"]["database"]["dbname"])
    print "     Username:   %s" % (
            jsonFileObject["ledleuchtturm"]["database"]["username"])
    print "     Password:   %s" % (
            jsonFileObject["ledleuchtturm"]["database"]["password"])
    print "     Table:   %s" % (
            jsonFileObject["ledleuchtturm"]["database"]["table"])
    print "     Column:   %s" % (
            jsonFileObject["ledleuchtturm"]["database"]["column"])

    print "\nHardware ---"
    print "     Pin Green LED:   %d" % (
            jsonFileObject["ledleuchtturm"]["hardware"]["green"])
    print "     Pin Yellow LED:   %d" % (
            jsonFileObject["ledleuchtturm"]["hardware"]["yellow"])
    print "     Pin Red LED:   %d" % (
            jsonFileObject["ledleuchtturm"]["hardware"]["red"])


def debug(string, DEBUG):
    '''
    Schreibt die Nachricht string auf der Konsole, falls DEBUG auf 1 gesetzt
        ist.

    @type string: string
    @type DEBUG: int
    @param string: Nachricht die auf der Konsole erscheinen soll
    @param DEBUG: Abhängigkeitsvariable
    '''

    if DEBUG == 1:
        print(string)

