# -*- coding: utf-8 -*-

import socket
import psycopg2


def testDBconnection(configData):
    '''
    Testen der Datenbankverbindung

    @type configData: Json Objekt
    @param configData: Beinhaltet die Daten aus der Konfigurationsdatei
        der Konfigurationsdatei
    @rtype: int oder psycopg2 Verbindungsvariable
    @return: Verbindungsvariable falls die Verbindung hergestellt werden kann,
        -1 falls die Verbindung nicht hergestellt werden kann
    '''

    dbServer = configData["ledleuchtturm"]["database"]["server"]
    dbPort = configData["ledleuchtturm"]["database"]["port"]
    dbUser = configData["ledleuchtturm"]["database"]["username"]
    dbPassword = configData["ledleuchtturm"]["database"]["password"]
    dbName = configData["ledleuchtturm"]["database"]["dbname"]

    try:
        dbConnection = psycopg2.connect(host=dbServer, port=dbPort,
            user=dbUser,  password=dbPassword, dbname=dbName, connect_timeout=5)

        return dbConnection

    except psycopg2.OperationalError as e:
        return -1


def waitForDBupdate(configData):
    '''
    Verbindet sich über Sockets zum dem in der Konfigurationsdatei
        festgelegten Postgresql Server und wartet auf ein
        Update der ebenfalls dort festgelegten Maschine, der Status nach diesem
        Update wird zurück gegeben

    @type configData: Json Objekt
    @param configData: Beinhaltet die Daten aus der Konfigurationsdatei
        der Konfigurationsdatei
    @rtype: string
    @return: Status der Maschine machineName bei einem Update
    '''

    # variables
    dbServer = configData["ledleuchtturm"]["database"]["server"]
    dbSocketPort = configData["ledleuchtturm"]["database"]["Socketport"]
    machineName = configData["ledleuchtturm"]["machine"]["name"]

    try:
        serversocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
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

    return updateArray[1]

def getCurrentDBstate(dbConnection, configData):
    '''
    Erstellt einen temporären Cursor für die Datenbank, führt darüber ein
        select auf die Tabelle tool aus, liest das Ergebnis ein, untersucht ob
        ein legaler Zustand für die in configData angegebene Maschine darin
        existiert und gibt diesen zurück.

    @type dbConnection: psycopg2 Verbindungsvariable
    @type configData: Json Objekt
    @param dbConnection: Variable der Verbindung mit der Datenbank
    @param configData: Beinhaltet die Daten aus der Konfigurationsdatei
        der Konfigurationsdatei
    @rtype: int oder string
    @return: Status der Maschine falls die Maschine gefunden wurde und ein
        legaler Status vorhanden war, -1 falls nicht
    '''

    state = "-1"
    machineName = configData["ledleuchtturm"]["machine"]["name"]

    # create a pycopg2 cursor
    dbCursor = dbConnection.cursor()

    # execute statement
    try:
        dbCursor.execute("select * from tool;")

    except psycopg2.ProgrammingError as e:
        print "ProgrammingError:\n---"
        print e
        print "---\n"
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

