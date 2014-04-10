package com.tomaskimer.gles3mark;

import android.annotation.TargetApi;
import android.app.Activity;
import android.app.NativeActivity;
import android.content.Intent;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.WindowManager;
import android.widget.Toast;

// TODO https://developer.android.com/training/system-ui/immersive.html ?
public class BenchmarkActivity extends NativeActivity {

	//int score;
	
	static {
		System.loadLibrary("gles3mark");
	}	
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
		//Log.v("NativeSubclass", "onCreate");
		//score = 0;
	}
	
	@TargetApi(Build.VERSION_CODES.KITKAT)
	@Override
	public void onWindowFocusChanged(boolean hasFocus) {
		super.onWindowFocusChanged(hasFocus);
		if (hasFocus) {
	        getWindow().getDecorView().setSystemUiVisibility(
	        		  View.SYSTEM_UI_FLAG_LAYOUT_STABLE
	        		| View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
	                | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
	                | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION  // 4.0 - lean back https://developer.android.com/training/system-ui/immersive.html
	                | View.SYSTEM_UI_FLAG_FULLSCREEN       // 4.0
	                | View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY);
	    }
	}

	@Override
	protected void onStart() {
		super.onStart();
		//nativeBlah(42); // dalvik call to native test
	}
	
//	 // only for mHelper
//	@Override
//	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
//		super.onActivityResult(requestCode, resultCode, data);
//		//Log.v("BenchmarkActivity", "onActivityResult");
//	}
	

	@Override
	public void onBackPressed() {
		super.onBackPressed();
	}
	
    public void FinishMe(String _xmlResult) {  // final
    	final String xmlResult = _xmlResult;
        this.runOnUiThread(new Runnable() {
            public void run() {
            	Intent resultData = new Intent();
        		resultData.putExtra("XML Result", xmlResult);
        		setResult(Activity.RESULT_OK, resultData);
//        		if (getParent() == null) setResult(Activity.RESULT_OK, resultData);
//        		else getParent().setResult(Activity.RESULT_OK, resultData);
            	
            	//score = finalScore;
            	finish();
            }
        });
    }

	@Override
	protected void onDestroy() {
		super.onDestroy();		
		Log.d("BenchmarkActivity", String.format("Activity destroyed"));
	}

	// We call this function from native to display a toast string
	public void showToastAlert(String text) {
		// We need to use a runnable here to ensure that when the spawned
		// native_app_glue thread calls, we actually post the work to the UI
		// thread. Otherwise, we'll likely get exceptions because there's no
		// prepared Looper on the native_app_glue main thread.
		final String finalText = text;
		runOnUiThread(new Runnable() {
			public void run() {
				Toast.makeText(getApplicationContext(), finalText, Toast.LENGTH_SHORT).show();
			}
		});
	}
	
	//private native void nativeBlah(int data); // dalvik call to native test

}
