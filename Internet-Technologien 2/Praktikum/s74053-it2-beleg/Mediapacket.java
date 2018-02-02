public class Mediapacket {
	byte[]	data;
	int			timeStamp;

	public Mediapacket(byte[] data, int timeStamp) {
		this.data = new byte[data.length];
		System.arraycopy(data, 0, this.data, 0, data.length);
		this.timeStamp = timeStamp;
	}

	public String toString() {
		//return Arrays.toString(data)+"\n";
		return "Packet "+timeStamp;
	}
}