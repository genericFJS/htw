-- needs paho installed
-- change BROKER to broker address
-- change PORT to broker port
-- important! make sure the language name is excactly the same when you installed it

CREATE OR REPLACE FUNCTION machine_send()  
	RETURNS TRIGGER AS
	$BODY$
		import paho.mqtt.publish as publish

		BROKER = "cougcv5yvgvitijp.myfritz.net"
		PORT = 1883
		TOPIC = "ledleuchtturm/"+TD["new"]["tool"]
		PAYLOAD = TD["new"]["state"]

		publish.single(TOPIC, PAYLOAD, retain=True, qos = 1, hostname = BROKER, port=PORT)
	$BODY$
	LANGUAGE plpythonu;
