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

public class HomeActivity extends DefaultActivity
{

	private ClientCle cc;

	@Override
	protected void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_home_vue);
		setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
		cc = new ClientCle(new HomeActivityHandler(this), this);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu)
	{
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.serveur, menu);
		return true;
	}

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

	public boolean verifData()
	{
		boolean portOk = false;
		boolean adressIpOk = false;
		EditText port = (EditText) findViewById(R.id.port);
		EditText addressIp = (EditText) findViewById(R.id.ip);

		String textport = port.getText().toString();
		String ip = addressIp.getText().toString();
		Log.e("Port", textport);
		Log.e("IP", ip);
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
			Intent intent = new Intent(HomeActivity.this, MainActivity.class);
			intent.putExtra("port", Integer.parseInt(textport));
			intent.putExtra("ip", ip);
			startActivity(intent);
			return;
		}
		else
			showInformationMessage("Synatxe incorrecte", "Réseau");

	}

	public void recupCle(View v)
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

	public void stopApplication(View w)
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
