/**
 * ============================================================================
 * @file    evp_digest.cpp
 *
 * @brief   
 * @details 
 *
 * @version 1.0  
 * @date    2013-06-07 16:20:45
 *
 * @author  shizhijie, shizhijie@baofeng.com
 * ============================================================================
 */

#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>

int main(int /*argc*/, char *argv[])
{
	EVP_MD_CTX mdctx;
	const EVP_MD *md = NULL;
	const char mess1[] = "Test Message\n";
	const char mess2[] = "Hello World\n";
	unsigned char md_value[EVP_MAX_MD_SIZE] = { 0 };
	unsigned int md_len = 0, i = 0;

	// load all EVP_Digest* functions
	OpenSSL_add_all_digests();

	if (NULL == argv[1])
	{
		printf("Usage: mdtest digestname\n");
		exit(EXIT_FAILURE);
	}

	// get the algrithm struct of EVP_MD via the digest's name.
	md = EVP_get_digestbyname(argv[1]);
	if (NULL == md)
	{
		printf("Unknown message digest %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	// initiate the digest struct mdctx, it is nesscessary for the calling to EVP_DigestInit_ex.
	EVP_MD_CTX_init(&mdctx);
	EVP_MD_CTX_set_flags(&mdctx, EVP_MD_CTX_FLAG_ONESHOT);
	// set mdctx with the structure md, and use a default algrithm when impl is NULL.
	EVP_DigestInit_ex(&mdctx, md, NULL);
	// compute the digest, and it can be called much times for more data.
	EVP_DigestUpdate(&mdctx, mess1, strlen(mess1));
//	EVP_DigestUpdate(&mdctx, mess2, strlen(mess2));
	// complete the compute of digest, and store digest's info in md_value, its length in md_len
	EVP_DigestFinal_ex(&mdctx, md_value, &md_len);
	// cleanup all resource that mdctx occupied, it's neccessary if use *_ex functions.
	EVP_MD_CTX_cleanup(&mdctx);

	printf("Digest is: 0x");
	for (i = 0; i < md_len; ++i)
	{
		printf("%02x", md_value[i]);
	}
	printf("\n");

	EVP_Digest(mess1, strlen(mess1), md_value, NULL, EVP_sha256(), NULL);
	printf("Digest is: 0x");
	for (i = 0; i < md_len; ++i)
	{
		printf("%02x", md_value[i]);
	}
	printf("\n");

	return 0;
}
