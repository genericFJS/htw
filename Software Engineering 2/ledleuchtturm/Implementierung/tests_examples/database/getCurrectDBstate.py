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
    print "ProgrammingError"
    quit()

# run a select statement ---
# create a pycopg2 cursor
dbCursor = dbConnection.cursor()

# execute statement
try:
    dbCursor.execute("select * from tool;")

except psycopg2.ProgrammingError as e:
    print "ProgrammingError"
    quit()

# get in the rows
rows = dbCursor.fetchall()

# print all the rows
print "\nShow me the database:\n"
for row in rows:
    if row[0] == machineName and len(row) == 7:
        state = row[6]
        break

if state not in ("IDLE", "PROC", "MAINT", "DOWN"):
    state = "-1"

print "State is: %s" % state

dbCursor.close()
dbConnection.close()
