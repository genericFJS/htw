-- 1.1
CREATE TABLE Fahrzeug(
  FzNr NUMBER(5) PRIMARY KEY,
  Bezeichnung VARCHAR2(15) NOT NULL,
  Gewicht FLOAT(10)
);

CREATE TABLE Bauteil(
  BtNr NUMBER(5) PRIMARY KEY,
  Teilename VARCHAR2(20) NOT NULL,
  Einbauzeit NUMBER(5),
  HstNr VARCHAR2(10),
  Baugruppe NUMBER(5),
  FOREIGN KEY (Baugruppe) REFERENCES Bauteil
);

CREATE TABLE Einbau(
  EbNr VARCHAR2(10) PRIMARY KEY,
  BtNr number(5) NOT NULL,
  FzNr number(5) NOT NULL,
  Anzahl number(5),
  FOREIGN KEY (BtNr) REFERENCES Bauteil,
  FOREIGN KEY (FzNr) REFERENCES Fahrzeug ON DELETE CASCADE -- Löschweitergabe
)

DROP TABLE Einbau;

-- 1.2
ALTER TABLE Einbau ADD CONSTRAINT uniqBtFz UNIQUE (BtNr, FzNr);

-- 1.3
CREATE TABLE Hersteller AS(
  SELECT *
  FROM db01.Hersteller
)
SELECT * FROM Hersteller;

-- 1.4
SELECT * FROM all_constraints WHERE owner = 'DB01' AND table_name = 'HERSTELLER';
SELECT * FROM ALL_TAB_COLUMNS WHERE owner = 'DB01' AND table_name = 'HERSTELLER';
SELECT * FROM ALL_CONS_COLUMNS WHERE owner = 'DB01' AND table_name = 'HERSTELLER';

ALTER TABLE Hersteller MODIFY(Kontaktaufnahme DEFAULT sysdate);
ALTER TABLE Hersteller ADD PRIMARY KEY(HstNr);

-- 1.5
INSERT INTO Hersteller VALUES('693253', 'Tower Zwickau', 'Kopernikusstr. 60', '08056', 'Zwickau', DEFAULT);

-- 1.6
SELECT HstName, Plz, Ort
FROM Hersteller
ORDER BY Plz;

-- 1.7
SELECT *
FROM Hersteller
WHERE (sysdate - Kontaktaufnahme) < 5;

-- 1.8
ALTER TABLE Bauteil ADD FOREIGN KEY (HstNr) REFERENCES Hersteller;

