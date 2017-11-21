import paho.mqtt.publish as publish
import time

BROKER = "cougcv5yvgvitijp.myfritz.net"
PORT = 1883
PAYLOAD = "Nachricht um "+str(time.strftime("%H:%M:%S", time.localtime()))+" Uhr"

publish.single("FJS/test", PAYLOAD, retain=True, qos = 1, hostname = BROKER, port=PORT)    # qos 1, um verlorenen Paketen vorzubeugen