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
SELECT * INTO Mita FROM Mitarbeiter

CREATE PROCEDURE NewYear AS
BEGIN
	UPDATE Mita SET Gebdat = DATEADD(YEAR, -1, GebDat)

	DELETE FROM Mita
	WHERE DATEDIFF(yyyy, Gebdat, GETDATE()) >= 60
END
	
WHILE EXISTS (select MitID from Mita)
BEGIN
	EXEC NewYear

	WAITFOR DELAY '00:00:01';
	SELECT MitID, DATEDIFF(yyyy, Gebdat, GETDATE()) AS MitAlter FROM Mita
END

DROP TABLE Mita

DROP PROCEDURE NewYear

--==================================================--
-- 3.4

-- Cursor-Beispiel:
DECLARE @myID CHAR(3)

DECLARE myCursor CURSOR FOR
	SELECT MitID FROM Mitarbeiter

OPEN myCursor

WHILE @@fetch_status != -1
BEGIN
	FETCH myCursor INTO @myID
	print @myID
END

CLOSE myCursor
DEALLOCATE myCursor

-- a
CREATE PROCEDURE myCP (@MitID char(3)) AS
BEGIN
	DECLARE @myName CHAR(20)
	DECLARE @myVorname CHAR(20)
	DECLARE @myBeruf CHAR(15)

	DECLARE myCursor CURSOR FOR
		SELECT Nachname, Vorname, Beruf FROM Mitarbeiter

	OPEN myCursor

	WHILE @@fetch_status != -1
	BEGIN
		FETCH myCursor INTO @myName
		print @myName + @myVorname + @myBeruf
	END

	CLOSE myCursor
	DEALLOCATE myCursor
END