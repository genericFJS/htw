package filetransfer_udp;

import static java.lang.System.err;
import static java.lang.System.out;

import java.net.DatagramPacket;
import java.net.DatagramSocket;

/**
 * @author jonatan
 *
 */
public class FileTransfer {


	int port;
	float packetLossRate = 0;
	int packetDelay = 0;
	boolean debug;
    DatagramSocket clientSocket;
    DatagramPacket sendPacket;
	static final String argumentMessage = "Arguments: <target address> <port number> <file name> [<packet loss rate> <average packet delay>] [--debug]";
	
	void exitApp(String message, int status) {
		String line = "----------------------------------------";
		if (status == 0) {
			out.println(line + "\n" + message);
		} else {
			err.println(line + "\n" + message);
		}
		System.exit(status);
	}
	
	void displayLossRateDelayValues(){
		if(packetDelay > 0 || packetLossRate > 0)
			out.println("Packet Loss:\t" + packetLossRate*100 + "%\nPacket Delay:\t" + packetDelay + "ms");		
	}
	void displayDebugStatus(){
		if(debug)
			out.println("=== DEBUG MODE ON ===");		
	}
}
