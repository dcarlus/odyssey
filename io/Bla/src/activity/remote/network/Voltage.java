package activity.remote.network;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import cryptography.Algorithms;
import activity.remote.MainActivityHandler;
import android.os.Bundle;
import android.os.Message;

/**
 * 
 * @author Antoine MOÏSE Thread which ask every second the battery level to
 *         Polyphemus
 */
public class Voltage extends Thread
{

	InputStream is = null;
	OutputStream os = null;
	int command;
	boolean stop = false;
	byte commandByte[];
	byte padding[] = new byte[12];
	MainActivityHandler mainActivityHandler;

	/**
	 * Construct a Voltage thread with the following arguments
	 * 
	 * @param is
	 *            inputStream from socket
	 * @param os
	 *            outputStream to socket
	 * @param mainActivity
	 *            required for updating the battery level
	 */
	public Voltage(InputStream is, OutputStream os,
			MainActivityHandler mainActivity)
	{
		this.is = is;
		this.os = os;
		this.mainActivityHandler = mainActivity;
		command = 5;
	}

	/**
	 * Stop the thread
	 */
	public void stopThread()
	{
		stop = true;
	}
	/**
	 * Send occured errors to the Main actvity to pop-up the errors description
	 * and to terminate the app
	 * 
	 * @param message
	 *            informations about the occured error
	 */
	public void sendErrors(String message)
	{
		Message msg = mainActivityHandler.obtainMessage();
		Bundle updateData = new Bundle();
		updateData.putString(mainActivityHandler.errorType, "Exception");
		updateData.putString(mainActivityHandler.errorMessage, message);
		msg.setData(updateData);
		mainActivityHandler.sendMessage(msg);
	}

	@Override
	public void run()
	{
		while (!stop)
		{
			// Padding is necessary for AES
			for (int i = 0; i < padding.length; i++)
				padding[i] = 0;
			commandByte = Utils.tranformIntToBytes(command);

			// Concatenate all buffer to create the whole message
			byte message[] = Utils.concatenateDatasToMessage(commandByte,
					Algorithms.hashFunction(commandByte), padding);

			synchronized (os)
			{
				try
				{
					// Sending command to get the battery
					os.write(message);
				}
				catch (IOException e)
				{
					sendErrors(e.getMessage());
					return;
				}
			}
			byte receivedData[] = new byte[48];
			byte level[] = new byte[4];
			byte hash[] = new byte[32];
			synchronized (is)
			{
				try
				{
					// Receiving the battery level
					is.read(receivedData);
				}
				catch (IOException e)
				{
					sendErrors(e.getMessage());
					return;
				}
				Utils.fetchDatasFromMessage(receivedData, level, hash);
				byte computedHash[] = Algorithms.hashFunction(level);

				// Verifying that hashes are equals
				if (Utils.equalsArray(hash, computedHash))
				{
					Message msg = mainActivityHandler.obtainMessage();
					Bundle updateData = new Bundle();
					updateData.putByte(mainActivityHandler.voltage, level[3]);

					msg.setData(updateData);
					mainActivityHandler.sendMessage(msg);
				}
			}
			try
			{
				sleep(1000);
			}
			catch (InterruptedException e)
			{
				e.printStackTrace();
			}

		}

	}

}
