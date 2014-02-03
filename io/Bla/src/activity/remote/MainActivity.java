package activity.remote;

import java.io.File;
import com.example.bla.R;
import com.example.bla.R.id;
import activity.DefaultActivity;
import activity.remote.network.Servertask;
import android.os.Bundle;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.DialogInterface.OnClickListener;
import android.content.pm.ActivityInfo;
import android.view.Menu;
import android.view.View;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.ProgressBar;
import android.widget.TextView;

/**
 * 
 * @author Antoine MOÏSE Activity which manage the UI and launch the server
 *         Thread
 */
public class MainActivity extends DefaultActivity
{

	private byte Stop = 0;
	private byte Forward = 1;
	private byte Backward = 2;
	private byte Left = 3;
	private byte Right = 4;
	private byte led_on = 6;
	private byte led_off = 7;
	private boolean led = false;
	/**
	 * The server thread
	 * 
	 * @see Servertask
	 */
	Servertask ct;

	/**
	 * Initialize the UI
	 * 
	 * @param value
	 *            activate or not the button on the UI
	 */
	public void initUI(boolean value)
	{
		Button up = (Button) findViewById(id.Up);
		Button down = (Button) findViewById(id.Down);
		Button left = (Button) findViewById(id.Left);
		Button right = (Button) findViewById(id.Right);
		Button stop = (Button) findViewById(id.Stop);
		CheckBox led = (CheckBox) findViewById(id.Led);
		up.setClickable(value);
		down.setClickable(value);
		left.setClickable(value);
		right.setClickable(value);
		stop.setClickable(value);
		led.setClickable(value);
		initProgressBar();

	}
	/**
	 * Initialize the UI progress bar
	 */
	public void initProgressBar()
	{
		// Initializing the progress bar to 0
		ProgressBar bar = (ProgressBar) findViewById(R.id.progressBarStep);
		bar.setProgress(0);
		bar.setMax(100);
	}

	@Override
	protected void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main_vue);
		Intent intent = getIntent();
		String ip = "1.1.1.1";
		int port = 1234;
		// Open all files containing security data(keys, counter)
		File securityData = new File(getFilesDir(), "keys");
		File counter_IO = new File(getFilesDir(), "counterIO");
		initUI(false);
		setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
		if (intent != null)
		{
			// Get data from the first activity
			ip = intent.getStringExtra("ip");
			port = intent.getIntExtra("port", 0);

			// Launch the server thread
			ct = new Servertask(new MainActivityHandler(this), ip, port,
					securityData, counter_IO);
			ct.start();
		}

	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu)
	{
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	/**
	 * Send command to polyphemus, here left This callback is call by the "left"
	 * button
	 * 
	 * @param view
	 *            the activity View
	 */
	public void leftCallback(View view)
	{
		ct.sendCommand(Left);

	}

	/**
	 * Send command to polyphemus, here right This callback is call by the
	 * "right" button
	 * 
	 * @param view
	 *            the activity View
	 */
	public void rightCallback(View view)
	{
		ct.sendCommand(Right);
	}

	/**
	 * Send command to polyphemus, here forward This callback is call by the
	 * "up" button
	 * 
	 * @param view
	 *            the activity View
	 */
	public void upCallback(View view)
	{
		ct.sendCommand(Forward);
	}

	/**
	 * Send command to polyphemus, here backward This callback is call by the
	 * "down" button
	 * 
	 * @param view
	 *            the activity View
	 */
	public void downCallback(View view)
	{
		ct.sendCommand(Backward);
	}

	/**
	 * Send command to polyphemus, here stop This callback is call by the "stop"
	 * button
	 * 
	 * @param view
	 *            the activity View
	 */
	public void stopCallback(View view)
	{
		ct.sendCommand(Stop);
	}

	/**
	 * Send command to polyphemus, here switch on/off led This callback is call
	 * by the Led checkBox
	 * 
	 * @param view
	 *            the activity View
	 */
	public void ledCallback(View view)
	{
		if (!led)
			ct.sendCommand(this.led_on);
		else
			ct.sendCommand(this.led_off);
		led = !led;
	}

	/**
	 * Send command to polyphemus, here switch on/off led This callback is call
	 * by the Led checkBox
	 * 
	 * @param view
	 *            the activity View
	 */
	public void stopApplication(View view)
	{
		AlertDialog.Builder build = new AlertDialog.Builder(this);
		// Set title to the alertDialog
		build.setTitle("Io");
		build.setMessage("Voulez-vous arrêter l'application ?");

		// Can not cancel the dialog box
		build.setCancelable(false);
		build.setPositiveButton("Oui", new OnClickListener() {

			@Override
			public void onClick(DialogInterface dialog, int which)
			{
				dialog.cancel();
				initUI(false);
				ct.stopServer();
				System.exit(1);
			}
		});

		build.setNegativeButton("Non", new OnClickListener() {

			@Override
			public void onClick(DialogInterface dialog, int which)
			{
				dialog.cancel();
			}
		});
		AlertDialog adb = build.create();
		adb.show();
	}
	/**
	 * Update the progress bar, by using a Handler
	 * 
	 * @param value
	 *            the progress value
	 * @param message
	 *            message to show for progresss
	 */
	public void updateProgressBar(int value, String message)
	{
		// Update the progress bar
		ProgressBar bar = (ProgressBar) findViewById(R.id.progressBarStep);
		bar.setProgress(bar.getProgress() + value);
		// Update the label Step
		TextView tx = (TextView) findViewById(R.id.labelSpinner);
		tx.setText(message);

		// Update the progress bar pourcentage
		tx = (TextView) findViewById(R.id.pourcentage);
		tx.setText(Integer.toString(bar.getProgress()) + '%');
	}

}
