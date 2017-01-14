package filetransfer_udp;

import static java.lang.System.err;
import static java.lang.System.out;

import java.io.DataInput;
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
 * @author jonatan
 *
 */
public abstract class FileTransfer {

	int port;
	float packetLossRate = 0;
	int packetDelay = 0;
	DatagramSocket dataSocket;
	DatagramPacket dataPacket;
	InetAddress connectionIP;
	byte[] previousPacket;
	byte[] currentPacket;
	byte[] byteSessionNumber = new byte[2];
	byte bytePacketNumber = (byte) 0;
	byte[] byteStartIdentifier = new byte[5];
	byte[] byteFileLength = new byte[8];
	byte[] byteFileNameLength = new byte[2];
	byte[] byteFileName;
	byte[] byteFirstPacketCRC = new byte[4];
	byte[] byteLastPacketCRC = new byte[4];
	int packetDataLength = 400;
	String fileName;
	// client
	File clientFile;
	String filePath;
	// server
	// other
	boolean debug;
	static final String LINE = "----------------------------------------";

	void exitApp(String message, int status) {
		if (status == 0) {
			out.println(LINE + "\nSTATUS: " + message);
		} else {
			err.println(LINE + "\nERROR:  " + message);
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
			return "=== DEBUG MODE ON ===";
		else
			return "";
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

	public boolean startIdentifierCorrect() {
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
	
	public void resetSession(){
		this.byteSessionNumber = new byte[2];
		this.bytePacketNumber = (byte)0;
		this.byteStartIdentifier = new byte[5];
		this.byteFileLength = new byte[8];
		this.byteFileNameLength = new byte[2];
		this.byteFileName = null;
	}
	
	public void printSessionData(){
		String sessionData = LINE +"\nSession Number: "+getByteSessionNumberShort();
		sessionData +="\nPacket Number: "+getBytePacketNumber();
		sessionData +="\nStart Identifier: "+getByteStartIdentifierString();
		sessionData +="\nFile Length: "+getByteFileLengthLong()+ " Byte";
		sessionData +="\nFile Name Length: "+getByteFileNameLengthShort()+ " Byte";
		sessionData +="\nFile Name: ";
		if (byteFileName != null)
			sessionData +=getByteFileNameString();
		else 
			sessionData +="N/A";
		out.println(sessionData);
	}

	// ================================
	// getter and setter
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

	public String getByteFileNameString(){
		return new String(byteFileName);
	}
	
	public void setByteFileName(byte[] byteFileName) {
		this.byteFileName = byteFileName.clone();
	}
	

	public void setByteFileName() {
		byteFileName = fileName.getBytes(StandardCharsets.UTF_8);
	}

	public byte[] getByteStartIdentifier() {
		return byteStartIdentifier;
	}
	
	public String getByteStartIdentifierString(){
		return new String(byteStartIdentifier);
	}

	public void setByteStartIdentifier(byte[] startIdentifier) {
		this.byteStartIdentifier = startIdentifier.clone();
	}

	public void setByteStartIdentifier() {
		this.byteStartIdentifier = "Start".getBytes(StandardCharsets.US_ASCII);
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

	public short getByteSessionNumberShort(){
		return ByteBuffer.wrap(byteSessionNumber).getShort();
	}

	public void setByteSessionNumber(byte[] sessionNumber) {
		this.byteSessionNumber = sessionNumber.clone();
	}

	public void setByteSessionNumber() {
		this.byteSessionNumber = ByteBuffer.allocate(2).putShort((short) new Random().nextInt(Short.MAX_VALUE+1)).array();
	}

	public byte getBytePacketNumber() {
		return bytePacketNumber;
	}


	public void setBytePacketNumber(byte packetNumber) {
		this.bytePacketNumber = packetNumber;
	}

	public void setBytePacketNumber(int packetNumber) {
		if (packetNumber == 0) {
			setBytePacketNumber((byte) 0);
		} else {
			setBytePacketNumber((byte) 1);
		}
	}

	public byte[] getByteFileLength() {
		return byteFileLength;
	}
	
	public long getByteFileLengthLong(){
		return ByteBuffer.wrap(byteFileLength).getLong();
	}

	public void setByteFileLength(byte[] fileLength) {
		this.byteFileLength = fileLength.clone();
	}

	public void setByteFileLength() {
		this.byteFileLength = ByteBuffer.allocate(8).putLong(clientFile.length()).array();
	}

	public byte[] getByteFileNameLength() {
		return byteFileNameLength;
	}

	public int getByteFileNameLengthShort() {
		return ByteBuffer.wrap(byteFileNameLength).getShort();
	}

	public void setByteFileNameLength(byte[] fileNameLength) {
		this.byteFileNameLength = fileNameLength.clone();
	}

	public void setByteFileNameLength() {
		this.byteFileNameLength = ByteBuffer.allocate(2).putShort((short) fileName.length()).array();
	}

	public File getClientFile() {
		return clientFile;
	}

	public void setClientFile(File file) {
		this.clientFile = file;
	}
	
	public void setClientFile(String filePath){
		setFilePath(filePath);
		this.clientFile = new File(filePath);
	}

	public int getPacketDataLength() {
		return packetDataLength;
	}

	public void setPacketDataLength(int packetDataLength) {
		this.packetDataLength = packetDataLength;
	}

	public InetAddress getConnectionIP() {
		return connectionIP;
	}

	public void setConnectionIP(InetAddress connectionIP) {
		this.connectionIP = connectionIP;
	}

	public void setConnectionIP(String connectionName) {
		try {
			this.connectionIP = InetAddress.getByName(connectionName);
		} catch (UnknownHostException e) {
			e.printStackTrace();
			exitApp("Could not resolve connection name to IP-address.", -1);
		}
	}

	public String getFilePath() {
		return filePath;
	}

	public void setFilePath(String filePath) {
		this.filePath = filePath;
		int fileLoc = filePath.lastIndexOf("/") + 1;
		this.setFileName(filePath.substring(fileLoc));
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
