package filetransferUDP;

import static java.lang.System.err;
import static java.lang.System.out;

import java.io.BufferedInputStream;
import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
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
 * FileTransfer is the base for a Server or Client.
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
	static final int PACKETDATALENGTH = 1400;
	static final int PACKETLENGTH = PACKETDATALENGTH + 2 + 1 + 4;
	static final int MAX_TRIES = 10;
	// globals
	DatagramSocket dataSocket;
	DatagramPacket dataPacket;
	InetAddress connectionIP;
	byte[] previousPacket;
	byte[] currentPacket;
	String fileName;
	int tries = 0;
	long bytesProcessed;
	byte[] processedBytes;
	int timeout = 1000;
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
	long startTime; 
	long lastInfo;
	int speed;
	boolean packedAllBytes = false;
	boolean finished = false;
	File clientFile;
	byte[] byteClientFile;
	String filePath;
	boolean sendPrevious = false;
	// server
	short activeSession = 0;
	byte[] packetData;
	// other
	boolean debug;
	static final String LINE = "----------------------------------------";
	static final String LINED = "========================================";

	/**
	 * Closes the Client/Server.
	 * @param message the message.
	 * @param status 0 for a positive exit status, everything else for errors.
	 */
	void exitApp(String message, int status) {
		if (status == 0) {
			out.println(LINED + "\nSTATUS: " + message);
		} else {
			err.println(LINED + "\nERROR:  " + message);
		}
		System.exit(status);
	}

	/**
	 * Packs the loss rate and delay value into a nice line.
	 * @return Line with packet loss and delay values.
	 */
	String getPrintableLossRateDelayValues() {
		if (packetDelay > 0 || packetLossRate > 0)
			return "Packet Loss:\t" + packetLossRate * 100 + "%\nPacket Delay:\t" + packetDelay + "ms";
		else
			return "";
	}

	/**
	 * Creates a nice line for displaying the debug-status.
	 * @return line with debug information.
	 */
	String getPrintableDebugStatus() {
		if (debug)
			return "============ DEBUG MODE ON =============";
		else
			return "";
	}

	/**
	 * Prints a message to the console.
	 * @param message the message.
	 * @param type 1 is debug (only printed in debug mode), 2 for errors, everything else a status.
	 */
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

	/**
	 * Prints a status message.
	 * @param message the message.
	 */
	void printMessage(String message) {
		printMessage(message, 0);
	}

	/**
	 * Returns the Location where the Client/Server runs (without /bin).
	 * @return location.
	 */
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

	/**
	 * Generates a new file name for saving a downloaded file.
	 * @param fileName the original file name.
	 * @return the file name.
	 */
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

	/**
	 * Flips the packet number between 0 and 1.
	 */
	public void flipPacketNumber() {
		if (getBytePacketNumber() == (byte) 0) {
			setBytePacketNumber(1);
		} else {
			setBytePacketNumber(0);
		}
	}

	/**
	 * Checks, if the start identifier is correct ASCII "Start".
	 * @param startIdentifier the identifier.
	 * @return true, if the identifier is correct.
	 */
	public boolean isCorrectStartIdentifier(byte[] startIdentifier) {
		if (Arrays.equals("Start".getBytes(StandardCharsets.US_ASCII), startIdentifier)) {
			return true;
		} else {
			return false;
		}
	}

	/**
	 * Creates the first packet.
	 * @return the first packet.
	 */
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
		packetBuffer.put(generateCRC(buffer.array()));
		return packetBuffer.array();
	}

	/**
	 * Generates the CRC value of a byte-array.
	 * @param packetContent the byte-array.
	 * @return The CRC of that byte-array.
	 */
	public byte[] generateCRC(byte[] packetContent) {
		CRC32 crc = new CRC32();
		crc.update(packetContent);
		long checksum = crc.getValue();
		return ByteBuffer.allocate(4).putInt((int) checksum).array();
	}

	/**
	 * Parses the first packet and saves its contents.
	 * @param packet the first packet.
	 */
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
		setActiveSession();
	}

	/**
	 * Resets a session.
	 */
	public void resetSession() {
		this.byteSessionNumber = new byte[2];
		this.bytePacketNumber = (byte) 0;
		this.byteStartIdentifier = new byte[5];
		this.byteFileLength = new byte[8];
		this.byteFileNameLength = new byte[2];
		this.byteFileName = null;
		this.activeSession = 0;
		this.bytesProcessed = 0;
		this.processedBytes = null;
	}

	/**
	 * Prints the data of a (new) session.
	 */
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

	/**
	 * Checks, if the packet number is as expected.
	 * @param packetNumber the packet number of the packet to check.
	 * @return true, if it is the correct number.
	 */
	public boolean isCorrectPacketNumber(byte packetNumber) {
		if (packetNumber == getBytePacketNumber()) {
			return true;
		}
		return false;
	}

	/**
	 * Checks, if the session number is as expected.
	 * @param sessionNumber the session number of the packet to check.
	 * @return true, if it is the correct number.
	 */
	public boolean isCorrectSessionNumber(byte[] sessionNumber) {
		if (Arrays.equals(sessionNumber, getByteSessionNumber())){
			return true;
		}
		return false;
	}

	/**
	 * Compares the CRC value of a given byte-array with another CRC value.
	 * @param packetContent the byte-array.
	 * @param crc the CRC number.
	 * @return true, if it is the same CRC number.
	 */
	public boolean isCorrectCRC(byte[] packetContent, byte[] crc) {
		if (Arrays.equals(generateCRC(packetContent), crc)) {
			return true;
		}
		return false;
	}

	/**
	 * Checks, if the acknowledge packet is correct (with the right session and packet number).
	 * @param packet the packet to check.
	 * @return 0 if correct, -1 if the session number is wrong and 1 if the packet number is wrong.
	 */
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

	public void toggleBytePacketNumber() {
		if (bytePacketNumber == (byte) 0) {
			setBytePacketNumber(1);
		} else {
			setBytePacketNumber(0);
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
		try {
			DataInputStream fileStream;
			fileStream = new DataInputStream(new BufferedInputStream(new FileInputStream(clientFile)));
			byteClientFile = new byte[(int) clientFile.length()];
			fileStream.read(byteClientFile);
			fileStream.close();
		} catch (Exception e) {
			exitApp("Could not open File.", -1);
		}
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

	public void setActiveSession() {
		this.activeSession = getByteSessionNumberShort();
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
