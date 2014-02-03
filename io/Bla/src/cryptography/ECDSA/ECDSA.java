package cryptography.ECDSA;

import java.math.BigInteger;
import cryptography.Algorithms;
import cryptography.EC.EllipticCurve;
import cryptography.EC.Point;

/**
 * 
 * @author Antoine MOÏSE Contains ECDSA sign process, and verify process
 */
public class ECDSA
{

	/**
	 * Perform ECDSA signature
	 * 
	 * @param curve
	 *            Elliptic Curve used for Signature
	 * @param message
	 *            message to be signed
	 * @param keys
	 *            ECDSA private and public Key, we only use the private key
	 * @return ECDSA Signature
	 */
	public static Signature Sign(EllipticCurve curve, byte[] message,
			KeyPair keys)
	{

		Point point = new Point("0", "0");
		byte hash[] = null;
		BigInteger numberHash;
		BigInteger U;
		BigInteger V;
		BigInteger temp;
		hash = message;
		assert (hash != null);
		assert (hash.length == 32);
		numberHash = new BigInteger(1, hash);
		while (true)
		{
			BigInteger K = Algorithms.random(curve.getN());
			// Compute K*generator
			point = curve.multiply(curve.getGenerator(), K);

			// Compute U
			U = point.getX().mod(curve.getN());
			System.out.println(U);
			if (U.compareTo(BigInteger.ZERO) == 0)
				continue;

			// Compute V
			temp = U.multiply(keys.getPrivateKey());
			temp = temp.add(numberHash);

			K = K.modInverse(curve.getN());
			temp = temp.multiply(K);
			V = temp.mod(curve.getN());
			if (V.compareTo(BigInteger.ZERO) != 0)
				break;
		}

		return new Signature(U, V);
	}

	/**
	 * Verify an ECDSA Signature
	 * 
	 * @param curve
	 *            Elliptic Curve used for Signature
	 * @param s
	 *            Signature to Check
	 * @param keys
	 *            ECDSA private and public Key, we only use the public key
	 * @param message
	 *            message to be signed
	 * @return true if the signature is correct, false else
	 */
	public static boolean Verify(EllipticCurve curve, Signature s,
			KeyPair keys, byte[] hash)
	{

		BigInteger U = s.getU();
		BigInteger V = s.getV();

		Point point = new Point("0", "0");
		Point point2 = new Point("0", "0");

		BigInteger NumberHash;
		BigInteger numberTemp;

		// 'u' must be between 1 and n - 1)
		if (!inBound(BigInteger.ONE, curve.getN(), U))
		{
			System.out.println("\nError : 'u' is not in [1; n - 1].\n");
			return false;
		}

		// 'v' must be between 1 and n - 1)
		if (!inBound(BigInteger.ONE, curve.getN(), V))
		{
			System.out.println("\nError : 'v' is not in [1; n - 1].\n");
			return false;
		}

		// Alice's public key (Q) must not be equal to (0, 0)
		if (keys.getPublicKey().isInfinite())
		{
			System.out
					.printf("\nError : Alice's public key is equal to (0, 0).\n");
			return false;
		}

		// n * Q must be equal to (0, 0)
		point = curve.multiply(keys.getPublicKey(), curve.getN());
		if (!point.isInfinite())
		{
			System.out.printf("\nError : n.Q != (0, 0).\n");
			System.out.println(point);
		}

		// Check if Q lies on the curve
		if (!curve.isOnCurve(keys.getPublicKey()))
		{
			System.out.printf("\nError : Q is not a point of the curve.\n");
			return false;
		}
		System.out.printf("done.\n\n");

		NumberHash = new BigInteger(1, hash);
		// Compute (H(m) / v) mod n using v^-1
		V = V.modInverse(curve.getN()); // Only v^-1 is used by other
										// calculations

		numberTemp = V.multiply(NumberHash);
		numberTemp = numberTemp.mod(curve.getN());

		// Compute (H(m) / v mod n) * P
		point = curve.multiply(curve.getGenerator(), numberTemp);

		// Compute u / v mod n using v^-1
		numberTemp = U.multiply(V);
		numberTemp = numberTemp.mod(curve.getN());

		// Multiply to public key Q
		point2 = curve.multiply(keys.getPublicKey(), numberTemp);

		// Add the two points
		point = curve.add(point, point2);

		// Is resulting point X coordinate equal to u ?
		numberTemp = point.getX().mod(curve.getN());

		if (U.compareTo(numberTemp) == 0)
		{
			System.out.printf("SUCCESS : signature matched.\n");
			return true;
		}
		else
			System.out.printf("FAILURE : bad signature.\n");
		return false;
	}

	public static boolean inBound(BigInteger minValue, BigInteger maxValue,
			BigInteger val)
	{

		return minValue.compareTo(val) <= 0 && maxValue.compareTo(val) > 0;
	}
}
