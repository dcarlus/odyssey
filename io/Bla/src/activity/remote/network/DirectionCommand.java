package activity.remote.network;

import java.io.IOException;
import java.io.OutputStream;
import java.util.Arrays;
import cryptography.Algorithms;

/**
 * 
 * @author Antoine MOÏSE Thread which send command to Polyphemus
 */
public class DirectionCommand extends Thread
{

	/**
	 * Stream from socket
	 */
	private OutputStream os;
	private int command;
	private byte padding[] = new byte[12];
	private byte commandByte[];

	/**
	 * Construct an CommandTask with the following arguments
	 * 
	 * @param command
	 *            the number of command
	 * @param os
	 *            stream to write in the socket
	 */
	public DirectionCommand(byte command, OutputStream os)
	{
		super();
		this.command = (byte) command;
		this.os = os;
		Arrays.fill(padding, (byte)0);
	}

	@Override
	public void run()
	{
		commandByte = Utils.tranformIntToBytes(command);
		byte hash[] = Algorithms.hashFunction(commandByte);
		byte message[] = Utils.concatenateDatasToMessage(commandByte, hash,
				padding);
		synchronized (os)
		{
			try
			{
				os.write(message);
			}
			catch (IOException e)
			{
				e.printStackTrace();
			}
		}
	}
}
