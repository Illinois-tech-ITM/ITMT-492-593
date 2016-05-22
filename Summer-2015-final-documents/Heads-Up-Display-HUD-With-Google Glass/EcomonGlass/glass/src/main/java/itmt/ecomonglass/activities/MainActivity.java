package itmt.ecomonglass.activities;

import com.google.android.glass.media.Sounds;
import com.google.android.glass.widget.CardBuilder;
import com.google.android.glass.widget.CardScrollAdapter;
import com.google.android.glass.widget.CardScrollView;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.media.AudioManager;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;

import java.util.ArrayList;
import java.util.List;

import itmt.ecomonglass.R;
import itmt.ecomonglass.dao.BoardDao;
import itmt.ecomonglass.dao.SensorsDao;
import itmt.ecomonglass.model.Board;

public class MainActivity extends Activity {

    private String[] boardsName;
    private CardScrollView mCardScroller;
    private List<CardBuilder> mCards;
    private CardScrollView mCardScrollView;
    private ExampleCardScrollAdapter mAdapter;
    private boolean finish = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        createCards();

        mCardScrollView = new CardScrollView(this);
        mAdapter = new ExampleCardScrollAdapter();
        mCardScrollView.setAdapter(mAdapter);
        mCardScrollView.activate();
        setContentView(mCardScrollView);

        setupClickListener();
        Runnable myRunnable = new Runnable(){
            public void run(){
                BoardDao dao = new BoardDao();
                List<Board> boards = dao.getBoards();
                for( int i=0;i<boards.size();i++){
                    mCards.get(i).setText(boards.get(i).getName());
                }
                finish = true;
            }
        };
        Thread thread = new Thread(myRunnable);
        thread.start();
        while(finish == false) {}
        mAdapter.notifyDataSetChanged();
    }

    private void createCards() {
        mCards = new ArrayList<CardBuilder>();

        mCards.add(new CardBuilder(this, CardBuilder.Layout.COLUMNS)
                .setText("Board 1")
                .setFootnote("Tap for more information"));

        mCards.add(new CardBuilder(this, CardBuilder.Layout.COLUMNS)
                .setText("Board 2")
                .setFootnote("Tap for more information"));

        mCards.add(new CardBuilder(this, CardBuilder.Layout.COLUMNS)
                .setText("Board 3")
                .setFootnote("Tap for more information"));

        mCards.add(new CardBuilder(this, CardBuilder.Layout.COLUMNS)
                .setText("Board 4")
                .setFootnote("Tap for more information"));
    }

    private void setupClickListener() {
        mCardScrollView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                Intent i = new Intent(MainActivity.this, SensorsActivity.class);
                i.putExtra("boardNumber", position+1);
                startActivity(i);
            }
        });
    }

    private class ExampleCardScrollAdapter extends CardScrollAdapter {

        @Override
        public int getPosition(Object item) {
            return mCards.indexOf(item);
        }

        @Override
        public int getCount() {
            return mCards.size();
        }

        @Override
        public Object getItem(int position) {
            return mCards.get(position);
        }

        @Override
        public int getViewTypeCount() {
            return CardBuilder.getViewTypeCount();
        }

        @Override
        public int getItemViewType(int position){
            return mCards.get(position).getItemViewType();
        }

        @Override
        public View getView(int position, View convertView, ViewGroup parent) {
            return mCards.get(position).getView(convertView, parent);
        }
    }
}
