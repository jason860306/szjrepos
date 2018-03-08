package com.cola.java.httpupload;

import java.io.BufferedOutputStream;
import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class HttpUploadTest {

	private static final String UPLOAD_URL = "http://192.168.200.15:8888/upload/?key=FDDD1573D4D1954A76E3F3F19DC4798FE2D2D018391DF232CEFFD3077B3AC2BC48EE8F3322BE88BC10421644CE69665BA70ED3F6B11EEA8F9799D03A5F0039E4";

	/**
	 * @param args
	 * @throws Exception
	 */
	public static void main(String[] args) throws Exception {

		DataInputStream dis = null;
		String filePath = "D:\\test.mp4";
		URL url = new URL(UPLOAD_URL);
		HttpURLConnection connection = (HttpURLConnection) url.openConnection();
		connection.setReadTimeout(100000);
		connection.setDoInput(true);
		connection.setDoOutput(true);
		connection.setRequestMethod("POST");
		connection.addRequestProperty("Host", "192.168.200.15");
//		connection.addRequestProperty("Content-Length", "20971520"/*"10634380"*/);
		connection.addRequestProperty("Content-Range",
				"bytes 0-15516775/15516776");
		connection.setRequestProperty("Content-MD5",
				"6CCADB6B45AA8582694A15DC39B8660A");
		connection.setRequestProperty("Content-Type",
				"application/octet-stream");
		BufferedOutputStream out = new BufferedOutputStream(
				connection.getOutputStream());
		
//		DataOutputStream out = new DataOutputStream(connection.getOutputStream());

		// ��ȡ�ļ��ϴ���������
		File file = new File(filePath);
		FileInputStream fileInputStream = new FileInputStream(file);
		byte[] buf = new byte[1024];
		int len = 0;
		while ((len = fileInputStream.read(buf)) != -1) {
			out.write(buf, 0, len);
		}
		out.flush();
		out.close();
		fileInputStream.close();
				
		if ((connection.getResponseCode() != 200) && (connection.getResponseCode() != 206)) {
			System.out.println(connection.getResponseCode());
			dis = new DataInputStream(connection.getErrorStream());
			byte[] bufIn = new byte[1024];
			int length = 0;
			while ((length = dis.read(bufIn)) != -1) {
				System.out.println(new String(bufIn, 0, length));
			}
			dis.close();
		} else {
			System.out.println(connection.getResponseCode());
			dis = new DataInputStream(connection.getInputStream());
			byte[] bufIn = new byte[1024];
			int length = 0;
			while ((length = dis.read(bufIn)) != -1) {
				System.out.println(new String(bufIn, 0, length));
			}
			dis.close();
		}

	}

}
