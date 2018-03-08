/**
 * ============================================================================
 * @file    dh.cpp
 *
 * @brief   
 * @details 
 *
 * @version 1.0  
 * @date    2013-06-07 14:45:07
 *
 * @author  shizhijie, shizhijie@baofeng.com
 * ============================================================================
 */

#include <stdio.h>
#include <memory.h>
#include <iostream>
#include <openssl/dh.h>

int main(void)
{
	DH *d1 = NULL, *d2 = NULL;
	BIO *b = NULL;
	int ret = 0, size = 0, i = 0, len1 = 0, len2 = 0;
	unsigned char sharekey1[128] = { 0 }, sharekey2[128] = { 0 };

	// construct the DH structure.
	d1 = DH_new(), d2 = DH_new();

	// generate a secret paramenters that can be public for d1.
	// generate p and g.
	ret = DH_generate_parameters_ex(d1, 64, DH_GENERATOR_2, NULL);
	if (ret != 1)
	{
		printf("DH_generate_parameters_ex err!\n");
		return -1;
	}

	// check the secrete paramenters.
	ret = DH_check(d1, &i);
	if (ret != 1)
	{
		printf("DH_check_err!\n");
		if (i & DH_CHECK_P_NOT_PRIME)
		{
			printf("p value is not prime\n");
		}
		if (i & DH_CHECK_P_NOT_SAFE_PRIME)
		{
			printf("p value is not a safe prime\n");
		}
		if (i & DH_UNABLE_TO_CHECK_GENERATOR)
		{
			printf("unable to check the generator value\n");
		}
		if (i & DH_NOT_SUITABLE_GENERATOR)
		{
			printf("the g value is not a generator\n");
		}
	}
	printf("DH paramenters appear to be ok.\n");

	// the length of secret key
	size = DH_size(d1);
	printf("DH key1 size: %d\n", size);

	// generator public-private key
	// generate pubkey and privkey.
	ret = DH_generate_key(d1);
	if (ret != 1)
	{
		printf("DH_generate_key err!\n");
		return -1;
	}

	// p and g are public secret key paramenters, can be copied.
	// p and g are copied from d1.
	d2->p = BN_dup(d1->p); d2->g = BN_dup(d1->g);

	// generator public-private key to test shared key
	// generate pubkey and privkey.
	ret = DH_generate_key(d2);
	if (ret != 1)
	{
		printf("DH_generate_key err!\n");
		return -1;
	}

	// check public key
	ret = DH_check_pub_key(d1, d1->pub_key, &i);
	if (ret != 1)
	{
		if (i & DH_CHECK_PUBKEY_TOO_SMALL)
		{
			printf("pub key too small\n");
		}
		if (i & DH_CHECK_PUBKEY_TOO_LARGE)
		{
			printf("pub key too large\n");
		}
	}

	// compute share key with s = g ^ privkey mod p
	len1 = DH_compute_key(sharekey1, d2->pub_key, d1);
	len2 = DH_compute_key(sharekey2, d1->pub_key, d2);
	if (len1 != len2)
	{
		printf("generate share key fail - 1\n");
		return -1;
	}
	if (memcmp(sharekey1, sharekey2, len1) != 0)
	{
		printf("generate share key fail - 2\n");
		return -1;
	}

	printf("generate share key successfully\n");

	b = BIO_new(BIO_s_file());
	BIO_set_fp(b, stdout, BIO_NOCLOSE);

	// print secret key
	DHparams_print(b, d1);
	BIO_free(b);

	DH_free(d1), DH_free(d2);

	return 0;
}
