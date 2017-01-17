--==================================================--
-- Aufgabe 5
-- 5.1
CREATE OR REPLACE TYPE TAdresse AS OBJECT(
  Strasse VARCHAR2(50),
  Plz VARCHAR2(5),
  Ort VARCHAR2(50)
);

-- 5.2
CREATE TABLE Lieferant(
  LiefNr NUMBER(6) PRIMARY KEY, 
  Name VARCHAR2(20) NOT NULL,
  Adresse TAdresse
);

-- 5.3
CREATE OR REPLACE VIEW Lieferant_OV(LiefNr, Name, Strasse, Plz, Ort) AS
  SELECT l.LiefNr, l.Name, l.Adresse.Strasse, l.Adresse.Plz, l.Adresse.Ort
  FROM Lieferant l;
  
-- 5.4
INSERT INTO Lieferant_OV VALUES(752443, 'Laepple Teublitz', 'Maxstr. 12', '93158', 'Teublitz');
-- geht nicht, weil die Adressdaten in der View nicht insertable bzw. deleteable sind