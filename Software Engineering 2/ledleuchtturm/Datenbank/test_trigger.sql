-- Create testing table.

CREATE TABLE test(
	header varchar(20)
)

-- Create the function that triggers when a row is inserted into the table.
-- Insert the added machine name to our test table.

CREATE OR REPLACE FUNCTION insert_test() RETURNS trigger AS $func$
	BEGIN
		INSERT INTO test(header) VALUES (NEW.tool);
        RETURN NULL;
    END;
$func$ LANGUAGE plpgsql;

-- Bind the funtion as a trigger to our table.

CREATE TRIGGER test_trigger AFTER INSERT ON state_report
FOR EACH ROW EXECUTE PROCEDURE insert_test();

-- Insert a test row into the state_report table.

INSERT INTO state_report VALUES (CURRENT_TIMESTAMP, 1234, 'TESTTOOL', 'OK', 343)

-- Visual confirmation

SELECT * FROM test
SELECT * FROM state_report

-- Delete the trigger. Only Raphael has the right at the moment?

DROP TRIGGER test_trigger on state_report
 
-- Delete the function. This can be done ourselves.

DROP FUNCTION insert_test()
 
