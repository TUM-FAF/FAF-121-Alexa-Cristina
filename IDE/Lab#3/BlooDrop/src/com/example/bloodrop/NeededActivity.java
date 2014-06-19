package com.example.bloodrop;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TableLayout;
import android.content.Intent;


public class NeededActivity extends Activity {
	TableLayout neededBlood;
	String neededBloodTable[][];
	
	protected void onCreate(Bundle savedInstanceState) {
		
		super.onCreate(savedInstanceState);
		setContentView(R.layout.solicitation_screen);	
	}
}
