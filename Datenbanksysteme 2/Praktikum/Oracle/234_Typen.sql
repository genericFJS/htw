--==================================================--
-- Aufgabe 2
-- 2.1
CREATE OR REPLACE TYPE TPreis AS OBJECT(
  Preis Number(10,2),
  MEMBER FUNCTION Netto RETURN NUMBER,
  MEMBER FUNCTION Brutto RETURN NUMBER,
  MEMBER FUNCTION Umrechnung(Faktor number) RETURN NUMBER
);

-- 2.2
CREATE OR REPLACE
TYPE BODY TPREIS AS

  MEMBER FUNCTION Netto RETURN NUMBER AS
  BEGIN
    RETURN Preis;
  END Netto;

  MEMBER FUNCTION Brutto RETURN NUMBER AS
  BEGIN
    RETURN Preis*1.19;
  END Brutto;

  MEMBER FUNCTION Umrechnung(Faktor number) RETURN NUMBER AS
  BEGIN
    RETURN Preis*Faktor;
  END Umrechnung;

END;

-- 2.3
ALTER TABLE Fahrzeug ADD Listenpreis TPreis;

SELECT *
FROM Fahrzeug;

--==================================================--
-- Aufgabe 3
-- 3.1
CREATE OR REPLACE TYPE AnzTueren AS VARRAY(5) OF CHAR(10);

-- 3.2
ALTER TABLE Fahrzeug ADD Tuerzahl AnzTueren;

-- 3.3
INSERT INTO Fahrzeug VALUES(10000,'BMW Z4 Roadstar', 900, TPreis(60000), AnzTueren('3-Türer'));
INSERT INTO Fahrzeug VALUES(10001,'VW Golf GTI', 800, TPreis(25000), AnzTueren('3-Türer','5-Türer'));
INSERT INTO Fahrzeug VALUES(10002,'Audi A3', 850, TPreis(30000), AnzTueren('3-Türer'));

-- 3.4
SELECT Bezeichnung, f.Listenpreis.Brutto()  -- Tabellenalias notwendig!
FROM Fahrzeug f;

-- Bei einer Umrechnung von 1.5 wäre folgender Preis zu zahlen:
SELECT Bezeichnung, f.Listenpreis.Umrechnung(1.5)
FROM Fahrzeug f;

--==================================================--
-- Aufgabe 4
-- 4.1
CREATE OR REPLACE TYPE tPreisentwicklung AS OBJECT(
  PeNr varchar2(10),
  Netto number(10,2),
  Datum Date
);

-- 4.2
CREATE OR REPLACE TYPE ntPreisentwicklung AS TABLE OF tPreisentwicklung;

-- 4.3
ALTER TABLE Bauteil ADD Preis ntPreisentwicklung 
  NESTED TABLE Preis STORE AS PreisentwicklungNT;

INSERT INTO Bauteil VALUES(5000,'Tuer links', 20, 134556, NULL, ntPreisentwicklung());
INSERT INTO TABLE (
  SELECT b.Preis
  FROM Bauteil b
  WHERE b.BtNr = 5000)
  VALUES(7007,900,to_date('12.10.2015','DD.MM.YYYY'));
INSERT INTO Bauteil VALUES(5001,'Spiegel rechts', 10, 588797, NULL, ntPreisentwicklung());
INSERT INTO TABLE (
  SELECT b.Preis
  FROM Bauteil b
  WHERE b.BtNr = 5001)
  VALUES(7008,100,to_date('12.10.2015','DD.MM.YYYY'));
INSERT INTO Bauteil VALUES(5002,'Auspuff', 30, 693253, NULL, ntPreisentwicklung());
INSERT INTO TABLE (
  SELECT b.Preis
  FROM Bauteil b
  WHERE b.BtNr = 5002)
  VALUES(7009,2000,to_date('12.10.2015','DD.MM.YYYY'));
  
 -- 4.4 (angepasstes to_date)
insert into Table (select b.Preis from bauteil b where b.BtNr=5000) values ('7019', 910, to_date('20.10.2013','DD.MM.YYYY'));
insert into bauteil values (5003, 'Tuergriff links', 15, '134556', 5000, ntPreisentwicklung());
insert into Table (select b.Preis from bauteil b where b.BtNr=5003) values ('7010', 20, to_date('12.10.2013','DD.MM.YYYY'));
insert into Table (select b.Preis from bauteil b where b.BtNr=5003) values ('7018', 22, to_date('12.11.2013','DD.MM.YYYY'));
insert into bauteil values (5004, 'Schlossriegel links', 5, '134556', 5000, ntPreisentwicklung());
insert into Table (select b.Preis from bauteil b where b.BtNr=5004) values ('7011', 10, to_date('12.10.2013','DD.MM.YYYY'));
insert into bauteil values (5005, 'Türgummi', 3, '134556', 5000, ntPreisentwicklung());
insert into Table (select b.Preis from bauteil b where b.BtNr=5005) values ('7012', 5, to_date('12.10.2013','DD.MM.YYYY'));
insert into bauteil values (5006, 'Auspuffrohr', 25, '693253', 5002, ntPreisentwicklung());
insert into Table (select b.Preis from bauteil b where b.BtNr=5006) values ('7013', 30, to_date('12.10.2013','DD.MM.YYYY'));
insert into bauteil values (5007, 'Schelle', 5, '693253', 5002, ntPreisentwicklung());
insert into Table (select b.Preis from bauteil b where b.BtNr=5007) values ('7014', 0.5, to_date('12.10.2013','DD.MM.YYYY'));
insert into bauteil values (5008, 'Schraube', 1, '693253', 5007, ntPreisentwicklung());
insert into Table (select b.Preis from bauteil b where b.BtNr=5008) values ('7015', 0.1, to_date('12.10.2013','DD.MM.YYYY'));
insert into bauteil values (5009, 'Spiegelglas', 10, '588797', 5001, ntPreisentwicklung());
insert into Table (select b.Preis from bauteil b where b.BtNr=5009) values ('7016', 2.30, to_date('12.10.2013','DD.MM.YYYY'));
insert into bauteil values (5010, 'Gehäuse', 12, '693253', 5001, ntPreisentwicklung());
insert into Table (select b.Preis from bauteil b where b.BtNr=5010) values ('7017', 6, to_date('12.10.2013','DD.MM.YYYY'));

-- 4.6
SHOW LPAD('Page 1',15,'*.');

SELECT LPAD('',50,' '), h.HSTNAME
FROM Hersteller h;

SELECT last_name, employee_id, manager_id, LEVEL*LPAD
  FROM employees
  START WITH employee_id = 100
  CONNECT BY PRIOR employee_id = manager_id
  ORDER SIBLINGS BY last_name;
