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
		
		//初始化GeofenceClient
		mGeofenceClient = ((Location)getApplication()).mGeofenceClient;
		//注册地理围栏进入的监听器
		mGeofenceClient.registerGeofenceTriggerListener(new GeofenceTriggerListener());
		//开启地理围栏服务
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
	 * 实现添加围栏监听器
	 *
	 */
	public class AddGeofenceListener implements OnAddBDGeofencesResultListener {

		@Override
		public void onAddBDGeofencesResult(int statusCode, String geofenceId) {
			try {
				if (statusCode == BDLocationStatusCodes.SUCCESS) {
					//开发者实现创建围栏成功的功能逻辑
					
					Toast.makeText(GeofenceActivity.this, "围栏" + geofenceId + "添加成功", Toast.LENGTH_SHORT).show();
					
					if (mGeofenceClient != null) {
						mGeofenceClient.start();//在添加地理围栏成功后，开启地理围栏服务，对本次创建成功且已进入的地理围栏，可以实时的提醒
					}
				}
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
	}
	
	/**
	 * 实现删除围栏监听器
	 *
	 */
	public class RemoveGeofenceListener implements OnRemoveBDGeofencesResultListener {

		@Override
		public void onRemoveBDGeofencesByRequestIdsResult(int statusCode, String[] geofenceIds) {
			if (statusCode == BDLocationStatusCodes.SUCCESS) {
				//开发者实现删除围栏成功的功能逻辑

				Toast.makeText(GeofenceActivity.this, "围栏删除成功", Toast.LENGTH_SHORT).show();
			}
		}
	}
	
	/**
	 * 实现进行围栏监听器
	 *
	 */
	public class GeofenceTriggerListener implements OnGeofenceTriggerListener {

		@Override
		public void onGeofenceTrigger(String geofenceId) {
			//开发者实现进入围栏的功能逻辑
			try {
				((Vibrator)GeofenceActivity.this.getApplication().getSystemService(Service.VIBRATOR_SERVICE)).vibrate(3000);
				Toast.makeText(GeofenceActivity.this, "已进入围栏" + geofenceId, Toast.LENGTH_SHORT).show();
			} catch (Exception e) {
				
			}
		}
	}
	
}
