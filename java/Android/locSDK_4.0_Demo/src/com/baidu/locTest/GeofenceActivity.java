package com.baidu.locTest;

import java.util.ArrayList;
import java.util.List;

import android.app.Activity;
import android.app.Service;
import android.os.Bundle;
import android.os.Vibrator;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.Toast;

import com.baidu.location.BDGeofence;
import com.baidu.location.BDLocationStatusCodes;
import com.baidu.location.GeofenceClient;
import com.baidu.location.GeofenceClient.OnAddBDGeofencesResultListener;
import com.baidu.location.GeofenceClient.OnGeofenceTriggerListener;
import com.baidu.location.GeofenceClient.OnRemoveBDGeofencesResultListener;

public class GeofenceActivity extends Activity {
	
	private GeofenceClient mGeofenceClient;
	
	private Button addGeofenceBtn;
	private Button removeGeofenceBtn;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		//��ʼ��GeofenceClient
		mGeofenceClient = ((Location)getApplication()).mGeofenceClient;
		//ע�����Χ������ļ�����
		mGeofenceClient.registerGeofenceTriggerListener(new GeofenceTriggerListener());
		//��������Χ������
//		mGeofenceClient.start();
		
		addGeofenceBtn = (Button) findViewById(R.id.add);
		removeGeofenceBtn = (Button) findViewById(R.id.remove);
		
		ClickListener listener = new ClickListener();
		addGeofenceBtn.setOnClickListener(listener);
		removeGeofenceBtn.setOnClickListener(listener);
	}
	
	public class ClickListener implements OnClickListener {

		@Override
		public void onClick(View v) {
			switch (v.getId()) {
			case R.id.add:
				addGeofence();
				break;
				
			case R.id.remove:
				removeGeofence();
				break;

			default:
				break;
			}
		}
	}
	
	private void addGeofence() {
		BDGeofence fence = new BDGeofence.Builder().setGeofenceId(Constants.GEOFENCE_ID).
				setCircularRegion(Constants.GEOFENCE_LONGTITUDE, Constants.GEOFENCE_LATITUDE, Constants.GEOFENCE_RADIUS_TYPE).
				setExpirationDruation(Constants.GEOFENCE_EXPIRATION).
				setCoordType(BDGeofence.COORD_TYPE_GCJ).
				build();
		
		mGeofenceClient.addBDGeofence(fence, new AddGeofenceListener());
	}
	
	private void removeGeofence() {
		List<String> fences = new ArrayList<String>();
		fences.add(Constants.GEOFENCE_ID);
		
		mGeofenceClient.removeBDGeofences(fences, new RemoveGeofenceListener());
	}
	
	/**
	 * ʵ�����Χ��������
	 *
	 */
	public class AddGeofenceListener implements OnAddBDGeofencesResultListener {

		@Override
		public void onAddBDGeofencesResult(int statusCode, String geofenceId) {
			try {
				if (statusCode == BDLocationStatusCodes.SUCCESS) {
					//������ʵ�ִ���Χ���ɹ��Ĺ����߼�
					
					Toast.makeText(GeofenceActivity.this, "Χ��" + geofenceId + "��ӳɹ�", Toast.LENGTH_SHORT).show();
					
					if (mGeofenceClient != null) {
						mGeofenceClient.start();//����ӵ���Χ���ɹ��󣬿�������Χ�����񣬶Ա��δ����ɹ����ѽ���ĵ���Χ��������ʵʱ������
					}
				}
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
	}
	
	/**
	 * ʵ��ɾ��Χ��������
	 *
	 */
	public class RemoveGeofenceListener implements OnRemoveBDGeofencesResultListener {

		@Override
		public void onRemoveBDGeofencesByRequestIdsResult(int statusCode, String[] geofenceIds) {
			if (statusCode == BDLocationStatusCodes.SUCCESS) {
				//������ʵ��ɾ��Χ���ɹ��Ĺ����߼�

				Toast.makeText(GeofenceActivity.this, "Χ��ɾ���ɹ�", Toast.LENGTH_SHORT).show();
			}
		}
	}
	
	/**
	 * ʵ�ֽ���Χ��������
	 *
	 */
	public class GeofenceTriggerListener implements OnGeofenceTriggerListener {

		@Override
		public void onGeofenceTrigger(String geofenceId) {
			//������ʵ�ֽ���Χ���Ĺ����߼�
			try {
				((Vibrator)GeofenceActivity.this.getApplication().getSystemService(Service.VIBRATOR_SERVICE)).vibrate(3000);
				Toast.makeText(GeofenceActivity.this, "�ѽ���Χ��" + geofenceId, Toast.LENGTH_SHORT).show();
			} catch (Exception e) {
				
			}
		}
	}
	
}
