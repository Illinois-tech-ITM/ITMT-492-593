package itmt.ecomonglass.dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import itmt.ecomonglass.model.Board;

public class BoardDao {
	private Connection connection;
	private ResultSet rs;
	
	public BoardDao(){
		this.connection = new ConnectionFactory().getConnection();
	}
	
	public List<Board> getBoards(){
		 String sql = "SELECT * FROM boardName";
		 List<Board> list = new ArrayList<Board>();
		 try{
			 PreparedStatement stmt = this.connection.prepareStatement(sql);
			 this.rs = stmt.executeQuery();
			 while (rs.next()) {
				 Board actual = new Board(rs.getInt("id"), rs.getString("name"));
				 list.add(actual);
			}
			this.rs.close();
			this.connection.close();
		 } catch(SQLException e) {
		    System.out.println(e);
		}
		return list;
	}
	
	public void changeNameById(Board board){
		String sql = "UPDATE boardName SET name= ? WHERE id = ?";
		try{
			 PreparedStatement stmt = this.connection.prepareStatement(sql);
			 stmt.setString(1, board.getName());
			 stmt.setInt(2, board.getId());
			 stmt.executeUpdate();
		} catch (SQLException e){
			System.out.println(e);
		}
	}
}
