#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>

void handleErrors(void)
{
  ERR_print_errors_fp(stderr);
  abort();
}

int envelope_seal(EVP_PKEY **pub_key, unsigned char *plaintext, int plaintext_len,
	unsigned char **encrypted_key, int *encrypted_key_len, unsigned char *iv,
	unsigned char *ciphertext)
{
	EVP_CIPHER_CTX *ctx;

	int ciphertext_len;

	int len;


	/* Create and initialise the context */
	if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

	/* Initialise the envelope seal operation. This operation generates
	 * a key for the provided cipher, and then encrypts that key a number
	 * of times (one for each public key provided in the pub_key array). In
	 * this example the array size is just one. This operation also
	 * generates an IV and places it in iv. */
	if(1 != EVP_SealInit(ctx, EVP_aes_256_cbc(), encrypted_key,
		encrypted_key_len, iv, pub_key, 1))
		handleErrors();

	/* Provide the message to be encrypted, and obtain the encrypted output.
	 * EVP_SealUpdate can be called multiple times if necessary
	 */
	if(1 != EVP_SealUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
		handleErrors();
	ciphertext_len = len;

	/* Finalise the encryption. Further ciphertext bytes may be written at
	 * this stage.
	 */
	if(1 != EVP_SealFinal(ctx, ciphertext + len, &len)) handleErrors();
	ciphertext_len += len;

	/* Clean up */
	EVP_CIPHER_CTX_free(ctx);

	return ciphertext_len;
}

int envelope_open(EVP_PKEY *priv_key, unsigned char *ciphertext, int ciphertext_len,
	unsigned char *encrypted_key, int encrypted_key_len, unsigned char *iv,
	unsigned char *plaintext)
{
	EVP_CIPHER_CTX *ctx;

	int len;

	int plaintext_len;


	/* Create and initialise the context */
	if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

	/* Initialise the decryption operation. The asymmetric private key is
	 * provided and priv_key, whilst the encrypted session key is held in
	 * encrypted_key */
	if(1 != EVP_OpenInit(ctx, EVP_aes_256_cbc(), encrypted_key,
		encrypted_key_len, iv, priv_key))
		handleErrors();

	/* Provide the message to be decrypted, and obtain the plaintext output.
	 * EVP_OpenUpdate can be called multiple times if necessary
	 */
	if(1 != EVP_OpenUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
		handleErrors();
	plaintext_len = len;

	/* Finalise the decryption. Further plaintext bytes may be written at
	 * this stage.
	 */
	if(1 != EVP_OpenFinal(ctx, plaintext + len, &len)) handleErrors();
	plaintext_len += len;

	/* Clean up */
	EVP_CIPHER_CTX_free(ctx);

	return plaintext_len;
}

int main (void)
{
  unsigned char* plaintext = (unsigned char*) "hello";
  unsigned char output[128];
  int plaintext_len = strlen((const char*) plaintext);
  unsigned char* encrypted_key = new unsigned char[256];
  int encrypted_key_len = 0;
  unsigned char iv[128];
  unsigned char ciphertext[128];
  memset(iv, 0, 128);
  memset(ciphertext, 0, 128);

  FILE* public_key_file = fopen("../advanced/public.pem", "rt");
  FILE* private_key_file = fopen("../advanced/private.pem", "rt");

  EVP_PKEY* pub_key, *priv_key;
  pub_key = PEM_read_PUBKEY(public_key_file, nullptr, nullptr, nullptr);
  priv_key = PEM_read_PrivateKey(private_key_file, nullptr, nullptr, nullptr);

  int ciphertext_len = envelope_seal(&pub_key, plaintext, plaintext_len,
	&encrypted_key, &encrypted_key_len, iv, ciphertext);

  int output_len = envelope_open(priv_key, ciphertext, ciphertext_len,
      encrypted_key, encrypted_key_len, iv, output);

  printf("[%i] %.*s", output_len, output_len, output);

  delete [] encrypted_key;
  fclose(public_key_file);
  fclose(private_key_file);

  return 0;
}

