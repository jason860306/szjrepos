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
		
		//当前系统默认时区的时间：
		Calendar calendar=new GregorianCalendar();
		System.out.print("时区："+calendar.getTimeZone().getID()+"  ");
		System.out.println("时间："+calendar.get(Calendar.HOUR_OF_DAY)+":"+calendar.get(Calendar.MINUTE));
		//美国洛杉矶时区
		TimeZone tz=TimeZone.getTimeZone("America/Los_Angeles");
		//时区转换
		calendar.setTimeZone(tz);
		System.out.print("时区："+calendar.getTimeZone().getID()+"  ");
		System.out.println("时间："+calendar.get(Calendar.HOUR_OF_DAY)+":"+calendar.get(Calendar.MINUTE));
		Date time=new Date();
		
		//1、取得本地时间：
		java.util.Calendar cal = java.util.Calendar.getInstance();

		//2、取得时间偏移量：
		int zoneOffset = cal.get(java.util.Calendar.ZONE_OFFSET);

		//3、取得夏令时差：
		int dstOffset = cal.get(java.util.Calendar.DST_OFFSET);

		//4、从本地时间里扣除这些差量，即可以取得UTC时间：
		cal.add(java.util.Calendar.MILLISECOND, -(zoneOffset + dstOffset));

		//之后调用cal.get(int x)或cal.getTimeInMillis()方法所取得的时间即是UTC标准时间。
		System.out.println("UTC:"+new Date(cal.getTimeInMillis()));
		
		Calendar calendar1 = Calendar.getInstance();
		TimeZone tztz = TimeZone.getTimeZone("GMT");       
		calendar1.setTimeZone(tztz);
		System.out.println(calendar.getTime());
		System.out.println(calendar.getTimeInMillis()); 
		

	}

}
