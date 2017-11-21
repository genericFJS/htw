echo "Nur ausführen, wenn sich Skript und sql-Dateien in ./ befinden und angepasst wurden!"
echo "plpythonu muss in der Datenbank installiert sein!"
echo "Eingabe Datenbankname: "
read db
sudo -u postgres psql -d $db -a -f machine_send.sql
sudo -u postgres psql -d $db -a -f trigger.sql