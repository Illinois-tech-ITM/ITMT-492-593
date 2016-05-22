package itmt.ecomonglass.dao;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class ConnectionFactory {
	public Connection getConnection() {
	     try {
	    	 Class.forName("com.mysql.jdbc.Driver").newInstance();
	         return DriverManager.getConnection("jdbc:mysql://64.131.111.99:3306/db1", "user", "abc123");
	     } catch (SQLException e) {
	         throw new RuntimeException(e);
	     } catch (ClassNotFoundException e) {
	    	  throw new RuntimeException(e);
		} catch (InstantiationException e) {
			 e.printStackTrace();
			 throw new RuntimeException(e);
		 } catch (IllegalAccessException e) {
			 e.printStackTrace();
			 throw new RuntimeException(e);
		 }
	}
}
