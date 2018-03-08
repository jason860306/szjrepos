/**
 * 
 */
package baidumapsdk.demo;

import java.io.*;
import java.net.*;
import java.util.Vector;

import android.util.Log;

public class MapCli {
	
	public static final String MAPSRV_ADDR = "192.168.200.15";
	public static final int MAPSRV_PORT = 7092;
	public static final String TAG = "MapProto";
	
	public MapCli(Runnable r) {
		try {
			new Thread(r).start();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	public String SendReport(String devID, MapLoc loc) {
		LocReport locReport = new LocReport();
		locReport.setDevID(devID);
		locReport.setProto_type(ProtoType.LOCATION_REPORT);
		locReport.setLength(LocReport.SIZE);
		locReport.setLoc(loc);
		Log.i(TAG, locReport.toString());
		try {
			Socket sock = new Socket(MAPSRV_ADDR, MAPSRV_PORT);
			DataOutputStream dostrm = new DataOutputStream(sock.getOutputStream());
			locReport.toStrm(dostrm);
			dostrm.flush();
			dostrm.close();
			return locReport.toString();
		} catch (UnknownHostException e) {
			e.printStackTrace();
		} catch (Exception e) {
			e.printStackTrace();
		}
		return null;
	}
	
	public Vector<LocResponse.LocNode> SendRequest(String devID, double radius, MapLoc loc) {
		LocRequest locRequest = new LocRequest();
		locRequest.setDevID(devID);
		locRequest.setProto_type(ProtoType.LOCATION_REQUEST);
		locRequest.setLength(LocRequest.SIZE);
		locRequest.setRadius(radius);
		locRequest.setLoc(loc);
		try {
			Socket sock = new Socket(MAPSRV_ADDR, MAPSRV_PORT);
			DataInputStream instrm = new DataInputStream(sock.getInputStream());
			DataOutputStream dostrm = new DataOutputStream(sock.getOutputStream());
			
			locRequest.toStrm(dostrm);
			dostrm.flush();
			Log.i(TAG, locRequest.toString());
			
			LocResponse locResponse = new LocResponse();
			locResponse.fromStrm(instrm);
			Log.i(TAG, locResponse.toString());
			
			dostrm.close();
			sock.close();
			return locResponse.getlocvec();
		} catch (Exception e) {
			e.printStackTrace();
		}
		return null;
	}
}