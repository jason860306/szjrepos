/**
 * 
 */
package baidumapsdk.demo;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.util.*;

class ProtoType
{
	static final int LOCATION_REPORT = 10;
	static final int LOCATION_REQUEST = 11;
	static final int LOCATION_RESPONSE = 12;
};

class Coordinate
{
	static final int COORDINATE_WGS84 = 20; /* ��������ϵ��������ͨ�õ�����ϵ */
    static final int COORDINATE_GCJ02 = 21; /* ��������ϵ��WGS84����ϵ�����ܺ������ϵ */
    static final int COORDINATE_BD09 = 22;  /* �ٶ�����ϵ��GCJ02����ϵ�����ܺ������ϵ */
    static final int COORDINATE_OTHER = 23; /* �ѹ�����ϵ��ͼ������ϵ�ȣ�����Ҳ����GCJ02�����ϼ��ܶ��ɵ� */
};

class MapLoc
{
	private double latitude;
    private double longitude;
    private int coordinate;
    private int loctype;
    static public int SIZE = ((Integer.SIZE / 8) * 2 + (Double.SIZE / 8) * 2);
    
    public MapLoc() {
    	
    }
    
    public MapLoc(double latitude, double longitude, int coordinate, int loctype) {
    	this.latitude = latitude;
    	this.longitude = longitude;
    	this.coordinate = coordinate;
    	this.loctype = loctype;
    }
    
    public int getSize() {
    	return SIZE;
    }
	public double getLatitude() {
		return latitude;
	}
	public void setLatitude(double latitude) {
		this.latitude = latitude;
	}
	public double getLongitude() {
		return longitude;
	}
	public void setLongitude(double longitude) {
		this.longitude = longitude;
	}
	public int getCoordinate() {
		return coordinate;
	}
	public void setCoordinate(int coordinate) {
		this.coordinate = coordinate;
	}
	public int getLoctype() {
		return loctype;
	}
	public void setLoctype(int loctype) {
		this.loctype = loctype;
	}
	public void toStrm(DataOutputStream dostrm) {
		try {
			dostrm.writeDouble(latitude);
			dostrm.writeDouble(longitude);
			dostrm.writeInt(coordinate);
			dostrm.writeInt(loctype);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	public void fromStrm(DataInputStream iostrm) {
		try {
			latitude = iostrm.readDouble();
			longitude = iostrm.readDouble();
			coordinate = iostrm.readInt();
			loctype = iostrm.readInt();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	public String toString() {
		StringBuffer sb = new StringBuffer();
		sb.append("MapLoc:\n");
		sb.append("MapLoc.latitude   = " + latitude + "\n");
		sb.append("MapLoc.longitude  = " + longitude + "\n");
		sb.append("MapLoc.coordinate = " + coordinate + "\n");
		sb.append("MapLoc.loctype    = " + loctype + "\n");
		return sb.toString();
	}
};

/* the protocol between mapcli and mapsrv */
public class MapProto
{
	private int proto_type;
	private int length;
	private byte[] devID = new byte[IDSIZE]; // 32 bytes
	static public int IDSIZE = 32;
    static public int SIZE = ((Integer.SIZE / 8) * 2 + IDSIZE);

    public MapProto() {
    }
	
	public MapProto(int proto_type, int length, String devID) {
		this.proto_type = proto_type;
		this.length = length;
    	setDevID(devID.getBytes());
	}
	public byte[] getDevID() {
		return devID;
	}
	public void setDevID(byte[] devID) {
		this.devID = devID;
	}
	public void setDevID(String devID) {
		setDevID(devID.getBytes());
	}
	public int getSize() {
		return SIZE;
	}
	public int getProto_type() {
		return proto_type;
	}
	public void setProto_type(int proto_type) {
		this.proto_type = proto_type;
	}
	public int getLength() {
		return length;
	}
	public void setLength(int length) {
		this.length = length;
	}
	public void toStrm(DataOutputStream dostrm) {
		try {
			dostrm.writeInt(proto_type);
			dostrm.writeInt(length);
			dostrm.write(devID, 0, IDSIZE);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	public void fromStrm(DataInputStream iostrm) {
		try {
			proto_type = iostrm.readInt();
			length = iostrm.readInt();
			iostrm.read(devID, 0, IDSIZE);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	public String toString() {
		StringBuffer sb = new StringBuffer();
		sb.append("MapProto.proto_type: " + proto_type + "\n");
		sb.append("MapProto.length: " + length + "\n");
		sb.append("MapProto.devID: " + devID + "\n");
		return sb.toString();
	}
};

/* the user(b/c) report their loc to mapsrv. */
class LocReport extends MapProto
{
	private MapLoc loc = new MapLoc();
    static public int SIZE = (MapProto.SIZE + MapLoc.SIZE);
    
    public LocReport() {
    	super();
    }
	public LocReport(int proto_type, int length, String devID, MapLoc loc) {
		super(proto_type, length, devID);
		setLoc(loc);
	}
	@Override
	public int getSize() {
		return SIZE;
	}
	public MapLoc getLoc() {
		return loc;
	}
	public void setLoc(MapLoc loc) {
		this.loc = loc;
	}
	public void toStrm(DataOutputStream dostrm) {
		super.toStrm(dostrm);
		loc.toStrm(dostrm);
	}
	public void fromStrm(DataInputStream iostrm) {
		super.fromStrm(iostrm);
		loc.fromStrm(iostrm);
	}
	public String toString() {
		StringBuffer sb = new StringBuffer();
		sb.append("LocReport:\n");
		sb.append(super.toString());
		sb.append(loc.toString());
		return sb.toString();
	}
};

/* the user(c) request all the users's loc who owned valid wifi signal. */
class LocRequest extends MapProto
{
	private double radius;
	private MapLoc loc = new MapLoc();
    static public int SIZE = (MapProto.SIZE + MapLoc.SIZE + (Double.SIZE / 8));
    
    public LocRequest() {
    	super();
    }
	public LocRequest(int proto_type, int length, String devID, double radius, MapLoc loc) {
		super(proto_type, length, devID);
		setRadius(radius);
		setLoc(loc);
	}
	@Override
	public int getSize() {
		return SIZE;
	}
	public double getRadius() {
		return radius;
	}
	public void setRadius(double radius) {
		this.radius = radius;
	}
	public MapLoc getLoc() {
		return loc;
	}
	public void setLoc(MapLoc loc) {
		this.loc = loc;
	}
	public void toStrm(DataOutputStream dostrm) {
		try {
			super.toStrm(dostrm);
			dostrm.writeDouble(radius);
			loc.toStrm(dostrm);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	public void fromStrm(DataInputStream iostrm) {
		try {
			super.fromStrm(iostrm);
			radius = iostrm.readDouble();
			loc.fromStrm(iostrm);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	public String toString() {
		StringBuffer sb = new StringBuffer();
		sb.append("LocRequest:\n");
		sb.append(super.toString());
		sb.append("LocRequest.radius: " + radius + "\n");
		sb.append(loc.toString());
		return sb.toString();
	}
};

/* mapsrv return all the valid users(b) to user(c). */
class LocResponse extends MapProto
{
	public class LocNode
	{
		byte[] devID = new byte[MapProto.IDSIZE];
		MapLoc loc = new MapLoc();
		
		public LocNode() {
		}
		public LocNode(String devID, MapLoc loc) {
			setDevID(devID);
			setLoc(loc);
		}
		public int getSize() {
			return MapProto.IDSIZE + MapLoc.SIZE;
		}
		public byte[] getDevID() {
			return devID;
		}
		public void setDevID(byte[] devID) {
			this.devID = devID;
		}
		public void setDevID(String devID) {
			setDevID(devID.getBytes());
		}
		public MapLoc getLoc() {
			return loc;
		}
		public void setLoc(MapLoc loc) {
			this.loc = loc;
		}
		public void toStrm(DataOutputStream dostrm) {
			try {
				dostrm.write(devID, 0, MapProto.IDSIZE);
				loc.toStrm(dostrm);
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
		public void fromStrm(DataInputStream iostrm) {
			try {
				iostrm.read(devID, 0, MapProto.IDSIZE);
				loc.fromStrm(iostrm);
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
		public String toString() {
			StringBuffer sb = new StringBuffer();
			sb.append("LocNode:\n");
			sb.append("LocNode.devID: " + devID + "\n");
			sb.append(loc.toString());
			return sb.toString();
		}
	}
	private Vector<LocNode> locvec = new Vector<LocNode>();
    static public int SIZE = 0;
    
    public LocResponse() {
    	super();
		SIZE = getSize();
    }
	
	public LocResponse(int proto_type, int length, String devID, Vector<LocNode> locvec) {
		super(proto_type, length, devID);
		setlocvec(locvec);
		SIZE = getSize();
	}

	@Override
	public int getSize() {
		int size = super.getSize();
		for (Iterator<LocNode> locIter = locvec.iterator(); locIter.hasNext(); ) {
			LocNode locNode = locIter.next();
			size += locNode.getSize();
		}
		return size;
	}
	public Vector<LocNode> getlocvec() {
		return locvec;
	}
	public void setlocvec(Vector<LocNode> locvec) {
		this.locvec = locvec;
	}
	public void toStrm(DataOutputStream dostrm) {
		for (Iterator<LocNode> locIter = locvec.iterator(); locIter.hasNext(); ) {
			LocNode locNode = locIter.next();
			locNode.toStrm(dostrm);
		}
	}
	public void fromStrm(DataInputStream iostrm) {
		try {
			super.fromStrm(iostrm);
			int locvecSize = (this.getLength() - MapProto.SIZE);
			int locvecNum = locvecSize / (MapLoc.SIZE + MapProto.IDSIZE);
			for (int i = 0; i < locvecNum; ++i) {
				LocNode locNode = new LocNode();
				locNode.fromStrm(iostrm);
				locvec.add(locNode);
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	public String toString() {
		StringBuffer sb = new StringBuffer();
		sb.append("LocResponse:\n");
		sb.append(super.toString());
		int i = 0;
		for (Iterator<LocNode> locIter = locvec.iterator(); locIter.hasNext(); ) {
			LocNode locNode = locIter.next();
			sb.append(++i + ".\n");
			sb.append(locNode.toString());
		}
		return sb.toString();
	}
};
