#include "AES.h"

void handleErrors(void)
{
    ERR_print_errors_fp(stderr);
    abort();
}

EVP_CIPHER_CTX* AESCreate()
{
	EVP_CIPHER_CTX *ctx = NULL;
	ERR_load_crypto_strings();
	OpenSSL_add_all_algorithms();
	OPENSSL_config(NULL);
	if (!(ctx = EVP_CIPHER_CTX_new())) handleErrors();
	//EVP_CIPHER_CTX_set_padding(ctx,0);
	return ctx;
}

int AESCipherInit(EVP_CIPHER_CTX *ctx, unsigned char *key, unsigned char *iv)
{
   return EVP_EncryptInit_ex(ctx, EVP_aes_256_ctr(), NULL, key, iv);

}

int AESDecipherInit(EVP_CIPHER_CTX *ctx, unsigned char *key, unsigned char *iv)
{	
   return EVP_DecryptInit_ex(ctx, EVP_aes_256_ctr(), NULL, key, iv);
}
   	

int AESCipher(EVP_CIPHER_CTX *ctx, unsigned char *plaintext, int plaintext_len, unsigned char *ciphertext)
{
    int len;
    int ciphertext_len;

    /* Provide the message to be encrypted, and obtain the encrypted output.
     * EVP_EncryptUpdate can be called multiple times if necessary
     */
    if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
	handleErrors();
    ciphertext_len = len;

    /* Finalise the encryption. Further ciphertext bytes may be written at
     * this stage.
     */
/*    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) handleErrors();
    ciphertext_len += len;*/

    return ciphertext_len;
}

int AESDecipher(EVP_CIPHER_CTX *ctx, unsigned char *ciphertext, int ciphertext_len, unsigned char *plaintext)
{

    int len;

    int plaintext_len;

    /* Provide the message to be decrypted, and obtain the plaintext output.
     * EVP_DecryptUpdate can be called multiple times if necessary
     */
    if (1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
	handleErrors();
    plaintext_len = len;

    /* Finalise the decryption. Further plaintext bytes may be written at
     * this stage.
     */
    if (1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len)) handleErrors();
    plaintext_len += len;

    return plaintext_len;
}

void AESCleanUp(EVP_CIPHER_CTX *ctx)
{
	EVP_CIPHER_CTX_free(ctx);
}


