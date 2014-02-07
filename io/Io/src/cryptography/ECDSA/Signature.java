package cryptography.ECDSA;

import java.math.BigInteger;

/**
 * 
 * @author Antoine MOÏSE Represents an ECDSA Signature
 */
public class Signature
{

	/**
	 * the U in ECDSA Signature
	 */
	private BigInteger U;

	/**
	 * the V in ECDSA Signature
	 */
	private BigInteger V;

	/**
	 * Constructs an Signature with the following argument
	 * 
	 * @param U
	 *            U
	 * @param V
	 *            V
	 */
	public Signature(BigInteger U, BigInteger V)
	{

		this.U = U;
		this.V = V;
	}

	public BigInteger getU()
	{
		return U;
	}

	public BigInteger getV()
	{
		return V;
	}

	public String toString()
	{
		String res = "U = " + U.toString() + "\n" + "V = " + V.toString();
		return res;
	}
}
