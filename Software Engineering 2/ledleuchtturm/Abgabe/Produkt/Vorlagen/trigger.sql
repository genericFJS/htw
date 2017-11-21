-- Ersetze "machine" im Namen des Triggers mit der Bezeichnung der gewünschter Maschine, wie sie in der Datenbank steht (Zeile 4). Beispiel: MET9001_trigger
-- Ersetze "machine" im Namen der Prozedur mit der Bezeichnung der Funktion für die gewünschte Maschine, die in machine_send.sql definiert wurde (Zeile 8). Beispiel: MET9001_send

CREATE TRIGGER machine_trigger
AFTER UPDATE
ON tool
FOR EACH ROW
EXECUTE PROCEDURE machine_send();