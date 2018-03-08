import java.io.*;
import java.net.*;

public class SockClient {

	private String ipAddr = "127.0.0.1";
	private int port = 9000;
	private Persistence persistence;
	private Socket sock;
	
	public SockClient() {
		persistence = new Persistence();
		try {
			sock = new Socket(ipAddr, port);
		} catch (UnknownHostException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public void send() throws IOException {
		System.out.println("----Client Begin Send Data----");
		try {
			OutputStream outStrm = sock.getOutputStream();
			byte b[] = new byte[2048];
			b = persistence.toBytes();
			outStrm.write(b);
			outStrm.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public static void main(String[] args) {
		try {
			SockClient client = new SockClient();
			client.send();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}
