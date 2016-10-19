SELECT * FROM Mitarbeiter
SELECT * FROM Projekt
SELECT * FROM Zuordnung

-- Aufgabe 3.1
INSERT INTO Mitarbeiter VALUES(210, 'Strube', 'Jonatan', 'Dresden', '04.05.1906', 'Student', NULL)

-- Aufgabe 3.2
INSERT INTO Projekt VALUES(46, 'MS-SQL-Prakt', 'Dresden', NULL, 3, 210)

-- Aufgabe 3.3
INSERT INTO Zuordnung VALUES(210,46,0.69,0.69)

-- Aufgabe 3.4
INSERT INTO Zuordnung VALUES(210,43,0.31,0.31)

-- Aufgabe 3.5
INSERT INTO Zuordnung VALUES(106,46,0.0,0.1)

-- Aufgabe 3.6
INSERT INTO Projekt VALUES(47, 'Oracle-Prakt', 'Dresden', NULL, 0, NULL)

-- Aufgabe 4

-- a
CREATE PROCEDURE ProInfo(@ProNr int) AS
BEGIN
	SELECT p.ProNr, p.ProAufwand, m.MitID, m.Nachname, m.Vorname
	FROM Projekt p INNER JOIN Mitarbeiter m ON p.Leiter = m.MitID
	WHERE p.ProNr = @ProNr
END

EXEC ProInfo 46

DROP PROCEDURE ProInfo

-- b

CREATE PROCEDURE ProInfo2(@ProNr int) AS
BEGIN
	--DECLARE @ProNr CHAR(3) = 46

	DECLARE @myID CHAR(15)
	DECLARE @myName CHAR(20)
	DECLARE @myVorname CHAR(20)
	DECLARE @myBeruf CHAR(15)
	DECLARE @myBeschr CHAR(30)
	DECLARE @myPlan FLOAT
	DECLARE @myIst FLOAT
	DECLARE @myDiff FLOAT

	DECLARE myCursor CURSOR FOR
		SELECT m.MitId, m.Nachname, m.Vorname, m.Beruf, p.ProBeschreibung, z.PlanAnteil, z.IstAnteil, z.PlanAnteil - z.IstAnteil AS PIdiff
		FROM (
			SELECT * 
			FROM Mitarbeiter 
			WHERE MitId=@MitID) m
		LEFT JOIN Zuordnung z ON z.MitID = m.MitID
		LEFT JOIN Projekt p ON p.ProNr = z.ProNr

	-- a
	OPEN myCursor

	PRINT '1. Ausgabeteil: Mitarbeiter'

	FETCH myCursor INTO @myID, @myName, @myVorname, @myBeruf, @myBeschr, @myPlan, @myIst, @myDiff
	IF @@fetch_status != -1
	BEGIN
		PRINT @myName + @myVorname + @myBeruf
	END
	ELSE
	BEGIN
		PRINT 'Mitarbeiter ' + @MitID + ' nicht gefunden.'
	END

	CLOSE myCursor

	-- b
	OPEN myCursor
	
	PRINT '2. Ausgabeteil: Projekt(e)'

	FETCH myCursor INTO @myID, @myName, @myVorname, @myBeruf, @myBeschr, @myPlan, @myIst, @myDiff
	WHILE @@fetch_status != -1
	BEGIN
		PRINT ISNULL(@myBeschr,'(keine Beschreibung)') + ' Plan-Anteil: ' + CONVERT(CHAR(10),@myPlan) + ' Ist-Anteil: ' + CONVERT(CHAR(10),@myIst) + ' Differenz: ' + CONVERT(CHAR(10),@myDiff)
		FETCH myCursor INTO @myID, @myName, @myVorname, @myBeruf, @myBeschr, @myPlan, @myIst, @myDiff
	END

	CLOSE myCursor

	-- c
	OPEN myCursor
	
	PRINT '3. Ausgabeteil: Auslastung'

	DECLARE @myPlanSum FLOAT = 0
	DECLARE @myIstSum FLOAT = 0
	DECLARE @myKulm FLOAT = 0

	FETCH myCursor INTO @myID, @myName, @myVorname, @myBeruf, @myBeschr, @myPlan, @myIst, @myDiff
	WHILE @@fetch_status != -1
	BEGIN
		SELECT @myPlanSum = @myPlanSum + @myPlan
		SELECT @myIstSum = @myIstSum + @myIst
		SELECT @myKulm = @myPlanSum - @myIstSum
		FETCH myCursor INTO @myID, @myName, @myVorname, @myBeruf, @myBeschr, @myPlan, @myIst, @myDiff
	END
	IF @myPlanSum > 1
		PRINT 'Mitarbeiter ' + RTRIM(@myName) + ' ist überfordert!'
	ELSE
	BEGIN
		IF @myKulm = 0
			PRINT 'Mitarbeiter ' + RTRIM(@myName) + ' ist optimal ausgelastet.'
		IF @myKulm < 0
			PRINT 'Mitarbeiter ' + RTRIM(@myName) + ' ist überlastet.'
		IF @myKulm > 0
			PRINT 'Mitarbeiter ' + RTRIM(@myName) + ' hat noch Reserven.'
	END

	CLOSE myCursor

	DEALLOCATE myCursor
END

EXEC proInfo2

DROP PROCEDURE proInfo2




