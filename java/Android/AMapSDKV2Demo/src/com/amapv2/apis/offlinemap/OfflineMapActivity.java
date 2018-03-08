package com.amapv2.apis.offlinemap;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.os.Environment;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;

import com.amap.api.maps.AMap;
import com.amap.api.maps.MapView;
import com.amap.api.maps.MapsInitializer;
import com.amap.api.maps.offlinemap.OfflineMapManager;
import com.amap.api.maps.offlinemap.OfflineMapManager.OfflineMapDownloadListener;
import com.amap.api.maps.offlinemap.OfflineMapStatus;
import com.amapv2.apis.R;
import com.amapv2.apis.util.AMapUtil;
import com.amapv2.apis.util.ToastUtil;

/**
 * AMapV2地图中简单介绍离线地图下载
 */
public class OfflineMapActivity extends Activity implements
		OfflineMapDownloadListener {
	private OfflineMapManager amapManager = null;
	private EditText cityName;
	private TextView statusText;
	private AMap aMap;
	private MapView mapView;
	private boolean update = false;

	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		// 设置应用单独的地图存储目录，在下载离线地图或初始化地图时设置
		MapsInitializer.sdcardDir = getSdCacheDir(this);
		setContentView(R.layout.offlinemap_activity);
		mapView = (MapView) findViewById(R.id.map);
		mapView.onCreate(savedInstanceState);// 此方法必须重写
		init();

	}

	/**
	 * 初始化AMap对象
	 */
	private void init() {
		if (aMap == null) {
			aMap = mapView.getMap();
		}
		amapManager = new OfflineMapManager(this, this);
		cityName = (EditText) findViewById(R.id.cityname);
		statusText = (TextView) findViewById(R.id.status);
	}

	/**
	 * 方法必须重写
	 */
	@Override
	protected void onResume() {
		super.onResume();
		mapView.onResume();
	}

	/**
	 * 方法必须重写
	 */
	@Override
	protected void onPause() {
		super.onPause();
		mapView.onPause();
	}

	/**
	 * 方法必须重写
	 */
	@Override
	protected void onSaveInstanceState(Bundle outState) {
		super.onSaveInstanceState(outState);
		mapView.onSaveInstanceState(outState);
	}

	/**
	 * 方法必须重写
	 */
	@Override
	protected void onDestroy() {
		super.onDestroy();
		mapView.onDestroy();
	}

	/**
	 * 点击开始按钮响应事件回调
	 */
	public void startButton(View view) {
		String city = AMapUtil.checkEditText(cityName);
		if ("".equals(city)) {
			ToastUtil.show(OfflineMapActivity.this, "请输入城市名字");
			return;
		} else {
			downloadMap(city);
		}
	}

	/**
	 * 开始下载离线地图
	 */
	private void downloadMap(String city) {
		boolean start = false;
		try {
			start = amapManager.downloadByCityName(city);
			if (!start) {
				ToastUtil.show(this, "下载离线地图数据失败");
			} else {
				ToastUtil.show(this, "开始下载离线地图数据");
			}
		} catch (Exception e) {
			e.printStackTrace();
			ToastUtil.show(this, "开启下载失败，请检查网络是否开启！");
		}

	}

	/**
	 * 点击暂停按钮响应事件回调
	 */
	public void pauseButton(View view) {
		amapManager.pause();
		ToastUtil.show(this, "暂停下载离线地图数据");
	}

	/**
	 * 点击停止按钮响应事件回调
	 */
	public void stopButton(View view) {
		amapManager.stop();
		ToastUtil.show(this, "停止下载离线地图数据");
	}

	/**
	 * 点击删除按钮响应事件回调
	 */
	public void deleteButton(View view) {
		String city = AMapUtil.checkEditText(cityName);
		if ("".equals(city)) {
			ToastUtil.show(OfflineMapActivity.this, "请输入城市名字");
			return;
		} else {
			amapManager.remove(city);
			ToastUtil.show(this, "删除离线地图数据");
		}

	}

	/**
	 * 点击更新按钮响应事件回调
	 */
	public void updateButton(View view) {
		final String city = AMapUtil.checkEditText(cityName);
		if ("".equals(city)) {
			ToastUtil.show(OfflineMapActivity.this, "请输入城市名字");
			return;
		} else {
			new Thread(new Runnable() {
				@Override
				public void run() {
					try {
						update = amapManager.updateOfflineCityByName(city);
						runOnUiThread(new Runnable() {
							@Override
							public void run() {
								if (update) {
									ToastUtil.show(OfflineMapActivity.this,
											city + "离线数据有更新");
									downloadMap(city);
								} else {
									ToastUtil.show(OfflineMapActivity.this,
											city + "离线数据已经是最新的了");
								}

							}
						});
					} catch (Exception e) {
						e.printStackTrace();
					}
				}
			}).start();
		}
	}

	/**
	 * 获取map 缓存和读取目录
	 * 
	 * @param context
	 * @return
	 */
	private String getSdCacheDir(Context context) {
		if (Environment.getExternalStorageState().equals(
				Environment.MEDIA_MOUNTED)) {
			java.io.File fExternalStorageDirectory = Environment
					.getExternalStorageDirectory();
			java.io.File autonaviDir = new java.io.File(
					fExternalStorageDirectory, "Company");
			boolean result = false;
			if (!autonaviDir.exists()) {
				result = autonaviDir.mkdir();
			}
			java.io.File minimapDir = new java.io.File(autonaviDir, "Name");
			if (!minimapDir.exists()) {
				result = minimapDir.mkdir();
			}
			return minimapDir.toString() + "/";
		} else {
			return null;
		}
	}

	@Override
	public void onDownload(int status, int completeCode, String arg2) {
		switch (status) {
		case OfflineMapStatus.SUCCESS:
			statusText.setText("下载成功");
			break;
		case OfflineMapStatus.LOADING:
			statusText.setText("正在下载," + "已完成：" + completeCode + "%" + arg2);
			break;
		case OfflineMapStatus.UNZIP:
			statusText.setText("正在解压");
			break;
		case OfflineMapStatus.WAITING:
			statusText.setText("正在等待");
			break;
		case OfflineMapStatus.PAUSE:
			statusText.setText("暂停下载");
			break;
		case OfflineMapStatus.STOP:
			statusText.setText("停止下载");
			break;
		case OfflineMapStatus.ERROR:
			statusText.setText("下载错误");
			break;
		default:
			break;
		}
	}
}
