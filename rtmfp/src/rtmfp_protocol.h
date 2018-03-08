/**
 * ============================================================================
 * @file    rtmfp_protocol.h
 *
 * @brief   
 * @details 
 *
 * @version 1.0  
 * @date    2013-06-20 16:31:14
 *
 * @author  shizhijie, shizhijie@baofeng.com
 * ============================================================================
 */

#ifndef __BFP2P_SERVER_RTMFP_PROTOCOL_H__
#define __BFP2P_SERVER_RTMFP_PROTOCOL_H__
#include <stdint.h>

void hex_print(const uint8_t *pstr, uint32_t len);
uint16_t checksum(const uint8_t *pstr, uint32_t len);

const uint8_t *generate_handshake1(uint8_t epd_type, const uint8_t *p_epd_data,
	uint32_t epd_len, const uint8_t *p_tag, uint32_t tag_size, uint8_t **pp_data,
	uint32_t &data_size);

#endif //__BFP2P_SERVER_RTMFP_PROTOCOL_H__
