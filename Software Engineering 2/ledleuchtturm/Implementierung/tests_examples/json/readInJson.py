import json
from sys import argv


def createDefaultConfigFile(jsonContent):
    file = open('configMe.json', 'w')
    file.write(jsonContent)
    file.close()


def printConfigSettings(jsonFileObject):
    print "\nMaschine ---"
    print "     Name: %s" % jsonFileObject["ledleuchtturm"]["maschine"]["name"]
    print "\nDatabase ---"
    print "     Server:     %s" % jsonFileObject["ledleuchtturm"]["database"]["server"]
    print "     Port:       %s" % jsonFileObject["ledleuchtturm"]["database"]["port"]
    print "     Name:       %s" % jsonFileObject["ledleuchtturm"]["database"]["dbname"]
    print "     Username:   %s" % jsonFileObject["ledleuchtturm"]["database"]["username"]
    print "     Password:   %s" % jsonFileObject["ledleuchtturm"]["database"]["password"]
    print "     Table:      %s" % jsonFileObject["ledleuchtturm"]["database"]["table"]
    print "     Column:     %s" % jsonFileObject["ledleuchtturm"]["database"]["column"]
    print "\nHardware ---"
    print "     Pin Green LED:  %d" % jsonFileObject["ledleuchtturm"]["hardware"]["green"]
    print "     Pin Yellow LED: %d" % jsonFileObject["ledleuchtturm"]["hardware"]["yellow"]
    print "     Pin Red LED:    %d" % jsonFileObject["ledleuchtturm"]["hardware"]["red"]

#if __name__ =="__main__":
# alles danach einrücken wie in funktion

# standard structure of a config file
defaultJsonConfig = """
    {
        \"ledleuchtturm\":{

            \"maschine\":{
                \"name\":\"default\"
            },

            \"database\":{
                \"server\":\"default\",
                \"port\":\"default\",
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
jsonObject = {"ledleuchtturm":
        {
            "maschine":
            {
                "name":"default"
            },
            "database":
            {
                "server"
            }
        }
    }

# read in arguments
# len(argv) dann ist klar wie viele argumente da sind
# argparse
try:
    script, configFile = argv
except:
    # create Json standard config file
    createDefaultConfigFile(defaultJsonConfig)
    print """Bitte geben Sie als Argument an das Programm den Namen ihrer
    Konfigurationsdatei an. Falls Sie noch keine Konfigurationsdatei erstellt
    haben koennen sie die Datei configMe.json bearbeiten und diese dann dem
    Programm uebergeben.
    Bsp \"python prog.py configMe.json\"!"""

# load content of a file to a variable
try:
    fileData = open(configFile).read()
except:
    # create Json standard config file
    createDefaultConfigFile(defaultJsonConfig)
    fileData = open('configMe.json').read()

# decode json content into data object
try:
    jsonFileObject = json.loads(fileData)
except:
    print "Bitte geben sie eine gueltige Konfigurationsdatei welche der Json Struktur entspricht an!"
    quit()

# print maschine name
printConfigSettings(jsonFileObject)
