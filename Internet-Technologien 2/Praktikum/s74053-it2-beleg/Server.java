
/* ------------------
   Server
   usage: java Server [RTSP listening port]
   ---------------------- */

import java.io.*;
import java.net.*;
import java.awt.*;
import java.util.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.Timer;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

@SuppressWarnings("serial")
public class Server extends JFrame implements ActionListener {

	// RTP variables:
	// ----------------
	DatagramSocket	RTPsocket;	// socket to be used to send and receive UDP packets
	DatagramPacket	senddp;			// UDP packet containing the video frames

	InetAddress	ClientIPAddr;				// Client IP address
	int					RTP_dest_port	= 0;	// destination port for RTP packets (given by the RTSP Client)

	// packet loss
	int			packetLoss	= 10;
	Random	rand				= new Random();

	// FEC
	// --------------------------
	int					fecGroupsize	= 5;
	FECmanager	fec;

	// GUI:
	// ----------------
	JFrame	f									= new JFrame("Server");
	JPanel	mainPanel					= new JPanel();
	JLabel	label							= new JLabel("Send frame #        ", JLabel.CENTER);
	JLabel	packetLossLabel		= new JLabel("Packet loss: " + packetLoss + "%", JLabel.CENTER);
	JSlider	packetLossSlider	= new JSlider(JSlider.HORIZONTAL, 0, 100, packetLoss);
	JLabel	fecLabel					= new JLabel("FEC group size: " + fecGroupsize, JLabel.CENTER);
	JSlider	fecSlider					= new JSlider(JSlider.HORIZONTAL, 2, 20, fecGroupsize);

	// Video variables:
	// ----------------
	int					imagenb				= 0;		// image nb of the image currently transmitted
	VideoStream	video;								// VideoStream object used to access video frames
	static int	MJPEG_TYPE		= 26;		// RTP payload type for MJPEG video
	static int	FEC_TYPE			= 127;
	static int	FRAME_PERIOD	= 40;		// Frame period of the video to stream, in ms
	static int	VIDEO_LENGTH	= 500;	// length of the video in frames

	Timer		timer;		// timer used to send the images at the video frame rate
	int			timerTime;
	byte[]	buf;			// buffer used to store the images to send to the client

	// RTSP variables
	// ----------------
	// rtsp states
	final static int	INIT		= 0;
	final static int	READY		= 1;
	final static int	PLAYING	= 2;
	// rtsp message types
	final static int	SETUP			= 3;
	final static int	PLAY			= 4;
	final static int	PAUSE			= 5;
	final static int	OPTIONS		= 6;
	final static int	DESCRIBE	= 7;
	final static int	TEARDOWN	= 8;

	static int	state;			// RTSP Server state == INIT or READY or PLAY
	Socket			RTSPsocket;	// socket used to send/receive RTSP messages
	// input and output stream filters
	static BufferedReader	RTSPBufferedReader;
	static BufferedWriter	RTSPBufferedWriter;
	static String					VideoFileName;			// video file requested from the client
	static int						RTSP_ID		= 123456;	// ID of the RTSP session
	int										RTSPSeqNb	= 0;			// Sequence number of RTSP messages within the session

	final static String CRLF = "\r\n";

	// --------------------------------
	// Constructor
	// --------------------------------
	public Server() {

		// build GUI
		// --------------------------
		// Frame
		f.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent e) {
				System.exit(0);
			}
		});
		// Content
		packetLossSlider.addChangeListener(new sliderListener());
		packetLossSlider.setMajorTickSpacing(10);
		packetLossSlider.setPaintTicks(true);
		fecSlider.addChangeListener(new sliderListener());
		fecSlider.setMajorTickSpacing(3);
		fecSlider.setPaintTicks(true);
		// frame layout
		mainPanel.setLayout(new GridLayout(0, 1));
		mainPanel.add(label);
		mainPanel.add(packetLossLabel);
		mainPanel.add(packetLossSlider);
		mainPanel.add(fecLabel);
		mainPanel.add(fecSlider);

		f.getContentPane().add(mainPanel, BorderLayout.CENTER);
		f.setSize(new Dimension(590, 200));
		f.setVisible(true);
		f.setAlwaysOnTop(true);
		f.setLocation(0, 370);

		// init Timer
		timer = new Timer(FRAME_PERIOD / 2, this);
		timer.setInitialDelay(0);
		timer.setCoalesce(true);

		// allocate memory for the sending buffer
		buf = new byte[15000];
	}

	// Handler for Slider
	// -----------------------
	class sliderListener implements ChangeListener {
		public void stateChanged(ChangeEvent e) {
			// update GUI
			packetLoss = packetLossSlider.getValue();
			packetLossLabel.setText("Packet loss: " + packetLoss + "%");
			fecGroupsize = fecSlider.getValue();
			fecLabel.setText("FEC group size: " + fecGroupsize);
		}
	}

	// ------------------------------------
	// main
	// ------------------------------------
	public static void main(String argv[]) throws Exception {
		// create a Server object
		Server theServer = new Server();

		// get RTSP socket port from the command line
		int RTSPport = Integer.parseInt(argv[0]);

		// Initiate TCP connection with the client for the RTSP session
		ServerSocket listenSocket = new ServerSocket(RTSPport);
		theServer.RTSPsocket = listenSocket.accept();
		listenSocket.close();

		// Get Client IP address
		theServer.ClientIPAddr = theServer.RTSPsocket.getInetAddress();

		// Initiate RTSPstate
		state = INIT;

		// Set input and output stream filters:
		RTSPBufferedReader = new BufferedReader(new InputStreamReader(theServer.RTSPsocket.getInputStream()));
		RTSPBufferedWriter = new BufferedWriter(new OutputStreamWriter(theServer.RTSPsocket.getOutputStream()));

		// Wait for the SETUP message from the client
		int request_type;
		boolean done = false;
		while (!done) {
			System.out.println("Checking request");
			request_type = theServer.parse_RTSP_request(); // blocking
			// System.out.println("Request received");

			if (request_type == SETUP) {
				done = true;

				// update RTSP state
				state = READY;
				System.out.println("New RTSP state: READY");

				// Send response
				theServer.send_RTSP_response(-1);

				// init the VideoStream object:
				theServer.video = new VideoStream(VideoFileName);

				// init RTP socket
				theServer.RTPsocket = new DatagramSocket();
			} else if (request_type == OPTIONS) {
				theServer.send_RTSP_response(OPTIONS);
			}
			if (request_type == TEARDOWN) {
				// stop timer
				theServer.timer.stop();
				// close sockets
				theServer.RTSPsocket.close();

				System.exit(0);
			}
		}

		// loop to handle RTSP requests
		while (true) {
			// parse the request
			request_type = theServer.parse_RTSP_request(); // blocking

			// send back response
			theServer.send_RTSP_response(request_type);
			if ((request_type == PLAY) && (state == READY)) {
				// start timer
				theServer.timer.start();
				// update state
				state = PLAYING;
				System.out.println("New RTSP state: PLAYING");
			} else if ((request_type == PAUSE) && (state == PLAYING)) {
				// stop timer
				theServer.timer.stop();
				// update state
				state = READY;
				System.out.println("New RTSP state: READY");
			} else if (request_type == OPTIONS) {
				theServer.send_RTSP_response(OPTIONS);
			} else if (request_type == DESCRIBE) {
				theServer.send_RTSP_response(DESCRIBE);
				System.out.println("	Describe response sent.");
			} else if (request_type == TEARDOWN) {
				// stop timer
				theServer.timer.stop();
				// close sockets
				theServer.RTSPsocket.close();
				theServer.RTPsocket.close();

				System.exit(0);
			}
		}
	}

	// ------------------------
	// Handler for timer
	// ------------------------
	public void actionPerformed(ActionEvent e) {
		timerTime += FRAME_PERIOD / 2;
		if ((timerTime % FRAME_PERIOD) == 0) {
			// image packet:
			// ====================================
			// if the current image nb is less than the length of the video
			if (imagenb < VIDEO_LENGTH) {
				// update current imagenb
				imagenb++;

				try {
					// get next frame to send from the video, as well as its size
					int image_length = video.getnextframe(buf);

					// Builds an RTPpacket object containing the frame
					RTPpacket rtp_packet = new RTPpacket(MJPEG_TYPE, imagenb, imagenb * FRAME_PERIOD, buf, image_length);

					// Add frame to FEC buffer
					fec.setBufferEntry(buf, imagenb * FRAME_PERIOD, imagenb);

					// get to total length of the full rtp packet to send
					int packet_length = rtp_packet.getlength();

					// retrieve the packet bitstream and store it in an array of bytes
					byte[] packet_bits = new byte[packet_length];
					rtp_packet.getpacket(packet_bits);

					// send the packet as a DatagramPacket over the UDP socket
					senddp = new DatagramPacket(packet_bits, packet_length, ClientIPAddr, RTP_dest_port);
					if (packetSent()) {
						// System.out.println("Send frame #"+imagenb);
						System.out.println("RTP packet: SeqNum # " + rtp_packet.getsequencenumber() + " TimeStamp " + rtp_packet.gettimestamp() + " ms");// , of type " + rtp_packet.getpayloadtype());
						// print the header bitstream
						// rtp_packet.printheader();
					} else {
						System.out.println("Losing Packet.");
					}

					// update GUI
					label.setText("Send frame #" + imagenb);
				} catch (Exception ex) {
					System.out.println("Exception caught: " + ex);
					System.exit(0);
				}
			} else {
				// if we have reached the end of the video file, stop the timer
				timer.stop();
			}
		} else if (imagenb > 0 && (imagenb % fecGroupsize) == 0) {
			// possible FEC packet:
			// ====================================
			try {
				byte[] fecData = fec.getFECdata(imagenb);
				RTPpacket rtp_packet = new RTPpacket(FEC_TYPE, imagenb, fecGroupsize, fecData, fecData.length); // timestamp gets violated as fecGroupsize ;-)

				// get to total length of the full rtp packet to send
				int packet_length = rtp_packet.getlength();

				// retrieve the packet bitstream and store it in an array of bytes
				byte[] packet_bits = new byte[packet_length];
				rtp_packet.getpacket(packet_bits);

				// send the packet as a DatagramPacket over the UDP socket
				senddp = new DatagramPacket(packet_bits, packet_length, ClientIPAddr, RTP_dest_port);
				if (packetSent()) {
					// System.out.println("Send frame #"+imagenb);
					System.out.println("\tFEC: SeqNum # " + rtp_packet.getsequencenumber());
					// print the header bitstream
					// rtp_packet.printheader();
				} else {
					System.out.println("Losing FEC-Packet.");
				}
			} catch (Exception ex) {
				System.out.println("Exception caught: " + ex);
				System.exit(0);
			}
		}
	}

	private boolean packetSent() throws IOException {
		if (rand.nextInt(100) + 1 > packetLoss) {
			RTPsocket.send(senddp);
			return true;
		} else {
			return false;
		}
	}

	// ------------------------------------
	// Parse RTSP Request
	// ------------------------------------
	private int parse_RTSP_request() {
		int request_type = -1;

		// System.out.println(" Parsing request");
		try {
			// parse request line and extract the request_type:
			String RequestLine = RTSPBufferedReader.readLine();
			// System.out.println("RTSP Server - Received from Client:");
			System.out.println(RequestLine);

			StringTokenizer tokens = new StringTokenizer(RequestLine);
			String request_type_string = tokens.nextToken();

			// convert to request_type structure:
			if ((new String(request_type_string)).compareTo("SETUP") == 0)
				request_type = SETUP;
			else if ((new String(request_type_string)).compareTo("PLAY") == 0)
				request_type = PLAY;
			else if ((new String(request_type_string)).compareTo("PAUSE") == 0)
				request_type = PAUSE;
			else if ((new String(request_type_string)).compareTo("OPTIONS") == 0)
				request_type = OPTIONS;
			else if ((new String(request_type_string)).compareTo("DESCRIBE") == 0)
				request_type = DESCRIBE;
			else if ((new String(request_type_string)).compareTo("TEARDOWN") == 0)
				request_type = TEARDOWN;

			if (request_type == SETUP) {
				// extract VideoFileName from RequestLine
				VideoFileName = tokens.nextToken();
			}

			if (request_type != DESCRIBE) {
				// parse the SeqNumLine and extract CSeq field
				String SeqNumLine = RTSPBufferedReader.readLine();
				System.out.println(SeqNumLine);
				tokens = new StringTokenizer(SeqNumLine);
				tokens.nextToken();
				RTSPSeqNb = Integer.parseInt(tokens.nextToken());

				// get LastLine
				String LastLine = "";
				if (request_type != OPTIONS) {
					LastLine = RTSPBufferedReader.readLine();
					System.out.println(LastLine);
				}

				if (request_type == SETUP) {
					// extract RTP_dest_port from LastLine
					tokens = new StringTokenizer(LastLine);
					for (int i = 0; i < 3; i++)
						tokens.nextToken(); // skip unused stuff
					RTP_dest_port = Integer.parseInt(tokens.nextToken());
					fec = new FECmanager(fecGroupsize);
				}
				// else LastLine will be the SessionId line ... do not check for now.
			}
		} catch (Exception ex) {
			System.out.println("Exception caught: " + ex);
			System.exit(0);
		}
		// System.out.println(" Request parsed.");
		return (request_type);
	}

	// ------------------------------------
	// Send RTSP Response
	// ------------------------------------
	private void send_RTSP_response(int request_type) {
		try {
			RTSPBufferedWriter.write("RTSP/1.0 200 OK" + CRLF);
			if (request_type != DESCRIBE) {
				RTSPBufferedWriter.write("CSeq: " + RTSPSeqNb + CRLF);
				if (request_type == OPTIONS) {
					RTSPBufferedWriter.write("Public: DESCRIBE, OPTIONS, SETUP, TEARDOWN, PLAY, PAUSE" + CRLF);
				} else {
					RTSPBufferedWriter.write("Session: " + RTSP_ID + CRLF);
				}
			} else { // Describe:
				RTSPBufferedWriter.write("Content-Base: rtsp://" + InetAddress.getLocalHost().getHostName() + "/" + VideoFileName + CRLF);
				RTSPBufferedWriter.write("Content-Type: application/sdp" + CRLF);
				RTSPBufferedWriter.write("Content-Length:" + VIDEO_LENGTH + CRLF);
			}
			RTSPBufferedWriter.flush();
			// System.out.println("RTSP Server - Sent response to Client.");
		} catch (Exception ex) {
			System.out.println("Exception caught: " + ex);
			System.exit(0);
		}
	}
}
