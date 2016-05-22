package edu.iit.hawk.iit.greenmon.activities;

import java.util.List;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import edu.iit.hawk.iit.greenmon.R;
import edu.iit.hawk.iit.greenmon.dao.BoardDao;
import edu.iit.hawk.iit.greenmon.model.Board;

public class Settings extends Activity {
	private String[] boardName = new String[4];
	private EditText texts[] = new EditText[4];
	private Button submit;
	private boolean finish = false;
	
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_settings);

        this.texts[0] = (EditText)findViewById(R.id.tb_board1Name);
        this.texts[1] = (EditText)findViewById(R.id.tb_board2Name);
        this.texts[2] = (EditText)findViewById(R.id.tb_board3Name);
        this.texts[3] = (EditText)findViewById(R.id.tb_board4Name);
        this.submit = (Button) findViewById(R.id.bt_submit);
       
        
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
		for(int i=0;i<4;i++){
			texts[i].setText(boardName[i]);
		}
		

        submit.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
            Runnable myRunnable = new Runnable(){
       		     public void run(){
       		    	 BoardDao dao = new BoardDao();
       		    	 int i=1;
       		    	 for(EditText text : texts){
       		    		 dao.changeNameById(new Board(i,text.getText().toString()));
       		    		 i++;
       		    	 }
       		    	 finish = true;
       		     }
       		};
       		Thread thread = new Thread(myRunnable);
       		thread.start();
       		while(finish == false){}
            onBackPressed();
            }
        });
        
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu_settings, menu);
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
}

