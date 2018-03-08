package jdbc_mysql;

import java.sql.*;

public class JdbcMysql {
	public static void main(String[] args) {
		try {
			// 1加载驱动
			Class.forName("com.mysql.jdbc.Driver");
			// DriverManager.registerDriver(new OracleDriver());
			// 2得到连接
			Connection conn = DriverManager
					.getConnection("jdbc:mysql://192.168.200.15:3306/wifigeiloc",
							"szj0306", "Szj0306");

			// 把事务设为不自动提交
			conn.setAutoCommit(false);
			// 3.创建sql对象(Statement / PreparedStatement /CallableStatement)
			Statement statement = conn.createStatement();

			// 提交所有事务
			conn.commit();

		} catch (Exception e) {
			// roll back

		} finally {
			// close conn
		}

	}

}
