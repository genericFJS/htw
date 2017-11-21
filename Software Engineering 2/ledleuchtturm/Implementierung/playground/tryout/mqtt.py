import paho.mqtt.client as mqtt
import time

BROKER = "cougcv5yvgvitijp.myfritz.net"
PORT = 1883
TOPIC = "ledleuchtturm/#"

# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))

    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    #client.subscribe("$SYS/#")
    client.subscribe(TOPIC)

# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    print(msg.topic+": "+str(msg.payload))

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect(BROKER, PORT, 60)

#client.publish("FJS/test", "Hallo?")

# Blocking call that processes network traffic, dispatches callbacks and
# handles reconnecting.
# Other loop*() functions are available that give a threaded interface and a
# manual interface.
client.loop_start()

while True:
    #client.publish("FJS/test", "Hallo?")
    #publish.single("FJS/test", "Jemand da?", qos = 1, hostname = Broker)    # qos 1, um verlorenen Paketen vorzubeugen
    time.sleep(2)
    
client.loop_stop()