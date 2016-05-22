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
import android.util.Log;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.List;

import itmt.ecomonglass.R;
import itmt.ecomonglass.dao.SensorsDao;
import itmt.ecomonglass.model.Sensors;

public class SensorsActivity extends Activity {

    private CardScrollView mCardScroller;

    private List<CardBuilder> mCards;
    private CardScrollView mCardScrollView;
    private ExampleCardScrollAdapter mAdapter;
    private Sensors sensors;
    private String[] sensorsData = new String[3];
    private boolean finish = false;

    private View mView;

    @Override
    protected void onCreate(Bundle bundle) {
        super.onCreate(bundle);
        createCards();

        mCardScrollView = new CardScrollView(this);
        mAdapter = new ExampleCardScrollAdapter();
        mCardScrollView.setAdapter(mAdapter);
        mCardScrollView.activate();
        setContentView(mCardScrollView);

        Runnable myRunnable = new Runnable(){
            public void run(){
                SensorsDao dao = new SensorsDao();
                sensors = dao.getLastSensorsByBoard(getIntent().getIntExtra("boardNumber", -1));
                DateFormat df = new SimpleDateFormat("MM/dd/yyyy HH:mm:ss");
                mCards.get(0).setText(String.format("Temperature: %f", sensors.getTemperature()));
                mCards.get(0).setFootnote(df.format(sensors.getTimeStamp()));
                mCards.get(1).setText(String.format("Luminosity: %f", sensors.getLuminosity()));
                mCards.get(1).setFootnote(df.format(sensors.getTimeStamp()));
                mCards.get(2).setText(String.format("Humidity: %f", sensors.getHumidity()));
                mCards.get(2).setFootnote(df.format(sensors.getTimeStamp()));
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

        mCards.add(new CardBuilder(this, CardBuilder.Layout.TEXT)
                .setText("Humidity      ")
                .setFootnote("Tap for more information"));

        mCards.add(new CardBuilder(this, CardBuilder.Layout.TEXT)
                .setText("Luminosity      ")
                .setFootnote("Tap for more information"));

        mCards.add(new CardBuilder(this, CardBuilder.Layout.TEXT)
                .setText("Temperature     ")
                .setFootnote("Tap for more information"));

    }

    @Override
    protected void onResume() {
        super.onResume();
       // mCardScroller.activate();
    }

    @Override
    protected void onPause() {
        //mCardScroller.deactivate();
        super.onPause();
    }

    /**
     * Builds a Glass styled "Hello World!" view using the {@link CardBuilder} class.
     */

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
