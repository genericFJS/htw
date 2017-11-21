import socket

waitForDBupdate(configData):
"""
Verbindet sich über Sockets zum dem in der Konfigurationsdatei
festgelegten Postgresql Server und wartet auf ein
Update der ebenfalls dort festgelegten Maschine, der Status nach diesem Update
wird zurück gegeben

@type: string
@param machineName: Name der Maschine deren Updates ausgewertet
werden sollen
@rtype: string
@return: Status der Maschine machineName bei einem Update
"""

# variables
host = configData["ledleuchtturm"]["database"]["server"]
port = configData["ledleuchtturm"]["database"]["port"]
machineName = configData["ledleuchtturm"]["machine"]["name"]

serversocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
serversocket.bind((host, port))
serversocket.listen(1) # become a server socket, maximum 5 connections
print "opened on port " + port
while True:
    connection, address = serversocket.accept()
    state = connection.recv(64)
    if len(state) > 0:
        print state
        break

    return state
