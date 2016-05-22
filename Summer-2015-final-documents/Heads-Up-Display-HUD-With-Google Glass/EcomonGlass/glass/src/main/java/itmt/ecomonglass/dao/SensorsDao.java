package itmt.ecomonglass.dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import itmt.ecomonglass.model.Sensors;

public class SensorsDao {
	private Connection connection;
	private ResultSet rs;

	public SensorsDao(){
		this.connection = new ConnectionFactory().getConnection();
	}

	public Sensors getLastSensorsByBoard(int boardNumber) {
		String sql = "SELECT * FROM sensors WHERE boardNumber = ? ORDER BY timeStamp DESC LIMIT 1";
		Sensors sensors = null;
		try{
			PreparedStatement stmt = this.connection.prepareStatement(sql);
			stmt.setInt(1, boardNumber);
			this.rs = stmt.executeQuery();
			while (rs.next()) {
				Sensors actual = new Sensors();
				actual.setBoardNumber(rs.getInt("boardNumber"));
				actual.setHumidity(rs.getDouble("humidity"));
				actual.setTemperature(rs.getDouble("temperature"));
				actual.setLuminosity(rs.getDouble("luminosity"));
				actual.setTimeStamp(rs.getDate("timeStamp"));
				sensors = actual;
			}
			this.rs.close();
			this.connection.close();
		} catch(SQLException e) {
			System.out.println(e);
		}
		return sensors;
	}

	public List<Double> getLastSevenByBoard(int boardNumber, String sensor){
		String sql = "SELECT " + sensor + " FROM sensors WHERE boardNumber = ? ORDER BY timeStamp ASC LIMIT 7";
		List<Double> sensorList = new ArrayList<Double>();
		try{
			PreparedStatement stmt = this.connection.prepareStatement(sql);
			stmt.setInt(1, boardNumber);
			this.rs = stmt.executeQuery();
			while (rs.next()) {
				Double sensorValue = Double.valueOf(rs.getDouble(sensor));
				sensorList.add(sensorValue);
			}
			this.rs.close();
			this.connection.close();
		} catch(SQLException e) {
			System.out.println(e);
		}
		return sensorList;
	}
}
