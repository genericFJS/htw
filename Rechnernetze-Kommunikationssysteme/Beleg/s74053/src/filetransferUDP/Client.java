package filetransferUDP;

import static java.lang.System.err;
import static java.lang.System.out;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;
import java.nio.ByteBuffer;
import java.util.Arrays;
import java.util.Random;

/**
 * The Client takes a file and transfers it to the server.
 * @author Falk-Jonatan Strube (s74053)
 *
 */
public class Client extends FileTransfer {

	static final String ARGUMENT_MESSAGE = "Arguments: <target address> <port number> <file name> [<packet loss rate> <average packet delay>] [--debug]";

	/**
	 * Executes the client.
	 * @param args command line arguments.
	 */
	public Client(String[] args) {
		parseArguments(args);
		displayArguments();

		initializeUpload();

		startTime = System.nanoTime();
		lastInfo = System.nanoTime();
		printMessage("Starting Upload of " + getByteFileLengthLong() + " Bytes.", 0);
		while (tries < MAX_TRIES) {
			byte[] packetToSend;
			if (sendPrevious) {
				packetToSend = previousPacket;
			} else {
				packetToSend = currentPacket;
			}
			if (sendPacket(packetToSend)) {
				receiveACK();
			}
			if (finished) {
				break;
			}
		}
		if (finished) {
			exitApp("File transfer successfull. Average transfer speed: " + speed + " kByte/s", 0);
		} else {
			if (packedAllBytes) {
				exitApp("File transfer not successfull (either wrong CRC, last ACK got lost or file could not be saved).", 2);
			}
			exitApp("File transfer not successfull.", 2);
		}
	}

	/**
	 * Prepares the first packet and sets the socket up.
	 */
	private void initializeUpload() {
		setByteSessionNumber();
		setByteStartIdentifier();
		setByteFileLength();
		setByteFileNameLength();
		setByteFileName();
		setClientFile(filePath);

		currentPacket = createFirstPacket();
		previousPacket = currentPacket.clone();

		try {
			dataSocket = new DatagramSocket();
			dataSocket.setSoTimeout(timeout);
			printMessage("Socket opened.", 1);
		} catch (SocketException e) {
			exitApp("Could not open Socket.", -1);
		}
	}

	/**
	 * Sends the packet to the server. If command line arguments are set, it may delay or lose the packet.
	 * @param packet the packet to be send.
	 * @return true, if the packet has been send, else false.
	 */
	private boolean sendPacket(byte[] packet) {
		dataPacket = new DatagramPacket(packet, packet.length, connectionIP, port);

		try {
			if (packetDelay > 0){
				int sleepTime = (int) (new Random().nextInt(packetDelay * 2));
//				printMessage("Sleep "+sleepTime+"ms",1);
				Thread.sleep(sleepTime);
			}
		} catch (InterruptedException e1) {
			printMessage("Could not wait...", 2);
		}

		if (new Random().nextInt(100) < packetLossRate * 100) {
//			printMessage("Lose packet.",1);
			return true;
		}

		try {
			dataSocket.send(dataPacket);
			printInfo();
//			printMessage("Packet sent: "+(short)bytePacketNumber, 1);
			return true;
		} catch (IOException e) {
			printMessage("Startpacket not sent.Try: " + tries, 1);
		}
		return false;
	}

	/**
	 * Tries to receive the acknowledge packet from the server.
	 */
	private void receiveACK() {
		try {
			dataSocket.receive(dataPacket);
			int ackStatus = verifyACK(dataPacket.getData());
			if (ackStatus == 0) {
				tries = 0;
				sendPrevious = false;
				getNextPacket();
			} else if (ackStatus == -1) {
				tries++;
				printMessage("ACK has wrong session number. Try: " + tries, 1);
			} else {
				tries++;
				printMessage("ACK has wrong packet number. Try: " + tries, 1);
				sendPrevious = true;
			}
//			printMessage("ACK received.", 1);
		} catch (IOException e) {
			tries++;
			printMessage("Connection timed out while waiting for ACK. Try: " + tries, 1);
		}
	}

	/**
	 * Loads the next packet to be send to the server.
	 */
	private void getNextPacket() {
		if (packedAllBytes) {
			finished = true;
			return;
		}
		previousPacket = currentPacket.clone();
		toggleBytePacketNumber();
		int fileBufferSize = PACKETDATALENGTH;
		long remainingBytes = getByteFileLengthLong() - bytesProcessed;
		ByteBuffer buffer;
		if (remainingBytes <= PACKETDATALENGTH) {
			fileBufferSize = (int) remainingBytes;
			buffer = ByteBuffer.allocate(3 + fileBufferSize + 4);
		} else {
			buffer = ByteBuffer.allocate(3 + fileBufferSize);
		}
		byte[] dataBytes = Arrays.copyOfRange(byteClientFile, (int) bytesProcessed, (int) bytesProcessed + fileBufferSize);
		buffer.put(byteSessionNumber);
		buffer.put(bytePacketNumber);
		// printMessage("Number of Bytes to Transfer: "+dataBytes.length,1);
		buffer.put(dataBytes);

		ByteBuffer procBuffer;
		procBuffer = ByteBuffer.allocate((int) bytesProcessed + fileBufferSize);
		if (processedBytes != null) {
			procBuffer.put(processedBytes);
		}
		procBuffer.put(dataBytes);
		processedBytes = procBuffer.array();
		if (remainingBytes <= PACKETDATALENGTH) {
			buffer.put(generateCRC(processedBytes));
			packedAllBytes = true;
		}
		currentPacket = buffer.array().clone();
		bytesProcessed += fileBufferSize;
	}

	/**
	 * Prints the secondly progress (and speed) info.
	 */
	private void printInfo() {
		speed = (int) ((float) bytesProcessed / (System.nanoTime() - startTime) * 1000000000.0f/1024);
		if (lastInfo + 250000000 < System.nanoTime()) {
			float percent = (long) ((float) bytesProcessed / getByteFileLengthLong() * 1000.0f) / 10.0f;
			printMessage("Progress: " + percent + "% - Speed: " + speed + " kByte/s", 0);
			lastInfo = System.nanoTime();
		}
	}
	
	/**
	 * Displays the client arguments.
	 */
	private void displayArguments() {
		String printableArguments = "Transfering to:\t" + connectionIP.getHostAddress() + ":" + port + " (" + connectionIP.getHostName() + ")\nFile:\t\t" + filePath;
		String printableLossRateDelayValues = getPrintableLossRateDelayValues();
		String printableDebugStatus = getPrintableDebugStatus();
		if (!printableLossRateDelayValues.isEmpty())
			printableArguments += "\n" + printableLossRateDelayValues;
		if (!printableDebugStatus.isEmpty())
			printableArguments += "\n" + printableDebugStatus;
		out.println(printableArguments);
	}

	/**
	 * Parses the command line arguments.
	 * @param args command line arguments.
	 */
	private void parseArguments(String[] args) {
		if (args.length < 3) {
			out.println(ARGUMENT_MESSAGE);
			exitApp("Error while parsing arguments: Too few Arguments", 1);
		}
		// Assign Server, Port and File
		setConnectionIP(args[0]);
		setPort(Integer.parseInt(args[1]));
		setClientFile(args[2]);
		if (args.length > 3) {
			// Check for debug flag (only even argument-length)
			if (args.length % 2 == 0 && (args[3].contains("--debug") || (args.length > 5 && args[5].contains("--debug")))) {
				setDebug(true);
			} else {
				err.println(ARGUMENT_MESSAGE);
				exitApp("Error while parsing arguments: Searched for --debug, but was not found!", 1);
			}
			// Assign optional Parameters
			if (args.length > 4) {
				setPacketLossRate(Float.parseFloat(args[3]));
				setPacketDelay(Integer.parseInt(args[4]));
			}
		}
	}
	
	/**
	 * Calls Client(args) and thereby starts the client.
	 * @param args command line arguments
	 */
	public static void main(String[] args) {
		new Client(args);
	}
}
