package com.example.bloodrop;

import android.app.ActionBar.LayoutParams;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.graphics.Typeface;
import android.os.Bundle;
import android.util.Log;
import android.view.Gravity;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.TextView;
public class information_activity extends Activity {
	
	Button donatorWhoButton;
	Button beforeDonationButton;
	Button afterDonationButton;
	Button bloodInformationButton;
	LinearLayout linLayout;
	String TAG = "myLogs";	
	TextView textWhy;
	String paragraphWhy = "\tIt’s useful;\n"
							+"\tThe need of blood is constant and your contribution is important for a healthy and reliable blood supply."
							+"And you’ll feel good knowing you've helped change a life.\n"
							+"\tIt’s safe and easy. Blood is always collected through a new, sterile needle that is used once and then discarded. \n"
							+"\tMost people feel fine after donating blood, a small number of people may just feel lightheaded or dizzy, "
							+"have an upset stomach or experience a bruise or pain where the needle was inserted. It all goes away quickly!\n"
							+"\tIt’s healthy;\n"
							+"\tYou will get free blood tests, burn calories and may reduce risk of heart disease.\n\n"
							+" \t\t\t\t\tWho can donate: \n"
							+"\tAnyone over 18 years old, in a healthy condition and not taking drugs or medicines.";
	
	public void onCreate (Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		setContentView(R.layout.information_fullscreen);
		
		textWhy = (TextView)findViewById(R.id.information_text);
		textWhy.setText(paragraphWhy);
		
		
		//donatorWhoButton = (Button)findViewById(R.id.donator_who_button);
		//beforeDonationButton = (Button)findViewById(R.id.before_donation_button);
		/**afterDonationButton = (Button)findViewById(R.id.after_donation_button);
		bloodInformationButton = (Button)findViewById(R.id.blood_information_button);
		
		donatorWhoButton.setOnClickListener(this);
		beforeDonationButton.setOnClickListener(this);
		afterDonationButton.setOnClickListener(this);
		bloodInformationButton.setOnClickListener(this);**/
		
		
	}

/**	@Override
	public void onClick(View v) {
		final Context context;
		final Intent Intent;

		switch(v.getId()) {
			case R.id.donator_who_button:
				int matchParent = LayoutParams.MATCH_PARENT;
				int wrapContent = LayoutParams.WRAP_CONTENT;
		        setContentView(R.layout.information_layout);
		        Log.d(TAG, "before defining LinLayout");
		        linLayout = (LinearLayout)findViewById(R.layout.information_layout);
		        Log.d(TAG, "after defining LinLayout");
		        LinearLayout.LayoutParams lpTextTitle = new LinearLayout.LayoutParams(wrapContent, wrapContent);
		        lpTextTitle.gravity=Gravity.CENTER_HORIZONTAL;
		        lpTextTitle.topMargin=40;
		        
		        String titleWho = "Cine poate fi donator ";
		        String paragraphWho = "Vîrsta cuprinsa între 18-60 ani\n"
		        					+ "Greutate corporala minima 50 kg;\n"
		        					+ "Tensiunea arteriala : maxima nu depaseste 180 mmHg, iar minima 100 mmHg;\n"
		        					+ "Valoarea hemoglibinei nu este mai joasa de 125g/l pentru femei si nu mai putin de 135 pentru barbati;\n"
		        					+ "Nu prezinta afectiuni de genul: boli de piele, sechele pulmonare, operatie de ulcer, tendinta de sîngerare anormala, s.a;\n"
		        					+ "Intervalul de timp între doua donari de sînge nu poate fi mai mic de 60 zile .";
		       
		        TextView textTitle = new TextView(this);
		        textTitle.setText(titleWho);
		        textTitle.setTextColor(getResources().getColor(R.color.white));
		        textTitle.setTextSize(26);
		        textTitle.setTypeface(null, Typeface.BOLD);
		        
		        //linLayout.addView(textTitle, lpTextTitle);
		        
		        
		        LinearLayout.LayoutParams lpTextParagraph = new LinearLayout.LayoutParams(wrapContent, wrapContent);
		        lpTextParagraph.leftMargin= 10;
		        lpTextParagraph.rightMargin=10;
		        lpTextParagraph.topMargin = 90;
		        lpTextParagraph.gravity=Gravity.CENTER_VERTICAL;
		        
		        TextView textParagraph = new TextView(this);
		        textParagraph.setTextColor(getResources().getColor(R.color.white));
		        textParagraph.setTextSize(16);
		        textParagraph.setText(paragraphWho);
		        
		       // linLayout.addView(textParagraph, lpTextParagraph);
		        
		        
		        
		        
				break;
				//Intent = new Intent(this, );
			case R.id.before_donation_button:
				break;
			case R.id.after_donation_button:
				break;
			case R.id.blood_information_button:
				break;
		}	
	}**/
}
