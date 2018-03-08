/**
 * ============================================================================
 * @file    endian_independent.c
 *
 * @brief   
 * @details 
 *
 * @version 1.0  
 * @date    2013-05-07 14:26:13
 *
 * @author  shizhijie, shizhijie@baofeng.com
 * ============================================================================
 */

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <arpa/inet.h>

const int i = 1;
#define is_bigendian() ((*(char *)&i) == 0)


typedef uint8_t byte, uint8, uint8_bitmask;
typedef uint16_t uint16, uint16_be, uint16_le;
typedef int16_t sint16, sint16_be, sint16_le;
typedef uint32_t uint32, uint32_be, uint32_le;
typedef int32_t sint32, sint32_be, sint32_le;
typedef struct __uint24 {
    uint8 b[3];
} uint24, uint24_be, uint24_le;
typedef uint64_t uint64, uint64_le, uint64_be;
typedef int64_t sint64, sint64_le, sint64_be;
typedef
#if SIZEOF_FLOAT == 8
    float
#elif SIZEOF_DOUBLE == 8
    double
#elif SIZEOF_LONG_DOUBLE == 8
    long double
#else
    uint64_t
#endif
number64, number64_le, number64_be;

//reverse_bytes - turn a BigEndian byte array into a LittleEndian integer
number64 reverse_bytes(byte *p, char len) {
#if 0
    uint r = 0;
    for (int i=0; i<len; i++)
        r |= (*(p+i) << (((len-1)*8)-8*i));
    return r;
#endif

#if 0
    uint64_t v = 0;
    byte *pv = reinterpret_cast<byte *>(&v);
    for (int i = 0; i < len; ++i)
    {
        pv[i] = p[len - i - 1];
    }
    return v;
#endif

#if 0
    /* swap 64 bits doubles */
    typedef union __convert_u {
        uint64 i;
        number64 f;
    } convert_u;

    convert_u c;
    byte *pv = reinterpret_cast<byte *>(&c.f);
    memset(pv, 0, sizeof(convert_u));
    for (int i = 0; i < len; ++i)
    {
        pv[i] = p[i];
    }

    //c.f = val_be;
    c.i = (((c.i & 0x00000000000000FFULL) << 56) |
		   ((c.i & 0x000000000000FF00ULL) << 40) |
		   ((c.i & 0x0000000000FF0000ULL) << 24) |
		   ((c.i & 0x00000000FF000000ULL) << 8)  |
		   ((c.i & 0x000000FF00000000ULL) >> 8)  |
		   ((c.i & 0x0000FF0000000000ULL) >> 24) |
		   ((c.i & 0x00FF000000000000ULL) >> 40) |
		   ((c.i & 0xFF00000000000000ULL) >> 56));
    return c.f;
#endif

#if 0
	uint32_t uiv = 0;
    byte *pv = reinterpret_cast<byte *>(&uiv);
    for (int i = 0; i < len; ++i)
    {
        pv[i] = p[i];
    }
	return htonl(uiv);
#endif
	std::reverse(p, p + len);
	number64 n64 = 0;
    byte *ptr = reinterpret_cast<byte *>(&n64);
    for (int i = 0; i < len; ++i)
    {
        ptr[i] = p[i];
    }
    return n64;	
}

int check_endian()
{
	int i = 1;
	char *p = (char *)&i;
	return (p[0] == 1) ? 0 : 1;
}

short reverseShort(short s)
{
	unsigned char c1, c2;
	if (is_bigendian())
	{
		return s;
	}
	else
	{
		c1 = s & 255;
		c2 = (s >> 8) & 255;

		return (c1 << 8) + c2;
	}
}

short reverseShort(unsigned char *c)
{
	short s;
	char *p = (char *)&s;

	if (is_bigendian())
	{
		p[0] = c[0];
		p[1] = c[1];
	}
	else
	{
		p[0] = c[1];
		p[1] = c[0];
	}

	return s;
}

int reverseInt(int i)
{
	unsigned char c1, c2, c3, c4;

	if (is_bigendian())
	{
		return i;
	}
	else
	{
		c1 = i & 255;
		c2 = (i >> 8) & 255;
		c3 = (i >> 16) & 255;
		c4 = (i >> 24) & 255;

		return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
	}
}

int reverseInt(unsigned char *c)
{
	int i;
	char *p = (char *)&i;

	if (is_bigendian())
	{
		p[0] = c[0];
		p[1] = c[1];
		p[2] = c[2];
		p[3] = c[3];
	}
	else
	{
		p[0] = c[3];
		p[1] = c[2];
		p[2] = c[1];
		p[3] = c[0];
	}

	return i;
}

int main(void)
{
	printf("sizeof(double) = %lu\n", sizeof(double));

	int val;
	unsigned char *ptr;
	ptr = (unsigned char *)&val;
	val = 0x12345678;

	unsigned char endian[2] = { 1, 0 };
	short x = *(short *)endian;
	printf("endian: %s => %d (%s endian) \n", endian, x, is_bigendian() ? "big" : "little");
	
	if (is_bigendian())
	{
		printf("ptr[0].ptr[1].ptr[2].ptr[3]\n%x.%x.%x.%x\n",
			ptr[0], ptr[1], ptr[2], ptr[3]);
	}
	else
	{
		printf("ptr[3].ptr[2].ptr[1].ptr[0]\n%x.%x.%x.%x\n",
			ptr[3], ptr[2], ptr[1], ptr[0]);
	}

	printf("this platform is %s endian.\n", (check_endian() == 1) ? "big" : "little");

	unsigned int j;
	long v = 0x112A380; /* value to play with */
	ptr = (unsigned char *)&v; /* byte pointer */

	/* observe value in host byte order */
	printf("\n");
	printf("v in hex: 0x%lx\n", v);
	printf("v by bytes: ");

	for (j = 0; j < sizeof(long); ++j)
	{
		printf("%x\t", ptr[j]);
	}
	printf("\n");

	/* observe value in network byte order */
	v = htonl(v);
	printf("\nafter htonl()\n\n");
	printf("v in hex: 0x%lx\n", v);
	printf("v by bytes: ");

	for (j = 0; j < sizeof(long); ++j)
	{
		printf("%x\t", ptr[j]);
	}
	printf("\n\n");

	int iv = 0x12345678;
	ptr = (unsigned char *)&iv;
	printf("iv in hex: 0x%x\n", iv);
	printf("iv by bytes: ");

	for (j = 0; j < sizeof(int); ++j)
	{
		printf("%x\t", ptr[j]);
	}
	printf("\n\n");

	printf("after reverseInt\n\n");
	iv = reverseInt(iv);

	printf("iv in hex: 0x%x\n", iv);
	printf("iv by bytes: ");

	for (j = 0; j < sizeof(int); ++j)
	{
		printf("%x\t", ptr[j]);
	}
	printf("\n");

	iv = reverseInt((unsigned char *)&iv);

	printf("iv in hex: 0x%x\n", iv);
	printf("iv by bytes: ");

	for (j = 0; j < sizeof(int); ++j)
	{
		printf("%x\t", ptr[j]);
	}
	printf("\n\n");

	uint64 value = 0x12345678;
	ptr = (unsigned char *)&value;
	printf("value in hex: 0x%lx\n", value);
	printf("value by bytes: ");
	for (j = 0; j < sizeof(uint64); ++j)
	{
		printf("%x\t", ptr[j]);
	}
	printf("\n\nafter reverse bytes\n\n");

	value = reverse_bytes(ptr, sizeof(value));
	printf("value in hex: 0x%lx\n", value);
	printf("value by bytes: ");
	for (j = 0; j < sizeof(uint64); ++j)
	{
		printf("%x\t", ptr[j]);
	}
	printf("\n\n");

	value = reverse_bytes(ptr, sizeof(value));
	printf("value in hex: 0x%lx\n", value);
	printf("value by bytes: ");
	for (j = 0; j < sizeof(uint64); ++j)
	{
		printf("%x\t", ptr[j]);
	}
	printf("\n\n");

	double dv = 12345678.0f;
	ptr = (unsigned char *)&dv;
	printf("dv: %lf\n", dv);
	printf("dv by bytes: ");
	for (j = 0; j < sizeof(double); ++j)
	{
		printf("%x\t", ptr[j]);
	}
	printf("\n\nafter reverse bytes\n\n");

	dv = reverse_bytes(ptr, sizeof(dv));
	printf("dv: %lf\n", dv);
	printf("dv by bytes: ");
	for (j = 0; j < sizeof(double); ++j)
	{
		printf("%x\t", ptr[j]);
	}
	printf("\n\n");

	dv = reverse_bytes(ptr, sizeof(dv));
	printf("dv: %lf\n", dv);
	printf("dv by bytes: ");
	for (j = 0; j < sizeof(double); ++j)
	{
		printf("%x\t", ptr[j]);
	}
	printf("\n\n");

	float fv = 12345678.0f;
	ptr = (unsigned char *)&fv;
	printf("fv: %lf\n", fv);
	printf("fv by bytes: ");
	for (j = 0; j < sizeof(float); ++j)
	{
		printf("%x\t", ptr[j]);
	}
	
	printf("\n\nafter htonl\n\n");

	fv = htonl(fv);
	
	printf("fv: %lf\n", fv);
	printf("fv by bytes: ");
	for (j = 0; j < sizeof(float); ++j)
	{
		printf("%x\t", ptr[j]);
	}
	printf("\n\n");

	fv = ntohl(fv);

	printf("fv: %lf\n", fv);
	printf("fv by bytes: ");
	for (j = 0; j < sizeof(float); ++j)
	{
		printf("%x\t", ptr[j]);
	}
	printf("\n\n");

	float fval = 12345678.0f;
	ptr = (unsigned char *)&fval;
	printf("fval: %lf\n", fval);
	printf("fval by bytes: ");
	for (j = 0; j < sizeof(float); ++j)
	{
		printf("%x\t", ptr[j]);
	}
	
	printf("\n\nafter htonl\n\n");

	fval = reverse_bytes(ptr, sizeof(fval));
	
	printf("fval: %lf\n", fval);
	printf("fval by bytes: ");
	for (j = 0; j < sizeof(float); ++j)
	{
		printf("%x\t", ptr[j]);
	}
	printf("\n\n");

	fval = ntohl(fval);

	printf("fval: %lf\n", fval);
	printf("fval by bytes: ");
	for (j = 0; j < sizeof(float); ++j)
	{
		printf("%x\t", ptr[j]);
	}
	printf("\n\n");

	return 0;
}
