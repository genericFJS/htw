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

--==================================================--
-- Aufgabe 6
-- 6.1
-- Limitierung auf NOT NULL usw.

-- 6.2
CREATE OR REPLACE TRIGGER Lieferant_OV_ins 
  INSTEAD OF INSERT
  ON Lieferant_OV
  FOR EACH ROW
  BEGIN
    IF INSERTING THEN
      INSERT INTO Lieferant 
        VALUES(:NEW.LiefNr, :NEW.Name, TAdresse(:NEW.Strasse, :NEW.Plz, :NEW.Ort));
    END IF;
  END;
/

INSERT INTO Lieferant_OV VALUES(752443, 'Laepple Teublitz', 'Maxstr. 12', '93158', 'Teublitz');

SELECT * FROM Lieferant_OV;

-- 6.3
-- a
CREATE SEQUENCE sq_einbau
  INCREMENT BY 1
  START WITH 2000;

-- b
CREATE OR REPLACE TRIGGER einbauPK
  BEFORE INSERT OR UPDATE ON Einbau
  FOR EACH ROW
  BEGIN
    IF INSERTING THEN
      SELECT 'E' || sq_einbau.NEXTVAL
      INTO :NEW.EbNr FROM dual;
    END IF;
    IF UPDATING THEN
      :NEW.EbNr := :OLD.Ebnr;
    END IF;
  END;
/

-- c
INSERT INTO Einbau VALUES(NULL, 5000, 10000, 1);

SELECT * FROM Einbau;

-- 6.4
CREATE OR REPLACE TRIGGER einbauPK
  BEFORE INSERT OR UPDATE ON Einbau
  FOR EACH ROW
  DECLARE
    exce EXCEPTION;
    cnt INT;
  BEGIN
    IF INSERTING THEN
      SELECT COUNT(*) INTO cnt
      FROM Bauteil b
      WHERE b.BAUGRUPPE IS NULL AND :NEW.Btnr = b.Btnr;
      IF cnt = 0 THEN
        RAISE exce;
      END IF;
      SELECT 'E' || sq_einbau.NEXTVAL
      INTO :NEW.EbNr FROM dual;
    END IF;
    IF UPDATING THEN
      :NEW.EbNr := :OLD.Ebnr;
    END IF;
  EXCEPTION
    WHEN exce THEN
      raise_application_error(-20042, 'Einfügen nicht möglich, da keine Baugruppe.');
  END;
/

-- 6.5
INSERT INTO Einbau VALUES(NULL, 5001, 10001, 1);
INSERT INTO Einbau VALUES(NULL, 5010, 10002, 2);

SELECT * FROM Einbau;

-- 6.6
SELECT * FROM Einbau;
SELECT * FROM Fahrzeug;
DELETE Fahrzeug WHERE FzNr = 10001;
-- mit dem Fahrzeug wurde auch der Eintrag in Einbau gelöscht.

--==================================================--
-- Aufgabe 7
set serveroutput on
-- 7.1
CREATE OR REPLACE PROCEDURE procWeight (limit IN INT)
IS
  CURSOR cur IS
    SELECT FzNr, Bezeichnung, Gewicht 
    FROM Fahrzeug
    WHERE Gewicht <= limit;
  BEGIN
    FOR item IN cur
    LOOP
      DBMS_OUTPUT.PUT_LINE('FzNr:        ' || item.FzNr);
      DBMS_OUTPUT.PUT_LINE('Bezeichnung: ' || item.Bezeichnung);
      DBMS_OUTPUT.PUT_LINE('Gewicht:     ' || item.Gewicht);
      DBMS_OUTPUT.PUT_LINE('----------------------------------------');
    END LOOP;
  END;
/

EXEC procWeight(900);

-- 7.2
-- Skript:
insert into einbau values (1,'5001', '10000', 1);
insert into einbau values (1,'5002', '10000', 2);
insert into einbau values (1,'5000', '10002', 1);
insert into einbau values (1,'5001', '10002', 1);
-- 
CREATE OR REPLACE PROCEDURE readEinbau
IS
  CURSOR cur1 IS
    SELECT DISTINCT Bezeichnung, f.FzNr
    FROM Fahrzeug f JOIN Einbau e ON e.FzNr = f.FzNr;
  CURSOR cur2 IS
    SELECT Teilename, e.FzNr
    FROM Bauteil b JOIN Einbau e ON e.BTNR = b.BTNR;
  BEGIN
    FOR fz IN cur1
    LOOP
      DBMS_OUTPUT.PUT_LINE(fz.Bezeichnung);
      FOR bt IN cur2
      LOOP
        IF bt.FzNr = fz.FzNr THEN
          DBMS_OUTPUT.PUT_LINE('    '||bt.Teilename);
        END IF;
      END LOOP;
    END LOOP;
  END;
/

EXEC readEinbau;



