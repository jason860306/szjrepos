package com.amapv2.apis.location;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.content.Context;
import android.location.Location;
import android.net.wifi.WifiManager;
import android.os.Build;
import android.os.Bundle;
import android.provider.Settings.Secure;
import android.telephony.TelephonyManager;
import android.util.Log;
import android.widget.TextView;

import com.amap.api.location.AMapLocation;
import com.amap.api.location.AMapLocationListener;
import com.amap.api.location.LocationManagerProxy;
import com.amap.api.location.LocationProviderProxy;
import com.amapv2.apis.R;
import com.amapv2.apis.util.AMapUtil;

/**
 * AMapV2地图中简单介绍混合定位
 */
public class LocationNetworkActivity extends Activity implements AMapLocationListener {
	private LocationManagerProxy mAMapLocManager = null;
	private TextView myLocation;
	public String androidUniqueDevID = null;
	MapCli mapCli = new MapCli();
	public static String TAG = "AMapLocTestDemo";
	
    public String getIMEI() {
        //1 compute IMEI
        TelephonyManager TelephonyMgr = (TelephonyManager)getSystemService(TELEPHONY_SERVICE);
    	String m_szImei = TelephonyMgr.getDeviceId(); // Requires READ_PHONE_STATE
    	
    	return m_szImei;
    }
    
    public String getDeviceID() {
        //2 compute DEVICE ID
        String m_szDevIDShort = "35" + //we make this look like a valid IMEI
        	Build.BOARD.length()%10+ Build.BRAND.length()%10 + 
        	Build.CPU_ABI.length()%10 + Build.DEVICE.length()%10 + 
        	Build.DISPLAY.length()%10 + Build.HOST.length()%10 + 
        	Build.ID.length()%10 + Build.MANUFACTURER.length()%10 + 
        	Build.MODEL.length()%10 + Build.PRODUCT.length()%10 + 
        	Build.TAGS.length()%10 + Build.TYPE.length()%10 + 
        	Build.USER.length()%10 ; //13 digits
        
        return m_szDevIDShort;
    }
    
    public String getAndroidID() {
        //3 android ID - unreliable
        String m_szAndroidID = Secure.getString(getContentResolver(), Secure.ANDROID_ID);
        return m_szAndroidID;
    }
    
    public String getWifiMAC() {
        //4 wifi manager, read MAC address - requires  android.permission.ACCESS_WIFI_STATE or comes as null
        WifiManager wm = (WifiManager)getSystemService(Context.WIFI_SERVICE);
        String m_szWLANMAC = wm.getConnectionInfo().getMacAddress();
        return m_szWLANMAC;
    }
    
    public String getBluetoothMAC() {
        //5 Bluetooth MAC address  android.permission.BLUETOOTH required
        BluetoothAdapter m_BluetoothAdapter	= null; // Local Bluetooth adapter
    	m_BluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
    	String m_szBTMAC = m_BluetoothAdapter.getAddress();
    	return m_szBTMAC;
    }
    
    public String getAndroidUniqueDevID() {
    	//6 SUM THE IDs
    	String m_szLongID = getIMEI() + getDeviceID() + getAndroidID()+ getWifiMAC();// + getBluetoothMAC();
    	MessageDigest m = null;
		try {
			m = MessageDigest.getInstance("MD5");
		} catch (NoSuchAlgorithmException e) {
			e.printStackTrace();
		} 
		m.update(m_szLongID.getBytes(),0,m_szLongID.length());
		byte p_md5Data[] = m.digest();
		
		String m_szUniqueID = new String();
		for (int i=0;i<p_md5Data.length;i++) {
			int b =  (0xFF & p_md5Data[i]);
			// if it is a single digit, make sure it have 0 in front (proper padding)
			if (b <= 0xF) m_szUniqueID+="0";
			// add number to string
			m_szUniqueID+=Integer.toHexString(b); 
		}
		m_szUniqueID = m_szUniqueID.toUpperCase();
		
		return m_szUniqueID;
    }

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.locationnetwork_activity);
		myLocation = (TextView) findViewById(R.id.myLocation);
		mAMapLocManager = LocationManagerProxy.getInstance(this);
		/*
		 * mAMapLocManager.setGpsEnable(false);//
		 * 1.0.2版本新增方法，设置true表示混合定位中包含gps定位，false表示纯网络定位，默认是true Location
		 * API定位采用GPS和网络混合定位方式
		 * ，第一个参数是定位provider，第二个参数时间最短是5000毫秒，第三个参数距离间隔单位是米，第四个参数是定位监听者
		 */
		mAMapLocManager.requestLocationUpdates(
				LocationProviderProxy.AMapNetwork, 5000, 10, this);

		androidUniqueDevID = getAndroidUniqueDevID();
	}

	@Override
	protected void onPause() {
		super.onPause();
		if (mAMapLocManager != null) {
			mAMapLocManager.removeUpdates(this);
		}
	}

	@Override
	protected void onDestroy() {
		if (mAMapLocManager != null) {
			mAMapLocManager.removeUpdates(this);
			mAMapLocManager.destory();
		}
		mAMapLocManager = null;
		super.onDestroy();
	}

	/**
	 * 此方法已经废弃
	 */
	@Override
	public void onLocationChanged(Location location) {
	}

	@Override
	public void onProviderDisabled(String provider) {

	}

	@Override
	public void onProviderEnabled(String provider) {

	}

	@Override
	public void onStatusChanged(String provider, int status, Bundle extras) {

	}

	/**
	 * 混合定位回调函数
	 */
	@Override
	public void onLocationChanged(AMapLocation location) {
		if (location != null) {
			Double geoLat = location.getLatitude();
			Double geoLng = location.getLongitude();
			String cityCode = "";
			String desc = "";
			Bundle locBundle = location.getExtras();
			if (locBundle != null) {
				cityCode = locBundle.getString("citycode");
				desc = locBundle.getString("desc");
			}
			String str = ("定位成功:(" + geoLng + "," + geoLat + ")"
					+ "\n精    度    :" + location.getAccuracy() + "米"
					+ "\n定位方式:" + location.getProvider() + "\n定位时间:"
					+ AMapUtil.convertToTime(location.getTime()) + "\n城市编码:"
					+ cityCode + "\n位置描述:" + desc + "\n省:"
					+ location.getProvince() + "\n市:" + location.getCity()
					+ "\n区(县):" + location.getDistrict() + "\n城市编码:"
					+ location.getCityCode() + "\n区域编码:" + location.getAdCode());

//			MapLoc mapLoc = new MapLoc();
//			mapLoc.setLatitude(location.getLatitude());
//			mapLoc.setLongitude(location.getLongitude());
//			mapLoc.setCoordinate(Coordinate.COORDINATE_BD09);
//			String s = location.getProvider();
////			mapLoc.setLoctype(location.getProvider());
//			Log.i(TAG, mapLoc.toString());
//			
//			if (null != mapCli.SendReport(androidUniqueDevID, mapLoc)) {
//				String strResponse = mapCli.SendRequest(androidUniqueDevID, 1e50, mapLoc);
//				if (null != strResponse) {
//					str += strResponse;
//				}
//			}
			
			myLocation.setText(str);
		}
	}
}
