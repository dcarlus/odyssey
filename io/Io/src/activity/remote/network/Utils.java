package activity.remote.network;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

/**
 * 
 * @author Antoine MOÏSE
 * Contains several methods related to Network communication
 */
public class Utils
{

	/**
	 * transform an 4 length byte array into an Integer
	 * @param bytes the integer value in a 4 length byte array format
	 * @return the integer value
	 */
	public static int transformBytesToInt(byte[] bytes)
	{
		// Check if the length of the byte array is correct(here 4 bytes)
		if (bytes.length != Integer.SIZE / 8)
			return -1;
		else
		{
			ByteBuffer buffer = ByteBuffer.wrap(bytes);
			return buffer.getInt();
		}
	}

	/**
	 * transform an 8 length byte array into an Long
	 * @param bytes the integer value in a 8 length byte array format
	 * @return the long value
	 */
	public static long transformBytesToLong(byte[] bytes)
	{
		// Check if the length of the byte array is correct(here 8 bytes)
		if (bytes.length != Long.SIZE / 8)
			return -1;
		else
		{
			ByteBuffer buffer = ByteBuffer.wrap(bytes);
			return buffer.getLong();
		}
	}
	/**
	 * Transform an int to a 4 length byte array
	 * @param value value to convert
	 * @return the value converted into byte array
	 */
	public static byte[] tranformIntToBytes(int value)
	{
		ByteBuffer buffer = ByteBuffer.allocate(Integer.SIZE / 8);
		buffer.order(ByteOrder.BIG_ENDIAN);
		buffer.putInt(value);
		return buffer.array();
	}

	/**
	 * Transform an long to a 8 length byte array
	 * @param value value to convert
	 * @return the value converted into byte array
	 */
	public static byte[] tranformLongToBytes(long value)
	{
		ByteBuffer buffer = ByteBuffer.allocate(Long.SIZE / 8);
		buffer.order(ByteOrder.BIG_ENDIAN);
		buffer.putLong(value);
		return buffer.array();
	}

	/**
	 * Check if two array are equals 
	 * @param a the first array
	 * @param b the second array
	 * @return true if the two arrays are equals, false otherwise
	 */
	public static boolean equalsArray(byte a[], byte b[])
	{
		if (a.length != b.length)
			return false;
		for (int i = 0; i < a.length; i++)
			if (a[i] != b[i])
				return false;
		return true;
	}

	/**
	 * Concatenate data to one single byte buffer
	 * @param data data to concatenate
	 * @return a buffer which contains 
	 */
	public static byte[] concatenateDatasToMessage(byte[]... data)
	{
		ByteArrayOutputStream bos = new ByteArrayOutputStream();
		for (int i = 0; i < data.length; i++)
		{
			try
			{
				bos.write(data[i]);
			}
			catch (IOException e)
			{
				e.printStackTrace();
			}
		}
		return bos.toByteArray();
	}
	/**
	 * Cut an byte array into several byte arrays
	 * @param message byte array which contains all data
	 * @param data all byte arrays
	 */
	public static void fetchDatasFromMessage(byte message[], byte[]... data)
	{
		ByteArrayInputStream bis = new ByteArrayInputStream(message);
		for (int i = 0; i < data.length; i++)
		{
			try
			{
				bis.read(data[i]);
			}
			catch (IOException e)
			{
				e.printStackTrace();
			}
		}
	}
}
