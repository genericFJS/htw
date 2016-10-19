-- Aufgabe 1

SELECT * FROM Mitarbeiter
SELECT * FROM Projekt
SELECT * FROM Zuordnung

-- Aufgabe 2.1
ALTER TABLE Projekt
ADD Leiter CHAR(3)

-- Aufgabe 2.2
UPDATE Projekt
SET Leiter = (
	SELECT m.MitID
	FROM Mitarbeiter m
	WHERE m.Nachname = Projekt.ProLeiter)

-- Aufgabe 2.3
UPDATE Projekt
SET Leiter = 103
WHERE ProLeiter = 'Igel'

-- Aufgabe 2.4
ALTER TABLE Projekt
DROP COLUMN ProLeiter