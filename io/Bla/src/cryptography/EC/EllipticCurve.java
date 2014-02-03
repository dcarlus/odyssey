package cryptography.EC;

import java.math.BigInteger;

import cryptography.Algorithms;

/**
 * 
 * @author Antoine MOÏSE Represent an Elliptic Curve, with all operation The EC
 *         is like : y^2 = x^3 + a4x + a6
 */
public class EllipticCurve
{

	/**
	 * Elliptic curve field
	 */
	private BigInteger p;
	/**
	 * Elliptic curve order
	 */
	private BigInteger n;
	/**
	 * Elliptic curve a4
	 */
	private BigInteger a4;
	/**
	 * Elliptic curve a6
	 */
	private BigInteger a6;

	/**
	 * One generator of this Elliptic Curve
	 */
	private Point generator;

	/**
	 * Build an Elliptic Curve from a File
	 * 
	 * @param data
	 *            data of the elliptic curve to create
	 */
	public EllipticCurve(String data[])
	{
		String format[] = Algorithms.getFileStructureCurve();
		boolean isConforme = Algorithms.structureConform(data, 0, format);
		if (!isConforme)
			System.exit(1);
		else
		{
			this.p = new BigInteger(
					Algorithms.parsingString(data[0], format[0]));
			this.n = new BigInteger(
					Algorithms.parsingString(data[1], format[1]));
			this.a4 = new BigInteger(Algorithms.parsingString(data[2],
					format[2]));
			this.a6 = new BigInteger(Algorithms.parsingString(data[3],
					format[3]));

			format = Algorithms.getFilePointStructure("Curve_Generator");
			if (!Algorithms.structureConform(data, 4, format))
				System.exit(1);
			else
				generator = new Point(Algorithms.parsingString(data[4],
						format[0]),
						Algorithms.parsingString(data[5], format[1]));
		}
	}

	public Point getGenerator()
	{
		return generator;
	}

	public BigInteger getN()
	{
		return n;
	}

	public BigInteger getP()
	{
		return p;
	}

	/**
	 * Create an Elliptic Curve with the following data
	 * 
	 * @param p
	 *            the EC field
	 * @param n
	 *            order
	 * @param a4
	 *            a4
	 * @param a6
	 *            a6
	 * @param generator
	 *            one generator of EC
	 */
	public EllipticCurve(BigInteger p, BigInteger n, BigInteger a4,
			BigInteger a6, Point generator)
	{
		this.p = p;
		this.n = n;
		this.a4 = a4;
		this.a6 = a6;
		this.generator = generator;
	}

	public String toString()
	{

		String res = "Elliptic Curve : \n" + "\t p : " + p + "\n" + "\t a4 :"
				+ a4 + "\n" + "\t a6 :" + a6 + "\n" + "\t G :"
				+ generator.toString();
		return res;

	}

	/**
	 * Perform addition of two P and Q
	 * 
	 * @param P
	 *            Point P
	 * @param Q
	 *            Point Q
	 * @param lambda
	 *            value of Lambda
	 * @param sum
	 *            the sum point
	 */
	private Point add(Point P, Point Q, BigInteger lambda)
	{
		BigInteger temp, resultX, resultY;

		resultX = new BigInteger(lambda.toString());
		resultY = new BigInteger(lambda.toString());

		// Compute xr
		resultX = resultX.multiply(lambda); // lambda^2
		resultX = resultX.subtract(P.getX()); // lambda^2 - xp
		resultX = resultX.subtract(Q.getX()); // lambda^2 - xp - xq
		resultX = resultX.mod(p); // modulo

		// Compute yr
		temp = lambda.negate(); // -lambda
		temp = temp.multiply(resultX); // -lambda * xr
		resultY = resultY.multiply(P.getX()); // lambda * xp (Result_Y is
												// initialised
		// with the value of lamda
		resultY = resultY.add(temp); // (-lambda * xr) + (lambda * xp)
		resultY = resultY.subtract(P.getY()); // (-lambda * xr) + (lambda *
												// xp) - yp
		resultY = resultY.mod(p);

		// return result
		return new Point(resultX, resultY);
	}

	/**
	 * Double a Point P
	 * 
	 * @param P
	 *            Point P
	 * @param doubleP
	 *            2*P
	 */
	private Point doublePoint(Point P)
	{

		BigInteger lambda, temp;
		BigInteger three = new BigInteger("3");

		if (P.isInfinite())
		{
			Point doubleP = new Point("0", "0");
			doubleP.setInfinite(true);
			return doubleP;
		}

		// Compute lambda
		// Compute numerator
		lambda = new BigInteger(P.getX().toString());
		lambda = lambda.multiply(P.getX()); // xp^2
		lambda = lambda.multiply(three); // 3*xp^2
		lambda = lambda.add(a4); // 3*xp^2 + a4

		// Compute denominator
		temp = new BigInteger("2");
		temp = temp.multiply(P.getY());
		// We can't compute integer division as it is not reliable, so invert
		// denominator to compute a*b^-1 instead of a/b
		temp = temp.modInverse(p);

		// Compute "division"
		lambda = lambda.multiply(temp);
		// Compute remainder to stay on Fp
		lambda = lambda.mod(p);

		// Double the point
		return add(P, P, lambda);

	}

	/**
	 * Perform addition of two different Points P and Q
	 * 
	 * @param P
	 *            Point P
	 * @param Q
	 *            Point Q
	 * @param sum
	 *            P+Q
	 */
	private Point addDifferentPoints(Point P, Point Q)
	{

		BigInteger lambda, temp;

		// Compute lambda
		// Compute numerator
		lambda = new BigInteger(P.getY().toString());
		lambda = lambda.subtract(Q.getY()); // yp - yq

		// Compute denominator
		temp = new BigInteger(P.getX().toString());
		temp = temp.subtract(Q.getX()); // xp - xq
		// We can't compute integer division as it is not reliable, so invert
		// denominator to compute a*b^-1 instead of a/b
		temp = temp.modInverse(p);

		// Compute "division"
		lambda = lambda.multiply(temp);
		// Compute remainder to stay on Fp
		lambda = lambda.mod(p);

		// Add the two points
		return add(P, Q, lambda);

	}

	/**
	 * Compute the opposite of the Input
	 * 
	 * @param P
	 *            Point P
	 * @param opposite
	 *            the opposite point of P
	 */
	public Point opposite(Point P)
	{

		Point opposite = new Point(P.getX(), P.getY().negate().mod(p));
		opposite.setInfinite(P.isInfinite());
		return opposite;
	}

	/**
	 * Compute sum of two Point P and Q
	 * 
	 * @param P
	 *            Point P
	 * @param Q
	 *            Point Q
	 * @param sum
	 *            P+Q
	 */
	public Point add(Point P, Point Q)
	{

		Point temp;
		Point sum;
		// Is P infinite ?
		if (P.isInfinite())
		{
			// Result is Q
			sum = new Point(Q.getX(), Q.getY());
			sum.setInfinite(Q.isInfinite());
			return sum;
		}

		// Is Q infinite ?
		if (Q.isInfinite())
		{
			// Result is P
			sum = new Point(P.getX(), P.getY());
			sum.setInfinite(P.isInfinite());
			return sum;
		}

		// Are P and Q opposite ?
		temp = opposite(Q);

		// Result is infinite
		if (P.isEqual(temp))
		{
			sum = new Point("0", "0");
			sum.setInfinite(true);
			return sum;
		}
		// Not infinite, choose correct adding function
		else
		{
			// Is P equal to Q ?
			if (P.isEqual(Q))
				return doublePoint(P); // Double the point
			else
				return addDifferentPoints(P, Q); // Add the two
													// different points
		}
	}

	/**
	 * Multiply an Point P with a Factor
	 * 
	 * @param P
	 *            Point P
	 * @param factor
	 *            factor
	 * @param result
	 *            factor*P
	 */
	public Point multiply(Point P, BigInteger factor)
	{
		int bitsCount, i;
		Point pointTemp;
		Point result = new Point("0", "0");
		// Initialize variables
		pointTemp = new Point(P);
		// Retrieve how many bits are used to store the factor number
		bitsCount = factor.bitLength();
		// Double-and-add starting from most significant bit to minimize
		// computations
		result.setInfinite(true);
		for (i = bitsCount - 1; i >= 0; i--)
		{
			// Always double the point
			result = doublePoint(result);
			// But add doubled values only when a factor bit is set
			if (factor.testBit(i))
			{
				result = add(result, pointTemp);
			}
		}

		// Free resources
		pointTemp = null;

		return result;
	}

	/**
	 * Test if an Point P is in this Elliptic Curve
	 * 
	 * @param P
	 *            Point P
	 * @return true if this P lay in this EC, false otherwise
	 */
	public boolean isOnCurve(Point P)
	{

		BigInteger leftHand, rightHand;
		BigInteger two = new BigInteger("2");

		// Compute x(x^2+a4)+a6
		// 1 mul less than original calcul : x^3 + a4 *x + a6
		// Initialize variables
		// Compute right part of the equation
		rightHand = a4.add(P.getX().modPow(two, p));
		rightHand = rightHand.multiply(P.getX());
		rightHand = rightHand.add(a6);
		rightHand = rightHand.mod(p);

		// Compute left part of the equation
		leftHand = P.getY().modPow(two, p);

		// Are the two parts equal (modulo p) ?
		return leftHand.compareTo(rightHand) == 0;
	}

}
