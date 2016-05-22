package edu.iit.hawk.iit.greenmon.model;

public class Board {
	private int id;
	private String name;
	
//	public Board(){
//		
//	}
	
	public Board(int id, String name){
		this.id = id;
		this.name = name;
	}
	
	public int getId() {
		return id;
	}
	public void setId(int id) {
		this.id = id;
	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	
	
}
