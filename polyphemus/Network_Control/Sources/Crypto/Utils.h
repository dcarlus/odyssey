/** @file Utils.h
 * Some utility functions.
 * @author Adrien RICCIARDI
 * @version 1.0 : 10/10/2013
 * @version 1.1 : 14/01/2014
 */
#ifndef H_UTILS_H
#define H_UTILS_H

#include <gmp.h>
#include "Elliptic_Curves.h"
#include "Point.h"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Constants
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
/** Length in bytes of a hash computed by the UtilsComputeHash() function. */
#define UTILS_HASH_SIZE_BYTES 32

/** Convert an mpz_t number to big endian binary data.
 * @param Source_Number The mpz number to convert.
 * @param Destination_Buffer The destination buffer.
 */
#define UTILS_MPZ_EXPORT(Source_Number, Destination_Buffer) mpz_export(Destination_Buffer, NULL, -1, ELLIPTIC_CURVE_SIZE_BYTES, 1, 0, Source_Number)

/** Convert a big endian exported mpz_t number buffer in the mpz_t representation.
 * @param Source_Buffer The buffer to convert.
 * @param Destination_Number The destination mpz.
 */
#define UTILS_MPZ_IMPORT(Source_Buffer, Destination_Number) mpz_import(Destination_Number, 1, -1, ELLIPTIC_CURVE_SIZE_BYTES, 1, 0, Source_Buffer)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Functions
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
/** Initialize the GMP random generator (same as srand()). */
void UtilsInitializeRandomGenerator(void);

/** Generate a random number.
 * @param Modulus The number will be in range 0..Modulus - 1.
 * @param Output_Number On output, store the generated random number.
 */
void UtilsGenerateRandomNumber(mpz_t Modulus, mpz_t Output_Number);

/** Free the previously initialized random generator. */
void UtilsFreeRandomGenerator(void);

/** Generate a private and a public keys on the specified elliptic curve.
 * @param Pointer_Elliptic_Curve The elliptic curve.
 * @param Pointer_Point_Public_Key On output, will contain the generated public key.
 * @param Private_Key On output, will contain the generated private key.
 */
void UtilsGenerateKeyPair(TEllipticCurve *Pointer_Elliptic_Curve, TPoint *Pointer_Point_Public_Key, mpz_t Private_Key);

/** Use the SHA-256 algorithm to compute the hash of the data.
 * @param Pointer_Data_Buffer The buffer containing the data to hash.
 * @param Data_Buffer_Size Size of the data to hash.
 * @param Pointer_Output_Hash On output, hold the hash (the output buffer must be almost UTILS_HASH_LENGTH bytes long).
 * @return 1 if the hash was correctly computed or 0 if an error occured.
 */
int UtilsComputeHash(void *Pointer_Data_Buffer, size_t Data_Buffer_Size, void *Pointer_Output_Hash);

#endif
