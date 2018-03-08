package com.baidu.locTest;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.regex.Pattern;

import android.app.Activity;
import android.app.Service;
import android.bluetooth.BluetoothAdapter;
import android.content.Context;
import android.content.Intent;
import android.net.wifi.WifiManager;
import android.os.Build;
import android.os.Bundle;
import android.os.Process;
import android.os.Vibrator;
import android.provider.Settings.Secure;
import android.telephony.TelephonyManager;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.TextView;

import com.baidu.location.LocationClient;
import com.baidu.location.LocationClientOption;

public class mainActivity extends Activity {
	private TextView mTv = null;
	private EditText mSpanEdit;
	private EditText mCoorEdit;
	private CheckBox mGpsCheck;
	private CheckBox mPriorityCheck;
	private Button   mStartBtn;
	private Button	 mSetBtn;
	private Button 	 mLocBtn;
	private Button 	 mPoiBtn;
	private Button 	 mOfflineBtn;
	private CheckBox mIsAddrInfoCheck;
	private boolean  mIsStart;
	private static int count = 1;
	private Vibrator mVibrator01 =null;
	private LocationClient mLocClient;
	private Button geofenceBtn;

	public static String TAG = "LocTestDemo";
	
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
    	String m_szLongID = /*getIMEI() + */getDeviceID()/* + getAndroidID()+ getWifiMAC()*/;// + getBluetoothMAC();
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

		setContentView(R.layout.main);
		mTv = (TextView)findViewById(R.id.textview);
		mSpanEdit = (EditText)findViewById(R.id.edit);
		mCoorEdit = (EditText)findViewById(R.id.coorEdit);
		mGpsCheck = (CheckBox)findViewById(R.id.gpsCheck);
		mPriorityCheck = (CheckBox)findViewById(R.id.priorityCheck);
		mStartBtn = (Button)findViewById(R.id.StartBtn);
		mLocBtn = (Button)findViewById(R.id.locBtn);
		mSetBtn = (Button)findViewById(R.id.setBtn);       
		mPoiBtn = (Button)findViewById(R.id.PoiReq);
		mOfflineBtn  = (Button)findViewById(R.id.offLineBtn);
		mIsAddrInfoCheck = (CheckBox)findViewById(R.id.isAddrInfocb);
		mIsStart = false;

		mLocClient = ((Location)getApplication()).mLocationClient;
		((Location)getApplication()).mTv = mTv;
		mVibrator01 =(Vibrator)getApplication().getSystemService(Service.VIBRATOR_SERVICE);
		((Location)getApplication()).mVibrator01 = mVibrator01;
		((Location)getApplication()).androidUniqueDevID = getAndroidUniqueDevID();
		geofenceBtn = (Button)findViewById(R.id.geofence);
			
		geofenceBtn.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				startActivity(new Intent(mainActivity.this, GeofenceActivity.class));
			}
		});
		
		//��ʼ/ֹͣ��ť 
		mStartBtn.setOnClickListener( new OnClickListener() {
			@Override
			public void onClick(View v) {
				if (!mIsStart) {
					setLocationOption();
					mLocClient.start();
					mStartBtn.setText("ֹͣ");
					mIsStart = true;

				} else {
					mLocClient.stop();
					mIsStart = false;
					mStartBtn.setText("��ʼ");
				} 
				Log.d(TAG, "... mStartBtn onClick... pid="+Process.myPid()+" count="+count++);
			}
		});

		//��λ��ť
		mLocBtn.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				if (mLocClient != null && mLocClient.isStarted()){
					setLocationOption();
					mLocClient.requestLocation();	
				}				
				else 
					Log.d(TAG, "locClient is null or not started");
				Log.d(TAG, "... mlocBtn onClick... pid="+Process.myPid()+" count="+count++);
				Log.d(TAG,"version:"+mLocClient.getVersion());
			}
		});

		//���ð�ť
		mSetBtn.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				setLocationOption();
			}
		});

		mPoiBtn.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				mLocClient.requestPoi();
			}
		});  
		
		//���߻�վ��λ��ť
		mOfflineBtn.setOnClickListener( new OnClickListener() {
			@Override
			public void onClick(View v) {
				int req = mLocClient.requestOfflineLocation();
				Log.d("req","req:"+req);
			}
		});
	}   

	@Override
	public void onDestroy() {
		mLocClient.stop();
		((Location)getApplication()).mTv = null;
		super.onDestroy();
	}

	//������ز���
	private void setLocationOption(){
		LocationClientOption option = new LocationClientOption();
		option.setOpenGps(mGpsCheck.isChecked());				//��gps
		option.setCoorType(mCoorEdit.getText().toString());		//������������
		option.setServiceName("com.baidu.location.service_v2.9");
		option.setPoiExtraInfo(mIsAddrInfoCheck.isChecked());	
		if(mIsAddrInfoCheck.isChecked())
		{
			option.setAddrType("all");
		}		
		if(null!=mSpanEdit.getText().toString())
		{
			boolean b = isNumeric(mSpanEdit.getText().toString());
			 if(b)
			{
				option.setScanSpan(Integer.parseInt(mSpanEdit.getText().toString()));	//���ö�λģʽ��С��1����һ�ζ�λ;���ڵ���1����ʱ��λ
			}
		}
//		option.setScanSpan(3000);
		
		if(mPriorityCheck.isChecked())
		{
			option.setPriority(LocationClientOption.NetWorkFirst);      //������������
		}
		else
		{
			option.setPriority(LocationClientOption.GpsFirst);        //�����ã�Ĭ����gps����
		}

		option.setPoiNumber(10);
		option.disableCache(true);		
		mLocClient.setLocOption(option);
	}

	protected boolean isNumeric(String str) {   
		Pattern pattern = Pattern.compile("[0-9]*");   
		return pattern.matcher(str).matches();   
	}  


}