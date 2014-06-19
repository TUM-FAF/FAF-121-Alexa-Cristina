
package com.example.bloodrop;

import java.util.Calendar;

import android.app.Activity;
import android.app.DatePickerDialog;
import android.app.Dialog;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.ArrayAdapter;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.DatePicker;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.TextView;
import android.content.Intent;


public class ActivityRegistration extends Activity implements OnClickListener{
	
	private static final String TAG="myLogs";
	
	private static final int DIALOG_DATE=1;
	private static final int DIALOG_DATE0 = 2;
	private int year;
	private int month;
	private int day;
	private int year0;
	private int month0;
	private int day0;
	
	EditText name;
	EditText surname;
	EditText phone_number;
	EditText e_mail;
	DatePicker birtDay_picker;
	String birthDate_value;
	TextView BirthDateLabel;
	Button ButtonBirthDay;
	
	CheckBox CheckRelative;
	CheckBox CheckVolunteer;
	
	TextView AppointmentLabel;
	DatePicker appointmentPicker;
	String appointment_value;
	Button ButtonAppointment;
	
	Spinner spinner_rhezus;
	Spinner spinner_group;
	Spinner spinner_hour; 
	Spinner spinner_locale; 
	String[] group_array={ "not known", "O(I)", "A(II)", "B(III)", "AB(IV)"};
	String[] rhezus_array={ "not known", "Rh(+)", "Rh(-)"};
	
	Button RegistrationButton;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		setContentView(R.layout.registration_fullscreen);

		final View controlsView = findViewById(R.id.fullscreen_content_controls);
		
		Log.d(TAG, "Initiated the layout");
		
		BirthDateLabel = (TextView)findViewById(R.id.birthdate_label);
		ButtonBirthDay = (Button) findViewById(R.id.choose_birthday);
		ButtonBirthDay.setOnClickListener(this);
		initializePicker(BirthDateLabel);
		
			
        
        spinner_group = (Spinner)findViewById(R.id.spinner_group);
        setTheSpinner(spinner_group, "Blood Group", group_array);
  
        spinner_rhezus =(Spinner)findViewById(R.id.spinner_rhezus);
		setTheSpinner(spinner_rhezus, "Rhezus", rhezus_array);
		
		CheckRelative = (CheckBox)findViewById(R.id.relative);
		CheckVolunteer = (CheckBox)findViewById(R.id.volunteer);
		
		
		
		spinner_hour = (Spinner)findViewById(R.id.spinner_time);
		setTheSpinner(spinner_hour, "Time", getResources().getStringArray(R.array.time));
		
		spinner_locale = (Spinner)findViewById(R.id.spinner_locale);
		setTheSpinner(spinner_locale, "Center", getResources().getStringArray(R.array.localitatea));
		
		AppointmentLabel = (TextView)findViewById(R.id.date_appointment);
		ButtonAppointment = (Button)findViewById(R.id.choose_appointment);
		ButtonAppointment.setOnClickListener(this);
		Log.d(TAG, "Invoked setOnClickListener");
		initializePicker(AppointmentLabel);
		Log.d(TAG, "Initialized second label");
		
		RegistrationButton = (Button) findViewById(R.id.register_button);
		RegistrationButton.setOnClickListener(this);
		
	}
	
	
	public void onCheckboxClicked(View v) {
		switch(v.getId()) { 	
		case R.id.relative:
			break;
		case R.id.volunteer:
			break;
		default:
			break;
		}
		
	}
	
	@Override
	protected Dialog onCreateDialog(int id) {
		switch (id) {
		case DIALOG_DATE:
			Log.d(TAG, "Entered in the dialog  1 state");
		   // set date picker as current date
		   return new DatePickerDialog(this, datePickerListener, 
                         year, month,day);
		case DIALOG_DATE0:
			return new DatePickerDialog(this, datePickerListener0, 
                    year0, month0, day0);
		}
		return null;
	}
	
	private DatePickerDialog.OnDateSetListener datePickerListener = new DatePickerDialog.OnDateSetListener() {
		
		@Override
		public void onDateSet(DatePicker view, int selectedYear,
			int selectedMonth, int selectedDay) {
			
				year = selectedYear;
				month = selectedMonth;
				day = selectedDay;
				
				BirthDateLabel.setText(new StringBuilder().append(month + 1)
						   .append(" : ").append(day).append(" : ").append(year)
						   .append(" "));
		}
	};
	
private DatePickerDialog.OnDateSetListener datePickerListener0 = new DatePickerDialog.OnDateSetListener() {
		
		@Override
		public void onDateSet(DatePicker view, int selectedYear,
			int selectedMonth, int selectedDay) {
			
				year0 = selectedYear;
				month0 = selectedMonth;
				day0 = selectedDay;
				
				AppointmentLabel.setText(new StringBuilder().append(month0 + 1)
						   .append(" : ").append(day0).append(" : ").append(year0)
						   .append(" "));
			
		}
	};
	
	
	

	@Override
	public void onClick(View v) {
		// TODO Auto-generated method stub
		switch (v.getId()) {
		case R.id.choose_birthday:
			showDialog(DIALOG_DATE);
			break;
		case R.id.choose_appointment:
			showDialog(DIALOG_DATE0);
			break; 
		case R.id.register_button:
			Intent Intent = new Intent(this, thanks_activity.class);
			startActivity(Intent);
			break;
		default:
			break;
		}
		
	}
	
	public void setTheSpinner(Spinner spinner, String string, String[] array) {
		ArrayAdapter<String> adapter = new ArrayAdapter<String>(this, android.R.layout.simple_spinner_item, array);
		adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        spinner.setAdapter(adapter);
        spinner.setPrompt(string);
        spinner.setSelection(1);
        spinner.setOnItemSelectedListener(new OnItemSelectedListener() {
        	@Override
        	public void onItemSelected(AdapterView <?> parent, View view, int position, long id) {
        	}

			@Override
			public void onNothingSelected(AdapterView<?> parent) {
				// TODO Auto-generated method stub
				
			}
        });	 
	}
	
	public void initializePicker(TextView label) {
		Log.d(TAG, "Entered the initioalization");
		final Calendar c = Calendar.getInstance();
		year0 = year = c.get(Calendar.YEAR);
		month0 = month = c.get(Calendar.MONTH);
		day0 = day = c.get(Calendar.DAY_OF_MONTH);
 
		// set current date into textview
		label.setText(new StringBuilder()
			// Month is 0 based, just add 1
			.append(month + 1).append(" : ").append(day).append(" : ")
			.append(year).append(" "));
		Log.d(TAG, "Defined label with current date");
	}
}


