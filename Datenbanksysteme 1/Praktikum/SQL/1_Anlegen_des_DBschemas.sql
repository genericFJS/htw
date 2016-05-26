-- Aufgabe 1.1-1.2
CREATE TABLE Mitarbeiter(
	MitID 		CHAR(3) PRIMARY KEY NOT NULL,
	Nachname	VARCHAR(20) NOT NULL,
	Vorname		VARCHAR(20),
	Ort			VARCHAR(30) NOT NULL,
	Gebdat		DATE NOT NULL,
	Beruf		VARCHAR(15) NOT NULL,
	Telnr		VARCHAR(20)
)

CREATE TABLE Projekt(
	ProNr		INT PRIMARY KEY NOT NULL,
	ProName		VARCHAR(20) NOT NULL,
	ProOrt		VARCHAR(30) NOT NULL,
	ProBeschreibung	VARCHAR(30),
	ProAufwand	INT NOT NULL,
	ProLeiter	VARCHAR(20)
)

CREATE TABLE Zuordnung(
	MitID 		CHAR(3) NOT NULL,
	ProNr		INT NOT NULL,
	Istanteil	FLOAT NOT NULL,
	PRIMARY KEY (MitID,ProNr),
	FOREIGN KEY (MitID)	REFERENCES Mitarbeiter,
	FOREIGN KEY (ProNr)	REFERENCES Projekt
)

-- Aufgabe 1.3
ALTER TABLE Zuordnung ADD Plananteil FLOAT NOT NULL	-- NOT NULL geht hier nur, weil Tabelle noch keine Einträge hat!

-- Aufgabe 1.4
INSERT INTO Mitarbeiter SELECT * FROM depotN.dbo.quelleMitarbeiter

INSERT INTO Projekt (ProName, ProNr, ProOrt, ProAufwand, ProLeiter) SELECT Proname, ProNr, ProOrt, Aufwand, Leiter FROM depotN.dbo.quelleProjekt

INSERT INTO Zuordnung SELECT * FROM depotN.dbo.quelleZuordnung

SELECT * FROM Mitarbeiter
SELECT * FROM Projekt
SELECT * FROM Zuordnung

-- Aufgabe 1.6
INSERT INTO Mitarbeiter VALUES(200, 'Nachbar', 'Linker', 'Dresden', '12.03.1904', 'Praktikant', NULL)
INSERT INTO Mitarbeiter VALUES(201, 'Nachbar', 'Rechter', 'Dresden', '04.05.1906', 'Praktikant', NULL)

-- Aufgabe 1.7
CREATE UNIQUE INDEX iNameKompl ON Mitarbeiter(Nachname, Vorname)
CREATE INDEX iBeruf ON Mitarbeiter(Beruf)

DROP INDEX Mitarbeiter.iBeruf

-- Aufgabe 1.8
CREATE VIEW vOrtBeruf AS (
	SELECT MitID, Nachname, Vorname, Ort, Beruf
	FROM Mitarbeiter
	WHERE Beruf != 'Vertreter'
)

SELECT * FROM vOrtBeruf

-- Aufgabe 1.9-1.10
CREATE VIEW vPaz AS (
	SELECT m.MitID, m.Nachname, p.Proname, z.Plananteil
	FROM Mitarbeiter m 
		JOIN Zuordnung z 
			ON m.MitID = z.MitID 
		JOIN Projekt p 
			ON z.ProNr = p.ProNr
)

SELECT * FROM vPaz