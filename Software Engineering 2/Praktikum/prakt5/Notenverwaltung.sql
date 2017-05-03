/*   creation script for database Notenverwaltung
**   database scheme version : 
*/

set quoted_identifier on


CREATE TABLE "Bewertung"
(
  "note"                           FLOAT        NULL,
  "matrikelnr"                     CHAR(5)      NOT NULL,
  "fachid"                         CHAR(2)      NOT NULL,
  CONSTRAINT "BEWERTUNG_PKEY" PRIMARY KEY (
    "MATRIKELNR",
    "FACHID"
  )
)
GO

GRANT ALL ON "Bewertung" TO PUBLIC
GO


CREATE TABLE "Fach"
(
  "fachid"                         CHAR(2)      NOT NULL,
  "bezeichnung"                    VARCHAR(50)  NOT NULL,
  CONSTRAINT "FACH_PKEY" PRIMARY KEY (
    "FACHID"
  )
)
GO

GRANT ALL ON "Fach" TO PUBLIC
GO


CREATE TABLE "Student"
(
  "matrikelnr"                     CHAR(5)      NOT NULL,
  "nachname"                       VARCHAR(50)  NOT NULL,
  "vorname"                        VARCHAR(50)  NOT NULL,
  "status"                         VARCHAR(2)   NULL,
  CONSTRAINT "STUDENT_PKEY" PRIMARY KEY (
    "MATRIKELNR"
  )
)
GO

GRANT ALL ON "Student" TO PUBLIC
GO


ALTER TABLE "Bewertung"
  ADD
    FOREIGN KEY (
      "matrikelnr"
    ) REFERENCES "Student"
GO
,
    FOREIGN KEY (
      "fachid"
    ) REFERENCES "Fach"
GO


CREATE INDEX "IDX0" ON "Bewertung" (
  "matrikelnr")

GO

CREATE INDEX "IDX1" ON "Bewertung" (
  "fachid")

GO



