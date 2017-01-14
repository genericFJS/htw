package filetransfer_udp;

import static java.lang.System.err;
import static java.lang.System.out;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStreamReader;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

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

//		try {
//			test();
//		} catch (Exception e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		}
		
		// BufferedReader inFromUser = new BufferedReader(new
		// InputStreamReader(System.in));
		//
		// DatagramSocket clientSocket = new DatagramSocket();
		//
		// InetAddress IPAddress = InetAddress.getByName("localhost");
		//
		// byte[] sendData = new byte[1024];
		// byte[] receiveData = new byte[1024];
		//
		// String sentence = inFromUser.readLine();
		// sendData = sentence.getBytes();
		// DatagramPacket sendPacket = new DatagramPacket(sendData,
		// sendData.length, IPAddress, 9876);
		//
		// clientSocket.send(sendPacket);
		//
		// DatagramPacket receivePacket = new DatagramPacket(receiveData,
		// receiveData.length);
		//
		// clientSocket.receive(receivePacket);
		//
		// String modifiedSentence = new String(receivePacket.getData());
		//
		// System.out.println("FROM SERVER:" + modifiedSentence);
		// clientSocket.close();

		//while (true) {

			// sendPackets();
		//}
		
		test_deux();
	}
	
	private void initializeUpload(){
		
	}	

	private void test() throws Exception {
		File f = new File(filePath);
		out.println("Bildpfad: " + f.getAbsolutePath());

		String savePath = getAppLocation();
		out.println("Speicherpfad: " + savePath);

		File f_new = new File(savePath + getNewFileName(filePath));
		out.println("Bild gespeichert unter: " + savePath + getNewFileName(filePath));
		DataInputStream fileStream = new DataInputStream(new BufferedInputStream(new FileInputStream(f)));
		byte[] buffer = new byte[(int) f.length()];
		int read = fileStream.read(buffer);

		f_new.createNewFile();
		FileOutputStream outputStream = new FileOutputStream(f_new);
		outputStream.write(buffer);
		fileStream.close();
	}
	
	private void test_deux(){
		this.setFilePath("test.jpg");
		this.setByteFileNameLength();
		out.println(fileName.length());
		out.println(this.getByteFileNameLengthShort());
		this.setFilePath("test/test500.jpg");
		this.setByteFileNameLength();
		out.println(fileName.length());
		out.println(this.getByteFileNameLengthShort());
		out.println(filePath);
		out.println(fileName);
	}

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
		// Assign Server and Port
		setConnectionIP(args[0]);
		setPort(Integer.parseInt(args[1]));
		setFilePath(args[2]);
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
