package filetransfer_udp;

import static java.lang.System.err;
import static java.lang.System.out;

import java.io.File;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.URISyntaxException;

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
	
	String getPrintableLossRateDelayValues(){
		if(packetDelay > 0 || packetLossRate > 0)
			return "Packet Loss:\t" + packetLossRate*100 + "%\nPacket Delay:\t" + packetDelay + "ms";	
		else
			return "";
	}
	String getPrintableDebugStatus(){
		if(debug)
			return "=== DEBUG MODE ON ===";		
		else
			return "";
	}
	
	String getAppLocation(){
		String appLocation = "";
		try {
			appLocation = FileTransfer.class.getProtectionDomain().getCodeSource().getLocation().toURI().getSchemeSpecificPart();
			// Location without /bin folder
			appLocation = appLocation.substring(0, appLocation.length() - 4);
		} catch (URISyntaxException e) {
			e.printStackTrace();
		}
		this.getClass();
		return appLocation;
	}
	
	String getNewFileName(String fileName){
		int fileLoc = fileName.lastIndexOf("/")+1;
		int extLoc = fileName.lastIndexOf(".");
		return fileName.substring(fileLoc, extLoc) + "1" + fileName.substring(extLoc);
	}
}
