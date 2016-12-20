CREATE TABLE Test1(
ID int, 
Name varchar2(29)
);

INSERT INTO Test1 VALUES (1, 'Meyer');
INSERT INTO Test1 VALUES (2, 'Lehmann');

SELECT * FROM Test1;

DROP TABLE Test1;