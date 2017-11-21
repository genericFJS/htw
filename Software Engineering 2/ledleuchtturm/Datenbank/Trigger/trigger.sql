-- replace testTrigger with machine_trigger where machine is the name of your machine for example: MET9001_trigger

CREATE TRIGGER testTrigger
AFTER UPDATE
ON tool
FOR EACH ROW
EXECUTE PROCEDURE machine_send();