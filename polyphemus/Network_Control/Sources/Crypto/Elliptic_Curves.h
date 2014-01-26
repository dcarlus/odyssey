/** @file Elliptic_Curves.h
 * Basic operations for Weierstrass elliptic curves.
 * @author Adrien RICCIARDI
 * @author Antoine MOISE
 * @version 1.0 : 08/10/2013
 * @version 1.1 : 13/01/2014, made some minor optimizations.
 */
#ifndef H_ELLIPTIC_CURVES_H
#define H_ELLIPTIC_CURVES_H

#include <gmp.h>
#include "Point.h"

//--------------------------------------------------------------------------------------------------------
// Constants
//--------------------------------------------------------------------------------------------------------
/** Use 256-bit (32 bytes) elliptic curves. */
#define ELLIPTIC_CURVE_SIZE_BYTES 32

//--------------------------------------------------------------------------------------------------------
// Types
//--------------------------------------------------------------------------------------------------------
/** Full elliptic curve description. */
typedef struct
{
	mpz_t p;
	mpz_t n;
	mpz_t a4;
	mpz_t a6;
	TPoint Point_Generator;
} TEllipticCurve;

//--------------------------------------------------------------------------------------------------------
// Functions
//--------------------------------------------------------------------------------------------------------
/** Initialize an empty curve.
 * @param Pointer_Curve The curve to initialize.
 * @warning You have to put real data in curve field after initializing it.
 */
void ECInit(TEllipticCurve *Pointer_Curve);

/** Load an elliptic curve from a .gp file.
 * @param String_Path Path to the file.
 * @param Pointer_Curve Where to store the curve.
 * @return 0 if the file was not found or 1 if the curve was successfully loaded.
 * @warning There is no need to call ECInit() before calling this function because it is called internally.
 */
int ECLoadFromFile(char *String_Path, TEllipticCurve *Pointer_Curve);

/** Free a curve.
 * @param Pointer_Curve The curve to destroy.
 */
void ECFree(TEllipticCurve *Pointer_Curve);

/** Compute the opposite of a point.
 * @param Pointer_Curve The elliptic curve.
 * @param Pointer_Input_Point The point to compute the opposite.
 * @param Pointer_Output_Point The computed opposite (the point must be created by the user).
 */
void ECOpposite(TEllipticCurve *Pointer_Curve, TPoint *Pointer_Input_Point, TPoint *Pointer_Output_Point);

/** Add two points.
 * @param Pointer_Curve The elliptic curve used for addition.
 * @param Pointer_Point_P First operand.
 * @param Pointer_Point_Q Second operand.
 * @param Pointer_Output_Point Result (the point must be created by the user).
 */
void ECAddition(TEllipticCurve *Pointer_Curve, TPoint *Pointer_Point_P, TPoint *Pointer_Point_Q, TPoint *Pointer_Output_Point);

/** Multiply a point with a scalar value.
 * @param Pointer_Curve The elliptic curve used for multiplication.
 * @param Pointer_Point The point to multiply.
 * @param Factor The scalar value to multiply the point with.
 * @param Pointer_Output_Point The result (il must be created by the user).
 */
void ECMultiplication(TEllipticCurve *Pointer_Curve, TPoint *Pointer_Point, mpz_t Factor, TPoint *Pointer_Output_Point);

/** Tell if a point lies on a curve or not.
 * @param Pointer_Curve The elliptic curve.
 * @param Pointer_Point The point to check.
 * @return 1 if the point lies on the curve or 0 otherwise.
 */
int ECIsPointOnCurve(TEllipticCurve *Pointer_Curve, TPoint *Pointer_Point);

#endif
