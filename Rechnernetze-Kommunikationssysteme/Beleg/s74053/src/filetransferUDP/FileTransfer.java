package filetransferUDP;

import static java.lang.System.err;
import static java.lang.System.out;

import java.io.File;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.URISyntaxException;
import java.net.UnknownHostException;
import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;
import java.util.Arrays;
import java.util.Random;
import java.util.zip.CRC32;

/**
 * @author Falk-Jonatan Strube (s74053)
 *
 */
public abstract class FileTransfer {

	// settings
	/**
	 * The port of the server. For the server: After the server is started, this variable is used as the port of the client.
	 */
	int port;
	float packetLossRate = 0;
	int packetDelay = 0;
	static final int PACKETDATALENGTH = 400;
	static final int PACKETLENGTH = PACKETDATALENGTH + 2 + 1 + 4;
	static final int MAX_TRIES = 10;
	static final int TIMEOUT = 1000;
	// globals
	DatagramSocket dataSocket;
	DatagramPacket dataPacket;
	InetAddress connectionIP;
	byte[] previousPacket;
	byte[] currentPacket;
	String fileName;
	int tries = 0;
	int bytesProccessed;
	byte[] processedBytes;
	// packet contents
	byte[] byteSessionNumber = new byte[2];
	/**
	 * The packet number of the current packet (client) or the expected packet (server).
	 */
	byte bytePacketNumber = (byte) 0;
	byte[] byteStartIdentifier = new byte[5];
	byte[] byteFileLength = new byte[8];
	byte[] byteFileNameLength = new byte[2];
	byte[] byteFileName;
	byte[] byteFirstPacketCRC = new byte[4];
	byte[] byteLastPacketCRC = new byte[4];
	// client
	File clientFile;
	String filePath;
	boolean sendPrevious = false;
	// server
	short activeSession = 0;
	byte[] packetData;
	// other
	boolean debug;
	static final String LINE = "----------------------------------------";
	static final String LINED = "========================================";

	void exitApp(String message, int status) {
		if (status == 0) {
			out.println(LINED + "\nSTATUS: " + message);
		} else {
			err.println(LINED + "\nERROR:  " + message);
		}
		System.exit(status);
	}

	String getPrintableLossRateDelayValues() {
		if (packetDelay > 0 || packetLossRate > 0)
			return "Packet Loss:\t" + packetLossRate * 100 + "%\nPacket Delay:\t" + packetDelay + "ms";
		else
			return "";
	}

	String getPrintableDebugStatus() {
		if (debug)
			return "============ DEBUG MODE ON =============";
		else
			return "";
	}

	void printMessage(String message, int type) {
		switch (type) {
		case 1:
			if (debug) {
				out.println("DEBUG:  " + message);
			}
			break;
		case 2:
			err.println("ERROR:  " + message);
			break;
		default:
			out.println("STATUS: " + message);
			break;
		}
	}

	void printMessage(String message) {
		printMessage(message, 0);
	}

	String getAppLocation() {
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

	String getNewFileName(String fileName) {
		int fileLoc = fileName.lastIndexOf("/") + 1;
		int extLoc = fileName.lastIndexOf(".");
		String extension = fileName.substring(extLoc);
		String newFileName = fileName.substring(fileLoc, extLoc);
		File f = new File(getAppLocation() + newFileName + extension);
		while (f.exists()) {
			newFileName += "1";
			f = new File(getAppLocation() + newFileName + extension);
		}
		return newFileName + extension;
	}

	public void flipPacketNumber() {
		if (getBytePacketNumber() == (byte) 0) {
			setBytePacketNumber(1);
		} else {
			setBytePacketNumber(0);
		}
	}

	public boolean isCorrectStartIdentifier() {
		if (Arrays.equals("Start".getBytes(StandardCharsets.US_ASCII), byteStartIdentifier)) {
			return true;
		} else {
			return false;
		}
	}

	public byte[] createFirstPacket() {
		int packetLength = 18 + fileName.length();

		ByteBuffer buffer = ByteBuffer.allocate(packetLength);
		buffer.put(byteSessionNumber);
		buffer.put(bytePacketNumber);
		buffer.put(byteStartIdentifier);
		buffer.put(byteFileLength);
		buffer.put(byteFileNameLength);
		buffer.put(byteFileName);

		ByteBuffer packetBuffer = ByteBuffer.allocate(packetLength + 4);
		packetBuffer.put(buffer.array());
		packetBuffer.put(createFirstPacketCRC(buffer.array()));
		return packetBuffer.array();
	}

	public byte[] createFirstPacketCRC(byte[] packetContent) {
		CRC32 crc = new CRC32();
		crc.update(packetContent);
		long checksum = crc.getValue();
		return ByteBuffer.allocate(4).putInt((int) checksum).array();
	}

	public void getFirstPacketContents(byte[] packet) {
		ByteBuffer buffer = ByteBuffer.wrap(packet);
		buffer.get(byteSessionNumber);
		bytePacketNumber = buffer.get();
		buffer.get(byteStartIdentifier);
		buffer.get(byteFileLength);
		buffer.get(byteFileNameLength);

		byteFileName = new byte[getByteFileNameLengthShort()];
		buffer.get(byteFileName);
		buffer.get(byteFirstPacketCRC);
	}

	public void resetSession() {
		this.byteSessionNumber = new byte[2];
		this.bytePacketNumber = (byte) 0;
		this.byteStartIdentifier = new byte[5];
		this.byteFileLength = new byte[8];
		this.byteFileNameLength = new byte[2];
		this.byteFileName = null;
		this.activeSession = 0;
	}

	public void printSessionData() {
		String sessionData = LINE + "\n" + "Session Number: " + getByteSessionNumberShort();
		sessionData += "\nPacket Number: " + getBytePacketNumber();
		sessionData += "\nStart Identifier: " + getByteStartIdentifierString();
		sessionData += "\nFile Length: " + getByteFileLengthLong() + " Byte";
		sessionData += "\nFile Name Length: " + getByteFileNameLengthShort() + " Byte";
		sessionData += "\nFile Name: ";
		if (byteFileName != null)
			sessionData += getByteFileNameString();
		else
			sessionData += "N/A";
		out.println(sessionData + "\n" + LINE);
	}

	public boolean isCorrectPacketNumber(byte sessionNumber) {
		if (sessionNumber == getBytePacketNumber()) {
			return true;
		} else {
			return false;
		}
	}
	
	public boolean isCorrectFirstPacketCRC(byte[] packetContent){
		if (Arrays.equals(createFirstPacketCRC(packetContent),byteFirstPacketCRC)){
			return true;
		}
		return false;
	}

	public int verifyACK(byte[] packet) {
		byte[] packetSession = Arrays.copyOfRange(packet, 0, 2);
		byte packetPacketNumber = packet[2];
		if (!Arrays.equals(packetSession, byteSessionNumber)) {
			printMessage("Wrong session number: " + getByteSessionNumberShort(packetSession), 1);
			return -1;
		} else if (packetPacketNumber != bytePacketNumber) {
			printMessage("Wrong packet number: " + packetPacketNumber, 1);
			return 1;
		}
		return 0;
	}

	// ================================
	// custom getter and setter
	public void setByteFileName() {
		byteFileName = fileName.getBytes(StandardCharsets.UTF_8);
	}

	public void setByteStartIdentifier() {
		this.byteStartIdentifier = "Start".getBytes(StandardCharsets.US_ASCII);
	}

	public short getByteSessionNumberShort() {
		return getByteSessionNumberShort(byteSessionNumber);
	}

	public short getByteSessionNumberShort(byte[] sessionNumber) {
		return ByteBuffer.wrap(sessionNumber).getShort();
	}

	public void setByteSessionNumber() {
		this.byteSessionNumber = ByteBuffer.allocate(2).putShort((short) (new Random().nextInt(Short.MAX_VALUE) + 1)).array();
	}

	public void setBytePacketNumber(int packetNumber) {
		if (packetNumber == 0) {
			setBytePacketNumber((byte) 0);
		} else {
			setBytePacketNumber((byte) 1);
		}
	}

	public long getByteFileLengthLong() {
		return ByteBuffer.wrap(byteFileLength).getLong();
	}

	public void setByteFileLength() {
		this.byteFileLength = ByteBuffer.allocate(8).putLong(clientFile.length()).array();
	}

	public int getByteFileNameLengthShort() {
		return ByteBuffer.wrap(byteFileNameLength).getShort();
	}

	public void setByteFileNameLength() {
		this.byteFileNameLength = ByteBuffer.allocate(2).putShort((short) fileName.length()).array();
	}

	public void setClientFile(String filePath) {
		setFilePath(filePath);
		this.clientFile = new File(filePath);
	}

	public void setConnectionIP(String connectionName) {
		try {
			this.connectionIP = InetAddress.getByName(connectionName);
		} catch (UnknownHostException e) {
			e.printStackTrace();
			exitApp("Could not resolve connection name to IP-address.", -1);
		}
	}

	public void setFilePath(String filePath) {
		this.filePath = filePath;
		int fileLoc = filePath.lastIndexOf("/") + 1;
		this.setFileName(filePath.substring(fileLoc));
	}

	public void setPacketLossRate(float packetLossRate) {
		if (packetLossRate < 0)
			this.packetLossRate = 0;
		if (packetLossRate > 1)
			this.packetLossRate = 1;
		else
			this.packetLossRate = packetLossRate;
	}

	public void setPacketDelay(int packetDelay) {
		if (packetDelay < 0)
			this.packetDelay = 0;
		else
			this.packetDelay = packetDelay;
	}

	// ================================
	// generic getter and setter
	public byte[] getByteFirstPacketCRC() {
		return byteFirstPacketCRC;
	}

	public void setByteFirstPacketCRC(byte[] byteFirstPacketCRC) {
		this.byteFirstPacketCRC = byteFirstPacketCRC.clone();
	}

	public byte[] getByteLastPacketCRC() {
		return byteLastPacketCRC;
	}

	public void setByteLastPacketCRC(byte[] byteLastPacketCRC) {
		this.byteLastPacketCRC = byteLastPacketCRC.clone();
	}

	public byte[] getByteFileName() {
		return byteFileName;
	}

	public String getByteFileNameString() {
		return new String(byteFileName);
	}

	public void setByteFileName(byte[] byteFileName) {
		this.byteFileName = byteFileName.clone();
	}

	public byte[] getByteStartIdentifier() {
		return byteStartIdentifier;
	}

	public String getByteStartIdentifierString() {
		return new String(byteStartIdentifier);
	}

	public void setByteStartIdentifier(byte[] startIdentifier) {
		this.byteStartIdentifier = startIdentifier.clone();
	}

	public byte[] getPreviousPacket() {
		return previousPacket;
	}

	public void setPreviousPacket(byte[] previousPacket) {
		this.previousPacket = previousPacket.clone();
	}

	public byte[] getCurrentPacket() {
		return currentPacket;
	}

	public void setCurrentPacket(byte[] currentPacket) {
		this.currentPacket = currentPacket.clone();
	}

	public byte[] getByteSessionNumber() {
		return byteSessionNumber;
	}

	public void setByteSessionNumber(byte[] sessionNumber) {
		this.byteSessionNumber = sessionNumber.clone();
	}

	public byte getBytePacketNumber() {
		return bytePacketNumber;
	}

	public void setBytePacketNumber(byte packetNumber) {
		this.bytePacketNumber = packetNumber;
	}

	public byte[] getByteFileLength() {
		return byteFileLength;
	}

	public void setByteFileLength(byte[] fileLength) {
		this.byteFileLength = fileLength.clone();
	}

	public byte[] getByteFileNameLength() {
		return byteFileNameLength;
	}

	public void setByteFileNameLength(byte[] fileNameLength) {
		this.byteFileNameLength = fileNameLength.clone();
	}

	public File getClientFile() {
		return clientFile;
	}

	public void setClientFile(File file) {
		this.clientFile = file;
	}

	public int getPACKETDATALENGTH() {
		return PACKETDATALENGTH;
	}

	public InetAddress getConnectionIP() {
		return connectionIP;
	}

	public void setConnectionIP(InetAddress connectionIP) {
		this.connectionIP = connectionIP;
	}

	public String getFilePath() {
		return filePath;
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

	public int getPacketDelay() {
		return packetDelay;
	}

	public String getFileName() {
		return fileName;
	}

	private void setFileName(String fileName) {
		this.fileName = fileName;
	}

	public DatagramSocket getDataSocket() {
		return dataSocket;
	}

	public void setDataSocket(DatagramSocket dataSocket) {
		this.dataSocket = dataSocket;
	}

	public DatagramPacket getDataPacket() {
		return dataPacket;
	}

	public void setDataPacket(DatagramPacket dataPacket) {
		this.dataPacket = dataPacket;
	}
}
