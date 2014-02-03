package cryptography;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.InputStream;
import java.io.OutputStream;
import java.math.BigInteger;
import java.security.InvalidAlgorithmParameterException;
import java.security.InvalidKeyException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.util.Scanner;
import javax.crypto.Cipher;
import javax.crypto.CipherInputStream;
import javax.crypto.CipherOutputStream;
import javax.crypto.NoSuchPaddingException;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;
import cryptography.EC.EllipticCurve;
import cryptography.EC.Point;
import cryptography.ECDSA.KeyPair;

/**
 * 
 * @author Antoine MOÏSE Contains several cryptography relatedMethod
 */
public class Algorithms
{
	/**
	 * random Algorithm used
	 */
	public final static String randomAlgorithmName = "SHA1PRNG";

	/**
	 * Hash function used
	 */
	public final static String hashFunctionName = "SHA-256";

	/**
	 * Symetrical cipher algorithm name
	 */
	public final static String symetricCipherAlgorithmName = "AES/CTR/NoPadding";

	/**
	 * Generate an random BigInteger between 0 and P-1
	 * 
	 * @param p
	 *            maximum random value
	 * @return random BigInteger
	 */
	public static BigInteger random(BigInteger p)
	{
		byte randomBytes[] = new byte[p.bitCount()];
		random(randomBytes);
		return new BigInteger(1, randomBytes);

	}

	/**
	 * Hash several data
	 * 
	 * @param data
	 *            data to hash
	 * @return the computed hash
	 */
	public static byte[] hashFunction(byte[]... data)
	{
		MessageDigest function = null;
		try
		{
			function = MessageDigest.getInstance(hashFunctionName);
		}
		catch (NoSuchAlgorithmException e)
		{
			e.printStackTrace();
		}

		for (int i = 0; i < data.length; i++)
			function.update(data[i]);
		return function.digest();
	}

	/**
	 * Generate random byte
	 * 
	 * @param randomBytes
	 *            contain the random bytes after generating
	 */
	public static void random(byte randomBytes[])
	{
		SecureRandom rand = null;
		try
		{
			rand = SecureRandom.getInstance(randomAlgorithmName);
		}
		catch (NoSuchAlgorithmException e)
		{
			e.printStackTrace();
		}
		rand.nextBytes(randomBytes);
	}

	/**
	 * Create an CipherInputStream with an AES Cipher initialized in
	 * DECRYPT_MODE and an Inputstream
	 * 
	 * @param is
	 *            inputStream
	 * @param AESKey
	 *            AES 256 key uses for exchange
	 * @param iv
	 *            AES Iv used for exchange
	 * @return the ciphered input Stream
	 */
	public static CipherInputStream getFromSocket(InputStream is,
			byte AESKey[], byte iv[])
	{
		assert (AESKey.length == 32); // AN aes 256 key length is 32 byte
		assert (iv.length == 16);
		CipherInputStream cis = null;
		Cipher c = null;
		try
		{
			c = Cipher.getInstance(symetricCipherAlgorithmName);
		}
		catch (NoSuchAlgorithmException e)
		{
			e.printStackTrace();

		}
		catch (NoSuchPaddingException e)
		{
			e.printStackTrace();
		}
		SecretKeySpec sk = new SecretKeySpec(AESKey, "AES");
		IvParameterSpec ivs = new IvParameterSpec(iv);

		try
		{
			c.init(Cipher.DECRYPT_MODE, sk, ivs);
		}
		catch (InvalidKeyException e)
		{
			e.printStackTrace();
		}
		catch (InvalidAlgorithmParameterException e)
		{
			e.printStackTrace();
		}
		cis = new CipherInputStream(is, c);
		return cis;
	}

	/**
	 * Create an CipherOutputStream with an AES Cipher initialized in
	 * ENCRYPT_MODE and an Outputstream
	 * 
	 * @param os
	 *            outputStream
	 * @param AESKey
	 *            AES 256 key uses for exchange
	 * @param iv
	 *            AES Iv used for exchange
	 * @return the ciphered Output Stream
	 */
	public static CipherOutputStream getFromSocket(OutputStream os,
			byte AESKey[], byte iv[])
	{
		assert (AESKey.length == 32); // AN aes 256 key length is 32 byte
		assert (iv.length == 16);
		CipherOutputStream cos = null;
		Cipher c = null;
		try
		{
			c = Cipher.getInstance(symetricCipherAlgorithmName);
		}
		catch (NoSuchAlgorithmException e)
		{
			e.printStackTrace();

		}
		catch (NoSuchPaddingException e)
		{
			e.printStackTrace();
		}

		SecretKeySpec sk = new SecretKeySpec(AESKey, "AES");
		IvParameterSpec ivs = new IvParameterSpec(iv);

		try
		{
			c.init(Cipher.ENCRYPT_MODE, sk, ivs);
		}
		catch (InvalidKeyException e)
		{
			e.printStackTrace();
		}
		catch (InvalidAlgorithmParameterException e)
		{
			e.printStackTrace();
		}
		cos = new CipherOutputStream(os, c);
		return cos;
	}

	public static String[] getFileData(File f)
	{
		int fileLength = 11;
		String data[] = new String[fileLength];
		Scanner sc = null;
		try
		{
			sc = new Scanner(f);
		}
		catch (FileNotFoundException e)
		{
			e.printStackTrace();
		}
		int i = 0;
		while (sc.hasNext() & i < fileLength)
		{
			data[i] = sc.next();
			i++;
		}
		return data;
	}

	/**
	 * Verify that the security data file structure is conform ie there is no
	 * syntax mistake
	 * 
	 * @param data
	 *            data from the file
	 * @param beginTagInddex
	 *            beginning index of verification
	 * @param tags
	 *            tags to verify
	 * @return true if conform, false otherwise
	 */
	public static boolean structureConform(String data[], int beginTagInddex,
			String tags[])
	{
		if ((data.length - beginTagInddex) < 2 * tags.length)
			return false;

		for (int i = 0; i < tags.length; i++)
		{
			if (!data[beginTagInddex + i].startsWith(tags[i]))
				return false;
		}
		return true;
	}

	/**
	 * Return header to get EC data from the file
	 * 
	 * @return headers
	 */
	public static String[] getFileStructureCurve()
	{
		String format[] = new String[4];
		format[0] = "Curve_p";
		format[1] = "Curve_n";
		format[2] = "Curve_a4";
		format[3] = "Curve_a6";
		return format;
	}

	/**
	 * Return header to get a EC Point from file
	 * 
	 * @param tag
	 *            point name (public_key for example)
	 * @return the format
	 */
	public static String[] getFilePointStructure(String tag)
	{
		String format[] = new String[2];
		format[0] = tag + "_X";
		format[1] = tag + "_Y";
		return format;

	}

	public static String parsingString(String Svalue, String pattern)
	{
		int endIndex = pattern.length() + 1; // =
		return Svalue.substring(endIndex);
	}

	/**
	 * Create an key pair from data
	 * 
	 * @param data
	 *            data
	 * @param ec
	 *            elliptic curve
	 * @return the ECDSA keyPair
	 */
	public static KeyPair createECDSAKeypair(String data[], EllipticCurve ec)
	{
		KeyPair kp = null;
		int line = 6;
		String value = parsingString(data[line + 2], "Own_Private_Key");
		BigInteger ECDSAPrivateKey = new BigInteger(value);
		Point publicKey = createPublicKeyFrom(data, "Own_", line);
		kp = new KeyPair(ECDSAPrivateKey, publicKey);
		return kp;
	}

	/**
	 * Create an ECDSA PublicKey from data
	 * 
	 * @param data
	 *            security data
	 * @param owner
	 *            the public Key owner
	 * @param line
	 *            the beginnig line
	 * @return the public Key
	 */
	public static Point createPublicKeyFrom(String data[], String owner,
			int line)
	{
		Point point;
		String format[] = getFilePointStructure(owner + "Public_Key");
		point = new Point(parsingString(data[line], format[0]), parsingString(
				data[line + 1], format[1]));
		return point;
	}

	/**
	 * Create the Aes 16 byte IV according the protocol scheme
	 * 
	 * @param receivedU
	 *            one part of the ECDSA signature
	 * @return the AES Iv
	 */
	public static byte[] createAESIv(byte[] receivedU)
	{
		byte AESIv[] = new byte[16];
		for (int i = 0; i < AESIv.length; i++)
			AESIv[i] = 0;

		// Copy the first eight byte from received Signature
		System.arraycopy(receivedU, 0, AESIv, 0, 8);
		return AESIv;
	}

}
