/**
 * ============================================================================
 * @file    bitfield1.c
 *
 * @brief   
 * @details 
 *
 * @version 1.0  
 * @date    Mon Dec 24 11:08:50 CST 2012
 *
 * @author  shizhijie, shizhijie@baofeng.com
 * ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char ts_strm[] = {
	0x47, 0x40, 0x00, 0x17, 0x00, 0x00, 0xB0, 0x0D, 0x00, 0x01, 0xC1, 0x00, 0x00, 0x00,
	0x01, 0xE0, 0x20, 0xA2, 0xC3, 0x29, 0x41, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

static const char ts_strm1[] = {
	0x47, 0x37, 0xB8, 0xE2, 0x52, 0x08, 0xAF, 0x3D, 0xD7, 0xD9, 0xB2, 0xBA, 0x9D, 0x66,
	0x5A, 0x75, 0x2E, 0x2F, 0x82, 0x56, 0xF2, 0x20, 0x0B, 0xC5, 0xBF, 0xA2, 0x24, 0xE5,
	0xCB, 0x72, 0xA1, 0xB9, 0x90, 0x07, 0x32, 0xC3, 0x8B, 0x9E, 0x9E, 0x8D, 0xEC, 0x00,
	0x1E, 0x09, 0xBD, 0x98, 0xFD, 0x75, 0xC8, 0x41, 0x99, 0x26, 0x97, 0x42, 0x14, 0xE8,
	0x16, 0x94, 0x31, 0xAA, 0xCB, 0x30, 0x0D, 0x20, 0x51, 0xCC, 0x39, 0x14, 0xAA, 0xAD,
	0x42, 0x47, 0x14, 0x50, 0x13, 0x2A, 0x66, 0xEC, 0x4C, 0x25, 0x94, 0x91, 0x81, 0x3B,
	0x0B, 0x92, 0x72, 0x42, 0x03, 0xA0, 0xD6, 0xC3, 0x1D, 0xBE, 0xE3, 0x87, 0xEF, 0x01,
	0x94, 0x25, 0x05, 0xAB, 0xE1, 0x02, 0x64, 0x3F, 0x1E, 0x7A, 0xC8, 0xFA, 0xC3, 0x89, 
	0x00, 0x6E, 0xDD, 0x2B, 0x13, 0x56, 0x48, 0x2C, 0xF8, 0xB6, 0x33, 0x85, 0xC4, 0x3D,
	0x16, 0x04, 0x67, 0xB4, 0x6A, 0xC0, 0x85, 0x09, 0x80, 0x54, 0x99, 0xD8, 0x0F, 0xA1,
	0x24, 0x94, 0xA1, 0x0B, 0x01, 0x2B, 0x2A, 0xF2, 0x40, 0xB1, 0x23, 0x9E, 0xB4, 0x05,
	0x45, 0xA3, 0xA1, 0x05, 0x12, 0xC0, 0x2C, 0x24, 0x8C, 0xC8, 0x6F, 0xCF, 0x51, 0x4B,
	0x8B, 0xE6, 0xCE, 0x11, 0xD6, 0x47, 0x9B, 0x51, 0x52, 0x88, 0x54, 0x2B, 0xB9, 0x32,
	0x75, 0xDD, 0x43, 0x33, 0xBF, 0x72, 0xEC, 0xCB, 0xBA, 0x85, 0x1B, 0xBB, 0x32, 0x4D,
	0xC6, 0x2B, 0x40, 0xC3, 0xEE, 0x50, 0x74, 0xD7, 0x45, 0x0C, 0x85, 0x98, 0x6F, 0x77,
	0x75, 0x0D, 0xE3, 0xAE, 0x65, 0xAA, 0xEB, 0x14, 0x2C, 0x1F, 0x67, 0x5E, 0x31, 0x77, 
	0x2C, 0x5F, 0xAB, 0x0A, 0xB0, 0xA8, 0x8D, 0x77, 0x17, 0x4A, 0x87, 0xC1, 0xBF, 0x61,
	0x7D, 0xAE, 0xEA, 0x14, 0x28, 0x1C, 0x64, 0x35, 0x19, 0x8D, 0x6C, 0xC7, 0xDB, 0x0F,
	0x86, 0x3D, 0xDB, 0x31, 0x61, 0xA0, 0x57, 0x47, 0x14, 0x20, 0x1F, 0xEC, 0x71, 0xDF,
	0x71, 0xD2, 0xC7, 0x50, 0xD2, 0x4C, 0x55, 0x52, 0x21, 0x46, 0x40, 0x30, 0x81, 0x76,
	0xEA, 0x72, 0x20, 0xE8, 0xD5, 0x9B, 0x13, 0xAF, 0x34, 0x37, 0x72, 0x06, 0xB9, 0xC1,
	0xF6, 0x3B, 0xA8, 0x3E, 0x87, 0x14, 0xD6, 0xFF, 0x36, 0xE0, 0xB7, 0xFF, 0xF0, 0x0C,
	0x00, 0x62, 0x84, 0x21, 0x2C, 0x90, 0xC2, 0x69, 0x40, 0x78, 0xB7, 0x12, 0x8F, 0x25,
	0x27, 0x61, 0x8E, 0x3C, 0x4F, 0x55, 0x0D, 0xAC, 0x85, 0x81, 0x87, 0xB0, 0xA2, 0x70, 
	0xEA, 0x80, 0x3A, 0xA7, 0xBD, 0x40, 0x85, 0xAB, 0x38, 0xA5, 0x21, 0x18, 0x0D, 0xC8,
	0xC1, 0x29, 0xD4, 0x55, 0x5A, 0x04, 0x60, 0xC3, 0x00, 0x6B, 0x5C, 0x21, 0x38, 0x8A,
	0x31, 0xBC, 0x99, 0xCF
};

typedef struct ts_pkt_hdr
{
	unsigned sync_byte:8;
	unsigned transport_error_indicator:1;
	unsigned payload_unit_start_indicator:1;
	unsigned transport_priority:1;
	unsigned PID:13;
	unsigned transport_scrambling_control:2;
	unsigned adaption_field_control:2;
	unsigned continuity_counter:4;
} ts_pkt_hdr;

typedef struct ts_PAT
{
	unsigned table_id:8;
	unsigned section_syntax_indicator:1;
	unsigned zero:1;
	unsigned reserved_1:2;
	unsigned section_length:12;
	unsigned transport_stream_id:16;
	unsigned reserved_2:2;
	unsigned version_number:5;
	unsigned current_next_indicator:1;
	unsigned section_number:8;
	unsigned last_section_number:8;
	unsigned program_number:16;
	unsigned reserved_3:3;
	unsigned network_PID:13;
	unsigned program_map_PID:13;
	unsigned CRC_32:32;
} ts_PAT;

typedef struct ts_PMT
{
	unsigned table_id:8;
	unsigned section_syntax_indicator:1;
	unsigned zero:1;
	unsigned reserved_1:2;
	unsigned section_length:12;
	unsigned program_number:16;
	unsigned reserved_2:2;
	unsigned version_number:5;
	unsigned current_next_indicator:1;
	unsigned section_number:8;
	unsigned last_section_number:8;
	unsigned reserved_3:3;
	unsigned PCR_PID:13;
	unsigned reserved_4:4;
	unsigned program_info_length:12;
	unsigned stream_type:8;
	unsigned reserved_5:3;
	unsigned elementary_PID:13;
	unsigned reserved_6:4;
	unsigned ES_info_length:12;
	unsigned CRC_32:32;
} ts_PMT;

// adjust TS packet header
void adjust_ts_pkt_hdr(ts_pkt_hdr* phdr)
{
	unsigned char buf[4];
	memcpy(buf, phdr, 4);
	phdr->transport_error_indicator = buf[1] >> 7;
	phdr->payload_unit_start_indicator = buf[1] >> 6 & 0x01;
	phdr->transport_priority = buf[1] >> 5 & 0x01;
	phdr->PID = (buf[1] & 0x1F) << 8 | buf[2];
	phdr->transport_scrambling_control = buf[3] >> 6;
	phdr->adaption_field_control = buf[3] >> 4 & 0x03;
	phdr->continuity_counter = buf[3] & 0x03;
}

// adjust PAT table
void adjust_PAT_table(ts_PAT* pkt, char* buf)
{
	int n = 0, len = 0;
	pkt->table_id = buf[0];
	pkt->section_syntax_indicator = buf[1]>>7;
	pkt->zero = buf[1]>>6&0x1;
	pkt->reserved_1 = buf[1]>>4&0x3;
	pkt->section_length = (buf[1]&0x0f)<<8|buf[2];
	pkt->transport_stream_id = buf[3]<<8|buf[4];
	pkt->reserved_2 = buf[5]>>6;
	pkt->version_number = buf[5]>>1&0x1f;
	pkt->current_next_indicator = (buf[5]<<7)>>7;
	pkt->section_number = buf[6];
	pkt->last_section_number = buf[7];
	// Get CRC_32
	len = 3 + pkt->section_length;
	pkt->CRC_32 = (buf[len-4]&0x000000ff)<<24 | (buf[len-3]&0x000000ff)<<16 |
		(buf[len-2]&0x000000ff) << 8 | (buf[len-1]&0x000000ff);
	// Parse network_PID or program_map_PID
	for (n = 0; n < pkt->section_length - 4; ++n)
	{
		pkt->program_number = buf[8]<<8|buf[9];
		pkt->reserved_3 = buf[10]>>5;
		if (pkt->program_number == 0x0)
		{
			pkt->network_PID = (buf[10]<<3)<<5 | buf[11];
		}
		else
		{
			pkt->program_map_PID = (buf[10]<<3)<<5|buf[11];
		}
		n += 5;
	}
}

// adjust PMT table
void adjust_PMT_table(ts_PMT* pkt, char* buf)
{
	int pos = 12, len = 0, i = 0;
	pkt->table_id = buf[0];
	pkt->section_syntax_indicator = buf[1]>>7;
	pkt->zero = buf[1]>>6;
	pkt->reserved_1 = buf[1]>>4;
	pkt->section_length = (buf[1]&0x0f)<<8|buf[2];
	pkt->program_number = buf[3]<<8|buf[4];
	pkt->reserved_2 = buf[5]>>6;
	pkt->version_number = buf[5]>>1&0x1f;
	pkt->current_next_indicator = (buf[5]<<7)>>7;
	pkt->section_number = buf[6];
	pkt->last_section_number = buf[7];
	pkt->reserved_3 = buf[8]>>5;
	pkt->PCR_PID = ((buf[8]<<8)|buf[9])&0x1fff;
	pkt->reserved_4 = buf[10]>>4;
	pkt->program_info_length = (buf[10]&0x0f)<<8|buf[11];
	// Get CRC_32
	len = pkt->section_length + 3;
	pkt->CRC_32 = (buf[len - 4] & 0x000000ff) << 24 | (buf[len-3]&0x000000ff)<<16
		| (buf[len-2]&0x000000ff)<<8 | (buf[len-1]&0x000000ff);
	// program info descriptor
	if (pkt->program_info_length != 0)
	{
		pos += pkt->program_info_length;
	}
	// Get stream type and PID
	for (; pos <= (pkt->section_length + 2) - 4; )
	{
		pkt->stream_type = buf[pos];
		pkt->reserved_5 = buf[pos+1]>>5;
		pkt->elementary_PID = ((buf[pos+1]<<8)|buf[pos+2])&0x1fff;
		pkt->reserved_6 = buf[pos+3]>>4;
		pkt->ES_info_length = (buf[pos+3]&0x0f)<<8|buf[pos+4];
		// Store in es
		es[i].type = pkt->stream_type;
		es[i].pid = pkt->elementary_PID;
		if (pkt->ES_info_length != 0)
		{
			pos += 5;
			pos += pkt->ES_info_length;
		}
		else
		{
			pos += 5;
		}
		++i;
	}
}

int main()
{
	ts_pkt_hdr ts_hdr;
	memset(&ts_hdr, 0, sizeof(ts_hdr));
	if (sizeof(ts_hdr) > sizeof(ts_strm))
	{
		return -1;
	}
	memcpy(&ts_hdr, ts_strm, sizeof(ts_hdr));
	adjust_ts_pkt_hdr(&ts_hdr);

	ts_PAT PAT;
	memset(&PAT, 0, sizeof(PAT));
	if (sizeof(PAT) > sizeof(ts_strm) - sizeof(ts_hdr))
	{
		return -1;
	}
	unsigned ts_offset = sizeof(ts_pkt_hdr);
	if (ts_hdr.payload_unit_start_indicator == 1)
	{
		ts_offset += 1;
	}
	adjust_PAT_table(&PAT, (char*)ts_strm + ts_offset);

	ts_PMT PMT;
	memset(&PMT, 0, sizeof(ts_PMT));
	adjust_PMT_table(&PMT, ts_strm1);

	return 0;
}
