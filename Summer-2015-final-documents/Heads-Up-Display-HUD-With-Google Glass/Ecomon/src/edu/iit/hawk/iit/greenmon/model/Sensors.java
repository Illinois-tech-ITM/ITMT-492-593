package edu.iit.hawk.iit.greenmon.model;

import java.sql.Date;

public class Sensors {
	private int boardNumber;
	private double temperature;
	private double humidity;
	private double luminosity;
	private Date timeStamp;

	public int getBoardNumber() {
		return boardNumber;
	}

	public void setBoardNumber(int boardNumber) {
		this.boardNumber = boardNumber;
	}

	public double getTemperature() {
		return temperature;
	}

	public void setTemperature(double temperature) {
		this.temperature = temperature;
	}

	public double getHumidity() {
		return humidity;
	}

	public void setHumidity(double humidity) {
		this.humidity = humidity;
	}

	public double getLuminosity() {
		return luminosity;
	}

	public void setLuminosity(double luminosity) {
		this.luminosity = luminosity;
	}

	public Date getTimeStamp() {
		return timeStamp;
	}

	public void setTimeStamp(Date timeStamp) {
		this.timeStamp = timeStamp;
	}
	
	
}
