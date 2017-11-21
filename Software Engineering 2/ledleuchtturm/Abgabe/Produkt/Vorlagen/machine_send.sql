-- Ersetze "127.0.0.1" mit der IP des Raspberry Pi, auf dem ledleuchtturm läuft (Zeile 14). Die einfachen Anführungszeichen um die IP nicht löschen!
-- Ersetze "8050" mit dem Port, der in der Konfigurationsdatei des Softwaresystems ledleuchtturm eingerichtet ist (Zeile 14).
-- Ersetze "machine" im Namen der Funktion mit der Bezeichnung der gewünschter Maschine, wie sie in der Datenbank steht (Zeile 7). Beispiel: MET9001_send
-- Ersetze "machine" im Funktionsrumpf mit der Bezeichnung der gewünschter Maschine, wie sie in der Datenbank steht (Zeile 11).
-- WICHTIG: Ersetze "plpythonu", wenn plpython in der Datenbank mit einem anderen Namen eingerichtet wurde (Zeile 22).

CREATE OR REPLACE FUNCTION machine_send()  
    RETURNS TRIGGER AS
$BODY$
    import socket
    if TD["new"]["tool"] == "machine": 
        try:
            s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            s.connect(('127.0.0.1', 8050)) 
            updated = TD["new"]["tool"] +" "+ TD["new"]["state"]
            s.sendall(updated)
        except:
            pass
    else:
        pass
$BODY$
    LANGUAGE plpythonu;