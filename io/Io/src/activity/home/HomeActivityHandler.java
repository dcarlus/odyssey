package activity.home;

import com.example.bla.R;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.widget.Button;

/**
 * 
 * @author Antoine MOÏSE Handler used to communicate between the server Activity
 *         and the ClienCle thread
 */
public class HomeActivityHandler extends Handler
{
	/**
	 * Activity that perform UI updates
	 */
	private HomeActivity ma;

	public final String message = "threadMessage";
	public final String tagMessage = "tagMessage";

	public HomeActivityHandler(HomeActivity ma)
	{
		this.ma = ma;
	}

	@Override
	public void handleMessage(Message msg)
	{

		Bundle data = msg.getData();
		String status = data.getString(message);
		String statusType = data.getString(tagMessage);
		if (status == null)
			status = "-";
		
		Button cle = (Button) ma.findViewById(R.id.keys);
		cle.setClickable(false);
		ma.showInformationMessage(status, statusType);
	}

}
