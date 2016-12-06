--==================================================--
-- Aufgabe 1

-- Aufgabe 1-1
BEGIN TRANSACTION
	DELETE Zuordnung
	SELECT * FROM Zuordnung

-- Aufgabe 1-2
ROLLBACK
SELECT * FROM Zuordnung

-- Aufgabe 1-3
-- Sobald 'Transaction' ausgeführt wurde, können alle Befehle die danach ausgeführt werden mit 'Rollback' zurückgesetzt werden

--==================================================--
-- Aufgabe 2

-- Als Nutzer A
sp_who
sp_helpuser s74053	-- Ich
sp_helpuser s74027	-- Pascal
sp_helprotect

DROP USER s74027

-- 2
CREATE USER s74027 
	FOR LOGIN s74027	-- [smb\s74027]
	WITH DEFAULT_SCHEMA = extern

-- 3 
CREATE SCHEMA extern
	authorization s74027

-- 6
GRANT SELECT ON Mitarbeiter TO s74027

-- 8
sp_helpuser
sp_helprotect Mitarbeiter

-- 9
INSERT INTO Mitarbeiter VALUES(543, 'Test', 'Torsten', DEFAULT , '01.02.1983', DEFAULT, 'niemals')

-- 11
-- während B im Holdlock ist (ohne rollbock/commit zu machen) steht der Befehl in Warteschlange

-- 12
INSERT INTO Mitarbeiter VALUES(543, 'Test', 'Torsten', DEFAULT , '01.02.1983', DEFAULT, 'niemals')
DELETE Mitarbeiter WHERE MitID = 543
SELECT * FROM Mitarbeiter

-- 13
GRANT CREATE TABLE TO s74027

-- 15
SELECT * FROM extern.Mitarbeiter

-- 16
SELECT * FROM Mitarbeiter

-- 18
REVOKE SELECT ON Mitarbeiter TO s74027
REVOKE CREATE TABLE TO s74027

-- Als Nutzer B

-- 1+4
USE ii15s74027

-- 5+7
SELECT * FROM Mitarbeiter

-- 9
BEGIN TRANSACTION
	SELECT *
	FROM Mitarbeiter
	WITH (HOLDLOCK)

-- 12
ROLLBACK

-- 14
CREATE TABLE Mitarbeiter(
id int primary key,
name char(20)
)
INSERT INTO Mitarbeiter VALUES (99, 'hallo')
SELECT * FROM Mitarbeiter

-- 17
DROP TABLE Mitarbeiter

USE ii15s74053