-- Aufgabe 2.1

-- a
SELECT *
FROM Mitarbeiter
WHERE Ort='Dresden'

-- b
SELECT *
FROM Mitarbeiter
WHERE Ort!='Dresden'

-- c
SELECT *
FROM Projekt
WHERE Proname LIKE 'R%'

-- d
SELECT *
FROM Mitarbeiter
WHERE Beruf LIKE 'Dipl%' AND Ort='Radebeul'
ORDER BY Nachname

-- e
SELECT *
FROM Zuordnung
WHERE Istanteil>0.7 OR Plananteil>0.7

-- f
SELECT *
FROM Projekt
WHERE ProLeiter IS NULL

-- Aufgabe 2,2

-- a
SELECT COUNT(*) AS MitarbeiterAnz
FROM Mitarbeiter

-- b
SELECT Ort, COUNT(Ort) AS AnzMitarbeiterInOrt
FROM Mitarbeiter
GROUP BY Ort

-- c
SELECT Pronr, SUM(Istanteil) AS GesamtIstanteil
FROM Zuordnung
WHERE Pronr = 31
GROUP BY Pronr

-- d
SELECT MitID, SUM(Plananteil)-SUM(Istanteil) AS DifferenzPlanIst
FROM Zuordnung
GROUP BY MitID

-- e
SELECT MAX(ProAufwand) AS MaxAufwand, SUM(ProAufwand) AS GesamtAufwand, COUNT(*) AS ProjektAnz
FROM Projekt

-- Aufgabe 2.3

-- a
SELECT Nachname, Vorname, DATEDIFF(yyyy, Gebdat, GETDATE()) AS MitAlter
FROM Mitarbeiter

-- b
SELECT *
FROM Mitarbeiter
WHERE DATEDIFF(yyyy,Gebdat,GETDATE()) > 30

-- c
SELECT Nachname, Vorname, Gebdat
FROM Mitarbeiter
WHERE MONTH(Gebdat) = 5

-- d
SELECT Nachname, Vorname, Gebdat
FROM Mitarbeiter
ORDER BY MONTH(Gebdat), DAY(Gebdat)

-- e
SELECT AVG(DATEDIFF(yyyy,Gebdat,GETDATE())) AS Durschnittsalter
FROM Mitarbeiter

-- f
SELECT Ort, AVG(DATEDIFF(yyyy,Gebdat,GETDATE())) AS Durchschnittsalter
FROM Mitarbeiter
GROUP BY Ort

-- Aufgabe 2.4

-- a
SELECT z.MitID, m.Nachname, p.Pronr, z.Istanteil
FROM Mitarbeiter m, Projekt p, Zuordnung z
WHERE z.MitID = m.MitID AND p.Pronr = z.Pronr

SELECT z.MitID, m.Nachname, p.Pronr, z.Istanteil
FROM Mitarbeiter m
JOIN Zuordnung z ON m.MitID = z.MitID
JOIN Projekt p ON p.Pronr = z.Pronr

-- b
SELECT p.ProNr, p.ProName, m.Nachname, m.Vorname, m.Beruf
FROM Mitarbeiter m, Projekt p, Zuordnung z
WHERE m.MitID = z.MitID AND p.Pronr = z.Pronr
ORDER BY p.ProNr

SELECT p.ProNr, p.ProName, m.Nachname, m.Vorname, m.Beruf
FROM Mitarbeiter m
JOIN Zuordnung z ON m.MitID = z.MitID
JOIN Projekt p ON p.Pronr = z.Pronr
ORDER BY p.ProNr

-- c
SELECT m.MitID, m.Nachname, p.ProName, z.Plananteil
FROM Mitarbeiter m, Projekt p, Zuordnung z
WHERE m.MitID = z.MitID AND p.Pronr = z.Pronr AND p.ProName='Reportgenerator'

SELECT p.ProNr, p.ProName, m.Nachname, m.Vorname, m.Beruf
FROM Mitarbeiter m
JOIN Zuordnung z ON m.MitID = z.MitID
JOIN Projekt p ON p.Pronr = z.Pronr
WHERE p.ProName='Reportgenerator'

-- d
SELECT m.MitID, m.Nachname, m.Vorname, p.ProNr, p.ProName, p.ProLeiter
FROM Mitarbeiter m, Projekt p
WHERE m.Nachname = p.ProLeiter

SELECT m.MitID, m.Nachname, m.Vorname, p.ProNr, p.ProName, p.ProLeiter
FROM Mitarbeiter m
JOIN Projekt p ON m.Nachname = p.ProLeiter
-- Erklärung: Projektleiter wird nach Nachname und nicht nach MitID bestimmt, dadurch ist es nicht eindeutig

-- e
SELECT p.*, z.MitID, z.Plananteil
FROM Projekt p
LEFT OUTER JOIN Zuordnung z ON p.ProNr=z.Pronr
ORDER BY p.Pronr

-- alternativ anschaulich:
SELECT p.Pronr, Proname, ProOrt, ProAufwand, ProLeiter, z.MitID, z.Plananteil
FROM Projekt p
INNER JOIN Zuordnung z ON p.Pronr = z.Pronr
UNION
SELECT p.Pronr, Proname, ProOrt, ProAufwand, ProLeiter, '*Keine*', 0.0
FROM Projekt p
WHERE p.Pronr NOT IN (SELECT z.Pronr FROM Zuordnung z)
ORDER BY p.Pronr, z.MitID

-- Aufgabe 2.5