package filetransfer_udp;

import static java.lang.System.err;
import static java.lang.System.out;

import java.io.BufferedInputStream;
import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;

/**
 * @author Falk-Jonatan Strube (s74053)
 *
 */
public class Client extends FileTransfer {

	private String server;
	private String filePath;
	private String fileName;
	

	public Client(String[] args) {
		parseArguments(args);
		displayArguments();
		
		//initializeUpload();
		
		while(true){
			
			//sendPackets();
		}
	}

	private void test() throws Exception {
		File f = new File(filePath);
		out.println("Bildpfad: "+f.getAbsolutePath());

		String savePath = getAppLocation();
		out.println("Speicherpfad: "+savePath);

		File f_new = new File(savePath + getNewFileName(filePath));
		out.println("Bild gespeichert unter: "+savePath + getNewFileName(filePath));
		DataInputStream fileStream = new DataInputStream(new BufferedInputStream(new FileInputStream(f)));
		byte[] buffer = new byte[(int) f.length()];
		int read = fileStream.read(buffer);

		f_new.createNewFile();
		FileOutputStream outputStream = new FileOutputStream(f_new);
		outputStream.write(buffer);
		fileStream.close();
	}
	
	private void displayArguments() {
		String printableArguments = "Transfering to:\t" + server + ":" + port + "\nFile:\t\t" + filePath;
		String printableLossRateDelayValues = getPrintableLossRateDelayValues();
		String printableDebugStatus = getPrintableDebugStatus();
		if (!printableLossRateDelayValues.isEmpty())
			printableArguments += "\n"+printableLossRateDelayValues;
		if (!printableDebugStatus.isEmpty())
			printableArguments += "\n"+printableDebugStatus;
		out.println(printableArguments);
	}

	private void parseArguments(String[] args) {
		if (args.length < 3) {
			out.println(argumentMessage);
			exitApp("Error while parsing arguments: Too few Arguments", 1);
		}
		// Assign Server and Port
		setServer(args[0]);
		setPort(Integer.parseInt(args[1]));
		setFileName(args[2]);
		if (args.length > 3) {
			// Check for debug flag
			if (args.length % 2 == 0 && (args[3].contains("--debug") || (args.length > 5 && args[5].contains("--debug")))) {
				setDebug(true);
			} else {
				err.println(argumentMessage);
				exitApp("Error while parsing arguments: Searched for --debug, but was not found!", 1);
			}
			// Assign optional Parameters
			if (args.length > 4) {
				setPacketLossRate(Float.parseFloat(args[3]));
				setPacketDelay(Integer.parseInt(args[4]));
			}
		}
	}

	public static void main(String[] args) {
		new Client(args);
	}

	public String getServer() {
		return server;
	}

	public void setServer(String server) {
		this.server = server;
	}

	public int getPort() {
		return port;
	}

	public void setPort(int port) {
		this.port = port;
	}

	public boolean isDebug() {
		return debug;
	}

	public void setDebug(boolean debug) {
		this.debug = debug;
	}

	public float getPacketLossRate() {
		return packetLossRate;
	}

	public void setPacketLossRate(float packetLossRate) {
		if (packetLossRate < 0)
			this.packetLossRate = 0;
		if (packetLossRate > 1)
			this.packetLossRate = 1;
		else
			this.packetLossRate = packetLossRate;
	}

	public int getPacketDelay() {
		return packetDelay;
	}

	public void setPacketDelay(int packetDelay) {
		if (packetDelay < 0)
			this.packetDelay = 0;
		else
			this.packetDelay = packetDelay;
	}

	public String getFileName() {
		return filePath;
	}

	public void setFileName(String fileName) {
		this.filePath = fileName;
	}
}
