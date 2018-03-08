package com.amapv2.apis.overlay;

import java.util.Arrays;
import java.util.List;

import android.app.Activity;
import android.graphics.Color;
import android.os.Bundle;
import android.widget.SeekBar;
import android.widget.SeekBar.OnSeekBarChangeListener;

import com.amap.api.maps.AMap;
import com.amap.api.maps.CameraUpdateFactory;
import com.amap.api.maps.MapView;
import com.amap.api.maps.model.LatLng;
import com.amap.api.maps.model.Polygon;
import com.amap.api.maps.model.PolygonOptions;
import com.amapv2.apis.R;
import com.amapv2.apis.util.Constants;

/**
 * AMapV2地图中简单介绍一些Polygon的用法.
 */
public class PolygonActivity extends Activity implements
		OnSeekBarChangeListener {
	private static final int WIDTH_MAX = 50;
	private static final int HUE_MAX = 360;
	private static final int ALPHA_MAX = 255;
	private AMap aMap;
	private MapView mapView;
	private Polygon polygon;
	private SeekBar mColorBar;
	private SeekBar mAlphaBar;
	private SeekBar mWidthBar;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.polygon_activity);
		mapView = (MapView) findViewById(R.id.map);
		mapView.onCreate(savedInstanceState);// 此方法必须重写
		init();
	}

	/**
	 * 初始化AMap对象
	 */
	private void init() {
		mColorBar = (SeekBar) findViewById(R.id.hueSeekBar);
		mColorBar.setMax(HUE_MAX);
		mColorBar.setProgress(0);

		mAlphaBar = (SeekBar) findViewById(R.id.alphaSeekBar);
		mAlphaBar.setMax(ALPHA_MAX);
		mAlphaBar.setProgress(0);

		mWidthBar = (SeekBar) findViewById(R.id.widthSeekBar);
		mWidthBar.setMax(WIDTH_MAX);
		mWidthBar.setProgress(0);
		if (aMap == null) {
			aMap = mapView.getMap();
			setUpMap();
		}
	}

	private void setUpMap() {
		mColorBar.setOnSeekBarChangeListener(this);
		mAlphaBar.setOnSeekBarChangeListener(this);
		mWidthBar.setOnSeekBarChangeListener(this);
		aMap.moveCamera(CameraUpdateFactory.newLatLngZoom(Constants.BEIJING, 5));// 设置指定的可视区域地图
		// 绘制一个长方形
		aMap.addPolygon(new PolygonOptions()
				.addAll(createRectangle(Constants.SHANGHAI, 1, 1))
				.fillColor(Color.LTGRAY).strokeColor(Color.RED).strokeWidth(1));
		PolygonOptions options = new PolygonOptions();
		int numPoints = 400;
		float semiHorizontalAxis = 5f;
		float semiVerticalAxis = 2.5f;
		double phase = 2 * Math.PI / numPoints;
		for (int i = 0; i <= numPoints; i++) {
			options.add(new LatLng(Constants.BEIJING.latitude
					+ semiVerticalAxis * Math.sin(i * phase),
					Constants.BEIJING.longitude + semiHorizontalAxis
							* Math.cos(i * phase)));
		}
		// 绘制一个椭圆
		polygon = aMap.addPolygon(options.strokeWidth(4f)
				.strokeColor(Color.BLACK).fillColor(Color.LTGRAY));
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
	 * 生成一个长方形的四个坐标点
	 */
	private List<LatLng> createRectangle(LatLng center, double halfWidth,
			double halfHeight) {
		return Arrays.asList(new LatLng(center.latitude - halfHeight,
				center.longitude - halfWidth), new LatLng(center.latitude
				- halfHeight, center.longitude + halfWidth), new LatLng(
				center.latitude + halfHeight, center.longitude + halfWidth),
				new LatLng(center.latitude + halfHeight, center.longitude
						- halfWidth));
	}

	@Override
	public void onStopTrackingTouch(SeekBar seekBar) {
	}

	@Override
	public void onStartTrackingTouch(SeekBar seekBar) {
	}

	/**
	 * Polygon中对填充颜色，透明度，画笔宽度设置响应事件
	 */
	@Override
	public void onProgressChanged(SeekBar seekBar, int progress,
			boolean fromUser) {
		if (polygon == null) {
			return;
		}
		if (seekBar == mColorBar) {
			polygon.setFillColor(Color.HSVToColor(
					Color.alpha(polygon.getFillColor()), new float[] {
							progress, 1, 1 }));
		} else if (seekBar == mAlphaBar) {
			int prevColor = polygon.getFillColor();
			polygon.setFillColor(Color.argb(progress, Color.red(prevColor),
					Color.green(prevColor), Color.blue(prevColor)));
		} else if (seekBar == mWidthBar) {
			polygon.setStrokeWidth(progress);
		}
	}
}
