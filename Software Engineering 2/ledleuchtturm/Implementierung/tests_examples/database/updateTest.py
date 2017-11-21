import psycopg2

dbServer = "localhost"
dbPort = "5432"
dbUser = "se2"
dbPassword = "CandyM4n();"
dbName = "se2"
machineName = "MET9001"
state = "-1"

try:
    dbConnection = psycopg2.connect(host=dbServer, port=dbPort,
    user=dbUser,  password=dbPassword, dbname=dbName, connect_timeout=5)

except psycopg2.OperationalError as e:
    print "ConnectionError"
    quit()

# run a select statement ---
# create a pycopg2 cursor
dbCursor = dbConnection.cursor()

# execute statement
try:
    dbCursor.execute("UPDATE tool SET state = \'IDLE\' WHERE tool = \'MET9001\';")

    dbConnection.commit()

except psycopg2.ProgrammingError as e:
    print "ProgrammingError"
    quit()


dbCursor.close()
dbConnection.close()
