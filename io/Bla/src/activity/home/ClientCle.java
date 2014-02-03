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
import android.util.Log;

/**
 * @author Antoine MOÏSE mail: moise.antoine@hotmail.fr manage the security data
 *         transfer
 */
public class ClientCle extends Thread
{

	private HomeActivityHandler hah;
	private DefaultActivity ha;
	private String ipAddress;
	private int port;

	public ClientCle(HomeActivityHandler handler, DefaultActivity ha)
	{
		this.hah = handler;
		this.ha = ha;
	}

	public void setData(String ip, int port)
	{
		ipAddress = ip;
		this.port = port;
	}

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
		String securityDataFile = "keys";
		try
		{
			socket = new Socket();
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
		long fileLength = Utils.transformBytesToLong(fileLengthByte);
		while (fileLength > 0)
		{
			byte data[] = null;
			try
			{
				length = is.read();
				data = new byte[length];
				is.read(data);
				os.write(data);
				os.write('\n');
			}
			catch (IOException e)
			{
				sendMessage("Exception", e.getMessage());
				return;
			}
			fileLength = fileLength - length - 1;
		}
		try
		{
			os.close();
		}
		catch (IOException e)
		{

			e.printStackTrace();
		}
		File counter = new File(ha.getFilesDir(), "counterIO");
		FileWriter fw;
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
		sendMessage("Sécurité", "Les données de sécurité ont été mises à jour");
	}
}
