package com.example.bloodrop;

import com.example.bloodrop.util.SystemUiHider;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.Toast;
import android.content.Intent;


public class MainActivity extends Activity  implements View.OnClickListener {
	
	//private static final boolean AUTO_HIDE = true;
	//private static final int AUTO_HIDE_DELAY_MILLIS = 3000;
	//private static final boolean TOGGLE_ON_CLICK = true;
	//private static final int HIDER_FLAGS = SystemUiHider.FLAG_HIDE_NAVIGATION;
	//private SystemUiHider mSystemUiHider;

	Button solicitingButton;
	Button informationButton;
	Button registerButton;
	
	private static final String TAG="myLogs";
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		
		super.onCreate(savedInstanceState);
		setContentView(R.layout.intro_fullscreen);
		
		solicitingButton = (Button)findViewById(R.id.soliciting_button);
		solicitingButton.setOnClickListener(this);
		informationButton = (Button)findViewById(R.id.information_button);
		informationButton.setOnClickListener(this);
		registerButton = (Button)findViewById(R.id.donation_button);
		registerButton.setOnClickListener(this);

		//final View controlsView = findViewById(R.id.fullscreen_content_controls);
		//final View contentView = findViewById(R.id.soliciting_button);		
		
	}
	
	@Override
	public void onClick(View v) {
		switch(v.getId()) {
		case R.id.soliciting_button:
			Log.d(TAG, "button solicitare");
			Intent Intent1 = new Intent(this, NeededActivity.class);
			Toast.makeText(this, "Pressed button Solicitare", Toast.LENGTH_LONG).show();
			startActivity(Intent1);
			break;
		case R.id.information_button:
			Log.d(TAG, "button informatie");
			Intent Intent2 = new Intent(this, information_activity.class);
			Toast.makeText(this, "Pressed button Informatie", Toast.LENGTH_LONG).show();
			startActivity(Intent2);
			break;
		case R.id.donation_button:
			Log.d(TAG, "button doneaza");
			Intent Intent3 = new Intent(this, ActivityRegistration.class);
			Toast.makeText(this, "Pressed button Doneaza", Toast.LENGTH_LONG).show();
			startActivity(Intent3);
			break;
		}
		
	}
	
		
		@Override
	protected void onPostCreate(Bundle savedInstanceState) {
		super.onPostCreate(savedInstanceState);
		
	}

}