import time
import unittest
import os
import RPi.GPIO as GPIO
import subprocess
import psycopg2
import signal


def update2updateTest(t):

    #t = 2
    dbServer = "10.42.0.1"
    dbPort = "5432"
    dbUser = "se2"
    dbPassword = "CandyM4n();"
    dbName = "se2"

    dbConnection = psycopg2.connect(host=dbServer, port=dbPort,
        user=dbUser,  password=dbPassword, dbname=dbName, connect_timeout=5)

    port = 16 # PROC
    
    # GPIOs einrichten
    GPIO.setmode(GPIO.BCM)
    GPIO.setwarnings(False)
    GPIO.setup(port, GPIO.OUT)

    # Status X in Datenbank schreiben
    cur1 = dbConnection.cursor()
    cur1.execute("UPDATE tool set state= \'MAINT\' where tool = \'MET9001\';")
    dbConnection.commit()
    cur1.close()

    DEVNULL = open(os.devnull,'wb')
    # leuchtturm Programm extern aufrufen
    args = [ 'python', 'ledleuchtturm.py', 'config.json' ]
    ledleuchtturm = subprocess.Popen(args, stdout=DEVNULL)

    # Status Y in Datenbank schreiben
    cur2 = dbConnection.cursor()
    cur2.execute("UPDATE tool set state= 'PROC' where tool = 'MET9001';")
    dbConnection.commit()
    time.sleep(t)

    if GPIO.input(21) ==  GPIO.HIGH:

        cur2.execute("UPDATE tool set state= 'MAINT' where tool = 'MET9001';")
        dbConnection.commit()
        cur2.close()
    
        time.sleep(1)

        print "Reaction test within",t,"s:",
        if GPIO.input(16) == GPIO.HIGH:
            print "OK"
        else:
            print "Failed"
    else:
        print "Reaction test within",t,"s: Failed"
    
    ledleuchtturm.send_signal(signal.SIGINT)
    
    dbConnection.close()

def oneSecondTest():
    dbServer = "10.42.0.1"
    dbPort = "5432"
    dbUser = "se2"
    dbPassword = "CandyM4n();"
    dbName = "se2"

    dbConnection = psycopg2.connect(host=dbServer, port=dbPort,
        user=dbUser,  password=dbPassword, dbname=dbName, connect_timeout=5)

    port = 21 # PROC
    
    # GPIOs einrichten
    GPIO.setmode(GPIO.BCM)
    GPIO.setwarnings(False)
    GPIO.setup(port, GPIO.OUT)

    # Status X in Datenbank schreiben
    cur1 = dbConnection.cursor()
    cur1.execute("UPDATE tool set state= \'IDLE\' where tool = \'MET9001\';")
    dbConnection.commit()
    cur1.close()

    DEVNULL = open(os.devnull,'wb')
    # leuchtturm Programm extern aufrufen
    args = [ 'python', 'ledleuchtturm.py', 'config.json' ]
    ledleuchtturm = subprocess.Popen(args, stdout=DEVNULL)

    # Zeitstempel A nehmen
    start = time.time()

    # Status Y in Datenbank schreiben
    cur2 = dbConnection.cursor()
    cur2.execute("UPDATE tool set state= 'PROC' where tool = 'MET9001';")
    dbConnection.commit()
    cur2.close()

    # Via GPIO nachschauen ob Status Y anliegt
    while time.time()-start < 1.0:
        if GPIO.input(port) == GPIO.HIGH:
            break
        time.sleep(0.1)

    # Zeitstempel B nehmen
    end = time.time()

    print "Duration: ",end-start,"s"
    print "    Test: ",
    if end-start <= 1.0:
        print "OK"
    else:
	print "Failed"
    ledleuchtturm.send_signal(signal.SIGINT)
    
    dbConnection.close()


if __name__ == '__main__':
    print "Test #1 - Reaction"
    oneSecondTest()

    print "Test #2 - Update to update reaction"
    t = 2
    while t>0:
        update2updateTest(t)
        t -= 0.2
