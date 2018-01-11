
//VideoStream

import java.io.*;
import java.util.Scanner;

public class VideoStream {

	FileInputStream	fis;			// video file
	int							frame_nb;	// current frame nb
	Scanner					scanner;

	// -----------------------------------
	// constructor
	// -----------------------------------
	public VideoStream(String filename) throws Exception {

		// init variables
		fis = new FileInputStream(filename);
		frame_nb = 0;
		scanner = new Scanner(fis);
	}

	// -----------------------------------
	// getnextframe
	// returns the next frame as an array of byte and the size of the frame
	// -----------------------------------
	public int getnextframe(byte[] frame) throws Exception {
		int length = 0;
		String length_string;
		byte[] frame_length = new byte[5];

//		scanner.useDelimiter("ÿØÿ");	// SOI
//		scanner.useDelimiter("ÿÙ");	// EOI
//
//		while (scanner.hasNext()) {
//			System.out.println("SQL statement: " + scanner.next());
//		}

		// read current frame length
		fis.read(frame_length, 0, 5);

		// transform frame_length to integer
		length_string = new String(frame_length);
		length = Integer.parseInt(length_string);

		return (fis.read(frame, 0, length));
	}
}
