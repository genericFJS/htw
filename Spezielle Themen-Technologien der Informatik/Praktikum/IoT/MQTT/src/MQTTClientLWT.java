import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.MqttCallback;
import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.eclipse.paho.client.mqttv3.MqttTopic;

public class MQTTClientLWT implements MqttCallback {

	private MqttClient myClient;
	private MqttConnectOptions connOpt;

	static final String BROKER_URL = "tcp://iot.eclipse.org:1883";

	/**
	 * 
	 * connectionLost This callback is invoked upon losing the MQTT connection.
	 * 
	 */
	@Override
	public void connectionLost(Throwable t) {
		System.out.println("Connection lost!");
		// code to reconnect to the broker would go here if desired
	}

	/**
	 * 
	 * deliveryComplete This callback is invoked when a message published by
	 * this client is successfully received by the broker.
	 * 
	 */
	public void deliveryComplete(MqttDeliveryToken token) {
		 try {
			System.out.println("Pub complete" + new
			 String(token.getMessage().getPayload()));
		} catch (MqttException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	/**
	 * 
	 * MAIN
	 * 
	 */
	public static void main(String[] args) {
		MQTTClientLWT smc = new MQTTClientLWT();
		smc.runClient();
	}

	/**
	 * 
	 * runClient The main functionality of this simple example. Create a MQTT
	 * client, connect to broker, pub/sub, disconnect.
	 * 
	 */
	public void runClient() {
		// setup MQTT Client
		String clientID = "MySimpleMQTTClient";
		connOpt = new MqttConnectOptions();

		connOpt.setCleanSession(true);
		connOpt.setKeepAliveInterval(30);
		

		// Connect to Broker
		try {
			myClient = new MqttClient(BROKER_URL, clientID);
			myClient.setCallback(this);
			myClient.connect(connOpt);
			
		} catch (MqttException e) {
			e.printStackTrace();
			System.exit(-1);
		}

		System.out.println("Connected to " + BROKER_URL);

		// setup topic filter
		String myTopic = "htwdd/s74053/clienterrors";
		

		// subscribe to topic if subscriber
		try {
			int subQoS = 0;
			myClient.subscribe(myTopic, subQoS);
		} catch (Exception e) {
			e.printStackTrace();
		}

		// disconnect
		try {
			// wait to ensure subscribed messages are delivered
			Thread.sleep(100000);
			myClient.disconnect();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	@Override
	public void deliveryComplete(IMqttDeliveryToken arg0) {
		// TODO Auto-generated method stub

	}

	@Override
	public void messageArrived(String topic, MqttMessage message) throws Exception {
		String theMessage = new String(message.getPayload());
		System.out.println("-------------------------------------------------");
		System.out.println("| Topic:" + topic);
		System.out.println("| Message: " + theMessage);
		System.out.println("| isRetained: "+message.isRetained());
		System.out.println("-------------------------------------------------");
	}
}