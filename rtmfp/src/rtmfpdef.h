/**
 * ============================================================================
 * @file    rtmfpdef.h
 *
 * @brief   
 * @details 
 *
 * @version 1.0  
 * @date    2013-06-09 12:26:52
 *
 * @author  shizhijie, shizhijie@baofeng.com
 * ============================================================================
 */

#ifndef __BFP2P_SERVER_RTMFPDEF_H__
#define __BFP2P_SERVER_RTMFPDEF_H__

#include <stdint.h>
#include <bitset>

/**
 * chunk's type definition
 */
#define RTMFP_PACKET_FRAGMENT             0x7f
#define RTMFP_CHUNK_IHELLO                0x30
#define RTMFP_CHUNK_FIHELLO               0x0f
#define RTMFP_CHUNK_RHELLO                0x70
#define RTMFP_CHUNK_RESPONDER_REDIRECT    0x71
#define RTMFP_CHUNK_RHELLO_COOKIE_CHANGE  0x79
#define RTMFP_CHUNK_IIKEY                 0x38
#define RTMFP_CHUNK_RIKEY                 0x78
#define RTMFP_CHUNK_PING                  0x01
#define RTMFP_CHUNK_PING_REPLY            0x41
#define RTMFP_CHUNK_USER_DATA             0x10
#define RTMFP_CHUNK_NEXT_USER_DATA        0x11
#define RTMFP_CHUNK_DATA_ACK_BITMAP       0x50
#define RTMFP_CHUNK_DATA_ACK_RANGE        0x51
#define RTMFP_CHUNK_BUFFER_PROBE          0x18
#define RTMFP_CHUNK_FLOW_EXCEPTION        0x5e
#define RTMFP_CHUNK_SESSION_CLOSE_REQUEST 0x0c
#define RTMFP_CHUNK_SESSION_CLOSE_ACK     0x4c
#define RTMFP_CHUNK_IGNORE_PADDING1       0x00
#define RTMFP_CHUNK_IGNORE_PADDING2       0xff

/**
 * some const variable definition
 */
#define RTMFP_CHUNK_HEADER_SIZE 0x03

#pragma pack(1)

typedef struct __option {
	uint8_t oplen; //vlu
	uint8_t optype; //vlu
	uint8_t opvalue[0];
} option_t;

typedef struct __packet {
	uint8_t marker;
	uint16_t timestamp;
	uint16_t timestamp_echo;
	void *p_chunk;
} packet_t;

typedef struct __ihello_chunk {
	uint8_t chunk_type; //0x30
	uint16_t chunk_len;
	
	//options_list结构
	uint8_t ignore; //epd_arry_len = epd1_len + 1
	uint8_t epd_len; //strlen(p_epd_data) + sizeof(epd1_type)
	uint8_t epd_type; //0x0a:fla2srv 0x0f:peer2peer
	uint8_t *p_epd_data; //[epd_len - 1]
	
	uint8_t tag[16]; //len = 16
} ihello_chunk_t;

typedef struct __rhello_chunk {
	uint8_t chunk_type; //0x70
	uint16_t chunk_len;
	
	uint8_t tag_len; //vlu = 16
	uint8_t *p_tag;  //len = 16
	
	uint8_t cookie_len; //vlu
	uint8_t *p_cookie_data;
	
	uint8_t *p_cert_data;
} rhello_chunk_t;

/* typedef struct __redirect_responder_chunk { */
/* 	uint8_t chunk_type; //0x70 */
/* 	uint16_t chunk_len; */
	
/* 	uint8_t tag_len; //vlu = 16 */
/* 	uint8_t *p_tag;  //len = 16 */
	
/* 	typedef struct __sock_addr { */
/* 		uint8_t flag; */
/* 		if (flag & 0x80) { */
/* 			uint8_t addr[16]; */
/* 		} else { */
/* 			uint8_t addr[4]; */
/* 		} */
/* 		uint16_t port; */
/* 	} sock_addr_t; */
	
/* 	while (remainder() > 0) { */
/* 		sock_addr_t sock_addr; */
/* 	} */
/* } redirect_responder_chunk_t; */

/* /\* */
/*     0 1 2 3 4 5 6 7|0 1 2 3 4 5 6 7|0 1 2 3 4 5 6 7|0 1 2 3 4 5 6 7 */
/*    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ */
/*    |      0x38     |          chunkLength          | */
/*    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ */
/*    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ */
/*    |                       initiatorSessionID                      | */
/*    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ */
/*    +-------------/-+-----------------------------------------------+ */
/*    | cookieLength\ |                  cookieEcho                   | */
/*    +-------------/-+-----------------------------------------------/ */
/*    +-------------/-+-----------------------------------------------+ */
/*    |  certLength \ |             initiatorCertificate              | */
/*    +-------------/-+-----------------------------------------------/ */
/*    +-------------/-+-----------------------------------------------+ */
/*    |  skicLength \ |          sessionKeyInitiatorComponent         | */
/*    +-------------/-+-----------------------------------------------/ */
/*    +---------------------------------------------------------------+ */
/*    |                           signature                           | */
/*    +---------------------------------------------------------------/ */
/* *\/ */
/* typedef struct __iikey_chunk { */
/* 	uint8_t chunk_type; //0x38 */
/* 	uint16_t chunk_len; */
	
/* 	uint32_t init_session_id; //must be 0 */
	
/* 	uint64_t cookie_len; //vlu */
/* 	uint8_t *p_cookie_echo; //[cookie_len] */
	
/* 	uint64_t cert_len; //vlu cert_len = deffie_hellman_pubkey_len + 2(=sizeof(type)) */
/* 	uint8_t *p_cert_data; //[cert_len], 用sha256算出来的是发送端的ID号 */
	
/* 	//options_list结构 */
/* 	uint32_t deffie_hellman_pubkey_len; */
/* 	uint8_t type[2]; //unknown */
/* 	uint8_t *p_deffie_hellman_pubkey; //[deffie_hellman_pubkey_len - 2] */
/* /\* */
/* 	options的结构如下： */
/*    +-------------/-+-----------------------------------------------+ */
/*    |   cert_len  \ |                 p_cert_data                   | */
/*    +-------------/-+-----------------------------------------------/ */
/*                    |    pubkey_len   |     type     |    pubkey    | */
/*                    +-----------------------------------------------/ */
/*                    |                 |   2 bytes    | pubken_len-2 | */
/*                    +-----------------------------------------------/ */
/*                    |     length      |     type     |     value    | */
/*                    +-----------------------------------------------/ */
/*                    ^                                               ^ */
/*                    +-------- length bytes long (may be 0) ---------+ */
/* *\/ */
/* 	uint32_t asymetric_key_len; //vlu */
/* 	uint8_t *p_asymetric_key; //用deffie_hellman交换密钥算法计算出双方协商后的密钥 */
	
/* 	uint8_t signature[0]; //always be 0x58 */
/* } iikey_chunk_t; */

/* /\* */
/*     0 1 2 3 4 5 6 7|0 1 2 3 4 5 6 7|0 1 2 3 4 5 6 7|0 1 2 3 4 5 6 7 */
/*    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ */
/*    |      0x78     |          chunkLength          | */
/*    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ */
/*    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ */
/*    |                       responderSessionID                      | */
/*    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ */
/*    +-------------/-+-----------------------------------------------+ */
/*    |  skrcLength \ |         sessionKeyResponderComponent          | */
/*    +-------------/-+-----------------------------------------------/ */
/*    +---------------------------------------------------------------+ */
/*    |                           signature                           | */
/*    +---------------------------------------------------------------/ */
/* *\/ */
/* typedef struct __rikey_trunk { */
/* 	uint8_t chunk_type; //0x78 */
/* 	uint16_t chunk_len; */
	
/* 	uint32_t sess_id; */
/* 	uint64_t sess_pubkey_len; //vlu */
/* 	uint8_t *p_sess_pubkey; //[sess_pubkey_len] */
/* 	uint8_t signature; //0x58 */
/* } rikey_trunk_t; */

/* typedef struct __user_data_trunk { */
/* 	uint8_t chunk_type; //0x10 */
/* 	uint16_t chunk_len; */
	
/* 	uint8_t flag; */
/* 	uint64_t flow_id; //vlu */
/* 	uint64_t sequence_num; //vlu */
/* 	uint64_t forward_sequence_num; //vlu */
	
/* 	/\* */
/* 		options的结构有如下两种： */
/* 		1. User's Per-Flow Metadata */
/* 		+-------------/-+-------------/-+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+ */
/* 		|   length    \ |     0x00    \ |         userMetadata          | */
/* 		+-------------/-+-------------/-+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~/ */
/* 		2. Return Flow Association */
/* 		+-------------/-+-------------/-+-------------/-+ */
/* 		|   length    \ |     0x0a    \ |    flowID   \ | */
/* 		+-------------/-+-------------/-+-------------/-+ */
/* 	*\/ */
/* 	if (flag & 0x80) { */
/* 		//options_list结构 */
/* 		option_t option; //assert(option.optype == 0x00) */
/* 		if (option_t.oplen > 0) { */
/* 			option_t option; //assert(option.optype == 0x0a) */
/* 		} */
/* 	} */
/* } user_data_trunk_t; */

/* typedef struct __next_user_data_trunk { */
/* 	uint8_t chunk_type; //0x11 */
/* 	uint16_t chunk_len; */
	
/* 	uint8_t flag; */
/* 	/\* */
/* 		options的结构有如下两种： */
/* 		1. User's Per-Flow Metadata */
/* 		+-------------/-+-------------/-+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+ */
/* 		|   length    \ |     0x00    \ |         userMetadata          | */
/* 		+-------------/-+-------------/-+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~/ */
/* 		2. Return Flow Association */
/* 		+-------------/-+-------------/-+-------------/-+ */
/* 		|   length    \ |     0x0a    \ |    flowID   \ | */
/* 		+-------------/-+-------------/-+-------------/-+ */
/* 	*\/ */
/* 	if (flag & 0x80) { */
/* 		//options_list结构 */
/* 		option_t option; //assert(option.optype == 0x00) */
/* 		if (option_t.oplen > 0) { */
/* 			option_t option; //assert(option.optype == 0x0a) */
/* 		} */
/* 	} */
/* } next_user_data_trunk_t; */

/* /\* */
/* 	data_range_ack结构如下： */
/* 	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ */
/* 	|      0x51     |          chunkLength          | */
/* 	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ */
/* 	+-------------/-+-------------/-+-------------/-+ */
/* 	|   flowID    \ |   bufAvail  \ |    cumAck   \ | */
/* 	+-------------/-+-------------/-+-------------/-+ */
/* 	+~~~~~~~~~~~~~/~+~~~~~~~~~~~~~/~+ */
/* 	|   #holes-1  \ |   #recv-1   \ | */
/* 	+~~~~~~~~~~~~~/~+~~~~~~~~~~~~~/~+ */
/*                     : */
/*                     : */
/* 	+~~~~~~~~~~~~~/~+~~~~~~~~~~~~~/~+ */
/* 	|   #holes-1  \ |   #recv-1   \ | */
/* 	+~~~~~~~~~~~~~/~+~~~~~~~~~~~~~/~+ */
/* *\/ */
/* typedef struct __data_range_ack { */
/* 	uint8_t chunk_type; //0x51 */
/* 	uint16_t chunk_len; */
	
/* 	uint64_t flow_id; //vlu */
/* 	uint64_t buffer_blocks_available; //vlu 数据块的数目（块大小1024-byte） */
/* 	// buffer_bytes_available = buffer_blocks_available * 1024 */
/* 	uint64_t cumulative_ack_num; //vlu 校验通过的数据块大小 */
	
/* 	typedef std::pair<uint64_t /\* vlu *\/, uint64_t /\* vlu *\/> ack_range_t; */
/* 	/\* */
/* 		ack_range_t.first = cumulative_ack_num + holes + 1; */
/* 		ack_range_t.second = ack_range_t.first + received + 1; */
/* 		eg. */
/* 		51 00 07  | Range Ack, length=7 */
/* 		05 7f 10  | flowID=5, bufAvail=127*1024 bytes, cumAck=0..16 */
/* 		00 00     | holes=00+1=1, received=00+1=1 -- missing 17, received 18 */
/* 		01 03     | holes=01+1=2, received=03+1=4 -- missing 19..20, received 21..24 */
/* 	*\/ */
/* 	typedef std::vector<ack_range_t> ack_range_vec_t; */
/* 	ack_range_vec_t ack_range_vec; */
/* } data_range_ack_t; */

/* typedef struct __ping { */
/* 	uint8_t chunk_type; //0x01 */
/* 	uint16_t chunk_len; */
	
/* 	uint8_t msg[0]; //actual length may be chunk_len; */
/* } ping_t; */

/* typedef struct __ping_reply { */
/* 	uint8_t chunk_type; //0x41 */
/* 	uint16_t chunk_len; */
	
/* 	uint8_t msg[0]; //The message from the Ping to which this is a response, unaltered. */
/* } ping_reply_t; */

/* typedef struct __flow_exception { */
/* 	uint8_t chunk_type; //0x5e */
/* 	uint16_t chunk_len; */
	
/* 	uint64_t exception_code; //vlu */
/* } flow_exception_t; */

#pragma pack()

#endif //__BFP2P_SERVER_RTMFPDEF_H__
