# -*- coding: utf-8 -*-
'''
    Funktionen zur Arbeit mit der Datenbank.

    @type globalDBconnection: psycopg2 database connection object
    @var globalDBconnection: Verbindungsvariable zur Datenbank.
    @type globalDBsocket: psycopg2 socket object
    @var globalDBsocket: Socketvariable zur Datenbank.
    @type globalDBcursor: psycopg2 cursor object
    @var globalDBcursor: Cursorvariable zur Datenbank.
    @author: Simon Retsch
'''

import socket
import psycopg2
import netifaces as ni

# global variables
globalDBconnection = -1
globalDBsocket = -1
globalDBcursor = -1


def testDBconnection(configData):
    '''
        Testen der Datenbankverbindung.

        @type configData: Json Object
        @param configData: Beinhaltet die Daten der Konfigurationsdatei.
        @rtype: int / psycopg2 Connectionvariable
        @return: Verbindungsvariable falls die Verbindung hergestellt werden
        kann, -1 falls die Verbindung nicht hergestellt werden kann.
        @author: Simon Retsch
    '''

    global globalDBconnection

    dbServer = configData["ledleuchtturm"]["database"]["server"]
    dbPort = configData["ledleuchtturm"]["database"]["port"]
    dbUser = configData["ledleuchtturm"]["database"]["username"]
    dbPassword = configData["ledleuchtturm"]["database"]["password"]
    dbName = configData["ledleuchtturm"]["database"]["dbname"]

    try:
        globalDBconnection = psycopg2.connect(
            host=dbServer, port=dbPort, user=dbUser,  password=dbPassword,
            dbname=dbName, connect_timeout=5)

        dbConnection = globalDBconnection

        return dbConnection

    except psycopg2.OperationalError as e:
        return -1


def waitForDBupdate(configData):
    '''
        Verbindet sich über Sockets zu dem in der Konfigurationsdatei
        festgelegten Postgresql Server und wartet auf ein
        Update der ebenfalls dort festgelegten Maschine, der Status
        nach diesem Update wird zurückgegeben.

        @type configData: Json Object
        @param configData: Beinhaltet die Daten aus der Konfigurationsdatei
        der Konfigurationsdatei.
        @rtype: string
        @return: Status der Maschine machineName bei einem Update.
        @author: Ragnar Luga (kleine Änderungen durch Simon Retsch)
    '''

    # variables
    global globalDBsocket
    interface = configData["ledleuchtturm"]["database"]["interface"]
    dbSocketPort = configData["ledleuchtturm"]["database"]["socketport"]
    machineName = configData["ledleuchtturm"]["machine"]["name"]

    try:
        ni.ifaddresses(interface)
        dbServer = ni.ifaddresses(interface)[ni.AF_INET][0]['addr']
    except:
        print "Es trat ein Fehler beim ermitteln der IP Adresse auf"
        return -1

    try:
        globalDBsocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        serversocket = globalDBsocket
        serversocket.bind((dbServer, dbSocketPort))
        serversocket.listen(1)  # become a server socket, maximum 5 connections

    except socket.error as e:
        print "socket.error happened"
        return -1

    print "opened on port %d" % dbSocketPort

    while True:
        connection, address = serversocket.accept()

        update = connection.recv(64)

        if len(update) > 0:
            updateArray = update.split(" ")

            if len(updateArray) == 2:

                if updateArray[0] == machineName:
                    break

    serversocket.close()
    return updateArray[1]


def getCurrentDBstate(dbConnection, configData):
    '''
        Erstellt einen temporären Cursor für die Datenbank, führt darüber ein
        select auf die Tabelle tool aus, liest das Ergebnis ein, untersucht
        ob ein valider Zustand für die in configData angegebene Maschine
        darin existiert und gibt diesen zurück.

        @type dbConnection: psycopg2 Connectionvariable
        @param dbConnection: Variable der Verbindung mit der Datenbank.
        @type configData: Json Object
        @param configData: Beinhaltet die Daten aus der Konfigurationsdatei
        der Konfigurationsdatei.

        @rtype: int / string
        @return: Status der Maschine falls die Maschine gefunden wurde und ein
        valider Status vorhanden war, -1 falls nicht.
        @author: Simon Retsch
    '''

    global globalDBcursor
    state = "-1"
    machineName = configData["ledleuchtturm"]["machine"]["name"]
    table = configData["ledleuchtturm"]["database"]["table"]

    # create a pycopg2 cursor
    globalDBcursor = dbConnection.cursor()
    dbCursor = globalDBcursor

    # execute statement
    try:
        dbCursor.execute("select * from " + str(table) + ";")

    except psycopg2.ProgrammingError as e:
        print "ProgrammingError"
        dbCursor.close()
        return -1

    # get in the rows
    rows = dbCursor.fetchall()

    # print all the rows
    for row in rows:
        if row[0] == machineName and len(row) == 7:
            state = row[6]
            break

    # state legal?
    if state not in ("IDLE", "PROC", "MAINT", "DOWN"):
        dbCursor.close()
        return -1

    dbCursor.close()
    return state

