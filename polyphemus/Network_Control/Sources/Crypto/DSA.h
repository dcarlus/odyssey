/** @file DSA.h
 * Compute and check the ECDSA signature of a message.
 * @author Adrien RICCIARDI
 * @version 1.1 : 17/01/2014
 * @version 1.2 : 24/01/2014, bugfixes.
 */
#ifndef H_DSA_H
#define H_DSA_H

#include <stdio.h> // For size_t
#include <gmp.h>
#include "Elliptic_Curves.h"
#include "Point.h"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Functions
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
/** Sign a message.
 * @param Pointer_Curve The curve used for calculations.
 * @param Pointer_Message The message to sign.
 * @param Message_Length Size of the message in bytes.
 * @param Private_Key The private key used to sign the message.
 * @param Output_Number_U On output, contain the generated signature 'u' number.
 * @param Output_Number_V On output, contain the generated signature 'v' number.
 */
void DSASign(TEllipticCurve *Pointer_Curve, unsigned char *Pointer_Message, size_t Message_Length, mpz_t Private_Key, mpz_t Output_Number_U, mpz_t Output_Number_V);

/** Check a message signature.
 * @param Pointer_Curve The curve used for calculations.
 * @param Pointer_Message The message to check.
 * @param Message_Length Size of message in bytes.
 * @param Pointer_Public_Key The public key used to check the message.
 * @param Number_U The signature 'u' number.
 * @param Number_V The signature 'v' number.
 * @return 0 if the signature is bad or 1 if there is a signature match.
 */
int DSACheck(TEllipticCurve *Pointer_Curve, unsigned char *Pointer_Message, size_t Message_Length, TPoint *Pointer_Public_Key, mpz_t Number_U, mpz_t Number_V);

#endif
