package activity.home;

import com.example.bla.R;

import activity.DefaultActivity;
import activity.remote.MainActivity;
import android.os.Bundle;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.DialogInterface.OnClickListener;
import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.widget.EditText;

/**
 * 
 * @author Antoine MOÏSE
 * Create an homeActivity which is used to get IP adress and port number of the server
 */
public class HomeActivity extends DefaultActivity
{

	/**
	 * Keys client used to update security data
	 */
	private KeyClient cc;

	@Override
	protected void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_home_vue);
		setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
		cc = new KeyClient(new HomeActivityHandler(this), this);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu)
	{
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.serveur, menu);
		return true;
	}
	/**
	 * Check if the Ip has a correct syntax
	 * @param value the Ip address
	 * @return true if it's correct, false otherwise
	 */
	public boolean checkIP(String value)
	{
		int i;
		int cpt = 0;
		for (i = 0; i < value.length(); i++)
		{
			if (value.charAt(i) == '.')
				cpt++;
		}

		return (cpt == 3);

	}

	/**
	 * Check an port number
	 * @param portValue the port number to test
	 * @return true if the port is correct, false otherwise
	 */
	public boolean checkPortNumber(String portValue)
	{
		if (portValue.length() <= 0)
			return false;
		for (int i = 0; i < portValue.length(); i++)
			if (!(portValue.charAt(i) >= '0' && portValue.charAt(i) <= '9'))
				return false;
		int port = Integer.parseInt(portValue);
		if (port < 1024)
			return false;
		else if (port < 65535)
			return true;
		else
			return false;

	}

	/**
	 * Verify that connection data are correctly written 
	 * @return true if correct, false otherwise
	 */
	public boolean verifData()
	{
		boolean portOk = false;
		boolean adressIpOk = false;
		EditText port = (EditText) findViewById(R.id.port);
		EditText addressIp = (EditText) findViewById(R.id.ip);

		//Getting the string value from text field
		String textport = port.getText().toString();
		String ip = addressIp.getText().toString();

		portOk = checkPortNumber(textport);
		adressIpOk = checkIP(ip);
		return portOk && adressIpOk;
	}

	public void onclick(View v)
	{
		EditText port = (EditText) findViewById(R.id.port);
		EditText addressIp = (EditText) findViewById(R.id.ip);

		String textport = port.getText().toString();
		String ip = addressIp.getText().toString();
		if (verifData())
		{
			//The data are correct, lauching the MainActivity
			Intent intent = new Intent(HomeActivity.this, MainActivity.class);
			intent.putExtra("port", Integer.parseInt(textport));
			intent.putExtra("ip", ip);
			startActivity(intent);
			return;
		}
		//Some syntax problems
		else
			showInformationMessage("Synatxe incorrecte", "Réseau");

	}

	/**
	 * Callback used to handle the "clés" button press.
	 * It launches the Key clients thread to update security data
	 * @param v
	 */
	public void updateSecurityData(View v)
	{

		AlertDialog.Builder build = new AlertDialog.Builder(this);
		// Set title to the alertDialog
		build.setTitle("Sécurité");
		build.setMessage("Voulez-vous charger les nouvelles données de sécurité?");

		// Can not cancel the dialog box
		build.setCancelable(false);
		build.setPositiveButton("Oui", new OnClickListener() {

			@Override
			public void onClick(DialogInterface dialog, int which)
			{
				if (verifData())
				{
					EditText port = (EditText) findViewById(R.id.port);
					EditText addressIp = (EditText) findViewById(R.id.ip);

					String textport = port.getText().toString();
					String ip = addressIp.getText().toString();

					cc.setData(ip, Integer.parseInt(textport));
					cc.start();
				}
				else
					showInformationMessage("Synatxe incorrecte", "Réseau");

			}
		});
		build.setNegativeButton("Non", new OnClickListener() {

			@Override
			public void onClick(DialogInterface dialog, int which)
			{
				dialog.cancel();
			}
		});

		AlertDialog dialog = build.create();
		dialog.show();
	}
	/**
	 * Callback which handle the "Arrêter" push
	 * Stop the activity and all thread which are running
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
}
