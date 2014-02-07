package cryptography.EC;

import java.math.BigInteger;

/**
 * 
 * @author Antoine MOÏSE Represents an Point in a Elliptic Curve
 */
public class Point
{

	/**
	 * X coordinate
	 */
	private BigInteger X;

	/**
	 * Y coordinate
	 */
	private BigInteger Y;

	/**
	 * Is this Point infinite
	 */
	private boolean isInfinite;

	/**
	 * Construct an Point with the following Argument
	 * 
	 * @param Sx
	 *            X coordinate
	 * @param Sy
	 *            Y coordinate
	 */
	public Point(String Sx, String Sy)
	{

		X = new BigInteger(Sx);
		Y = new BigInteger(Sy);
		isInfinite = false;
	}

	/**
	 * Construct an Point with the following Argument
	 * 
	 * @param Sx
	 *            X coordinate
	 * @param Sy
	 *            Y coordinate
	 */
	public Point(BigInteger X, BigInteger Y)
	{

		this.X = new BigInteger(X.toString());
		this.Y = new BigInteger(Y.toString());
		isInfinite = false;
	}

	/**
	 * Construct an Point with the following Argument
	 * 
	 * @param p1
	 *            Point to copy
	 */
	public Point(Point p1)
	{

		X = new BigInteger(p1.X.toString());
		Y = new BigInteger(p1.Y.toString());
		isInfinite = false;
	}

	public void setInfinite(boolean isInfinite)
	{
		this.isInfinite = isInfinite;
	}

	public BigInteger getX()
	{

		return X;
	}

	public void setX(BigInteger x)
	{

		X = x;
	}

	public BigInteger getY()
	{

		return Y;
	}

	public void setY(BigInteger y)
	{

		Y = y;
	}

	public String toString()
	{

		if (isInfinite())
			return "Point is Infinite";

		return ("[" + X.toString() + "," + Y.toString() + "]");
	}

	public boolean isInfinite()
	{
		return isInfinite;
	}

	public boolean isEqual(Point Q)
	{
		boolean Xequal = X.equals(Q.getX());
		boolean Yequal = Y.equals(Q.getY());
		return Xequal && Yequal;
	}

	public boolean equals(Point Q)
	{
		return isEqual(Q);
	}
}
