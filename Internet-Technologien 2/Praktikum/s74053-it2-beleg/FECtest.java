import java.nio.ByteBuffer;
import java.util.Arrays;

public class FECtest {

	public static void main(String argv[]) throws Exception {
		FECmanager fec = new FECmanager(5);

		byte[] bytesA = { 0x1, 0x2 };
		byte[] bytesB = { 0x5, 0x7, 0xA };
		byte[] bytesC = { 0x6 };
		byte[] bytesD = { 0xA, 0xA, 0xA, 0xA, 0xF, 0x0 };
		byte[] bytesE = { 0xE };

		fec.setBufferEntry(bytesA, 0, 1);
		fec.setBufferEntry(bytesB, 0, 2);
		fec.setBufferEntry(bytesC, 0, 3);
		fec.setBufferEntry(bytesD, 0, 4);
		fec.setBufferEntry(bytesE, 0, 5);

		System.out.println("Input:");
		System.out.format("1 - Hex: %25s / Bin: %-20s\n", Arrays.toString(fec.getBufferEntry(1).data), showBinary(fec.getBufferEntry(1).data));
		System.out.format("2 - Hex: %25s / Bin: %-20s\n", Arrays.toString(fec.getBufferEntry(2).data), showBinary(fec.getBufferEntry(2).data));
		System.out.format("3 - Hex: %25s / Bin: %-20s\n", Arrays.toString(fec.getBufferEntry(3).data), showBinary(fec.getBufferEntry(3).data));
		System.out.format("4 - Hex: %25s / Bin: %-20s\n", Arrays.toString(fec.getBufferEntry(4).data), showBinary(fec.getBufferEntry(4).data));
		System.out.format("5 - Hex: %25s / Bin: %-20s\n\n", Arrays.toString(fec.getBufferEntry(5).data), showBinary(fec.getBufferEntry(5).data));

		byte[] bytesFEC = fec.getFECdata(5);

		System.out.println("FEC:");
		System.out.format("    Hex: %25s / Bin: %-20s\n\n", Arrays.toString(bytesFEC), showBinary(bytesFEC));

		System.out.println("Remove 3.");
		fec.resetPacket(3);
		fec.correctPacket(bytesFEC, 5, 5);

		System.out.format("Corrected 3: %s\n\n", Arrays.toString(fec.getBufferEntry(3).data));

		System.out.println("Remove 2.");
		fec.resetPacket(2);
		fec.correctPacket(bytesFEC, 5, 5);

		System.out.format("Corrected 2: %s\n", Arrays.toString(fec.getBufferEntry(2).data));

	}

	public static String showBinary(byte[] bytes) {
		String out = "";
		for (int i = 0; i < bytes.length; i++) {
			out += leadingZeros(Integer.toBinaryString(bytes[i]), 4);
			if (i < bytes.length - 1)
				out += " ";
		}
		return out;
	}

	public static String leadingZeros(String s, int length) {
		if (s.length() >= length)
			return s;
		else
			return String.format("%0" + (length - s.length()) + "d%s", 0, s);
	}
}