package jdbc_mysql;

import java.sql.*;

public class JdbcMysql {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		String url="jdbc:mysql://192.168.200.15:3306/wifigeoloc";
		String user="root", passwd="Szj0306";
		String sql="select id,lat,lon,geoloc,score,bandwidth from wifitbl where score between 0 and 0.1";
		try {
			try {
				Class.forName("com.mysql.jdbc.Driver");
			} catch (ClassNotFoundException e) {
				e.printStackTrace();
			}
			Connection conn=DriverManager.getConnection(url, user, passwd);
			// 把事务设为不自动提交
			conn.setAutoCommit(false);
			// 3.创建sql对象(Statement / PreparedStatement /CallableStatement)
			Statement stmt=conn.createStatement();
			ResultSet rs=stmt.executeQuery(sql);
			while (rs.next()) {
				System.out.println(rs.getString("id") + " " + rs.getString("lat") +
						" " + rs.getString("lon") + " " + rs.getString("geoloc") +
						" " + rs.getString("score") + " " + rs.getString("bandwidth"));
			}
			// 提交所有事务
			conn.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		}
	}
}
