package filetransferUDP;

import static java.lang.System.err;
import static java.lang.System.out;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;
import java.nio.ByteBuffer;
import java.util.Arrays;

/**
 * @author Falk-Jonatan Strube (s74053)
 *
 */
public class Server extends FileTransfer {

	static final String ARGUMENT_MESSAGE = "Arguments: <port number> [<packet loss rate> <average packet delay>] [--debug]";

	public Server(String[] args) {
		parseArguments(args);
		displayArguments();

		initializeDownload();

		while (true) {
			receivePacket();
			proccessPacket();
		}

	}

	private void initializeDownload() {
		try {
			dataSocket = new DatagramSocket(port);
			dataSocket.setSoTimeout(TIMEOUT);
			printMessage("Socket opened.", 1);
		} catch (SocketException e) {
			exitApp("Could not open Socket.", -1);
		}
	}

	/**
	 * Tries to receive a packet. If the receiving process times out and a session was active, delete the session.
	 */
	private void receivePacket() {
		dataPacket = new DatagramPacket(new byte[PACKETLENGTH], PACKETLENGTH);
		packetData = null;

		for (int tryNumber = 1; tryNumber <= MAX_TRIES; tryNumber++) {
			try {
				dataSocket.receive(dataPacket);
				packetData = new byte[dataPacket.getLength()];
				packetData = Arrays.copyOfRange(dataPacket.getData(), 0, packetData.length);
				break;
			} catch (Exception e) {
				if (activeSession != 0 && tryNumber == MAX_TRIES) {
					printMessage("Connection timed out, waiting for new connection.", 1);
					resetSession();
				}
				tryNumber = 1;
				continue;
			}
		}
	}

	/**
	 * Processes the received packet. The packet is either a first packet or a data packet. <br>
	 * If everything went o.k., an ACK is sent. <br>
	 * If the data packet has the wrong packet number, an ACK with the expected packet number is sent.
	 */
	private void proccessPacket() {
		if (activeSession == 0) {
			getFirstPacketContents(packetData);
			if (isCorrectStartIdentifier() && isCorrectPacketNumber(bytePacketNumber) && isCorrectFirstPacketCRC(Arrays.copyOf(packetData, packetData.length-4))) {
				setPort(dataPacket.getPort());
				setConnectionIP(dataPacket.getAddress());
				sendACK((byte) 0);
				setBytePacketNumber(1);
				if (debug) {
					printSessionData();
				}
			} else {
				resetSession();
			}
		} else {
			printMessage("DataPacket");
		}
	}

	private void sendACK(byte packetNumber) {		
        ByteBuffer buffer = ByteBuffer.allocate(3);
        buffer.put(byteSessionNumber);
        buffer.put(packetNumber);
//		printMessage("ACK Session Number: "+getByteSessionNumberShort(),1);
//		printMessage("ACK Packet Number: "+ (short)packetNumber,1);
		dataPacket = new DatagramPacket(buffer.array(), 3, connectionIP, port);
		try {
			dataSocket.send(dataPacket);
			printMessage("ACK send.", 1);
		} catch (IOException e) {
			printMessage("ACK not send", 1);
		}
	}

	private void displayArguments() {
		String printableArguments = "Waiting on port:\t" + port;
		String printableLossRateDelayValues = getPrintableLossRateDelayValues();
		String printableDebugStatus = getPrintableDebugStatus();
		if (!printableLossRateDelayValues.isEmpty())
			printableArguments += "\n" + printableLossRateDelayValues;
		if (!printableDebugStatus.isEmpty())
			printableArguments += "\n" + printableDebugStatus;
		out.println(printableArguments);
	}

	private void parseArguments(String[] args) {
		if (args.length < 1) {
			out.println(ARGUMENT_MESSAGE);
			exitApp("Error while parsing arguments: Too few Arguments", 1);
		}
		// Assign Port
		setPort(Integer.parseInt(args[0]));
		if (args.length > 1) {
			// Check for debug flag (only even argument-length)
			if (args.length % 2 == 0 && (args[1].contains("--debug") || (args.length > 3 && args[3].contains("--debug")))) {
				setDebug(true);
			} else {
				err.println(ARGUMENT_MESSAGE);
				exitApp("Error while parsing arguments: Searched for --debug, but was not found!", 1);
			}
			// Assign optional Parameters
			if (args.length > 2) {
				setPacketLossRate(Float.parseFloat(args[1]));
				setPacketDelay(Integer.parseInt(args[2]));
			}
		}
	}

	public static void main(String[] args) {
		new Server(args);
	}

}
