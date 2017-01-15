package test;

import java.io.BufferedReader;
import java.io.ByteArrayInputStream;
import java.io.InputStreamReader;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketTimeoutException;

@SuppressWarnings({ "resource", "unused" })
public class PingClient {

	private static final double LOSS_RATE = 0.3;
	private static final int AVERAGE_DELAY = 100; // milliseconds
	private static long returnTime;
	private static int returnSeq;

	public static void main(String[] args) throws Exception {
		if (args.length != 2) {
			System.out.println("Required arguments: host port");
			return;
		}
		String host = args[0];
		int port = Integer.parseInt(args[1]);

		DatagramSocket socket = new DatagramSocket();
		socket.setSoTimeout(1000);
		InetAddress serverAddress = InetAddress.getByName(host);
		byte[] sendData = new byte[1024];
		byte[] receiveData = new byte[1024];

		for (int i = 0; i < 10; i++) {
			String clientMess = "PING ";
			Long tstamp = new Long(System.currentTimeMillis());
			clientMess += (new Integer(i).toString()) + " ";
			clientMess += (tstamp.toString() + " \r\n");
			sendData = clientMess.getBytes();
			DatagramPacket sendPacket = new DatagramPacket(sendData, clientMess.length(), serverAddress, port);
			socket.send(sendPacket);

			DatagramPacket request = new DatagramPacket(new byte[1024], 1024);

			try {
				socket.receive(request);
				parseReply(request);

				if (!checkSequence(returnSeq, i)) {
					System.out.print("received out of order packet");
				}
				printData(request);
			} catch (SocketTimeoutException e) {
				System.out.println("Error: recieve timed out");
			}
		}
	}

	private static void printData(DatagramPacket request) throws Exception {
		long currentTime = System.currentTimeMillis();
		long rtt = currentTime - returnTime;
		System.out.println("Received from " + request.getAddress().getHostAddress() + ": " + returnSeq + ":" + returnTime + " elapsed: " + rtt);
	}

	private static boolean checkSequence(int returnSeq, int packetNumber) {
		if (returnSeq != packetNumber)
			return false;
		else
			return true;
	}

	private static void parseReply(DatagramPacket request) throws Exception {
		byte[] buf = request.getData();
		ByteArrayInputStream bais = new ByteArrayInputStream(buf);
		InputStreamReader isr = new InputStreamReader(bais);
		BufferedReader br = new BufferedReader(isr);

		String line = br.readLine();
		String resp[] = line.split(" ");
		System.out.println("sequence = " + resp[1]);
		returnSeq = Integer.parseInt(resp[1]);
		System.out.println("ts = :" + resp[2]);
		returnTime = Long.parseLong(resp[2].trim());
	}
}
