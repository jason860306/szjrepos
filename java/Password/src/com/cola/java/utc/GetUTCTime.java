package com.cola.java.utc;

import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;
import java.util.TimeZone;

public class GetUTCTime {

	/**
	 * @param args
	 */
	public static void main(String[] args) {

		SimpleDateFormat foo = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
		System.out.println("foo:"+foo.format(new Date()));
		
		Calendar gc = GregorianCalendar.getInstance();
		System.out.println("gc.getTime():"+gc.getTime());
		System.out.println("gc.getTimeInMillis():"+new Date(gc.getTimeInMillis()));
		
		//��ǰϵͳĬ��ʱ����ʱ�䣺
		Calendar calendar=new GregorianCalendar();
		System.out.print("ʱ����"+calendar.getTimeZone().getID()+"  ");
		System.out.println("ʱ�䣺"+calendar.get(Calendar.HOUR_OF_DAY)+":"+calendar.get(Calendar.MINUTE));
		//������ɼ�ʱ��
		TimeZone tz=TimeZone.getTimeZone("America/Los_Angeles");
		//ʱ��ת��
		calendar.setTimeZone(tz);
		System.out.print("ʱ����"+calendar.getTimeZone().getID()+"  ");
		System.out.println("ʱ�䣺"+calendar.get(Calendar.HOUR_OF_DAY)+":"+calendar.get(Calendar.MINUTE));
		Date time=new Date();
		
		//1��ȡ�ñ���ʱ�䣺
		java.util.Calendar cal = java.util.Calendar.getInstance();

		//2��ȡ��ʱ��ƫ������
		int zoneOffset = cal.get(java.util.Calendar.ZONE_OFFSET);

		//3��ȡ������ʱ�
		int dstOffset = cal.get(java.util.Calendar.DST_OFFSET);

		//4���ӱ���ʱ����۳���Щ������������ȡ��UTCʱ�䣺
		cal.add(java.util.Calendar.MILLISECOND, -(zoneOffset + dstOffset));

		//֮�����cal.get(int x)��cal.getTimeInMillis()������ȡ�õ�ʱ�伴��UTC��׼ʱ�䡣
		System.out.println("UTC:"+new Date(cal.getTimeInMillis()));
		
		Calendar calendar1 = Calendar.getInstance();
		TimeZone tztz = TimeZone.getTimeZone("GMT");       
		calendar1.setTimeZone(tztz);
		System.out.println(calendar.getTime());
		System.out.println(calendar.getTimeInMillis()); 
		

	}

}
