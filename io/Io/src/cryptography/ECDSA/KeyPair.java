package cryptography.ECDSA;

import java.math.BigInteger;
import cryptography.Algorithms;
import cryptography.EC.EllipticCurve;
import cryptography.EC.Point;

public class KeyPair
{
	private BigInteger privateKey;
	private Point publicKey;

	public KeyPair(EllipticCurve curve)
	{
		privateKey = Algorithms.random(curve.getP());
		publicKey = curve.multiply(curve.getGenerator(), privateKey);
	}

	public KeyPair(BigInteger privateKey, EllipticCurve curve)
	{
		this.privateKey = privateKey;
		publicKey = curve.multiply(curve.getGenerator(), privateKey);
	}

	public KeyPair(BigInteger privateKey, Point publicKey)
	{
		this.publicKey = publicKey;
		this.privateKey = privateKey;
	}
	public String toString()
	{
		String res;
		res = "ECDSA Key Pair = \n Private Key :" + privateKey + "\n"
				+ "PublicKey :" + publicKey;
		return res;
	}

	public BigInteger getPrivateKey()
	{
		return privateKey;
	}

	public Point getPublicKey()
	{
		return publicKey;
	}

}
