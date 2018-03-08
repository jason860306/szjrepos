/**
 * ============================================================================
 * @file    ihello_chunk_imp.h
 *
 * @brief   
 * @details 
 *
 * @version 1.0  
 * @date    2013-06-13 11:35:51
 *
 * @author  shizhijie, shizhijie@baofeng.com
 * ============================================================================
 */

#ifndef __BFP2P_SERVER_IHELLO_CHUNK_IMP_H__
#define __BFP2P_SERVER_IHELLO_CHUNK_IMP_H__
#include "rtmfpdef.h"

uint32_t get_chunk_capacity(const ihello_chunk_t *p_ihello_chunk);
uint32_t get_chunk_len(const ihello_chunk_t *p_ihello_chunk);
ihello_chunk_t *read_chunk_ihello(const uint8_t *pstr, ihello_chunk_t **pp_chunk);
const uint8_t *write_chunk_ihello(const ihello_chunk_t *p_chunk, uint8_t **pp_chunk_data,
	uint32_t &chunk_size);

ihello_chunk_t *create_ihello(uint8_t epd_type, const uint8_t *p_epd_data, uint32_t epd_len,
	const uint8_t *p_tag, uint16_t tag_len,	ihello_chunk_t **pp_ihello);
const ihello_chunk_t *chunk_clone(const ihello_chunk_t *p_ihello,
	ihello_chunk_t **pp_new_ihello);
void free_chunk_ihello(ihello_chunk_t *p_chunk);

void ihello_print(const ihello_chunk_t *p_ihello);

#endif //__BFP2P_SERVER_IHELLO_CHUNK_IMP_H__
