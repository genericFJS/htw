DROP Table Zuordnung
DROP TABLE Mitarbeiter
DROP TABLE Projekt

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
	Plananteil	FLOAT NOT NULL,
	PRIMARY KEY (MitID,ProNr),
	FOREIGN KEY (MitID)	REFERENCES Mitarbeiter,
	FOREIGN KEY (ProNr)	REFERENCES Projekt
)

INSERT INTO Mitarbeiter SELECT * FROM depotN.dbo.quelleMitarbeiter

INSERT INTO Projekt (ProName, ProNr, ProOrt, ProAufwand, ProLeiter) SELECT Proname, ProNr, ProOrt, Aufwand, Leiter FROM depotN.dbo.quelleProjekt

INSERT INTO Zuordnung SELECT * FROM depotN.dbo.quelleZuordnung