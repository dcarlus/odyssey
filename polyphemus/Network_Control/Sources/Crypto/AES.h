#ifndef AES_H_INCLUDED
#define AES_H_INCLUDED

#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>
#include <gmp.h>

/** Size of a whole AES block. */
#define AES_BLOCK_SIZE_BYTES 16

/** AES key size in bytes. */
#define AES_KEY_SIZE_BYTES 32

/** Compute the size in bytes of the encrypted text corresponding to the given plain data size. The formula is (Number_Of_Corresponding_Blocks + 1) * Block_Size. */
//#define AES_CIPHERED_MESSAGE_SIZE_BYTES(Plain_Data_Size_Bytes) (((Plain_Data_Size_Bytes / AES_BLOCK_SIZE_BYTES) + 1) * AES_BLOCK_SIZE_BYTES)
#define AES_CIPHERED_MESSAGE_SIZE_BYTES(a) 48

/** Create a new AES 256 CTR context
 * @return ctx a new AES cipher context.
 */
EVP_CIPHER_CTX* AESCreate();

/**
	Initialise the AES Context to cipher data
	@param ctx cipher context
	@param key AES Secret Key
	@param iv AES iv
	@return -1 if error
*/
int AESCipherInit(EVP_CIPHER_CTX* ctx,unsigned char *key, unsigned char *iv);

/**
	Initialise the AES Context to decipher data
	@param ctx cipher context
	@param key AES Secret Key
	@param iv AES iv
	@return -1 if error
*/
int AESDecipherInit(EVP_CIPHER_CTX* ctx,unsigned char *key, unsigned char *iv);

/**
	Cipher data
	@param ctx cipher context
	@param plaintext plaintext to cipher
	@param plaintext_len plaintext length
	@param ciphertext plaintext which is ciphered
	@return length of ciphered data
*/
int AESCipher(EVP_CIPHER_CTX* ctx,unsigned char *plaintext, int plaintext_len, unsigned char *ciphertext);

/**
	Cipher data
	@param ctx cipher context
	@param plaintext plaintext to cipher
	@param plaintext_len plaintext length
	@param ciphertext plaintext which is ciphered
	@return length of ciphered data
*/
int AESDecipher(EVP_CIPHER_CTX* ctx,unsigned char *ciphertext, int ciphertext_len, unsigned char *plaintext);

void AESCleanUp(EVP_CIPHER_CTX *ctx);

#endif
