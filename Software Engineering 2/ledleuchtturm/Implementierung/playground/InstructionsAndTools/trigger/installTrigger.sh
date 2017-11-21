echo "Nur ausführen, wenn sich Skript und sql-Dateien in ./ befinden!"
echo "plpythonu muss in der Datenbank installiert sein!"
sudo -u postgres psql -d se2 -a -f machine_send.sql
sudo -u postgres psql -d se2 -a -f trigger.sql