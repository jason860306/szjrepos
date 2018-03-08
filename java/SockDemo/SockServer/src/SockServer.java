import java.io.*;
import java.net.*;

public class SockServer {

	private ServerSocket srvSock;
	private BufferedReader bufReader = null;
	Socket sock;
	
	public SockServer() {
		try {
			srvSock = new ServerSocket(9000);
			System.out.println("Waiting For Accept Client");
			sock = srvSock.accept();
			System.out.println("Accepted Client");
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public void recv() {
		try {
			System.out.println("----Begin Received From Client");
			Persistence persistence = new Persistence();
			InputStream inStrm = sock.getInputStream();
			byte b[] = new byte[2048];
			inStrm.read(b);
			Person obj = persistence.readBytes(b);
			System.out.println("Read From Client Data is: " + obj.getAddr());
			System.out.println("Read From Client Data is: " + obj.getBirthday());
			System.out.println("Read From Client Data is: " + obj.getName());
			System.out.println("Read From Client Data is: " + obj.getStreet());
			System.out.println("Read From Client Data is: " + obj.getSex());
			inStrm.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public static void main(String[] args) {
		SockServer ss = new SockServer();
		ss.recv();
	}
}
