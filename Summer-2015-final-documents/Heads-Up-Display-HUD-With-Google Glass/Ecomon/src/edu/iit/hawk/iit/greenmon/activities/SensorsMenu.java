package edu.iit.hawk.iit.greenmon.activities;

import java.util.ArrayList;
import java.util.HashMap;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.speech.RecognizerIntent;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;
import edu.iit.hawk.iit.greenmon.R;
import edu.iit.hawk.iit.greenmon.dao.SensorsDao;
import edu.iit.hawk.iit.greenmon.model.Sensors;

public class SensorsMenu extends Activity {
	private int		 	boardNumber;
	private String	 	boardName;
	private Sensors 	sensors;
	
	private TextView 	txtBoardName;
	private TextView 	txtHumidity;
	private TextView 	txtLuminosity;
	private TextView 	txtTemperature;
	
	static final int check = 1111;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_sensors_menu);
		
		Button voicebt = (Button) findViewById(R.id.bt_voice);
		voicebt.setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
				Intent i = new Intent(RecognizerIntent.ACTION_RECOGNIZE_SPEECH);
				i.putExtra(RecognizerIntent.EXTRA_LANGUAGE_MODEL,RecognizerIntent.LANGUAGE_MODEL_FREE_FORM);
				i.putExtra(RecognizerIntent.EXTRA_PROMPT, "Say the name of the sensor");
				startActivityForResult(i,check);
			}
		});
		
		this.txtBoardName = (TextView) findViewById(R.id.BoardName);
		this.txtHumidity = (TextView) findViewById(R.id.tx_sensor1Info);
		this.txtLuminosity = (TextView) findViewById(R.id.tx_sensor2Info);
		this.txtTemperature = (TextView) findViewById(R.id.tx_sensor3Info);
		
		this.boardNumber = getIntent().getIntExtra("boardNumber", -1);
		
		if(boardNumber!=-1){
			this.boardName = getIntent().getStringExtra("boardName");
			this.txtBoardName.setText(this.boardName);
			Runnable myRunnable = new Runnable(){
			     public void run(){
			    	 SensorsDao dao = new SensorsDao();
			    	 sensors = dao.getLastSensorsByBoard(boardNumber);
			    	 setViews();
			     }
			};

			Thread thread = new Thread(myRunnable);
			thread.start();
		}
		
		this.txtHumidity.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				Intent i = new Intent(SensorsMenu.this, DetailsActivity.class);
				i.putExtra("boardNumber",boardNumber);
				i.putExtra("boardName", boardName);
				i.putExtra("sensor", "humidity");
				startActivity(i);
			}
		});
		
		this.txtTemperature.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				Intent i = new Intent(SensorsMenu.this, DetailsActivity.class);
				i.putExtra("boardNumber",boardNumber);
				i.putExtra("boardName", boardName);
				i.putExtra("sensor", "temperature");
				startActivity(i);
			}
		});
		
		
		this.txtLuminosity.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				Intent i = new Intent(SensorsMenu.this, DetailsActivity.class);
				i.putExtra("boardNumber",boardNumber);
				i.putExtra("boardName", boardName);
				i.putExtra("sensor", "luminosity");
				startActivity(i);
			}
		});
	}
	
	private void setViews(){
		if(sensors!= null){
			runOnUiThread(new Runnable() {
				@Override
				public void run() {
					txtHumidity.setText( String.format( "%f", sensors.getHumidity() ) );
					txtLuminosity.setText( String.format( "%f", sensors.getLuminosity() ) );
					txtTemperature.setText( String.format( "%f", sensors.getTemperature() ) );
				}
			});
		}
	}
	
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.sensors_menu, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle action bar item clicks here. The action bar will
		// automatically handle clicks on the Home/Up button, so long
		// as you specify a parent activity in AndroidManifest.xml.
		int id = item.getItemId();
		boolean handle = false;
		switch(id)
		{
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
	@Override
	protected	void onActivityResult(int requestCode, int resultCode, Intent data) {
		TextView lb_humidity = (TextView) findViewById(R.id.humidityLabel);
		TextView lb_luminosity = (TextView) findViewById(R.id.luminosityLabel);
		TextView lb_temperature = (TextView) findViewById(R.id.temperatureLabel);
		boolean c = false;
		if(requestCode == check && resultCode == RESULT_OK)
		{
			HashMap<String, Integer> hash = new HashMap<String, Integer>();
			hash.put(lb_humidity.getText().toString(),1);
			hash.put(lb_luminosity.getText().toString(),2);
			hash.put(lb_temperature.getText().toString(),3);

			ArrayList<String> results = data.getStringArrayListExtra(RecognizerIntent.EXTRA_RESULTS);

			for(String result:results)
			{
				Integer board = hash.get(result);
				if(board!=null)
				{
					switch (board) {
						case 1:
						{
							c = true;
							Intent i = new Intent(SensorsMenu.this, DetailsActivity.class);
							i.putExtra("boardNumber", boardNumber);
							i.putExtra("boardName", boardName);
							i.putExtra("sensor", "humidity");
							startActivity(i);
							break;
						}
						case 2:
						{
							c = true;
							Intent i = new Intent(SensorsMenu.this, DetailsActivity.class);
							i.putExtra("boardNumber", boardNumber);
							i.putExtra("boardName", boardName);
							i.putExtra("sensor", "luminosity");
							startActivity(i);
							break;
						}
						case 3:
						{
							c = true;
							Intent i = new Intent(SensorsMenu.this, DetailsActivity.class);
							i.putExtra("boardNumber", boardNumber);
							i.putExtra("boardName", boardName);
							i.putExtra("sensor", "temperature");
							startActivity(i);
							break;
						}
					}
				}
			}
			if (!c)
			{
				Toast toast = Toast.makeText(getApplicationContext(),"No sensors were found with this name", Toast.LENGTH_SHORT);
				toast.show();
			}
		}
		super.onActivityResult(requestCode, resultCode, data);
	} // end of activityOnResult method
}
