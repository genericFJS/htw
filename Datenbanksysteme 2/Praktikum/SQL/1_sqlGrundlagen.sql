-- Aufgabe 1

SELECT * FROM Mitarbeiter
SELECT * FROM Projekt
SELECT * FROM Zuordnung

--==================================================--
-- Aufgabe 2

-- 1
ALTER TABLE Projekt
ADD Leiter CHAR(3)

-- 2
UPDATE Projekt
SET Leiter = (
	SELECT m.MitID
	FROM Mitarbeiter m
	WHERE m.Nachname = Projekt.ProLeiter)

-- 3
UPDATE Projekt
SET Leiter = 103
WHERE ProLeiter = 'Igel'

-- 4
ALTER TABLE Projekt
DROP COLUMN ProLeiter

SELECT * FROM Mitarbeiter
SELECT * FROM Projekt
SELECT * FROM Zuordnung

--==================================================--
-- Aufgabe 3

-- 1
INSERT INTO Mitarbeiter VALUES(210, 'Strube', 'Jonatan', 'Dresden', '04.05.1906', 'Student', NULL)

-- 2
INSERT INTO Projekt VALUES(46, 'MS-SQL-Prakt', 'Dresden', NULL, 3, 210)

-- 3
INSERT INTO Zuordnung VALUES(210,46,0.69,0.69)

-- 4
INSERT INTO Zuordnung VALUES(210,43,0.31,0.31)

-- 5
INSERT INTO Zuordnung VALUES(106,46,0.0,0.1)

-- 6
INSERT INTO Projekt VALUES(47, 'Oracle-Prakt', 'Dresden', NULL, 0, NULL)

--==================================================--
-- Aufgabe 4

CREATE PROCEDURE ProInfo(@ProNr int) AS
BEGIN
	--DECLARE @ProNr CHAR(3) = 46
	DECLARE @myID CHAR(15)
	DECLARE @myName CHAR(20)
	DECLARE @myVorname CHAR(20)
	DECLARE @myBeruf CHAR(15)
	DECLARE @myPlan FLOAT
	DECLARE @myIst FLOAT
	DECLARE @myDiff FLOAT

	-- a
	SELECT p.ProNr, p.ProAufwand, m.MitID, m.Nachname, m.Vorname
	FROM Projekt p INNER JOIN Mitarbeiter m ON p.Leiter = m.MitID
	WHERE p.ProNr = @ProNr

	-- b
	DECLARE myCursor CURSOR FOR
		SELECT m.MitId, m.Nachname, m.Vorname, m.Beruf, z.PlanAnteil, z.IstAnteil, z.PlanAnteil - z.IstAnteil AS PIdiff
		FROM Mitarbeiter m JOIN Zuordnung z ON z.MitID = m.MitID
		WHERE z.ProNr = @ProNr

	OPEN myCursor
	
	FETCH myCursor INTO @myID, @myName, @myVorname, @myBeruf, @myPlan, @myIst, @myDiff
	WHILE @@fetch_status != -1
	BEGIN
		PRINT @myID + @myName + @myVorname + @myBeruf + CONVERT(CHAR(10),@myPlan) + CONVERT(CHAR(10),@myIst) + CONVERT(CHAR(10),@myDiff)
		FETCH myCursor INTO @myID, @myName, @myVorname, @myBeruf, @myPlan, @myIst, @myDiff	
	END

	CLOSE myCursor

	DEALLOCATE myCursor
END

EXEC proInfo 46

DROP PROCEDURE proInfo

--==================================================--
-- Aufgabe 5

-- 1 implizit
SELECT m.Nachname, m.Vorname, m.Ort, p.ProNr AS Leitet
FROM Mitarbeiter m, Projekt p
WHERE m.MitID = p.Leiter

-- 1 explizit
SELECT m.Nachname, m.Vorname, m.Ort, p.ProNr AS Leitet
FROM Mitarbeiter m 
	JOIN Projekt p ON m.MitID = p.Leiter

-- 2 implizit
SELECT m.MitID, m.Nachname, m.Vorname, m.Ort, m.Gebdat, m.Beruf, m.Telnr, z.ProNr, z.Istanteil
FROM Mitarbeiter m, Zuordnung z
WHERE m.MitID = z.MitID

-- 2 explizit
SELECT m.MitID, m.Nachname, m.Vorname, m.Ort, m.Gebdat, m.Beruf, m.Telnr, z.ProNr, z.Istanteil
FROM Mitarbeiter m 
	JOIN Zuordnung z ON m.MitID = z.MitID

-- 3 implizit
SELECT p.ProNr, p.ProName, p.ProOrt, p.ProBeschreibung, p.ProAufwand, p.Leiter, m.Nachname, m.Vorname, m.Ort, z.Istanteil
FROM Mitarbeiter m, Zuordnung z, Projekt p
WHERE m.MitID = p.Leiter AND p.Leiter = z.MitID AND p.ProNr = z.ProNr AND p.ProAufwand >= 3

-- 3 explizit
SELECT p.ProNr, p.ProName, p.ProOrt, p.ProBeschreibung, p.ProAufwand, p.Leiter, m.Nachname, m.Vorname, m.Ort, z.Istanteil
FROM Projekt p 
	JOIN Mitarbeiter m ON p.Leiter = m.MitID
	JOIN Zuordnung z ON p.Leiter = z.MitID AND p.ProNr = z.ProNr
WHERE p.ProAufwand >=3

-- 4 a
SELECT p.ProNr, p.ProName, SUM(z.Istanteil) AS GesamtIstanteil
FROM Projekt p LEFT JOIN Zuordnung z ON p.ProNr = z.ProNr
GROUP BY p.ProNr, p.ProName

-- 4 b
SELECT p.ProNr, p.ProName, SUM(z.Istanteil) AS GesamtIstanteil
FROM Projekt p JOIN Zuordnung z ON p.ProNr = z.ProNr
GROUP BY p.ProNr, p.ProName
UNION
SELECT p.ProNr, p.ProName, 9000.1
FROM Projekt p
WHERE p.ProNr NOT IN(
	SELECT ProNr
	FROM Zuordnung
	)

-- 5
SELECT m.MitID, m.Nachname, m.Vorname, 1-SUM(z.Plananteil) AS Reserve
FROM Mitarbeiter m LEFT JOIN Zuordnung z ON m.MitID = z.MitID
GROUP BY m.MitID, m.Nachname, m.Vorname



-- für ODBC
SELECT p.ProNr, p.ProName, z.Istanteil, z.Plananteil
FROM Zuordnung z JOIN Projekt p ON p.ProNr = z.ProNr
WHERE z.MitID = 106

UPDATE Mitarbeiter
SET Telnr = 'niemals'
WHERE MitID = '200' OR MitID = '201' OR MitID = '210'