import psycopg2
import signal
import sys


def signal_handler(signal, frame):
    print('You pressed Ctrl+C!')

    ret = globalConn.close()
    if globalConn.closed == 0:
        print "conn.close failed"

    sys.exit(0)


# global vars
globalConn = -1

def conn():
    global globalConn
    dbServer = "localhost"
    dbPort = "5432"
    dbUser = "se2"
    dbPassword = "CandyM4n();"
    dbName = "se2"

    try:
        globalConn = psycopg2.connect(host=dbServer, port=dbPort,
        user=dbUser,  password=dbPassword, dbname=dbName, connect_timeout=5)

        dbConnection = globalConn

    except psycopg2.OperationalError as e:
        print "operationalError"
        quit()

    print "connection enabled"
    signal.pause()
    print "\n\nThis will not be executed!\n\n"
    dbConnection.close()

if __name__=="__main__":

    signal.signal(signal.SIGINT, signal_handler)
    print('Press Ctrl+C')
    conn()

