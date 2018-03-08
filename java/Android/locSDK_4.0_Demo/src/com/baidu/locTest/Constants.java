package com.baidu.locTest;

import com.baidu.location.BDGeofence;

/**
 *�˴��Կ��ƴ���Ϊ��������һ������Χ������ز�������
 * @param GEOFENCE_ID 			: 	Χ��ID
 * @param GEOFENCE_COORD_TYPE 	:	��������
 * @param GEOFENCE_LONGTITUDE	: 	���ĵ㾭��
 * @param GEOFENCE_LATITUDE		:	���ĵ�γ��
 * @param GEOFENCE_RADIUS_TYPE	:	���ĵ�뾶����
 * @param GEOFENCE_EXPIRATION	:	����Χ����Чʱ��
 */
public class Constants {
	public static final String GEOFENCE_ID = "���ƴ���";
	public static final String GEOFENCE_COORD_TYPE = BDGeofence.COORD_TYPE_GCJ;
	public static final double GEOFENCE_LONGTITUDE = 116.30677;
	public static final double GEOFENCE_LATITUDE = 40.04173;
	public static final int GEOFENCE_RADIUS_TYPE = 1;
	public static final long GEOFENCE_EXPIRATION = 10L * (3600 * 1000);//Ĭ��10Сʱ
	
	public static final String MAPSRV_ADDR = "192.168.200.15";
	public static final int MAPSRV_PORT = 7092;
}
