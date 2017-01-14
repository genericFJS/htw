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
	byte[] bytePacketNumber = new byte[1];
	byte[] byteStartIdentifier = new byte[5];
	byte[] byteFileLength = new byte[8];
	byte[] byteFileNameLength = new byte[2];
	byte[] byteFileName;
	int packetDataLength = 400;
	String fileName;
	File file;
	// client
	String filePath;
	// server
	// other
	boolean debug;

	void exitApp(String message, int status) {
		String line = "----------------------------------------";
		if (status == 0) {
			out.println(line + "\n" + message);
		} else {
			err.println(line + "\n" + message);
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
		if (getBytePacketNumberInt() == 0) {
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

	public byte[] getFirstPacket(){
		int packetLength = 18 + fileName.length();
		byte[] packetWithoutCRC = new byte[packetLength];
		byte[] packet = new byte[packetLength+4];
		
		ByteBuffer buffer = ByteBuffer.allocate(packetLength);
		buffer.put(byteSessionNumber);
		buffer.put(bytePacketNumber);
		buffer.put(byteStartIdentifier);
		buffer.put(byteFileLength);
		buffer.put(byteFileNameLength);
		buffer.put(byteFileName);
//		buffer.put(src)
		return packet;
	}
	
    public byte[] getFirstPacketCRC(byte[] packetContent) {
        CRC32 crc = new CRC32();

        crc.update(packetContent);

        long checksum = crc.getValue();
        byte byteChecksum[] = new byte[4];

        for (int i = 0; i < 4; i++) {
            byteChecksum[3-i] = (byte) (checksum >> i*8);
        }     
        
        return byteChecksum;
    }

	// ================================
	// getter and setter

	public byte[] getByteFileName() {
		return byteFileName;
	}

	public void setByteFileName(byte[] byteFileName) {
		this.byteFileName = byteFileName;
	}
	
	public void setByteFileName(){
        byteFileName = fileName.getBytes(StandardCharsets.UTF_8);
	}

	public byte[] getByteStartIdentifier() {
		return byteStartIdentifier;
	}

	public void setByteStartIdentifier(byte[] startIdentifier) {
		this.byteStartIdentifier = startIdentifier;
	}

	public void setByteStartIdentifier() {
		this.byteStartIdentifier = "Start".getBytes(StandardCharsets.US_ASCII);
	}

	public byte[] getPreviousPacket() {
		return previousPacket;
	}

	public void setPreviousPacket(byte[] previousPacket) {
		this.previousPacket = previousPacket;
	}

	public byte[] getCurrentPacket() {
		return currentPacket;
	}

	public void setCurrentPacket(byte[] currentPacket) {
		this.currentPacket = currentPacket;
	}

	public byte[] getByteSessionNumber() {
		return byteSessionNumber;
	}

	public void setByteSessionNumber(byte[] sessionNumber) {
		this.byteSessionNumber = sessionNumber;
	}

	public void setByteSessionNumber() {
		new Random().nextBytes(byteSessionNumber);
	}

	public byte[] getBytePacketNumber() {
		return bytePacketNumber;
	}

	public int getBytePacketNumberInt() {
		return ByteBuffer.wrap(bytePacketNumber).getInt();
	}

	public void setBytePacketNumber(byte[] packetNumber) {
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

	public void setByteFileLength(byte[] fileLength) {
		this.byteFileLength = fileLength;
	}

	public void setByteFileLength() {
		this.byteFileLength = ByteBuffer.allocate(8).putLong(file.length()).array();
	}

	public byte[] getByteFileNameLength() {
		return byteFileNameLength;
	}
	
	public int getByteFileNameLengthShort(){
		return ByteBuffer.wrap(byteFileNameLength).getShort();
	}

	public void setByteFileNameLength(byte[] fileNameLength) {
		this.byteFileNameLength = fileNameLength;
	}

	public void setByteFileNameLength() {
		this.byteFileNameLength = ByteBuffer.allocate(2).putShort((short) fileName.length()).array();
	}
	
	public File getFile() {
		return file;
	}

	public void setFile(File file) {
		this.file = file;
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
