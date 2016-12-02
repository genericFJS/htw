--==================================================--
-- Teil I

-- Aufgabe I-1 Skalarwertfunktion
CREATE FUNCTION AlterErmitteln(@GebDat date)
RETURNS int
AS
BEGIN
	DECLARE @age int;
	IF ( MONTH(@Gebdat) < MONTH(GETDATE()) OR ( MONTH(@Gebdat) = MONTH(GETDATE()) AND DAY(@Gebdat) <= DAY(GETDATE()) ) )
		SELECT @age = DATEDIFF(yyyy,@Gebdat,GETDATE())
	ELSE 
		SELECT @age = DATEDIFF(yyyy,@Gebdat,GETDATE())-1   
	RETURN @age
END

SELECT Nachname, dbo.AlterErmitteln(Gebdat) AS [Alter]
FROM Mitarbeiter

-- Aufgabe I-2 Tabellenwertfunktion
CREATE FUNCTION Auslastung(@thresh float)
RETURNS @table TABLE(
	MitID char(3),
	Auslastung float)
AS
BEGIN
	INSERT INTO @table
	SELECT MitID, SUM(Istanteil)
	FROM Zuordnung
	GROUP BY MitID
	HAVING SUM(Istanteil) > @thresh
	RETURN
END

SELECT *
FROM dbo.Auslastung(0.8)

--==================================================--
-- Teil II

-- Aufgabe II-1 DEFAULTS
ALTER TABLE Mitarbeiter ADD CONSTRAINT DF_Mitarbeiter_Ort
DEFAULT 'Dresden' FOR Ort

ALTER TABLE Mitarbeiter ADD CONSTRAINT DF_Mitarbeiter_Beruf
DEFAULT 'Dipl.-Ing.' FOR Beruf

INSERT INTO Mitarbeiter VALUES(942, 'Test', 'Torsten', DEFAULT , '01.02.1983', DEFAULT, 'niemals')
SELECT * FROM Mitarbeiter

DELETE Mitarbeiter WHERE MitID=942

-- Aufgabe II-2 CHECK

-- Aufgabe II-2.1
ALTER TABLE Mitarbeiter ADD CONSTRAINT CK_Mitarbeiter_Alter CHECK (dbo.AlterErmitteln(Gebdat)>= 18 AND dbo.AlterErmitteln(Gebdat) <= 60)
ALTER TABLE Mitarbeiter ADD CONSTRAINT CK_Mitarbeiter_ID CHECK (MitID > 99)

INSERT INTO Mitarbeiter VALUES(943, 'Test', 'Torsten', DEFAULT , '01.02.2010', DEFAULT, 'niemals')
INSERT INTO Mitarbeiter VALUES(944, 'Test', 'Torsten', DEFAULT , '01.02.1900', DEFAULT, 'niemals')
INSERT INTO Mitarbeiter VALUES(45, 'Test', 'Torsten', DEFAULT , '01.02.1983', DEFAULT, 'niemals')
INSERT INTO Mitarbeiter VALUES(945, 'Test', 'Torsten', DEFAULT , '01.02.1983', DEFAULT, 'niemals')

DELETE Mitarbeiter WHERE MitID=945

-- Aufgabe II-2.2
ALTER TABLE Zuordnung ADD CONSTRAINT CK_Zuordnung_Ist CHECK (Istanteil <= 1)

INSERT INTO Zuordnung VALUES(210,44,1.1,0.5)
INSERT INTO Zuordnung VALUES(210,44,0.9,0.5)

DELETE Zuordnung WHERE MitID = 210 AND ProNr = 44

--==================================================--
-- Aufgabe III

ALTER TABLE Projekt ADD CONSTRAINT FK_Projekt_Mitarbeiter FOREIGN KEY (Leiter) REFERENCES Mitarbeiter(MitID)


SELECT * FROM Mitarbeiter
SELECT * FROM Projekt

-- h
INSERT INTO Mitarbeiter VALUES(946, 'Test', 'Torsten', DEFAULT , '01.02.1983', DEFAULT, 'niemals')
INSERT INTO Projekt VALUES(98, 'Test-Projekt', 'Dresden', NULL, 9, 946)

UPDATE Mitarbeiter
SET MitID = 947
WHERE MitID = 946
-- funktioniert nicht wegen FK_Projekt_Mitarbeiter

-- i
DELETE Mitarbeiter WHERE MitID = 947
-- es gibt nichts zum löschen

-- j
UPDATE Projekt
SET Leiter = 210
WHERE ProNr = 98

UPDATE Mitarbeiter
SET MitID = 947
WHERE MitID = 946

DELETE Mitarbeiter WHERE MitID = 947
-- funktioniert nun

-- k
INSERT INTO Projekt VALUES(99,'Test-Projekt 2', 'Dresden', NULL, 9,1)
-- funktioniert nicht wegen FK_Projekt_Mitarbeiter

-- l
INSERT INTO Projekt VALUES(99,'Test-Projekt 2', 'Dresden', NULL, 9,NULL)
-- funktioniert

DELETE Projekt WHERE ProNr = 98
DELETE Projekt WHERE ProNr = 99

--==================================================--
-- Aufgabe IV

-- 4 - semantische Integrität

CREATE TRIGGER tZuordnung ON Zuordnung FOR INSERT, UPDATE, DELETE 
AS
	-- 4.1
	IF EXISTS(
		SELECT SUM(Plananteil)
			FROM Zuordnung 
			GROUP BY MitID 
			HAVING SUM(Plananteil)>1
	) BEGIN
		print 'Plananteil darf nicht über 1.0 liegen'
		SELECT MitID, SUM(Plananteil)
			FROM Zuordnung 
			GROUP BY MitID 
			HAVING SUM(Plananteil)>1
		ROLLBACK TRANSACTION
	END
	-- 4.2
	UPDATE Projekt SET Leiter = NULL WHERE ProNr NOT IN(SELECT ProNr FROM Zuordnung) AND Leiter IS NOT NULL
RETURN

DROP TRIGGER tZuordnung

-- m
UPDATE Zuordnung SET Plananteil = Plananteil + 0.3
-- n
UPDATE Zuordnung SET Plananteil = Plananteil + 0.4 WHERE MitID = 105
-- o
DELETE Zuordnung WHERE MitID = 130 AND ProNr = 36
DELETE Zuordnung WHERE MitID = 106 AND ProNr = 36
DELETE Zuordnung WHERE MitID = 107 AND ProNr = 36
-- Wiederherstellen:
INSERT INTO Zuordnung VALUES(130,36,0.3,0.4)
INSERT INTO Zuordnung VALUES(106,36,0.1,0.1)
INSERT INTO Zuordnung VALUES(107,36,0.5,0.5)
-- p 
UPDATE Zuordnung SET ProNr = 35 WHERE ProNr = 37

SELECT * FROM Zuordnung ORDER BY ProNr
SELECT * FROM Projekt

-- 5 - Protokollierung

