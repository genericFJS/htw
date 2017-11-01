import java.io.*;
import java.net.*;

class RTSPvlc {

	public static void main(String argv[]) throws Exception {
		String[] sentences = new String[7];
		String response;

		// BufferedReader inFromUser = new BufferedReader(new InputStreamReader(System.in));
		// sentence = inFromUser.readLine();
		sentences[0] = "OPTIONS * RTSP/1.0\n";
		sentences[1] = "DESCRIBE rtsp://idefix.informatik.htw-dresden.de:5554/mystream RTSP/1.0\n";
		sentences[2] = "SETUP rtsp://idefix.informatik.htw-dresden.de:5554/mystream RTSP/1.0\n";
		sentences[3] = "PLAY rtsp://idefix.informatik.htw-dresden.de:5554/mystream RTSP/1.0\n";
		sentences[4] = "PAUSE rtsp://idefix.informatik.htw-dresden.de:5554/mystream RTSP/1.0\n";
		sentences[5] = "PLAY rtsp://idefix.informatik.htw-dresden.de:5554/mystream RTSP/1.0\n";
		sentences[6] = "TEARDOWN rtsp://idefix.informatik.htw-dresden.de:5554/mystream RTSP/1.0\n";

		Socket clientSocket = new Socket("idefix.informatik.htw-dresden.de", 5554);

		DataOutputStream outToServer = new DataOutputStream(clientSocket.getOutputStream());
		BufferedReader inFromServer = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));

		for (String sentence : sentences) {
			System.out.println("SENDING: \n--------\n" + sentence);
			outToServer.writeBytes(sentence + '\n');

			System.out.println("RECIEVING: \n----------");
			while (((response = inFromServer.readLine()) != null) && (response.length() > 0)) {
				System.out.println(response);
			}
			System.out.println("===========================================================");
		}

		clientSocket.close();

	}
}