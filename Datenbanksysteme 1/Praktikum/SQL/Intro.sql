CREATE TABLE Kunde (
	id INT PRIMARY KEY,
	name VARCHAR(20) NOT NULL
)	-- einsehbar unter Ordner Tabelle

INSERT INTO Kunde VALUES (123, 'Maier')	-- nur �ber Abfrage einsehbar
INSERT INTO Kunde VALUES (124, 'Mueller')

-- Kommentar Zeile
/*
	Kommentar Block
*/

SELECT * FROM Kunde

DROP TABLE Kunde

-- F5: ausf�hren (alles, oder wenn etwas markiert ist nur dieses)