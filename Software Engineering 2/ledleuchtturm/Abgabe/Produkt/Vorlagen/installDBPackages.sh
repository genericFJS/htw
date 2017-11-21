echo "Installiere notwendige PostgreSQL Pakete:"
sudo apt-get install postgresql-contrib postgresql-plpython
echo "Eingabe Datenbankname: "
read db
echo "Richte PL/Python als \"plpythonu\" ein:"
sudo -u postgres psql -d $db -a -c "CREATE PROCEDURAL LANGUAGE 'plpythonu' HANDLER plpython_call_handler"
sudo -u postgres psql -d $db -a -c "UPDATE pg_language SET lanpltrusted = true WHERE lanname LIKE 'plpythonu';"