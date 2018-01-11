import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Arrays;

public class FECmanager {
	int	bufferSize	= 100;
	int	fecGroupsize;			// FEC-Gruppengröße

	Mediapacket[] buffer; // Puffer für Medienpakete

	// Sender --------------------------------------
	public FECmanager(int groupsize) {
		this.fecGroupsize = groupsize;
		this.resetBuffer();
	}

	// Empfänger -----------------------------------
	public FECmanager() {
		this.resetBuffer();
	}

	// ----------------------------------------------
	// *** Universell ***
	// ----------------------------------------------

	// Ergänzt Puffer um Medieneintrag
	public void setBufferEntry(byte[] data, int timestamp, int packetNo) {
		packetNo = getRealPacketNo(packetNo);
		// wenn Eintrag schon vorhanden ist, bedeutet das ein neues Paket erstellt werden muss
		if (buffer[packetNo] != null)
			this.resetPacket(packetNo);
		buffer[packetNo] = new Mediapacket(data, timestamp);
	}

	// Setzt ein Paket null.
	public void resetPacket(int packetNo) {
		packetNo = getRealPacketNo(packetNo);
		buffer[packetNo] = null;
	}

	// Löscht/Initialisiert den Puffer mit der entsprechenden Größe.
	private void resetBuffer() {
		buffer = new Mediapacket[bufferSize];
	}

	// Schritt zum berechnen eines FEC-Pakets
	private byte[] calculateFECpacketStep(byte[] shortPacket, byte[] longPacket) {
		int i = 0;
		byte[] fecPacket = new byte[longPacket.length];
		System.arraycopy(longPacket, 0, fecPacket, 0, longPacket.length);
		// System.out.format("FEC step: %-20s XOR %-20s =", FECtest.showBinary(shortPacket), FECtest.showBinary(longPacket));
		for (byte b : shortPacket) {
			fecPacket[i] = (byte) (b ^ fecPacket[i]);
			i++;
		}
		// System.out.format(" %-20s\n", FECtest.showBinary(longPacket));
		return fecPacket;
	}

	// Richtige Paketnummer anhand der Puffergröße zurückgeben:
	private int getRealPacketNo(int packetNo) {
		if (packetNo < 0)
			return (bufferSize - packetNo) % bufferSize;
		return packetNo % bufferSize;
	}

	// ----------------------------------------------
	// *** SENDER ***
	// ----------------------------------------------

	// Erstellt fertiges FEC-Paket
	public byte[] getFECdata(int packetNo) {
		// xor byte array:
		byte[] fecCode = new byte[0];
		for (int i = 0; i < fecGroupsize; i++) {
			int entry = (packetNo - i) % bufferSize;
			if (fecCode.length < buffer[entry].data.length)
				fecCode = calculateFECpacketStep(fecCode, buffer[entry].data);
			else
				fecCode = calculateFECpacketStep(buffer[entry].data, fecCode);
		}
		return fecCode;
	}

	// ------------------------------------------------
	// *** RECEIVER ***
	// ------------------------------------------------

	// Korrigiert Fehler und gibt Erfolg aus. packetNo gibt die Nummer des FEC-Pakets aus. Diese entspricht immer dem letzten Paket, das der FEC-Code abdeckt.
	public int correctPacket(byte[] fecdata, int packetNo, int fecGroupsize) {
		// Korrigiere Fehler. Überprüfe nebenbei, ob Fehler korrigierbar ist (maximal ein Paket ist null).
		int numberOfLostPackets = 0;
		int correctedPacket = 0;
		// for (int i = packetNo; i > (packetNo - fecGroupsize); i--)
		int i = getRealPacketNo(packetNo); // Paketnummer
		int j = 0; // bearbeitete Pakete
		String lostPackets = "";
		while (j < fecGroupsize) {
			// Prüfe, ob Paket null ist. Und setzte ggf. korregierte Paketnummer. Bei mehreren null-Paketen ist Fehler nicht korrigierbar.
			if (buffer[i] == null) {
				numberOfLostPackets++;
				correctedPacket = i;
				lostPackets += i + ", ";
			} else {
				fecdata = calculateFECpacketStep(buffer[i].data, fecdata);
			}
			i = getRealPacketNo(i - 1);
			j++;
		}
		if (numberOfLostPackets == 0) {
			// System.out.println("\t\tAvailable packets: [" + availablePackets.replaceAll(", $","")+"]");
			return numberOfLostPackets;
		} else if (numberOfLostPackets > 1) {
			System.out.println("\t\t Too much packets lost: " + numberOfLostPackets + " (Lost packets: [" + lostPackets.replaceAll(", $", "") + "])");
			return numberOfLostPackets;
		}
		int timestamp;
		if (buffer[getRealPacketNo(correctedPacket - 1)] != null) {
			timestamp = buffer[getRealPacketNo(correctedPacket - 1)].timeStamp;
		} else {
			timestamp = buffer[getRealPacketNo(correctedPacket + 1)].timeStamp;
		}
		buffer[correctedPacket] = new Mediapacket(fecdata, timestamp);
		System.out.println("\t\t\tFEC-Paket " + packetNo + " corrected frame " + correctedPacket + ".");
//		try (PrintWriter out = new PrintWriter("buffer" + packetNo + ".txt")) {
//			out.println(Arrays.toString(buffer));
//		} catch (FileNotFoundException e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		}
		return numberOfLostPackets;
	}

	public Mediapacket getBufferEntry(int packetNo) {
		return buffer[packetNo % bufferSize];
	}
}
