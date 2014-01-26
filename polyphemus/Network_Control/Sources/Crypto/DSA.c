/** @file DSA.c
 * @see DSA.h for description.
 * @author Adrien RICCIARDI
 */
#include <stdio.h>
#include <gmp.h>
#include "Elliptic_Curves.h"
#include "Point.h"
#include "Utils.h"
#include "../Log.h"
#include "DSA.h"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Private functions
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
/** Check if the number is comprised between 1 and Number_Order - 1.
 * @param Number The number to check.
 * @param Number_Order The order of the group.
 * @return 1 if the number is in bounds or 0 if not.
 */
static int IsNumberInBounds(mpz_t Number, mpz_t Number_Order)
{
	if (mpz_cmp_ui(Number, 1) < 0) return 0;
	if (mpz_cmp(Number, Number_Order) >= 0) return 0;
	return 1;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Public functions
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void DSASign(TEllipticCurve *Pointer_Curve, unsigned char *Pointer_Message, size_t Message_Length, mpz_t Private_Key, mpz_t Output_Number_U, mpz_t Output_Number_V)
{
	unsigned char Buffer_Hash[UTILS_HASH_SIZE_BYTES];
	mpz_t Number_Temp, Number_Hash, Number_Random;
	TPoint Point;

	// Initialize variables
	mpz_init(Number_Temp);
	mpz_init(Number_Hash);
	mpz_init(Number_Random);
	PointCreate(0, 0, &Point);

	// Compute message hash
	UtilsComputeHash(Pointer_Message, Message_Length, Buffer_Hash);
	UTILS_MPZ_IMPORT(Buffer_Hash, Number_Hash);

	// Generate signature pair (u, v)
	while (1)
	{
		// Get a random K between 1 et n - 1
		do
		{
			UtilsGenerateRandomNumber(Pointer_Curve->n, Number_Random);
		} while (!IsNumberInBounds(Number_Random, Pointer_Curve->n));

		// Compute a curve point
		ECMultiplication(Pointer_Curve, &Pointer_Curve->Point_Generator, Number_Random, &Point);

		// Calculate 'u'
		mpz_mod(Output_Number_U, Point.X, Pointer_Curve->n);
		// Retry if the computed 'u' is 0
		if (mpz_cmp_ui(Output_Number_U, 0) == 0) continue;

		// Calculate 'v'
		mpz_mul(Number_Temp, Output_Number_U, Private_Key); // u * s
		mpz_add(Number_Temp, Number_Temp, Number_Hash); // H(m) + (u * s)
		mpz_invert(Output_Number_V, Number_Random, Pointer_Curve->n); // Compute k^-1 mod n
		mpz_mul(Number_Temp, Output_Number_V, Number_Temp); // (k^-1) * (H(m) + (u * s))
		mpz_mod(Output_Number_V, Number_Temp, Pointer_Curve->n); // (k^-1) * (H(m) + (u * s)) mod n

		// Retry if the computed 'v' is 0
		if (mpz_cmp_ui(Output_Number_V, 0) != 0) break;
	}

	// Free resources
	mpz_clear(Number_Temp);
	mpz_clear(Number_Hash);
	mpz_clear(Number_Random);
	PointFree(&Point);
}

int DSACheck(TEllipticCurve *Pointer_Curve, unsigned char *Pointer_Message, size_t Message_Length, TPoint *Pointer_Public_Key, mpz_t Number_U, mpz_t Number_V)
{
	unsigned char Buffer_Hash[UTILS_HASH_SIZE_BYTES];
	mpz_t Number_Hash, Number_Temp, Number_U_Temp, Number_V_Temp;
	TPoint Point_Temp, Point_Temp_2;
	int Return_Value = 0;

	// Initialize variables
	mpz_init(Number_Hash);
	mpz_init(Number_Temp);
	mpz_init(Number_U_Temp);
	mpz_init(Number_V_Temp);
	PointCreate(0, 0, &Point_Temp);
	PointCreate(0, 0, &Point_Temp_2);

	// Make copy of provided parameters to avoid changing their value
	mpz_set(Number_U_Temp, Number_U);
	mpz_set(Number_V_Temp, Number_V);

	// Check parameters correctness
	// 'u' must be between 1 and n - 1
	if (!IsNumberInBounds(Number_U_Temp, Pointer_Curve->n))
	{
		Log(LOG_ERR, "[DSA.DSACheck] Number U is not in bounds.");
		goto Exit;
	}

	// 'v' must be between 1 and n - 1
	if (!IsNumberInBounds(Number_V_Temp, Pointer_Curve->n))
	{
		Log(LOG_ERR, "[DSA.DSACheck] Number V is not in bounds.");
		goto Exit;
	}

	// Alice's public key (Q) must not be equal to (0, 0)
	if (Pointer_Public_Key->Is_Infinite)
	{
		Log(LOG_ERR, "[DSA.DSACheck] Public key point is infinite.");
		goto Exit;
	}

	// n * Q must be equal to (0, 0)
	ECMultiplication(Pointer_Curve, Pointer_Public_Key, Pointer_Curve->n, &Point_Temp);
	if (!Point_Temp.Is_Infinite)
	{
		Log(LOG_ERR, "[DSA.DSACheck] n * Q point is infinite.");
		goto Exit;
	}

	// Check if Q lies on the curve
	if (!ECIsPointOnCurve(Pointer_Curve, Pointer_Public_Key))
	{
		Log(LOG_ERR, "[DSA.DSACheck] Q point does not lie on the curve.");
		goto Exit;
	}

	// Compute message hash
	UtilsComputeHash(Pointer_Message, Message_Length, Buffer_Hash);
	UTILS_MPZ_IMPORT(Buffer_Hash, Number_Hash);

	// Check signature
	// Compute (H(m) / v) mod n using v^-1
	mpz_invert(Number_V_Temp, Number_V_Temp, Pointer_Curve->n); // Only v^-1 is used by other calculations
	mpz_mul(Number_Temp, Number_Hash, Number_V_Temp);
	mpz_mod(Number_Temp, Number_Temp, Pointer_Curve->n);

	// Compute (H(m) / v mod n) * P
	ECMultiplication(Pointer_Curve, &Pointer_Curve->Point_Generator, Number_Temp, &Point_Temp);

	// Compute u / v mod n using v^-1
	mpz_mul(Number_Temp, Number_U_Temp, Number_V_Temp);
	mpz_mod(Number_Temp, Number_Temp, Pointer_Curve->n);

	// Multiply to public key Q
	ECMultiplication(Pointer_Curve, Pointer_Public_Key, Number_Temp, &Point_Temp_2);

	// Add the two points
	ECAddition(Pointer_Curve, &Point_Temp, &Point_Temp_2, &Point_Temp);

	// Is resulting point X coordinate equal to u ?
	mpz_mod(Number_Temp, Point_Temp.X, Pointer_Curve->n);
	if (mpz_cmp(Number_U_Temp, Number_Temp) == 0)
	{
		Log(LOG_DEBUG, "[DSA.DSACheck] Signature matched.");
		Return_Value = 1;
	}

Exit:
	// Free resources
	mpz_clear(Number_Hash);
	mpz_clear(Number_Temp);
	mpz_clear(Number_U_Temp);
	mpz_clear(Number_V_Temp);
	PointFree(&Point_Temp);
	PointFree(&Point_Temp_2);
	return Return_Value;
}
