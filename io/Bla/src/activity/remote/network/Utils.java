package activity.remote.network;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class Utils
{

	public static int transformBytesToInt(byte[] bytes)
	{
		if (bytes.length != Integer.SIZE / 8)
			return -1;
		else
		{
			ByteBuffer buffer = ByteBuffer.wrap(bytes);
			return buffer.getInt();
		}
	}

	public static long transformBytesToLong(byte[] bytes)
	{
		if (bytes.length != Long.SIZE / 8)
			return -1;
		else
		{
			ByteBuffer buffer = ByteBuffer.wrap(bytes);
			buffer.order(ByteOrder.BIG_ENDIAN);
			return buffer.getLong();
		}
	}

	public static byte[] tranformIntToBytes(int value)
	{
		ByteBuffer buffer = ByteBuffer.allocate(Integer.SIZE / 8);
		buffer.order(ByteOrder.BIG_ENDIAN);
		buffer.putInt(value);
		return buffer.array();
	}

	public static byte[] tranformLongToBytes(long value)
	{
		ByteBuffer buffer = ByteBuffer.allocate(Long.SIZE / 8);
		buffer.order(ByteOrder.BIG_ENDIAN);
		buffer.putLong(value);
		return buffer.array();
	}

	public static boolean equalsArray(byte a[], byte b[])
	{
		if (a.length != b.length)
			return false;
		for (int i = 0; i < a.length; i++)
			if (a[i] != b[i])
				return false;
		return true;
	}

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
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		return bos.toByteArray();
	}

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
