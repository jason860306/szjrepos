/**
 * ============================================================================
 * @file    ihello_chunk_imp.cpp
 *
 * @brief   
 * @details 
 *
 * @version 1.0  
 * @date    2013-06-13 14:11:12
 *
 * @author  shizhijie, shizhijie@baofeng.com
 * ============================================================================
 */

#include <string.h>
#include <algorithm>
#include "ihello_chunk_imp.h"

extern void hex_print(const uint8_t *pstr, uint32_t len);

uint32_t get_chunk_capacity(const ihello_chunk_t *p_ihello_chunk)
{
	return ((p_ihello_chunk == NULL) ? 0 : (sizeof(*p_ihello_chunk) +
											p_ihello_chunk->chunk_len));
}

uint32_t get_chunk_len(const ihello_chunk_t *p_ihello_chunk)
{
	return ((p_ihello_chunk == NULL) ? 0 : (p_ihello_chunk->chunk_len +
											sizeof(p_ihello_chunk->chunk_type) +
											sizeof(p_ihello_chunk->chunk_len)));
}

ihello_chunk_t *read_chunk_ihello(const uint8_t *pstr, ihello_chunk_t **pp_chunk)
{
	ihello_chunk_t *p_chunk = NULL;
	if (NULL == pstr)
	{
		return NULL;
	}
	if (NULL != pp_chunk)
	{
		p_chunk = *pp_chunk;
	}
	if (NULL == p_chunk)
	{
		p_chunk = new ihello_chunk_t();
	}
	p_chunk->chunk_type = *pstr;
	p_chunk->chunk_len = *reinterpret_cast<const uint16_t *>(
		pstr + offsetof(ihello_chunk_t, chunk_len));
	p_chunk->chunk_len = (p_chunk->chunk_len << 8) | (p_chunk->chunk_len >> 8);
	p_chunk->ignore = *(pstr + offsetof(ihello_chunk_t, ignore));
	p_chunk->epd_len = *(pstr + offsetof(ihello_chunk_t, epd_len));
	p_chunk->epd_type = *(pstr + offsetof(ihello_chunk_t, epd_type));
	uint16_t epd_len = p_chunk->epd_len - 1;
	p_chunk->p_epd_data = new uint8_t[epd_len];
	memset(p_chunk->p_epd_data, 0xff, epd_len);
	memcpy(p_chunk->p_epd_data, pstr + offsetof(ihello_chunk_t, p_epd_data), epd_len);
	memcpy(p_chunk->tag, pstr + offsetof(ihello_chunk_t, p_epd_data) + epd_len,
		   sizeof(p_chunk->tag));

	return p_chunk;
}

const uint8_t *write_chunk_ihello(const ihello_chunk_t *p_chunk, uint8_t **pp_chunk_data,
								  uint32_t &chunk_size)
{
	uint32_t ihello_size = get_chunk_len(p_chunk);
	if (NULL == p_chunk || (NULL != pp_chunk_data && NULL != *pp_chunk_data &&
							ihello_size > chunk_size))
	{
		return NULL;
	}
	uint8_t *p_chunk_data = NULL;
	if (NULL != pp_chunk_data)
	{
		p_chunk_data = *pp_chunk_data;
	}
	if (NULL == p_chunk_data)
	{
		p_chunk_data = new uint8_t[ihello_size];
		memset(p_chunk_data, 0xff, ihello_size);
		chunk_size = ihello_size;
	}
	memcpy(p_chunk_data, &p_chunk->chunk_type, sizeof(p_chunk->chunk_type));
	uint16_t chunk_len = p_chunk->chunk_len;
	chunk_len = (p_chunk->chunk_len << 8) | (p_chunk->chunk_len >> 8);
	memcpy(p_chunk_data + offsetof(ihello_chunk_t, chunk_len), &chunk_len, sizeof(chunk_len));
	memcpy(p_chunk_data + offsetof(ihello_chunk_t, ignore), &p_chunk->ignore,
		   sizeof(p_chunk->ignore));
	memcpy(p_chunk_data + offsetof(ihello_chunk_t, epd_len), &p_chunk->epd_len,
		   sizeof(p_chunk->epd_len));
	memcpy(p_chunk_data + offsetof(ihello_chunk_t, epd_type), &p_chunk->epd_type,
		   sizeof(p_chunk->epd_type));
	uint16_t epd_len = p_chunk->epd_len - 1;	
	memcpy(p_chunk_data + offsetof(ihello_chunk_t, p_epd_data), p_chunk->p_epd_data, epd_len);
	memcpy(p_chunk_data + offsetof(ihello_chunk_t, p_epd_data) + epd_len, p_chunk->tag,
		   sizeof(p_chunk->tag));

	return p_chunk_data;
}

ihello_chunk_t *create_ihello(uint8_t epd_type, const uint8_t *p_epd_data, uint32_t epd_len,
							  const uint8_t *p_tag, uint16_t tag_len,
							  ihello_chunk_t **pp_ihello)
{
	ihello_chunk_t *p_ihello = NULL;
	if (NULL != pp_ihello)
	{
		p_ihello = *pp_ihello;
	}
	if (NULL == p_ihello)
	{
		p_ihello = new ihello_chunk_t();
	}
	p_ihello->chunk_type = 0x30;
	p_ihello->epd_type = epd_type;
	p_ihello->epd_len = epd_len + sizeof(p_ihello->epd_type);
	p_ihello->p_epd_data = new uint8_t[p_ihello->epd_len - 1];
	memset(p_ihello->p_epd_data, 0xff, p_ihello->epd_len - 1);
	memcpy(p_ihello->p_epd_data, p_epd_data, p_ihello->epd_len - 1);
	p_ihello->ignore = p_ihello->epd_len + 1;

	memcpy(p_ihello->tag, p_tag, tag_len);

	p_ihello->chunk_len = sizeof(p_ihello->ignore) + sizeof(p_ihello->epd_len) +
		sizeof(p_ihello->epd_type) + (p_ihello->epd_len - 1) + tag_len;

	return p_ihello;
}

const ihello_chunk_t *chunk_clone(const ihello_chunk_t *p_ihello_chunk,
								  ihello_chunk_t **pp_new_ihello_chunk)
{
	ihello_chunk_t *p_ihello = NULL;
	if (NULL != pp_new_ihello_chunk)
	{
		p_ihello = *pp_new_ihello_chunk;
	}
	if (NULL == p_ihello_chunk)
	{
		return NULL;
	}
	if (NULL == p_ihello)
	{
		p_ihello = new ihello_chunk_t();
	}
	memcpy(p_ihello, p_ihello_chunk, sizeof(*p_ihello_chunk));
	p_ihello->p_epd_data = new uint8_t[p_ihello_chunk->epd_len - 1];
	memset(p_ihello->p_epd_data, 0xff, p_ihello_chunk->epd_len - 1);
	memcpy(p_ihello->p_epd_data, p_ihello_chunk->p_epd_data, p_ihello_chunk->epd_len - 1);
	return p_ihello;
}

void free_chunk_ihello(ihello_chunk_t *p_chunk)
{
	if (NULL != p_chunk)
	{
		if (NULL != p_chunk->p_epd_data)
		{
			delete[] p_chunk->p_epd_data;
			p_chunk->p_epd_data = NULL;
		}
		delete p_chunk; p_chunk = NULL;
	}
}

void ihello_print(const ihello_chunk_t *p_ihello)
{
	if (NULL == p_ihello)
	{
		return;
	}
		  
	printf("chunk_type: 0x%02x\n", p_ihello->chunk_type);
	printf("chunk_len: %d\n", p_ihello->chunk_len);
	printf("ignore: 0x%02x\n", p_ihello->ignore);
	printf("epd_len: %d\n", p_ihello->epd_len);
	printf("epd_type: 0x%02x\n", p_ihello->epd_type);
	printf("epd_data: %s\n", p_ihello->p_epd_data);
	printf("tag: ");	
	hex_print(p_ihello->tag, sizeof(p_ihello->tag));
}
