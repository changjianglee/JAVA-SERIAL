package org.cat.dao;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import javax.swing.JOptionPane;

public class ReadAndInsertData {
	public static Connection conn = null;
	public static boolean getConnection(String ip,String port,String database,String username,String pwd){
		try {
			Class.forName("com.mysql.jdbc.Driver");
			String url = "jdbc:mysql://"+ip+":"+port+"/"+database;
			conn = DriverManager.getConnection(url, username, pwd);
			return true;
		} catch (ClassNotFoundException | SQLException e) {
			JOptionPane.showMessageDialog(null, "�������ݿ�ʧ��!");
			e.printStackTrace();
		}
		return false;
	}
	//�����¶Ⱥ�ʪ�ȵ�һ����¼
	public boolean insertTandH(double temp,double hum){
		String sql = "insert into tempandhum(temp,hum)values(?,?)";
		try {
			PreparedStatement pstmt = conn.prepareStatement(sql);
			pstmt.setDouble(1, temp);
			pstmt.setDouble(2, hum);
			int x = pstmt.executeUpdate();
			if(x == 1) return true;
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return false;
		
	}
	//��ȡ�Ƿ���ȵı�־
	public int getHitFlag(){
		String sql = "select * from isHit";
		try {
			PreparedStatement pstmt = conn.prepareStatement(sql);
			int isHit = 0;
			ResultSet rs = pstmt.executeQuery();
			while(rs.next()){
				isHit = rs.getInt(1);
			}
			return isHit;
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return 0;
	}
}
