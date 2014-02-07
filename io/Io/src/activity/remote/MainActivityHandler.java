package activity.remote;

import com.example.bla.R;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.widget.TextView;

/**
 * 
 * @author Antoine MOÏSE Handle all communication between thread and
 *         MainActivity
 */
public class MainActivityHandler extends Handler
{

	public final String voltage = "voltage";
	public final String errorMessage = "errorMessage";
	public final String errorType = "errorType";
	public final String informationType = "informationType";
	public final String informationMessage = "informationMessage";
	public final String progressBarUpdate = "progressBarValue";
	public final String progressBarMessage = "progressText";
	public final String activateUI = "UiOn";
	public final String unactivateUI = "UiOff";

	MainActivity ma;

	public MainActivityHandler(MainActivity ma)
	{
		this.ma = ma;
	}

	@Override
	public void handleMessage(Message msg)
	{
		Bundle data = msg.getData();
		if (data.containsKey(voltage))
		{
			// Update the battery level, the Voltage thread send a message
			int compteur = data.getByte(voltage);
			TextView tx = (TextView) ma.findViewById(R.id.Voltage);
			tx.setText(Integer.toString(compteur) + '%');
		}
		else if (data.containsKey(errorMessage))
		{
			// There is an error in the autentification protocol, the servertask
			// send the error description
			// Nevertheless, an message from exception could be null
			String receivedErrorMessage = data.getString(errorMessage);
			String receivedErrorType = data.getString(errorType);
			if (receivedErrorMessage == null)
				receivedErrorMessage = "Aucune information";
			ma.showErrorMessage(receivedErrorType, receivedErrorMessage);
		}
		else if (data.containsKey(informationMessage))
		{
			// The servertask send an information to User
			String informationType = data.getString(this.informationType);
			String informationMessage = data.getString(this.informationMessage);
			ma.showInformationMessage(informationType, informationMessage);
		}
		else if (data.containsKey(progressBarUpdate))
		{
			// The servertask update the autentification progress
			int updateValue = data.getInt(progressBarUpdate);
			String progressBarMessageValue = data.getString(progressBarMessage);
			ma.updateProgressBar(updateValue, progressBarMessageValue);
		}
		else if (data.containsKey(activateUI))
		{
			//Activate the UI
			boolean value = data.getBoolean(activateUI);
			ma.initUI(value);
		}
	}
}
