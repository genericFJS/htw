--==================================================--
-- 3.1
CREATE PROCEDURE Display_MP AS
	SELECT m.Nachname, m.Vorname, p.ProName
	FROM Mitarbeiter m, Projekt p JOIN Zuordnung z ON p.ProNr = z.ProNr
	WHERE z.MitID = m.MitID

EXEC Display_MP

DROP PROCEDURE Display_MP

--==================================================--
-- 3.2
CREATE PROCEDURE Display_MPB(@ProNr int) AS
BEGIN
	SELECT m.Nachname, m.Vorname, m.Beruf, p.ProName
	FROM Mitarbeiter m, Projekt p JOIN Zuordnung z ON p.ProNr = z.ProNr
	WHERE z.MitID = m.MitID AND z.ProNr = @ProNr
END

EXEC Display_MPB 31

DROP PROCEDURE Display_MPB

--==================================================--
-- 3.3
CREATE PROCEDURE NewYear (@years int) AS
BEGIN
	WHILE EXISTS (select MitID from Mita)
	BEGIN
		IF @years < 1
			BREAK
		UPDATE Mita SET Gebdat = DATEADD(YEAR, -1, GebDat)

		DELETE FROM Mita
		WHERE DATEDIFF(yyyy, Gebdat, GETDATE()) >= 60

		SELECT @years = @years - 1

		WAITFOR DELAY '00:00:01';
		SELECT MitID, DATEDIFF(yyyy, Gebdat, GETDATE()) AS MitAlter FROM Mita
	END
END
	
SELECT * INTO Mita FROM Mitarbeiter

EXEC NewYear 5

DROP TABLE Mita

DROP PROCEDURE NewYear

--==================================================--
-- 3.4

-- Cursor-Beispiel:
DECLARE @myID CHAR(3)

DECLARE myCursor CURSOR FOR
	SELECT MitID FROM Mitarbeiter

OPEN myCursor

FETCH myCursor INTO @myID
WHILE @@fetch_status != -1
BEGIN
	print @myID
	FETCH myCursor INTO @myID
END

CLOSE myCursor
DEALLOCATE myCursor

-- a
SELECT * FROM Mitarbeiter

CREATE PROCEDURE myCP (@MitID char(3)) AS
BEGIN
	--DECLARE @MitID CHAR(3) = 102

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
	--PRINT CONVERT(CHAR(10),@myPlanSum) + CONVERT(CHAR(10),@myIstSum) + CONVERT(CHAR(10),@myKulm)

	CLOSE myCursor

	DEALLOCATE myCursor
END

EXEC myCP 102

DROP PROCEDURE myCP

SELECT * From Mitarbeiter