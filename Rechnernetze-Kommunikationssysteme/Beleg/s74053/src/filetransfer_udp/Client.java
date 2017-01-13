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
public class Client extends FileTransfer{

	private String server;
	String fileName;

	public Client(String[] args) {
		if (!argumentsParsed(args)) {
			exitApp("Error while parsing arguments.", 1);
		}
		displayArguments();
		try {
			// test();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	private void test() throws Exception {
		File f = new File(fileName);
		out.println(f.getAbsolutePath());

		out.println(f.getParent());
		String savePath = Client.class.getProtectionDomain().getCodeSource().getLocation().toURI().getSchemeSpecificPart();
		savePath = savePath.substring(0, savePath.length() - 4);
		out.println(savePath);

		int extLoc = fileName.lastIndexOf(".");
		int fileLoc = fileName.lastIndexOf("/");
		File f_new = new File(savePath + fileName.substring(fileLoc + 1, extLoc) + "1" + fileName.substring(extLoc));
		out.println(savePath + fileName.substring(fileLoc + 1, extLoc) + "1" + fileName.substring(extLoc));
		DataInputStream fileStream = new DataInputStream(new BufferedInputStream(new FileInputStream(f)));
		byte[] buffer = new byte[(int) f.length()];
		int read = fileStream.read(buffer);

		f_new.createNewFile();
		FileOutputStream outputStream = new FileOutputStream(f_new);
		outputStream.write(buffer);
		fileStream.close();
	}

	private void displayArguments() {
		out.println("Transfering to:\t" + server + ":" + port + "\nFile:\t\t" + fileName);
		displayLossRateDelayValues();
		displayDebugStatus();
	}

	private boolean argumentsParsed(String[] args) {
		if (args.length < 3) {
			out.println(argumentMessage);
			return false;
		}
		// Assign Server and Port
		setServer(args[0]);
		setPort(Integer.parseInt(args[1]));
		setFileName(args[2]);
		if (args.length > 3) {
			// Check for debug flag
			if (args.length % 2 == 0 && (args[3].equals("--debug") || (args.length > 5 && args[5].equals("--debug")))) {
				setDebug(true);
			} else {
				err.println("Searched for --debug, but was not found! Check your arguments.\n" + argumentMessage);
				return false;
			}
			// Assign optional Parameters
			if (args.length > 4) {
				setPacketLossRate(Float.parseFloat(args[3]));
				setPacketDelay(Integer.parseUnsignedInt(args[4]));
			}
		}
		return true;
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
		if (packetLossRate > 1)
			this.packetLossRate = 1;
		else
			this.packetLossRate = packetLossRate;
	}

	public int getPacketDelay() {
		return packetDelay;
	}

	public void setPacketDelay(int packetDelay) {
		this.packetDelay = packetDelay;
	}

	public String getFileName() {
		return fileName;
	}

	public void setFileName(String fileName) {
		this.fileName = fileName;
	}
}
