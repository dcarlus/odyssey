package activity.remote.network;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.math.BigInteger;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Scanner;
import cryptography.Algorithms;
import cryptography.EC.EllipticCurve;
import cryptography.EC.Point;
import cryptography.ECDSA.ECDSA;
import cryptography.ECDSA.KeyPair;
import cryptography.ECDSA.Signature;
import activity.remote.MainActivityHandler;
import android.os.Bundle;
import android.os.Message;

/**
 * 
 * @author Antoine MOÏSE Thread which manages network, autentification
 */
public class Servertask extends Thread
{

	/**
	 * Polyphemus address
	 */
	private String add = "";
	/**
	 * Polyphemus Server port
	 */
	private int port;
	private InputStream is = null;
	private OutputStream os = null;

	private MainActivityHandler ma;

	/**
	 * File which contains security data
	 */
	private File securityData;
	/**
	 * File which contains counter
	 */
	private File counterIO;

	/**
	 * authentication message length
	 */
	public final int autentificationMessageLength = 132;

	/**
	 * Size of U,V, EC point's coordinate length
	 */
	public final int numberDataLength = 32;
	private int counterIOint = -1;
	private Voltage v = null;
	byte AESKey[];
	byte AESIv[];

	/**
	 * Create an Commandtask with the following argument
	 * 
	 * @param ma
	 *            handler to communicate with MainActivity
	 * @param addr
	 *            Polyphemus address
	 * @param port
	 *            Polyphemus port
	 * @param securityData
	 *            file which contains security data
	 * @param counterIO
	 *            file which contains counter
	 */
	public Servertask(MainActivityHandler ma, String addr, int port,
			File securityData, File counterIO)
	{
		this.port = port;
		this.add = addr;
		this.ma = ma;
		this.securityData = securityData;
		this.counterIO = counterIO;
	}

	@Override
	public void run()
	{
		Socket socket = null;
		sendAuthentificationProgress(10, "Connexion");

		try
		{
			socket = new Socket();
			socket.connect(new InetSocketAddress(add, port) {
			}, 10000);

		}
		catch (UnknownHostException e)
		{
			sendError("Exception", e.getMessage());
			return;
		}
		catch (IOException e)
		{
			sendError("Exception", e.getMessage());
			return;
		}
		try
		{
			is = socket.getInputStream();
			os = socket.getOutputStream();
		}
		catch (IOException e)
		{
			sendError("Exception", e.getMessage());
			return;
		}
		authentification();

		v = new Voltage(is, os, ma);
		v.start();
		boolean shutDownServer = false;
		while (!shutDownServer)
		{
			boolean isClosed = socket.isClosed();
			boolean inputStreamOn = socket.isInputShutdown();
			boolean outputStreamOn = socket.isOutputShutdown();
			shutDownServer = isClosed || inputStreamOn || outputStreamOn;
		}
		sendError("Application",
				"La communcation avec Polyphemus a été interropue");
		return;
	}

	/**
	 * Send the authentication progress, and the current autentification step
	 * 
	 * @param value
	 * @param authentificationStep
	 */
	public void sendAuthentificationProgress(int value,
			String authentificationStep)
	{
		Message msg = ma.obtainMessage();
		Bundle bundle = msg.getData();
		bundle.putInt(ma.progressBarUpdate, value);
		bundle.putString(ma.progressBarMessage, authentificationStep);
		msg.setData(bundle);
		ma.sendMessage(msg);
	}

	/**
	 * Send an error to MainActivity which create an pop-up with data
	 * 
	 * @param errorType
	 *            errorType
	 * @param errorMessage
	 *            errorMessage
	 */
	public void sendError(String errorType, String errorMessage)
	{
		Message msg = ma.obtainMessage();
		Bundle bundle = msg.getData();
		bundle.putString(ma.errorType, errorType);
		bundle.putString(ma.errorMessage, errorMessage);
		msg.setData(bundle);
		ma.sendMessage(msg);
	}

	/**
	 * Send an message to MainActivity which create an pop-up with data
	 * 
	 * @param messageType
	 *            Message Type
	 * @param message
	 *            message
	 */
	public void sendMessage(String messageType, String message)
	{
		Message msg = ma.obtainMessage();
		Bundle bundle = msg.getData();
		bundle.putString(ma.informationType, messageType);
		bundle.putString(ma.informationMessage, message);
		msg.setData(bundle);
		ma.sendMessage(msg);
	}

	/**
	 * Send command to Polyphemus
	 * 
	 * @param i
	 *            the command value
	 */
	public void sendCommand(byte i)
	{
		Thread t = new DirectionCommand(i, os);
		t.start();
	}

	/**
	 * Stop the server and all other threads
	 */
	public void stopServer()
	{
		if (v != null)
			v.stopThread();
		try
		{
			if (os != null)
				os.close();
			if (is != null)
				is.close();
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}

	}
	/**
	 * Perform the authentification protocol between Io and Polyphemus
	 */
	public void authentification()
	{
		String data[] = Algorithms.getFileData(securityData);
		EllipticCurve ec = new EllipticCurve(data);
		KeyPair mine = Algorithms.createECDSAKeypair(data, ec);
		String publicKeySx = Algorithms.parsingString(data[9],
				"Other_Public_Key_1_X");
		String publicKeySy = Algorithms.parsingString(data[10],
				"Other_Public_Key_1_Y");

		Point otherPublicKey = new Point(new BigInteger(publicKeySx),
				new BigInteger(publicKeySy));

		// Checking if the ECDSA private key is correct
		Point p = ec.multiply(ec.getGenerator(), mine.getPrivateKey());
		boolean privateKeyTest = p.equals(mine.getPublicKey());

		// Checking if the public key belong to the current Elliptic Curve
		boolean publicKeyTest = ec.isOnCurve(mine.getPublicKey());
		if (!publicKeyTest || !privateKeyTest)
		{
			sendMessage("Authentification", "Paire de clés ECDSA érronée");
			return;
		}

		// Check if KeyPair can be use with ECDSA
		byte message[] = new byte[128];

		// Choose a random message
		Algorithms.random(message);

		Signature OwnSignature = ECDSA.Sign(ec, message, mine);
		boolean signatureOk = ECDSA.Verify(ec, OwnSignature, mine, message);

		if (!signatureOk)
		{
			sendMessage("Authentification",
					"Signature ECDSA impossible avec cette paire de clés");
			return;
		}
		sendAuthentificationProgress(10, "Vérification des clés ECDSA");

		// Choose an random Number j
		BigInteger j = Algorithms.random(ec.getP());
		// Load counter value from internal phone storage

		// Read counter Value from Io FileSystem
		Scanner sc = null;
		try
		{
			sc = new Scanner(counterIO);
		}
		catch (FileNotFoundException e)
		{
			sendError(e.getMessage(), "Exception");
			return;
		}

		if (sc.hasNext())
			counterIOint = sc.nextInt();
		else
			counterIOint = -1;
		counterIOint++;
		sc.close();

		// Getting the byte representation of the counter
		byte counterByte[] = Utils.tranformIntToBytes(counterIOint);

		// Compute his shared Key
		Point sharedKey = ec.multiply(ec.getGenerator(), j);
		byte sharedKeyX[] = sharedKey.getX().toByteArray();
		byte sharedKeyY[] = sharedKey.getY().toByteArray();

		// Compute hash counterIO||sharedKeyX using SHA-256
		byte hash[];
		hash = Algorithms.hashFunction(counterByte, sharedKeyX, sharedKeyY);

		// SHA-256 hash length is 32 byte
		assert (hash.length == 32);
		Signature mySignature = ECDSA.Sign(ec, hash, mine);
		sendAuthentificationProgress(20, "Signature ECDSA effectuée");
		// Send the follwing message
		// counter | keypart | U | V
		byte UByte[] = mySignature.getU().toByteArray();
		byte VByte[] = mySignature.getV().toByteArray();
		byte myMessage[] = Utils.concatenateDatasToMessage(counterByte,
				sharedKeyX, sharedKeyY, UByte, VByte);
		try
		{
			os.write(myMessage);
		}
		catch (IOException e)
		{
			sendError(e.getMessage(), "Exception");
			return;
		}
		sendAuthentificationProgress(10, "Envoi du Message à Polyphemus");

		byte receivedMessage[] = new byte[autentificationMessageLength];
		try
		{
			is.read(receivedMessage);
		}
		catch (IOException e)
		{
			sendError(e.getMessage(), "Exception");
			return;
		}
		sendAuthentificationProgress(10, "Réception du Message de Polyphemus");
		byte receivedCounterByte[] = new byte[4];
		byte receivedSharedKeyX[] = new byte[numberDataLength];
		byte receivedSharedKeyY[] = new byte[numberDataLength];
		byte receivedU[] = new byte[numberDataLength];
		byte receivedV[] = new byte[numberDataLength];

		Utils.fetchDatasFromMessage(receivedMessage, receivedCounterByte,
				receivedSharedKeyX, receivedSharedKeyY, receivedU, receivedV);
		if (receivedMessage.length != autentificationMessageLength)
		{
			this.sendError("Authentification",
					"Longueur du message non conforme");
			return;
		}

		byte otherHash[] = Algorithms.hashFunction(receivedCounterByte,
				receivedSharedKeyX, receivedSharedKeyY);
		Signature received = new Signature(new BigInteger(1, receivedU),
				new BigInteger(1, receivedV));

		int receivedCounter = Utils.transformBytesToInt(receivedCounterByte);
		boolean auth = ECDSA.Verify(ec, received,
				new KeyPair(j, otherPublicKey), otherHash);

		if (!auth)
		{
			this.sendError("Authentification", "Signature ECDSA non conforme");
			return;
		}
		if (receivedCounter >= counterIOint)
		{
			counterIOint = receivedCounter + 1;
			FileWriter fw = null;
			try
			{
				fw = new FileWriter(counterIO);
				fw.write(Integer.toString(counterIOint));
				fw.close();
			}
			catch (IOException e)
			{
				sendError(e.getMessage(), "Exception");
			}
		}
		else
		{
			this.sendError("Authentification", "counter non conforme");
			return;
		}

		// Creating the AES Stuff :
		// AES key and AES Iv
		// Send the progression to MainActivity
		sendAuthentificationProgress(20, "Authentification Polyphemus");

		byte AesIV[] = Algorithms.createAESIv(receivedU);

		Point aesPoint = new Point(new BigInteger(1, receivedSharedKeyX),
				new BigInteger(1, receivedSharedKeyY));
		aesPoint = ec.multiply(aesPoint, j);

		byte aesKey[] = aesPoint.getX().toByteArray();
		sendAuthentificationProgress(20, "Clé secrète AES 256 générée");

		// Creating cipheredStream using AES 256 Ciphers
		os = Algorithms.getFromSocket(os, aesKey, AesIV);
		is = Algorithms.getFromSocket(is, aesKey, AesIV);

		sendMessage("Authentification", "Authentification Terminée");
		sendAuthentificationProgress(0, "Authentifé");
		activateUI(true);

		AESKey = aesKey;
		AESIv = AesIV;
	}

	/**
	 * Activate the MainActivity UI
	 * 
	 * @param status
	 *            activate or not the UI, yes if true, no otherwise
	 */
	public void activateUI(boolean status)
	{
		Message msg = ma.obtainMessage();
		Bundle bundle = msg.getData();
		bundle.putBoolean(ma.activateUI, status);
		ma.sendMessage(msg);
	}

}
