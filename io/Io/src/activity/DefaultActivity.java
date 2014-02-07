package activity;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.DialogInterface.OnClickListener;

/**
 * 
 * @author Antoine MOÏSE
 * An activity with pop-up creating methods
 */
public class DefaultActivity extends Activity
{
	public final String securityDataFilename = "keys";
	public final String counterIoFilename = "counterIO";
	/**
	 * Show a Error information pop-up and quit the application
	 * 
	 * @param message
	 *            message to show
	 * @param messageType
	 *            message to show
	 */
	public void showErrorMessage(String messageType, String message)
	{
		AlertDialog.Builder build = new AlertDialog.Builder(this);
		// Set title to the alertDialog
		build.setTitle(messageType);
		build.setMessage(message);

		// Can not cancel the dialog box
		build.setCancelable(false);
		build.setNeutralButton("Ok", new OnClickListener() {

			@Override
			public void onClick(DialogInterface dialog, int which)
			{
				dialog.cancel();
				System.exit(1);
			}
		});
		build.create().show();
	}

	/**
	 * Create an Android dialog (pop-up)
	 * 
	 * @param message
	 *            message to show inside the dialog
	 * @param messageType
	 *            title of the dialog
	 */
	public void showInformationMessage(String messageType, String message)
	{
		AlertDialog.Builder build = new AlertDialog.Builder(this);
		// Set title to the alertDialog
		build.setTitle(messageType);
		build.setMessage(message);

		// Can not cancel the dialog box
		build.setCancelable(false);
		build.setNeutralButton("Ok", new OnClickListener() {

			@Override
			public void onClick(DialogInterface dialog, int which)
			{
				dialog.cancel();
			}
		});

		build.create().show();
	}
}
