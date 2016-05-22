package edu.iit.hawk.iit.greenmon.activities;

import java.util.List;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import edu.iit.hawk.iit.greenmon.R;
import edu.iit.hawk.iit.greenmon.dao.SensorsDao;
import edu.iit.hawk.iit.greenmon.model.Graph;

public class DetailsActivity extends Activity {
	private String sensor;
	private String board;
	private int boardNumber;
	private float[] values;
	private String[] horlabels = new String[] { "", "6 days ago","5 days ago","4 days ago","3 days ago", "2 days ago", "1 day ago", "today", ""};
	private String[] verlabels = new String[] {"", "", "", ""};
	private boolean verify = false;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_details);
		
		
		this.sensor = getIntent().getStringExtra("sensor");
		this.board = getIntent().getStringExtra("boardName");
		this.boardNumber = getIntent().getIntExtra("boardNumber", -1);
		
		
		Runnable myRunnable = new Runnable(){
		     public void run(){
		    	 SensorsDao dao = new SensorsDao();
		    	 List<Double> lastSensorsByBoard = dao.getLastSevenByBoard(boardNumber, sensor);
		    	 int i=1;
		    	 values = new float[lastSensorsByBoard.size()+2];
		    	 values[0] = 0;
		    	 for (Double value : lastSensorsByBoard){
		    		 values[i] = value.floatValue();
		    		 i++;
		    	 }
		    	 values[i] = 0;
		    	 verify = true;
		     }
		};
		Thread thread = new Thread(myRunnable);
		thread.start();
		
		while(verify == false){}
		
		Graph graphView = new Graph(this, values, String.format("%s - %s", board, sensor), horlabels, verlabels, Graph.LINE);
 		setContentView(graphView);
		
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.details, menu);
		return true;
	}

//	@Override
//	public boolean onOptionsItemSelected(MenuItem item) {
//		// Handle action bar item clicks here. The action bar will
//		// automatically handle clicks on the Home/Up button, so long
//		// as you specify a parent activity in AndroidManifest.xml.
//		int id = item.getItemId();
//		if (id == R.id.action_settings) {
//			return true;
//		}
//		return super.onOptionsItemSelected(item);
//	}
	
	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle action bar item clicks here. The action bar will
		// automatically handle clicks on the Home/Up button, so long
		// as you specify a parent activity in AndroidManifest.xml.
		int id = item.getItemId();
		boolean handle = false;
		switch (id) {
			case R.id.action_exit:
				handle = true;
				Intent intent = new Intent(this, MainActivity.class);
				intent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
				intent.putExtra("Exit me", true);
				startActivity(intent);
				finish();
				break;
			default:
				handle = super.onOptionsItemSelected(item);
		}
		return handle;
	}
}
