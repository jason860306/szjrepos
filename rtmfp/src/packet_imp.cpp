/**
 * ============================================================================
 * @file    packet_imp.cpp
 *
 * @brief   
 * @details 
 *
 * @version 1.0  
 * @date    2013-06-09 14:47:41
 *
 * @author  shizhijie, shizhijie@baofeng.com
 * ============================================================================
 */

#include <string.h>
#include "packet_imp.h"
#include "ihello_chunk_imp.h"

uint8_t get_chunk_type(const void *p_trunk)
{
	if (NULL == p_trunk)
	{
		return RTMFP_CHUNK_IGNORE_PADDING1;
	}
	return *(uint8_t *)p_trunk;
}

uint16_t get_chunk_capacity(const void *p_chunk)
{
	if (NULL == p_chunk)
	{
		return 0;
	}
	return *reinterpret_cast<uint16_t *>((char *)p_chunk + sizeof(uint8_t)) +
		RTMFP_CHUNK_HEADER_SIZE;
}

uint16_t get_chunk_length(const void *p_chunk)
{
	if (NULL == p_chunk)
	{
		return NULL;
	}
	uint16_t chunk_len = 0;
	switch (uint8_t type = get_chunk_type(p_chunk))
	{
	case RTMFP_CHUNK_IHELLO:
		chunk_len = get_chunk_len((ihello_chunk_t *)p_chunk);
		break;
#if 0
	case RTMFP_CHUNK_FIHELLO:
		break;
	case RTMFP_CHUNK_RHELLO:
		chunk_len = get_chunk_len(reinterpret_cast<rhello_chunk_t *>(p_chunk));
		break;
	case RTMFP_CHUNK_RESPONDER_REDIRECT:
		chunk_len = get_chunk_len(reinterpret_cast<redirect_responder_chunk_t *>(p_chunk));
		break;
	case RTMFP_CHUNK_RHELLO_COOKIE_CHANGE:
		break;
	case RTMFP_CHUNK_IIKEY:
		chunk_len = get_chunk_len(reinterpret_cast<iikey_chunk_t *>(p_chunk));
		break;
	case RTMFP_CHUNK_RIKEY:
		chunk_len = get_chunk_len(reinterpret_cast<rikey_chunk_t *>(p_chunk));
		break;
	case RTMFP_CHUNK_PING:
		chunk_len = get_chunk_len(reinterpret_cast<ping_chunk_t *>(p_chunk));
		break;
	case RTMFP_CHUNK_PING_REPLY:
		chunk_len = get_chunk_len(reinterpret_cast<ping_reply_chunk_t *>(p_chunk));
		break;
	case RTMFP_CHUNK_USER_DATA:
		chunk_len = get_chunk_len(reinterpret_cast<user_data_chunk_t *>(p_chunk));
		break;
	case RTMFP_CHUNK_NEXT_USER_DATA:
		chunk_len = get_chunk_len(reinterpret_cast<next_user_data_chunk_t *>(p_chunk));
		break;
	case RTMFP_CHUNK_DATA_ACK_BITMAP:
		break;
	case RTMFP_CHUNK_DATA_ACK_RANGE:
		chunk_len = get_chunk_len(reinterpret_cast<data_range_ack_chunk_t *>(p_chunk));
		break;
	case RTMFP_CHUNK_BUFFER_PROBE:
		break;
	case RTMFP_CHUNK_FLOW_EXCEPTION:
		chunk_len = get_chunk_len(reinterpret_cast<flow_exception_chunk_t *>(p_chunk));
		break;
#endif
	case RTMFP_CHUNK_SESSION_CLOSE_REQUEST:
	case RTMFP_CHUNK_SESSION_CLOSE_ACK:
	default:
		static_cast<void>(type);
		break;
	}
	return chunk_len;
}

const packet_t *set_packet(uint8_t mark, uint16_t timestamp, uint16_t timestamp_echo,
						   void *p_chunk, packet_t **pp_pkt)
{
	packet_t *p_pkt = NULL;
	if (NULL != pp_pkt)
	{
		p_pkt = *pp_pkt;
	}
	if (NULL == p_chunk)
	{
		return NULL;
	}
	if (NULL == p_pkt)
	{
		p_pkt = new packet_t();
		memset(p_pkt, 0xff, sizeof(packet_t));
	}
	p_pkt->marker = mark;
	if (mark & 0x08)
	{
		p_pkt->timestamp = timestamp;
	}
	if (mark & 0x04)
	{
		p_pkt->timestamp = timestamp_echo;
	}
	p_pkt->p_chunk = const_cast<void *>(chunk_clone(p_chunk, &p_pkt->p_chunk));

	return p_pkt;
}

uint32_t get_packet_len(const packet_t *p_pkt)
{
	if (NULL == p_pkt)
	{
		return 0;
	}
	return (sizeof(packet_t) + get_chunk_capacity(p_pkt->p_chunk));
}

const packet_t *read_packet(const uint8_t *pstr, packet_t **pp_pkt)
{
	packet_t *p_pkt = NULL;
	if (NULL != pp_pkt)
	{
		p_pkt = *pp_pkt;
	}
	if (NULL == pstr)
	{
		return NULL;
	}
	if (NULL == p_pkt)
	{
		p_pkt = new packet_t();
		memset(p_pkt, 0xff, sizeof(packet_t));
	}

	p_pkt->marker = *(uint8_t *)pstr;
	uint32_t offset = sizeof(uint8_t);
	if (p_pkt->marker & 0x08)
	{
		p_pkt->timestamp = *(uint16_t *)(pstr + offset);
		p_pkt->timestamp = ((p_pkt->timestamp << 8) | (p_pkt->timestamp >> 8));
		offset += sizeof(p_pkt->timestamp);
	}
	if (p_pkt->marker & 0x04)
	{
		p_pkt->timestamp_echo = *(uint16_t *)(pstr + offset);
		p_pkt->timestamp_echo = ((p_pkt->timestamp_echo << 8) |
								 (p_pkt->timestamp_echo >> 8));
		offset += sizeof(p_pkt->timestamp_echo);
	}
	p_pkt->p_chunk = const_cast<void *>(read_chunk(pstr + offset, &p_pkt->p_chunk));

	return p_pkt;
}

const uint8_t *write_packet(const packet_t *p_pkt, uint8_t **pp_pktdata, uint32_t &pktlen)
{
	uint32_t loc_pktlen = get_packet_len(p_pkt);
	if (NULL == p_pkt || (NULL != pp_pktdata && NULL != *pp_pktdata && loc_pktlen > pktlen))
	{
		return NULL;
	}
	uint8_t *p_pktdata = NULL;
	if (NULL == p_pktdata)
	{
		p_pktdata = new uint8_t[loc_pktlen];
		memset(p_pktdata, 0xff, loc_pktlen);
		pktlen = loc_pktlen;
	}
	memcpy(p_pktdata, &p_pkt->marker, sizeof(p_pkt->marker));

	uint16_t offset = sizeof(p_pkt->marker);
	if (p_pkt->marker & 0x08)
	{
		uint16_t timestamp = p_pkt->timestamp;
		timestamp = (timestamp << 8) | (timestamp >> 8);
		memcpy(p_pktdata + offset, &timestamp, sizeof(timestamp));
		offset += sizeof(p_pkt->timestamp);
	}
	if (p_pkt->marker & 0x04)
	{
		uint16_t timestamp_echo = p_pkt->timestamp_echo;
		timestamp_echo = (timestamp_echo << 8) | (timestamp_echo >> 8);
		memcpy(p_pktdata + offset, &timestamp_echo, sizeof(timestamp_echo));
		offset += sizeof(p_pkt->timestamp_echo);
	}
	uint8_t *p_data = p_pktdata + offset;
	uint32_t size = loc_pktlen - offset;
	write_chunk(p_pkt->p_chunk, &p_data, size);

	return p_pktdata;
}

const void *read_chunk(const uint8_t *pstr, void **pp_chunk)
{
	if (NULL == pstr)
	{
		return NULL;
	}
	void *p_chunk = NULL;
	switch (uint8_t type = get_chunk_type(*pp_chunk))
	{
	case RTMFP_CHUNK_IHELLO:
		p_chunk = read_chunk_ihello(pstr, (ihello_chunk_t **)pp_chunk);
		break;
#if 0
	case RTMFP_CHUNK_FIHELLO:
		break;
	case RTMFP_CHUNK_RHELLO:
		p_chunk = read_chunk_rhello(pstr, (rhello_chunk_t **)pp_chunk);
		break;
	case RTMFP_CHUNK_RESPONDER_REDIRECT:
		p_chunk = read_chunk_responder_redirect(pstr, (redirect_responder_chunk_t **)pp_chunk);
		break;
	case RTMFP_CHUNK_RHELLO_COOKIE_CHANGE:
		break;
	case RTMFP_CHUNK_IIKEY:
		p_chunk = read_chunk_iikey(pstr, (iikey_chunk_t **)pp_chunk);
		break;
	case RTMFP_CHUNK_RIKEY:
		p_chunk = read_chunk_rikey(pstr, (rikey_chunk_t **)pp_chunk);
		break;
	case RTMFP_CHUNK_PING:
		p_chunk = read_chunk_ping(pstr, (ping_chunk_t **)pp_chunk);
		break;
	case RTMFP_CHUNK_PING_REPLY:
		p_chunk = read_chunk_ping_reply(pstr, (ping_reply_chunk_t **)pp_chunk);
		break;
	case RTMFP_CHUNK_USER_DATA:
		p_chunk = read_chunk_user_data(pstr, (user_data_chunk_t **)pp_chunk);
		break;
	case RTMFP_CHUNK_NEXT_USER_DATA:
		p_chunk = read_chunk_next_user_data(pstr, (next_user_data_chunk_t **)pp_chunk);
		break;
	case RTMFP_CHUNK_DATA_ACK_BITMAP:
		break;
	case RTMFP_CHUNK_DATA_ACK_RANGE:
		p_chunk = read_chunk_data_ack_range(pstr, (data_range_ack_chunk_t **)pp_chunk);
		break;
	case RTMFP_CHUNK_BUFFER_PROBE:
		break;
	case RTMFP_CHUNK_FLOW_EXCEPTION:
		p_chunk = read_chunk_flow_exception(pstr, (flow_exception_chunk_t **)pp_chunk);
		break;
#endif
	case RTMFP_CHUNK_SESSION_CLOSE_REQUEST:
	case RTMFP_CHUNK_SESSION_CLOSE_ACK:
	default:
		static_cast<void>(type);
		break;
	}
	return p_chunk;
}

const uint8_t *write_chunk(const void *p_chunk, uint8_t **pp_data, uint32_t &size)
{
	if (NULL == p_chunk)
	{
		return NULL;
	}
	const uint8_t *p_chunk_data = NULL;
	switch (uint8_t type = get_chunk_type(p_chunk))
	{
	case RTMFP_CHUNK_IHELLO:
		p_chunk_data = write_chunk_ihello((const ihello_chunk_t *)p_chunk, pp_data, size);
		break;
#if 0
	case RTMFP_CHUNK_FIHELLO:
		break;
	case RTMFP_CHUNK_RHELLO:
		p_chunk_data = write_chunk_rhello((const rhello_chunk_t *)p_chunk, pp_data, size);
		break;
	case RTMFP_CHUNK_RESPONDER_REDIRECT:
		p_chunk_data = write_chunk_responder_redirect(
			(const redirect_responder_chunk_t *)p_chunk, pp_data, size);
		break;
	case RTMFP_CHUNK_RHELLO_COOKIE_CHANGE:
		break;
	case RTMFP_CHUNK_IIKEY:
		p_chunk_data = write_chunk_iikey((const iikey_chunk_t *)p_chunk, pp_data, size);
		break;
	case RTMFP_CHUNK_RIKEY:
		p_chunk_data = write_chunk_rikey((const rikey_chunk_t *)p_chunk, pp_data, size);
		break;
	case RTMFP_CHUNK_PING:
		p_chunk_data = write_chunk_ping((const ping_chunk_t *)p_chunk, pp_data, size);
		break;
	case RTMFP_CHUNK_PING_REPLY:
		p_chunk_data = write_chunk_ping_reply((const ping_reply_chunk_t *)p_chunk,
											  pp_data, size);
		break;
	case RTMFP_CHUNK_USER_DATA:
		p_chunk_data = write_chunk_user_data((const user_data_chunk_t *)p_chunk, pp_data, size);
		break;
	case RTMFP_CHUNK_NEXT_USER_DATA:
		p_chunk_data = write_chunk_next_user_data((const next_user_data_chunk_t *)p_chunk,
												  pp_data, size);
		break;
	case RTMFP_CHUNK_DATA_ACK_BITMAP:
		break;
	case RTMFP_CHUNK_DATA_ACK_RANGE:
		p_chunk_data = write_chunk_data_ack_range((const data_range_ack_chunk_t *)p_chunk,
												  pp_data, size);
		break;
	case RTMFP_CHUNK_BUFFER_PROBE:
		break;
	case RTMFP_CHUNK_FLOW_EXCEPTION:
		p_chunk_data = write_chunk_flow_exception((const flow_exception_chunk_t *)p_chunk,
												  pp_data, size);
		break;
#endif
	case RTMFP_CHUNK_SESSION_CLOSE_REQUEST:
	case RTMFP_CHUNK_SESSION_CLOSE_ACK:
	default:
		static_cast<void>(type);
		break;
	}
	return p_chunk_data;
}

const void *chunk_clone(const void *p_chunk, void **pp_new_chunk)
{
	void *p_new_chunk = NULL;
	if (NULL == p_chunk)
	{
		return NULL;
	}
	if (NULL != pp_new_chunk)
	{
		p_new_chunk = *pp_new_chunk;
	}
	switch (uint8_t type = get_chunk_type(p_chunk))
	{
	case RTMFP_CHUNK_IHELLO:
	{
		ihello_chunk_t *p_new_ihello = static_cast<ihello_chunk_t *>(p_new_chunk);
		p_new_chunk = (void *)chunk_clone((const ihello_chunk_t *)p_chunk, &p_new_ihello);
	}
		break;
#if 0
	case RTMFP_CHUNK_FIHELLO:
		break;
	case RTMFP_CHUNK_RHELLO:
		p_new_chunk = chunk_clone((const rhello_chunk_t *)p_chunk);
		break;
	case RTMFP_CHUNK_RESPONDER_REDIRECT:
		p_new_chunk = chunk_clone((const redirect_responder_chunk_t *)p_chunk);
		break;
	case RTMFP_CHUNK_RHELLO_COOKIE_CHANGE:
		break;
	case RTMFP_CHUNK_IIKEY:
		p_new_chunk = chunk_clone((const iikey_chunk_t *)p_chunk);
		break;
	case RTMFP_CHUNK_RIKEY:
		p_new_chunk = chunk_clone((const rikey_chunk_t *)p_chunk);
		break;
	case RTMFP_CHUNK_PING:
		p_new_chunk = chunk_clone((const ping_chunk_t *)p_chunk);
		break;
	case RTMFP_CHUNK_PING_REPLY:
		p_new_chunk = chunk_clone((const ping_reply_chunk_t *)p_chunk);
		break;
	case RTMFP_CHUNK_USER_DATA:
		p_new_chunk = chunk_clone((const user_data_chunk_t *)p_chunk);
		break;
	case RTMFP_CHUNK_NEXT_USER_DATA:
		p_new_chunk = chunk_clone((const next_user_data_chunk_t *)p_chunk);
		break;
	case RTMFP_CHUNK_DATA_ACK_BITMAP:
		break;
	case RTMFP_CHUNK_DATA_ACK_RANGE:
		p_new_chunk = chunk_clone((const data_range_ack_chunk_t *)p_chunk);
		break;
	case RTMFP_CHUNK_BUFFER_PROBE:
		break;
	case RTMFP_CHUNK_FLOW_EXCEPTION:
		p_new_chunk = chunk_clone((const flow_exception_chunk_t *)p_chunk);
		break;
#endif
	case RTMFP_CHUNK_SESSION_CLOSE_REQUEST:
	case RTMFP_CHUNK_SESSION_CLOSE_ACK:
	default:
		static_cast<void>(type);
		break;
	}
	return p_new_chunk;
}

void free_packet(packet_t *p_pkt)
{
	if (NULL == p_pkt)
	{
		return;
	}
	switch (uint8_t type = get_chunk_type(p_pkt->p_chunk))
	{
	case RTMFP_CHUNK_IHELLO:
		free_chunk_ihello((ihello_chunk_t *)p_pkt->p_chunk);
		break;
#if 0
	case RTMFP_CHUNK_FIHELLO:
		break;
	case RTMFP_CHUNK_RHELLO:
		free_chunk_rhello((rhello_chunk_t *)p_pkt->p_chunk);
		break;
	case RTMFP_CHUNK_RESPONDER_REDIRECT:
		free_chunk_responder_redirect((redirect_responder_chunk_t *)p_pkt->p_chunk);
		break;
	case RTMFP_CHUNK_RHELLO_COOKIE_CHANGE:
		break;
	case RTMFP_CHUNK_IIKEY:
		free_chunk_iikey((iikey_chunk_t *)p_pkt->p_chunk);
		break;
	case RTMFP_CHUNK_RIKEY:
		free_chunk_rikey((rikey_chunk_t *)p_pkt->p_chunk);
		break;
	case RTMFP_CHUNK_PING:
		free_chunk_ping((ping_chunk_t *)p_pkt->p_chunk);
		break;
	case RTMFP_CHUNK_PING_REPLY:
		free_chunk_ping_reply((ping_reply_chunk_t *)p_pkt->p_chunk);
		break;
	case RTMFP_CHUNK_USER_DATA:
		free_chunk_user_data((user_data_chunk_t *)p_pkt->p_chunk);
		break;
	case RTMFP_CHUNK_NEXT_USER_DATA:
		free_chunk_next_user_data((next_user_data_chunk_t *)p_pkt->p_chunk);
		break;
	case RTMFP_CHUNK_DATA_ACK_BITMAP:
		break;
	case RTMFP_CHUNK_DATA_ACK_RANGE:
		free_chunk_data_ack_range((data_range_ack_chunk_t *)p_pkt->p_chunk);
		break;
	case RTMFP_CHUNK_BUFFER_PROBE:
		break;
	case RTMFP_CHUNK_FLOW_EXCEPTION:
		free_chunk_flow_exception((flow_exception_chunk_t *)p_pkt->p_chunk);
		break;
#endif
	case RTMFP_CHUNK_SESSION_CLOSE_REQUEST:
	case RTMFP_CHUNK_SESSION_CLOSE_ACK:
	default:
		static_cast<void>(type);
		break;
	}
}

void packet_print(const packet_t *p_pkt)
{
	if (NULL == p_pkt)
	{
		return;
	}

	printf("marker: 0x%02x\n", p_pkt->marker);
	printf("timestamp: %d\n", p_pkt->timestamp);
	printf("timestamp_echo: %d\n", p_pkt->timestamp_echo);
	ihello_print((ihello_chunk_t *)p_pkt->p_chunk);
}
