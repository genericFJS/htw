-- replace '192.168.0.100' with the machine actual ip
-- replace 8050 with the port the machine 
-- replace machine with our machine/tool name example: MET9001_send
-- replace MET9001 with the name of your machine
-- important! make sure the language name is excactly the same when you installed it

CREATE OR REPLACE FUNCTION machine_send()  
    RETURNS TRIGGER AS
$BODY$
    import socket
    if TD["new"]["tool"] == "MET9001": 
        try:
            s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            s.connect(('127.0.0.1', 8050)) 
            updated = TD["new"]["tool"] +" "+ TD["new"]["state"]
            s.sendall(updated)
        except:
            pass
    else:
        pass
$BODY$
    LANGUAGE plpython;
