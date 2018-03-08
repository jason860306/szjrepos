/**
 * ============================================================================
 * @file    bitfield.c
 *
 * @brief   
 * @details 
 *
 * @version 1.0
 * @date    Thu Dec 20 18:05:49 CST 2012
 *
 * @author  shizhijie, shizhijie@baofeng.com
 * ============================================================================
 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stddef.h>

int main()
{
	struct foo
	{
		int a:1;
		int b:2;
		short c:1;
	} afoo;
	memset(&afoo, 0, sizeof(afoo));
	afoo.a = 1;
	afoo.b = 2;
	afoo.c = 1;
    /* error: attempt to take address of bit-field structure member ‘a’ */
	/* printf("offsets: a = %ld; b = %ld; c = %ld;\n", */
	/* 	   (long)offsetof(struct foo, a), */
	/* 	   (long)offsetof(struct foo, b), */
	/* 	   (long)offsetof(struct foo, c)); */
	printf("value in foo: a = 0x%x, b = 0x%x, c = 0x%x\n", afoo.a, afoo.b, afoo.c);
	printf("sizeof(afoo) = %lu\n", sizeof(afoo));

	struct foo1
	{
		int a:1;
		int :2;
		short c:1;
	} afoo1;
	memset(&afoo1, 0, sizeof(afoo1));
	afoo1.a = 1;
	afoo1.c = 1;

    /* error: attempt to take address of bit-field structure member ‘a’ */
	/* printf("offsets: a = %ld; c = %ld;\n", */
	/* 	   (long)offsetof(struct foo1, a), */
	/* 	   (long)offsetof(struct foo1, c)); */
	printf("value in foo1: a = 0x%x, c = 0x%x\n", afoo1.a, afoo1.c);
	printf("sizeof(afoo1) = %lu\n", sizeof(afoo1));

	struct foo2
	{
		char a:2;
		char b:3;
		char c:1;
	} afoo2;
	memset(&afoo2, 0, sizeof(afoo2));
	afoo2.a = 3;
	afoo2.b = 4;
	afoo2.c = 1;

    /* error: attempt to take address of bit-field structure member ‘a’ */
	/* printf("offsets: a = %ld; b = %ld; c = %ld;\n", */
	/* 	   (long)offsetof(struct foo2, a), */
	/* 	   (long)offsetof(struct foo2, b), */
	/* 	   (long)offsetof(struct foo2, c)); */
	printf("value in foo2: a = 0x%x, b = 0x%x, c = 0x%x\n", afoo2.a, afoo2.b, afoo2.c);
	printf("sizeof(afoo2) = %lu\n", sizeof(afoo2));

	struct foo3
	{
		char a:2;
		char b:3;
		char c:7;
	} afoo3;
	memset(&afoo3, 0, sizeof(afoo3));
    /*
	 * warning: overflow in implicit constant conversion
	 * 此种情况下会将a填充为从6的二进位中的低位开始向上对齐到a的最大位数的值。
	 * 比如：
	 * 6 = 0x110;
	 * afoo3.a = 0x10;
	 */
	afoo3.a = 6;
	afoo3.b = 5;
	afoo3.c = 100;

    /* error: attempt to take address of bit-field structure member ‘a’ */
	/* printf("offsets: a = %ld; b = %ld; c = %ld;\n", */
	/* 	   (long)offsetof(struct foo3, a), */
	/* 	   (long)offsetof(struct foo3, b), */
	/* 	   (long)offsetof(struct foo3, c)); */
	printf("value in foo3: a = 0x%x, b = 0x%x, c = 0x%x\n", afoo3.a, afoo3.b, afoo3.c);
	printf("sizeof(afoo3) = %lu\n", sizeof(afoo3));

	struct foo4
	{
		char a:2;
		char b:3;
		int c:1;
	} afoo4;
	memset(&afoo4, 0, sizeof(afoo4));
	afoo4.a = 3;
	afoo4.b = 6;
	afoo4.c = 1;

    /* error: attempt to take address of bit-field structure member ‘a’ */
	/* printf("offsets: a = %ld; b = %ld; c = %ld;\n", */
	/* 	   (long)offsetof(struct foo4, a), */
	/* 	   (long)offsetof(struct foo4, b), */
	/* 	   (long)offsetof(struct foo4, c)); */
	printf("value in foo4: a = 0x%x, b = 0x%x, c = 0x%x\n", afoo4.a, afoo4.b, afoo4.c);
	printf("sizeof(afoo4) = %lu\n", sizeof(afoo4));

	uint8_t p_ts[4] = { 0x47, 0x00, 0x00, 0x00 };
	uint16_t i_pid = 65230;
	p_ts[1] &= ~0x1f;
	p_ts[1] |= (i_pid >> 8) & 0x1f;
	p_ts[2] = i_pid & 0xff;
	
	return 0;
}
