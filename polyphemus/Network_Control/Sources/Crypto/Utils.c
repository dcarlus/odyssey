/** @file Utils.c
 * @see Utils.h for description.
 * @author Adrien RICCIARDI
 */
#include <sys/time.h>
#include <stdio.h>
#include <openssl/evp.h>
#include "Utils.h"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Private variables
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
/** Internal random state. */
static gmp_randstate_t Random_State;

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Public functions
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void UtilsInitializeRandomGenerator(void)
{
	struct timeval Time;

	// Get a pseudo random seed
	gettimeofday(&Time, NULL);

	// Initialize GMP random number generator
	gmp_randinit_default(Random_State);
	gmp_randseed_ui(Random_State, (unsigned long) Time.tv_usec);
}

void UtilsGenerateRandomNumber(mpz_t Modulus, mpz_t Random_Number)
{
	mpz_urandomm(Random_Number, Random_State, Modulus);
}

void UtilsFreeRandomGenerator(void)
{
	gmp_randclear(Random_State);
}

void UtilsGenerateKeyPair(TEllipticCurve *Pointer_Elliptic_Curve, TPoint *Pointer_Point_Public_Key, mpz_t Private_Key)
{
	// Generate private key
	UtilsGenerateRandomNumber(Pointer_Elliptic_Curve->p, Private_Key);

	// Generate public key
	ECMultiplication(Pointer_Elliptic_Curve, &Pointer_Elliptic_Curve->Point_Generator, Private_Key, Pointer_Point_Public_Key);
}

int UtilsComputeHash(void *Pointer_Data_Buffer, size_t Data_Buffer_Size, void *Pointer_Output_Hash)
{
        EVP_MD_CTX Context;

        OpenSSL_add_all_digests();

        // Initialize SSL context
        EVP_MD_CTX_init(&Context);

        // Select SHA-256 algorithm
        if (!EVP_DigestInit_ex(&Context, EVP_sha256(), NULL))
        {
                EVP_MD_CTX_cleanup(&Context);
                return 0;
        }

        // "Digest" data to hash
        if (!EVP_DigestUpdate(&Context, Pointer_Data_Buffer, Data_Buffer_Size))
        {
                EVP_MD_CTX_cleanup(&Context);
                return 0;
        }

        // Output hash
        if (!EVP_DigestFinal_ex(&Context, Pointer_Output_Hash, NULL))
        {
                EVP_MD_CTX_cleanup(&Context);
                return 0;
        }

        EVP_MD_CTX_cleanup(&Context);
        return 1;
}
