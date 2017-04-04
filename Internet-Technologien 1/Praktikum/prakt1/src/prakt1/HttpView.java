package prakt1;

import java.io.*;
import java.net.*;

import static java.lang.System.err;
import static java.lang.System.out;
class HttpView {
	
	
	public static void main( String args[]) throws Exception {
		String hostname = "";
		int port = 80;
		String path = "";
		if (args.length < 3) {
			err.println("Falsche Parameter");
			System.exit(-1);
		}
		if (args[0].compareToIgnoreCase("wget") != 0){
			err.println("Falsche Parameter (wget): "+args[0]);
			System.exit(-1);
		}
		hostname = args[1];
		port = Integer.parseInt(args[2]);
		if (args.length == 4){
			path = " "+args[3];
		}
		//out.println("Input: "+hostname+path+" "+port );
		Socket httpSocket = new Socket( hostname.toString(), 80);
		// Übergabe von GET/Host
		String request = "GET"+path+" HTTP/1.1\r\nHost: "+hostname+"\r\n\r\n";
		out.print(request);
		DataOutputStream outToServer = new DataOutputStream(httpSocket.getOutputStream());
		outToServer.writeBytes(request);
		// Ausgabe
		BufferedReader br = new BufferedReader(new InputStreamReader(httpSocket.getInputStream()));
		String t;
		Boolean headFinished = false;
		System.out.println("==== HTTP-ANTWORT ====\n");
		while((t = br.readLine()) != null){
			if (t.compareTo("") == 0 && !headFinished){
				headFinished = true;
				System.out.println("\n==== HTTP-DATEN ====\n");
			} else {
				System.out.println(t);
			}
		}
		br.close();
	}
}