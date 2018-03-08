/**
 * ============================================================================
 * @file    rtmfp_protocol.cpp
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

#include <string.h>
#include <iostream>
#include <algorithm>
#include <openssl/aes.h>
#include "rtmfp_protocol.h"
#include "rtmfpdef.h"
#include "packet_imp.h"
#include "ihello_chunk_imp.h"

void hex_print(const uint8_t *pstr, uint32_t len)
{
	for (uint32_t i = 0; i < len; ++i)
	{
		printf("0x%02x ", pstr[i]);
		if (0 == (i + 1) % 16)
		{
			printf("\n");
		}
	}
	printf("\n");	
}

uint16_t checksum(const uint8_t *pstr, uint32_t len)
{
	if (NULL == pstr)
	{
		return 0;
	}
	int32_t sum = 0;
	const uint8_t *pbeg = pstr;
	uint8_t available = len - (pbeg - pstr);
	while (available > 0)
	{
		if (available == 1)
		{
			printf("s = %u\n", *pbeg);
			sum += *pbeg++;
		}
		else
		{
			uint16_t s = *((const uint16_t *)pbeg);
			s = ((s << 8) | (s >> 8));
			printf("s = %u\n", s);
			sum += s;
			pbeg += sizeof(s);
		}
		available = len - (pbeg - pstr);
	}

	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);
	return ~sum;
}

const uint8_t *generate_handshake1(uint8_t epd_type, const uint8_t *p_epd_data,
								   uint32_t epd_len, const uint8_t *p_tag, uint32_t tag_size,
								   uint8_t **pp_data, uint32_t &data_size)
{
	uint8_t *p_data = NULL;
	if (NULL != pp_data)
	{
		p_data = *pp_data;
	}
	
	ihello_chunk_t *p_ihello = NULL;
	p_ihello = create_ihello((epd_type = 0x0a), p_epd_data, epd_len, p_tag, tag_size,
							 &p_ihello);

	uint16_t timestamp = time(NULL);
	packet_t *p_pkt = NULL;
	p_pkt = const_cast<packet_t *>(set_packet(0x0b, timestamp, 0x00, p_ihello, &p_pkt));
	free_chunk_ihello(p_ihello);

	uint32_t pktlen = get_packet_len(p_pkt);
	uint8_t *p_pkt_data = NULL;
	write_packet(p_pkt, &p_pkt_data, pktlen);
	free_packet(p_pkt);

	uint32_t scrambled_sessid = 0x00;
	std::reverse((uint8_t *)(&scrambled_sessid),
				 (uint8_t *)(&scrambled_sessid) + sizeof(scrambled_sessid));
	uint16_t sum = 0;
	data_size = sizeof(sum) + pktlen;
	data_size = ((data_size + 1) / AES_BLOCK_SIZE + 1) * AES_BLOCK_SIZE;
	data_size += sizeof(scrambled_sessid);
	if (NULL == p_data)
	{
		p_data = new uint8_t[data_size];
		memset(p_data, 0xff, data_size);
	}
	memcpy(p_data + sizeof(scrambled_sessid) + sizeof(sum), p_pkt_data, pktlen);
	sum = checksum(p_data + sizeof(scrambled_sessid) + sizeof(sum),
				   data_size - sizeof(scrambled_sessid) - sizeof(sum));
	std::reverse((uint8_t *)&sum, (uint8_t *)&sum + sizeof(sum));
	memcpy(p_data + sizeof(scrambled_sessid), &sum, sizeof(sum));

	delete[] p_pkt_data; p_pkt_data = NULL;

	AES_KEY aes_key;
	if (AES_set_encrypt_key((uint8_t *)&"Adobe Systems 02"[0], 0x80, &aes_key) < 0)
	{
		fprintf(stderr, "Unable to set encryption key in AES\n");
		exit(EXIT_FAILURE);
	}
	uint8_t *p_encrypt_str = p_data + sizeof(scrambled_sessid);
	uint32_t encrypt_size = data_size - sizeof(scrambled_sessid);
	uint8_t iv[AES_BLOCK_SIZE] = { 0 };
	AES_cbc_encrypt(p_encrypt_str, p_encrypt_str, encrypt_size, &aes_key,
					iv, AES_ENCRYPT);

	uint32_t first32 = (*(uint32_t *)(p_data + sizeof(scrambled_sessid)));
	std::reverse((uint8_t *)&first32, (uint8_t *)&first32 + sizeof(first32));
	uint32_t second32 = (*(uint32_t *)(p_data + 2 * sizeof(scrambled_sessid)));
	std::reverse((uint8_t *)&second32, (uint8_t *)&second32 + sizeof(second32));
	scrambled_sessid = scrambled_sessid ^ first32 ^ second32;
	std::reverse((uint8_t *)(&scrambled_sessid),
				 (uint8_t *)(&scrambled_sessid) + sizeof(scrambled_sessid));
	memcpy(p_data, (uint8_t *)&scrambled_sessid, sizeof(scrambled_sessid));

	return p_data;
}
