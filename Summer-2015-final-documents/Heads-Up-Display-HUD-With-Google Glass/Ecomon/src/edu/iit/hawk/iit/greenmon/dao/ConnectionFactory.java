package edu.iit.hawk.iit.greenmon.dao;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class ConnectionFactory {
	public Connection getConnection() {
	     try {
	    	 Class.forName("com.mysql.jdbc.Driver");
	         return DriverManager.getConnection("jdbc:mysql://64.131.111.99:3306/db1", "user", "abc123");
	     } catch (SQLException e) {
	         throw new RuntimeException(e);
	     } catch (ClassNotFoundException e) {
	    	  throw new RuntimeException(e);
		}
	 }
}
