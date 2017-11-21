import psycopg2


dbServer = "localhost"
dbPort = "5432"
dbUser = "se2"
dbPassword = "CandyM4n();"
dbName = "se2"

try:
    dbConnection = psycopg2.connect(host=dbServer, port=dbPort,
    user=dbUser,  password=dbPassword, dbname=dbName, connect_timeout=5)

except psycopg2.OperationalError as e:
    print "operationalError"
    quit()

print "Connected to DB"

dbConnection.close()

if dbConnection.closed != 0:
    print "Connection was closed"
