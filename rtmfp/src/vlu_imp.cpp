/**
 * ============================================================================
 * @file    vlu_imp.c
 *
 * @brief   
 * @details 
 *
 * @version 1.0  
 * @date    2013-04-26 18:34:30
 *
 * @author  shizhijie, shizhijie@baofeng.com
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#if 0
static size_t write7bitInt(uint64_t value, void *dst)
{
	uint64_t v2;
	size_t v3;
	signed int v4;
	char source[12];

	v2 = value;
	v3 = 0;
	v4 = 10;

	do
	{
		--v4;
		if (v3)
		{
			source[v4] = (v2 & 0x7F) | 0x80;
		}
		else
		{
			source[v4] = v2 & 0x7F;
		}
		v2 >>= 7;
		++v3;
	} while (v2 && v3 < 10);

	if (dst)
	{
		memmove(dst, &source[v4], v3);
	}

	return v3;
}
#endif

uint32_t read7bit(const char *pstr)
{
	uint8_t vlu_nbyte = 0, vlu_byte = 0;
	uint32_t vlu_value = 0;
	vlu_byte = *pstr++;
	while ((vlu_byte & 0x80) && vlu_nbyte++ < 3)
	{
		vlu_value <<= 7;
		vlu_value |= (vlu_byte & 0x7F);
		vlu_byte = *pstr++;
	}
	vlu_value <<= ((vlu_nbyte < 3) ? 7 : 8);
	vlu_value |= vlu_byte;
	return vlu_value;
}

uint64_t read7bit_long(const char *pstr)
{
	uint8_t vlu_nbyte = 0, vlu_byte = 0;
	uint64_t vlu_value = 0;
	vlu_byte = *pstr++;
	while ((vlu_byte & 0x80) && vlu_nbyte++ < 8)
	{
		vlu_value <<= 7;
		vlu_value |= (vlu_byte & 0x7F);
		vlu_byte = *pstr++;
	}
	vlu_value <<= ((vlu_nbyte < 8) ? 7 : 8);
	vlu_value |= vlu_byte;
	return vlu_value;
}

static uint8_t calc_vlu7bit_size(uint64_t value)
{
	uint64_t limit = 0x80;
	uint8_t vlu_nbyte = 1;
	while (value >= limit)
	{
		limit <<= 7;
		++vlu_nbyte;
	}
	return vlu_nbyte;
}

uint32_t write7bit(uint32_t value)
{
	uint32_t vlu_value = 0;
	char *p_vlu_buf = reinterpret_cast<char *>(&vlu_value);
	
	uint8_t shift = (calc_vlu7bit_size(value) - 1) *  7;
	bool max = (shift >= 21);
	if (max) ++shift;

	while (shift >= 7)
	{
		*p_vlu_buf++ = (0x80 | ((value >> shift) & 0x7F));
		shift -= 7;
	}
	*p_vlu_buf++ = (max ? value & 0xFF : value & 0x7F);

	return vlu_value;
}

uint64_t write7bit_long(uint64_t value)
{
	uint64_t vlu_value = 0;
	char *p_vlu_buf = reinterpret_cast<char *>(&vlu_value);

	uint8_t shift = (calc_vlu7bit_size(value) - 1) * 7;
	bool max = (shift >= 63);
	if (max) ++shift;

	while (shift >= 7)
	{
		*p_vlu_buf++ = (0x80 | ((value >> shift) & 0x7F));		
		shift -= 7;
	}
	*p_vlu_buf++ = (max ? value & 0xFF : value & 0x7F);

	return vlu_value;
}

