/**
 * ============================================================================
 * @file    packet_imp.h
 *
 * @brief   
 * @details 
 *
 * @version 1.0  
 * @date    2013-06-09 14:44:45
 *
 * @author  shizhijie, shizhijie@baofeng.com
 * ============================================================================
 */

#ifndef __BFP2P_SERVER_PACKET_IMP_H__
#define __BFP2P_SERVER_PACKET_IMP_H__
#include "rtmfpdef.h"

uint8_t get_chunk_type(const void *p_chunk);
uint16_t get_chunk_length(const void *p_chunk);
uint16_t get_chunk_capacity(const void *p_chunk);

const void *read_chunk(const uint8_t *pstr, void **pp_chunk);
const uint8_t *write_chunk(const void *p_chunk, uint8_t **pp_data, uint32_t &size);
const void *chunk_clone(const void *p_chunk, void **pp_new_chunk);

const packet_t *set_packet(uint8_t mark, uint16_t timestamp, uint16_t timestamp_echo,
	void *p_chunk, packet_t **pp_pkt);
uint32_t get_packet_len(const packet_t *p_pkt);
const packet_t *read_packet(const uint8_t *pstr, packet_t **pp_pkt);
const uint8_t *write_packet(const packet_t *p_pkt, uint8_t **pp_pktdata, uint32_t &pktlen);
void free_packet(packet_t *p_pkt);

void packet_print(const packet_t *p_pkt);

#endif //__BFP2P_SERVER_PACKET_IMP_H__

