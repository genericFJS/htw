package filetransferUDP;

import static java.lang.System.err;
import static java.lang.System.out;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;

/**
 * @author Falk-Jonatan Strube (s74053)
 *
 */
public class Client extends FileTransfer {

	static final String ARGUMENT_MESSAGE = "Arguments: <target address> <port number> <file name> [<packet loss rate> <average packet delay>] [--debug]";

	public Client(String[] args) {
		parseArguments(args);
		displayArguments();

		initializeUpload();

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
//			exitApp("packetSent", 0);
		}
	}

	private void initializeUpload() {
		setByteSessionNumber();
		setByteStartIdentifier();
		setByteFileLength();
		setByteFileNameLength();
		setByteFileName();

		currentPacket = createFirstPacket();
		previousPacket = currentPacket.clone();

		try {
			dataSocket = new DatagramSocket();
			dataSocket.setSoTimeout(TIMEOUT);
			printMessage("Socket opened.", 1);
		} catch (SocketException e) {
			exitApp("Could not open Socket.", -1);
		}
	}

	private boolean sendPacket(byte[] packet) {
		dataPacket = new DatagramPacket(packet, packet.length, connectionIP, port);
		try {
			dataSocket.send(dataPacket);
			printMessage("Startpacket sent.", 1);
			return true;
		} catch (IOException e) {
			printMessage("Startpacket not sent.", 1);
		}
		return false;
	}

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
				printMessage("ACK has wrong session number.", 1);
			} else {
				tries++;
				printMessage("ACK has wrong packet number.", 1);
				sendPrevious = true;
			}
		} catch (IOException e) {
			printMessage("Connection timed out while waiting for ACK.", 2);
		}
	}

	private void getNextPacket() {
		previousPacket = currentPacket.clone();
		
	}

	// private void test() throws Exception {
	// File f = new File(filePath);
	// out.println("Bildpfad: " + f.getAbsolutePath());
	//
	// String savePath = getAppLocation();
	// out.println("Speicherpfad: " + savePath);
	//
	// File f_new = new File(savePath + getNewFileName(filePath));
	// out.println("Bild gespeichert unter: " + savePath + getNewFileName(filePath));
	// DataInputStream fileStream = new DataInputStream(new BufferedInputStream(new FileInputStream(f)));
	// byte[] buffer = new byte[(int) f.length()];
	// int read = fileStream.read(buffer);
	//
	// f_new.createNewFile();
	// FileOutputStream outputStream = new FileOutputStream(f_new);
	// outputStream.write(buffer);
	// fileStream.close();
	// }
	//
	// private void test_deux(){
	// ByteBuffer buffer = ByteBuffer.allocate(9);
	// buffer.put("123456789".getBytes(StandardCharsets.US_ASCII));
	// out.println(ByteBuffer.wrap(this.createFirstPacketCRC(buffer.array())).getInt());
	// out.println(this.createFirstPacketCRC(buffer.array()));
	// }

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

	public static void main(String[] args) {
		new Client(args);
	}
}
