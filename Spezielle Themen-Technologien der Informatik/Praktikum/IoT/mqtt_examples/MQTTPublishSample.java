import java.text.SimpleDateFormat;
import java.util.Date;

import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.eclipse.paho.client.mqttv3.persist.MemoryPersistence;

public class MQTTPublishSample  {

    public static void main(String[] args) {

        String topic        = "htwdd/devices/sensor/a";
        int qos             = 2;
        String broker       = "tcp://localhost:1883";
        
        MemoryPersistence persistence = new MemoryPersistence();

        try {
        	// create client
            MqttClient sampleClient = 
            
            // set connection options and connect
            MqttConnectOptions connOpts = n
            connOpts.
            
            System.out.println("Connecting to broker: "+broker);

            sampleClient.

            System.out.println("Connected");
            
            // prepare and send message
            String content = "My Simple Hello Message" +new SimpleDateFormat("yyyy-MM-dd HH:mm:ss.SSS").format(new Date());
                      System.out.println("Publishing message: "+ content );
            MqttMessage message = new MqttMessage(
            message.setQos
            sampleClient.publish
            System.out.println("Message published");
          
            //cleanup
            sampleClient.disconnect();
            System.out.println("Disconnected");
            System.exit(0);

        } catch(MqttException me) {
            System.out.println("reason "+me.getReasonCode());
            System.out.println("msg "+me.getMessage());
            System.out.println("loc "+me.getLocalizedMessage());
            System.out.println("cause "+me.getCause());
            System.out.println("excep "+me);
            me.printStackTrace();
        }
    }

}