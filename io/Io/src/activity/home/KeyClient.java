package activity.home;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.UnknownHostException;

import activity.DefaultActivity;
import activity.remote.network.Utils;
import android.os.Bundle;
import android.os.Message;

/**
 * @author Antoine MOÏSE mail: moise.antoine@hotmail.fr manage the security data
 *         transfer
 */
public class KeyClient extends Thread
{

	/**
	 * Handler used to send message to show to UI
	 */
	private HomeActivityHandler hah;
	/**
	 * The caller activity, used to get the private application folder to store security data
	 */
	private DefaultActivity ha;
	/**
	 * Security data updater server ip address
	 */
	private String ipAddress;
	/**
	 * Security data updater server port
	 */
	private int port;

	/**
	 * Create an KeyClient thread with the following arguments 
	 * @param handler handler to send message
	 * @param ha the caller activity
	 */
	public KeyClient(HomeActivityHandler handler, DefaultActivity ha)
	{
		this.hah = handler;
		this.ha = ha;
	}

	/**
	 * Set server related data 
	 * @param ip server IP
	 * @param port server port
	 */
	public void setData(String ip, int port)
	{
		ipAddress = ip;
		this.port = port;
	}

	/**
	 * Send a Message to an Activity using Handler
	 * @param messageType Type of message, an error or an informations
	 * @param message the message
	 */
	private void sendMessage(String messageType, String message)
	{
		Message msg = hah.obtainMessage();
		Bundle bundle = new Bundle();
		bundle.putString(hah.tagMessage, messageType);
		bundle.putString(hah.message, message);
		msg.setData(bundle);
		hah.sendMessage(msg);

	}

	@Override
	public void run()
	{
		Socket socket = null; 
		String securityDataFile = ha.securityDataFilename;
		int maximumBufferSize = 2000;
		//All exception are caught and create an pop-up entitled "Exception" with the exception description 
		try
		{
			socket = new Socket();
			//Setting the timeout to 10 seconds
			socket.connect(new InetSocketAddress(ipAddress, port) {
			}, 10000);

		}
		catch (UnknownHostException e)
		{
			sendMessage("Exception", e.getMessage());
			return;
		}
		catch (IOException e)
		{
			sendMessage("Exception", e.getMessage());
			return;

		}
		assert (socket != null);
		//Getting the key file
		File f = new File(ha.getFilesDir(), securityDataFile);
		FileOutputStream os = null;

		try
		{
			os = new FileOutputStream(f);
		}
		catch (FileNotFoundException e)
		{
			sendMessage("Exception", e.getMessage());
			return;
		}

		InputStream is = null;
		try
		{
			is = socket.getInputStream();
		}
		catch (IOException e)
		{
			sendMessage("Exception", e.getMessage());
			return;
		}
		int length = 0;
		byte fileLengthByte[] = new byte[8];
		try
		{
			is.read(fileLengthByte);
		}
		catch (IOException e)
		{
			sendMessage("Exception", e.getMessage());
			return;
		}
		//The file length is send by the server, the length is on 8 byte
		long fileLength = Utils.transformBytesToLong(fileLengthByte);
		byte data[] = new byte [maximumBufferSize];
		while (fileLength > 0)
		{
			try
			{
				length = is.read();
				if(length>maximumBufferSize)
				{
					sendMessage("Mémoire", "La mémoire allouée est insuffisante");
					return;
				}
				is.read(data,0,length);
				os.write(data,0,length);
				os.write('\n');
			}
			catch (IOException e)
			{
				sendMessage("Exception", e.getMessage());
				return;
			}
			// the -1 is for '\n'
			fileLength = fileLength - length - 1;
		}
		try
		{
			os.close();
			is.close();
		}
		catch (IOException e)
		{

			e.printStackTrace();
		}
		File counter = new File(ha.getFilesDir(), ha.counterIoFilename);
		FileWriter fw;
		
		//Initialising the counter to 0
		try
		{
			fw = new FileWriter(counter);
			fw.write("0000");

		}
		catch (IOException e)
		{
			sendMessage("Exception", e.getMessage());
			return;
		}
		try
		{
			fw.close();
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
		//No error, ready for using the new data
		sendMessage("Sécurité", "Les données de sécurité ont été mises à jour");
	}
}
