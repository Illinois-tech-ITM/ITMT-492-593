package edu.iit.hawk.iit.greenmon.activities;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.speech.RecognizerIntent;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import edu.iit.hawk.iit.greenmon.R;
import edu.iit.hawk.iit.greenmon.dao.BoardDao;
import edu.iit.hawk.iit.greenmon.model.Board;

public class MainActivity extends Activity {
	private Button[] btBoards  = new Button[4];
	private String[] boardName = new String[4];
	private	static	final int VOICE_RECOGNITION_REQUEST_CODE = 1234;
	static final int check = 1111;
	private boolean finish = false;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		if( getIntent().getBooleanExtra("Exit me", false)){
			finish();
			return; // add this to prevent from doing unnecessary stuffs
		}
		
		Runnable myRunnable = new Runnable(){
		     public void run(){
		    	 BoardDao dao = new BoardDao();
		    	 List<Board> boards = dao.getBoards();
		    	 int i=0;
		    	 for(Board board : boards){
		    		 boardName[i] = board.getName();
		    		 i++;
		    	 }
		    	 finish = true;
		    	 
		     }
		};
		Thread thread = new Thread(myRunnable);
		thread.start();
		
		while(finish==false){}
		//Giving names to the boards
		this.btBoards[0] = (Button) findViewById(R.id.bt_board1);
		this.btBoards[1] = (Button) findViewById(R.id.bt_board2);
		this.btBoards[2] = (Button) findViewById(R.id.bt_board3);
		this.btBoards[3] = (Button) findViewById(R.id.bt_board4);
		
		
		for(int i=0;i<4;i++){
			btBoards[i].setText(boardName[i]);
		}
		

		/*this.boardName[0] = this.btBoards[0].getText().toString();
		this.boardName[1] = this.btBoards[1].getText().toString();
		this.boardName[2] = this.btBoards[2].getText().toString();
		this.boardName[3] = this.btBoards[3].getText().toString();*/

		Button voicebt = (Button) findViewById(R.id.bt_voice);

		voicebt.setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
				Intent i = new Intent(RecognizerIntent.ACTION_RECOGNIZE_SPEECH);
				i.putExtra(RecognizerIntent.EXTRA_LANGUAGE_MODEL,RecognizerIntent.LANGUAGE_MODEL_FREE_FORM);
				i.putExtra(RecognizerIntent.EXTRA_PROMPT, "Say the name of the board");
				startActivityForResult(i,check);
			}
		});

		for (int i=0;i<4;i++) {
			this.setOnClickListenerButtonBoard(this.btBoards[i], i);
		}
	}

		@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		//This function adds items to the menu
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		int id = item.getItemId();
		boolean handle = false;
		switch(id)
		{
			case R.id.action_exit:
				handle = true;
				finish();
				break;
			case R.id.action_settings:
				handle = true;
				Intent i = new Intent(MainActivity.this, Settings.class);
				startActivityForResult(i, 1);

				break;
			default:
				handle = super.onOptionsItemSelected(item);
		}
		return handle;
	}

	@Override
	protected	void onActivityResult(int requestCode, int resultCode, Intent data) {
		this.btBoards[0] = (Button) findViewById(R.id.bt_board1);
		this.btBoards[1] = (Button) findViewById(R.id.bt_board2);
		this.btBoards[2] = (Button) findViewById(R.id.bt_board3);
		this.btBoards[3] = (Button) findViewById(R.id.bt_board4);
		if(requestCode == check && resultCode == RESULT_OK)
		{
			HashMap<String, Integer> hash = new HashMap<String, Integer>();
			hash.put(this.btBoards[0].getText().toString(),1);
			hash.put(this.btBoards[1].getText().toString(),2);
			hash.put(this.btBoards[2].getText().toString(),3);
			hash.put(this.btBoards[3].getText().toString(),4);

			ArrayList<String> results = data.getStringArrayListExtra(RecognizerIntent.EXTRA_RESULTS);


			for(String result:results)
			{
				Integer board = hash.get(result);
				if(board!=null)
				{
					Intent i = new Intent(MainActivity.this, SensorsMenu.class);
					i.putExtra("boardNumber", board);
					i.putExtra("boardName", boardName[board-1]);
					startActivity(i);
				}
			}
		}
		
		if(requestCode == 1){
			this.recreate();
		}
		super.onActivityResult(requestCode, resultCode, data);
	} // end of activityOnResult method


	private void setOnClickListenerButtonBoard(Button bt, final int number){
		bt.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				Intent i = new Intent(MainActivity.this, SensorsMenu.class);
				i.putExtra("boardNumber", number + 1);
				i.putExtra("boardName", boardName[number]);
				startActivity(i);
			}
		});
	}
}
