
/* ------------------
   Client
   usage: java Client [Server hostname] [Server RTSP listening port] [Video file requested]
   ---------------------- */

import java.io.*;
import java.net.*;
import java.util.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.Timer;
import javax.swing.border.EmptyBorder;

public class Client {

	// GUI
	// ----
	JFrame		f								= new JFrame("Client");
	JButton		setupButton			= new JButton("Setup");
	JButton		playButton			= new JButton("Play");
	JButton		pauseButton			= new JButton("Pause");
	JButton		optionsButton		= new JButton("Options");
	JButton		describeButton	= new JButton("Describe");
	JButton		tearButton			= new JButton("Teardown");
	JPanel		mainPanel				= new JPanel();
	JPanel		buttonPanel			= new JPanel();
	JPanel		statsPanel			= new JPanel();
	JLabel		videoLabel			= new JLabel();
	JLabel		packRecStat			= new JLabel();
	JLabel		packLostStat		= new JLabel();
	JLabel		packCorrStat		= new JLabel();
	JLabel		packUncorrStat	= new JLabel();
	JLabel		packNoFECStat		= new JLabel();
	JLabel		currFrameStat		= new JLabel();
	ImageIcon	icon;

	// RTP variables:
	// ----------------
	DatagramPacket	rcvdp;									// UDP packet received from the server
	DatagramSocket	RTPsocket;							// socket to be used to send and receive UDP packets
	static int			RTP_RCV_PORT	= 25000;	// port where the client will receive the RTP packets

	Timer				timer;											// timer used to receive data from the UDP socket
	static int	BUFFER_TIME	= -2000;
	static int	TIMER_STEP	= 20;
	int					timerTime		= BUFFER_TIME;
	byte[]			buf;												// buffer used to store data received from the server
	Random			rand				= new Random();

	// RTSP variables
	// ----------------
	// rtsp states
	final static int	INIT			= 0;
	final static int	READY			= 1;
	final static int	PLAYING		= 2;
	final static int	OPTIONS		= 3;
	final static int	DESCRIBE	= 4;
	static int				state;					// RTSP state == INIT or READY or PLAYING
	static int				stateParallel;	// RTSP state == INIT or READY or PLAYING
	Socket						RTSPsocket;			// socket used to send/receive RTSP messages
	// input and output stream filters
	static BufferedReader	RTSPBufferedReader;
	static BufferedWriter	RTSPBufferedWriter;
	static String					VideoFileName;			// video file to request to the server
	int										RTSPSeqNb	= 0;			// Sequence number of RTSP messages within the session
	int										RTSPid		= 0;			// ID of the RTSP session (given by the RTSP Server)

	final static String CRLF = "\r\n";

	// Statistics
	// --------------------------
	int	packets_received			= 0;
	int	packets_lost					= 0;
	int	packets_corrected			= 0;
	int	packets_uncorrectable	= 0;

	// FEC
	// --------------------------
	FECmanager	fec						= new FECmanager();
	static int	FEC_TYPE			= 127;
	int					currentPacket	= 0;

	// Video constants:
	// ------------------
	static int MJPEG_TYPE = 26; // RTP payload type for MJPEG video

	// --------------------------
	// Constructor
	// --------------------------
	public Client() {

		// build GUI
		// --------------------------

		// Frame
		f.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent e) {
				System.exit(0);
			}
		});

		// Buttons
		buttonPanel.setLayout(new GridLayout(1, 0));
		buttonPanel.add(setupButton);
		buttonPanel.add(playButton);
		buttonPanel.add(pauseButton);
		buttonPanel.add(optionsButton);
		buttonPanel.add(describeButton);
		buttonPanel.add(tearButton);
		setupButton.addActionListener(new setupButtonListener());
		playButton.addActionListener(new playButtonListener());
		pauseButton.addActionListener(new pauseButtonListener());
		optionsButton.addActionListener(new optionsButtonListener());
		describeButton.addActionListener(new describeButtonListener());
		tearButton.addActionListener(new tearButtonListener());

		// Image display label
		videoLabel.setIcon(null);

		// Stats
		packRecStat.setText("Received: " + packets_received);
		packLostStat.setText("Lost: " + packets_received);
		packCorrStat.setText("Corrected: " + packets_received);
		packUncorrStat.setText("Uncorrectable: " + packets_received);
		packNoFECStat.setText("No matching FEC: " + packets_received);
		currFrameStat.setText("Current Frame: " + packets_received);
		statsPanel.setLayout(new GridLayout(0, 1));
		statsPanel.setBorder(new EmptyBorder(10, 10, 10, 10));
		statsPanel.add(packRecStat);
		statsPanel.add(packLostStat);
		statsPanel.add(packCorrStat);
		statsPanel.add(packUncorrStat);
		//statsPanel.add(packNoFECStat);
		statsPanel.add(currFrameStat);

		// frame layout
		mainPanel.setLayout(null);
		mainPanel.add(videoLabel);
		mainPanel.add(buttonPanel);
		mainPanel.add(statsPanel);
		videoLabel.setBounds(0, 0, 380, 280);
		buttonPanel.setBounds(0, 280, 580, 50);
		statsPanel.setBounds(380, 0, 200, 280);

		f.getContentPane().add(mainPanel, BorderLayout.CENTER);
		f.setSize(new Dimension(590, 370));
		f.setVisible(true);
		f.setAlwaysOnTop(true);

		// init timer
		// --------------------------
		timer = new Timer(TIMER_STEP, new timerListener());
		timer.setInitialDelay(0);
		timer.setCoalesce(true);

		// allocate enough memory for the buffer used to receive data from the server
		buf = new byte[15000];
	}

	// ------------------------------------
	// main
	// ------------------------------------
	public static void main(String argv[]) throws Exception {
		// Create a Client object
		Client theClient = new Client();

		// get server RTSP port and IP address from the command line
		// ------------------
		int RTSP_server_port = Integer.parseInt(argv[1]);
		String ServerHost = argv[0];
		InetAddress ServerIPAddr = InetAddress.getByName(ServerHost);

		// get video filename to request:
		VideoFileName = argv[2];

		// Establish a TCP connection with the server to exchange RTSP messages
		// ------------------
		theClient.RTSPsocket = new Socket(ServerIPAddr, RTSP_server_port);

		// Set input and output stream filters:
		RTSPBufferedReader = new BufferedReader(new InputStreamReader(theClient.RTSPsocket.getInputStream()));
		RTSPBufferedWriter = new BufferedWriter(new OutputStreamWriter(theClient.RTSPsocket.getOutputStream()));

		// init RTSP state:
		state = INIT;
	}

	// ------------------------------------
	// Handler for buttons
	// ------------------------------------

	// Handler for Setup button
	// -----------------------
	class setupButtonListener implements ActionListener {
		public void actionPerformed(ActionEvent e) {

			// System.out.println("Setup Button pressed !");

			if (state == INIT) {
				// Init non-blocking RTPsocket that will be used to receive data
				try {
					// construct a new DatagramSocket to receive RTP packets from the server, on port RTP_RCV_PORT
					RTPsocket = new DatagramSocket(RTP_RCV_PORT);
					// set TimeOut value of the socket to 5msec.
					RTPsocket.setSoTimeout(5);
				} catch (SocketException se) {
					System.out.println("Socket exception: " + se);
					System.exit(0);
				}

				// init RTSP sequence number
				RTSPSeqNb = 1;

				// Send SETUP message to the server
				send_RTSP_request("SETUP");

				// Wait for the response
				if (parse_server_response() != 200)
					System.out.println("Invalid Server Response");
				else {
					// change RTSP state and print new state
					state = READY;
					System.out.println("New RTSP state: READY");
				}
			} // else if state != INIT then do nothing
		}
	}

	// Handler for Play button
	// -----------------------
	class playButtonListener implements ActionListener {
		public void actionPerformed(ActionEvent e) {

			// System.out.println("Play Button pressed !");

			if (state == READY) {
				// increase RTSP sequence number
				RTSPSeqNb++;

				// Send PLAY message to the server
				send_RTSP_request("PLAY");

				// Wait for the response
				if (parse_server_response() != 200)
					System.out.println("Invalid Server Response");
				else {
					// change RTSP state and print out new state
					state = PLAYING;
					System.out.println("New RTSP state: PLAYING");

					// start the timer
					timer.start();
				}
			} // else if state != READY then do nothing
		}
	}

	// Handler for Pause button
	// -----------------------
	class pauseButtonListener implements ActionListener {
		public void actionPerformed(ActionEvent e) {

			// System.out.println("Pause Button pressed !");

			if (state == PLAYING) {
				// increase RTSP sequence number
				RTSPSeqNb++;

				// Send PAUSE message to the server
				send_RTSP_request("PAUSE");

				// Wait for the response
				if (parse_server_response() != 200)
					System.out.println("Invalid Server Response");
				else {
					// change RTSP state and print out new state
					state = READY;
					System.out.println("New RTSP state: READY");

					// stop the timer
					timer.stop();
				}
			}
			// else if state != PLAYING then do nothing
		}
	}

	// Handler for Options button
	// -----------------------
	class optionsButtonListener implements ActionListener {
		public void actionPerformed(ActionEvent e) {
			if (state == INIT) {
				// increase RTSP sequence number
				RTSPSeqNb++;

				// Send DESCRIBE message to the server
				send_RTSP_request("OPTIONS");
				state = OPTIONS;

				// Wait for the response
				if (parse_server_response() != 200)
					System.out.println("Invalid Server Response");
			}
		}
	}

	// Handler for Describe button
	// -----------------------
	class describeButtonListener implements ActionListener {
		public void actionPerformed(ActionEvent e) {
			if (state != INIT) {

				// Send PAUSE message to the server
				send_RTSP_request("DESCRIBE");
				stateParallel = DESCRIBE;

				// Wait for the response
				if (parse_server_response() != 200)
					System.out.println("Invalid Server Response");
			}
		}
	}

	// Handler for Teardown button
	// -----------------------
	class tearButtonListener implements ActionListener {
		public void actionPerformed(ActionEvent e) {
			// increase RTSP sequence number
			RTSPSeqNb++;

			// Send TEARDOWN message to the server
			send_RTSP_request("TEARDOWN");

			// Wait for the response
			if (parse_server_response() != 200)
				System.out.println("Invalid Server Response");
			else {
				// change RTSP state and print out new state
				state = INIT;
				System.out.println("New RTSP state: INIT");

				// stop the timer
				timer.stop();

				// exit
				System.exit(0);
			}
		}
	}

	// ------------------------------------
	// Handler for timer
	// ------------------------------------

	class timerListener implements ActionListener {
		public void actionPerformed(ActionEvent e) {
			// Timertaktung
			timerTime += TIMER_STEP;
			// System.out.println("timer: " + timerTime);

			// Construct a DatagramPacket to receive data from the UDP socket
			rcvdp = new DatagramPacket(buf, buf.length);

			try {
				// receive the DP from the socket:
				RTPsocket.receive(rcvdp);

				// create an RTPpacket object from the DP
				RTPpacket rtp_packet = new RTPpacket(rcvdp.getData(), rcvdp.getLength());

				int pType = rtp_packet.getpayloadtype();
				int packetNo = rtp_packet.getsequencenumber();
				// get the payload bitstream from the RTPpacket object
				int payload_length = rtp_packet.getpayload_length();
				byte[] payload = new byte[payload_length];
				rtp_packet.getpayload(payload);
				// media package:
				if (pType != FEC_TYPE) {
					currentPacket = packetNo;
					int timeStamp = rtp_packet.gettimestamp();
					// print important header fields of the RTP packet received:;
					// System.out.println("RTP packet: SeqNum # " + packetNo + " TimeStamp " + timeStamp + " ms");// , of type " + rtp_packet.getpayloadtype());

					// print header bitstream:
					// rtp_packet.printheader();

					bufferImage(payload, timeStamp, packetNo);

					packets_received += 1;
					packets_lost = currentPacket - packets_received;
				} else {
					// fecpackage
					int packetsCorrected = fec.correctPacket(payload, packetNo, rtp_packet.gettimestamp());
					switch (packetsCorrected) {
					case 0:
						// System.out.println("\t\t\tFEC-Paket " + packetNo + " has nothing to correct.");
						break;
					case 1:
						packets_corrected += 1;
						break;
					default:
						//System.out.println("\t\t\tFEC-Paket " + packetNo + " could not correct frame.");
						packets_uncorrectable += packetsCorrected;
						break;
					}
				}
			} catch (InterruptedIOException iioe) {
				// System.out.println("Nothing to read");
			} catch (IOException ioe) {
				System.out.println("Exception caught: " + ioe);
			}

			if (timerTime > 0) {
				// Ausgabe des Bildes:
				if ((timerTime % 40) == 0) {
					// System.out.println("\tShow frame " + timerTime / 40);
					currFrameStat.setText("Current Frame: " + timerTime / 40);
					displayImage(timerTime / 40);
				}
			} else {
				// Zeige Puffer-Fortschritt:
				if ((timerTime % (rand.nextInt(100) + 1)) == 0)
					// if ((timerTime % 10) == 0)
					videoLabel.setText("Buffering: " + (timerTime / 20 + 100) + "%");
				else if (timerTime == BUFFER_TIME + TIMER_STEP)
					videoLabel.setText("Buffering: " + (timerTime / 20 + 100) + "%");
				else if (timerTime == 0 - TIMER_STEP)
					videoLabel.setText("Buffering: 100%");
			}

			if ((timerTime % 1000) == 0) {
				updateStats();
			}

			// hard stop:
			if (timerTime / 40 >= 500) {
				System.out.println("Finished.");
				// increase RTSP sequence number
				RTSPSeqNb++;

				// Send PAUSE message to the server
				send_RTSP_request("PAUSE");

				// Wait for the response
				if (parse_server_response() != 200)
					System.out.println("Invalid Server Response");
				else {
					// change RTSP state and print out new state
					state = READY;
					System.out.println("New RTSP state: READY");

					// stop the timer
					timer.stop();
				}
			}
		}
	}

	private void bufferImage(byte[] payload, int timeStamp, int packetNo) {
		fec.setBufferEntry(payload, timeStamp, packetNo);
	}

	private void displayImage(int packetNo) {
		Mediapacket mediaPacket = fec.getBufferEntry(packetNo);
		if (mediaPacket == null) {
			// System.out.println("\t Frame " + packetNo + " existiert nicht.");
			return;
		}
		if (mediaPacket.timeStamp < (timerTime - 200)) {
			// reset missing packages
			fec.resetPacket(packetNo);
			System.out.println("\t Frame " + packetNo + " nicht korrekt.");
			return;
		}
		// get an Image object from the payload bitstream
		Toolkit toolkit = Toolkit.getDefaultToolkit();
		Image image = toolkit.createImage(mediaPacket.data, 0, mediaPacket.data.length);
		//System.out.println("Frame " + packetNo);
		// display the image as an ImageIcon object
		icon = new ImageIcon(image);
		videoLabel.setIcon(icon);
		fec.resetPacket(packetNo);
	}

	private void updateStats() {
		packRecStat.setText("Received: " + packets_received);
		packLostStat.setText("Lost: " + packets_lost);
		packCorrStat.setText("Corrected: " + packets_corrected);
		packUncorrStat.setText("Uncorrectable: " + packets_uncorrectable);
		packNoFECStat.setText("No matching FEC: " + (packets_lost - (packets_corrected + packets_uncorrectable)));
	}

	// ------------------------------------
	// Parse Server Response
	// ------------------------------------
	private int parse_server_response() {
		int reply_code = 0;
		// System.out.println(" Parsing response.");
		try {
			// parse status line and extract the reply_code:
			String StatusLine = RTSPBufferedReader.readLine();
			// System.out.println("RTSP Client - Received from Server:");
			System.out.println(StatusLine);

			StringTokenizer tokens = new StringTokenizer(StatusLine);
			tokens.nextToken(); // skip over the RTSP version
			reply_code = Integer.parseInt(tokens.nextToken());

			// if reply code is OK get and print the 2 other lines
			if (reply_code == 200) {
				if (stateParallel != DESCRIBE) {
					String SeqNumLine = RTSPBufferedReader.readLine();
					System.out.println(SeqNumLine);

					String SessionLine = RTSPBufferedReader.readLine();
					System.out.println(SessionLine);

					// if state == INIT gets the Session Id from the SessionLine
					if (state != OPTIONS) {
						tokens = new StringTokenizer(SessionLine);
						tokens.nextToken(); // skip over the Session:
						RTSPid = Integer.parseInt(tokens.nextToken());
					} else {
						state = INIT;
					}
				} else { // Describe:
					String contentBaseLine = RTSPBufferedReader.readLine();
					System.out.println(contentBaseLine);
					String contentTypeLine = RTSPBufferedReader.readLine();
					System.out.println(contentTypeLine);
					String contentLengthLine = RTSPBufferedReader.readLine();
					System.out.println(contentLengthLine);
				}
			}
		} catch (Exception ex) {
			System.out.println("Exception caught in parse_server_response: " + ex);
			System.exit(0);
		}
		// System.out.println(" Response parsed.");
		return (reply_code);
	}

	// ------------------------------------
	// Send RTSP Request
	// ------------------------------------

	// .............
	// TO COMPLETE
	// .............

	private void send_RTSP_request(String request_type) {
		try {
			// Use the RTSPBufferedWriter to write to the RTSP socket

			// write the request line:
			RTSPBufferedWriter.write(request_type + " " + VideoFileName + " RTSP/1.0\n");
			// more lines only, when not describe
			if (!request_type.equals("DESCRIBE")) {
				// write the CSeq line:
				RTSPBufferedWriter.write("Cseq: " + RTSPSeqNb + "\n");

				// check if request_type is equal to "SETUP" and in this case write the Transport: line advertising to the server the port used to receive the RTP packets RTP_RCV_PORT
				if (request_type.equals("SETUP")) {
					RTSPBufferedWriter.write("Transport: RTP/UDP; client_port= " + RTP_RCV_PORT + "\n");
				} else if (request_type.equals("OPTIONS")) {
					// nothing to do here...
				} else { // otherwise, write the Session line from the RTSPid field
					RTSPBufferedWriter.write("Session: " + RTSPid + "\n");
				}
			}

			RTSPBufferedWriter.flush();
		} catch (Exception ex) {
			System.out.println("Exception caught: " + ex);
			System.exit(0);
		}
	}

}// end of Class Client
