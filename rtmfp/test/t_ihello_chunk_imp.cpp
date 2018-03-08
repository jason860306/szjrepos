/**
 * ============================================================================
 * @file    t_ihello_chunk.cpp
 *
 * @brief   
 * @details 
 *
 * @version 1.0  
 * @date    2013-06-13 15:10:42
 *
 * @author  shizhijie, shizhijie@baofeng.com
 * ============================================================================
 */

#include <string.h>
#include "rtmfp_protocol.h"
#include "ihello_chunk_imp.h"

int main(int /*argc*/, char */*argv*/[])
{
	uint32_t chunk_len = get_chunk_len(NULL);

	static uint8_t ihello[] = {
		0x30, 0x00, 0x29, 0x18, 0x17, 0x0A, 0x72, 0x74,
		0x6D, 0x66, 0x70, 0x3A, 0x2F, 0x2F, 0x31, 0x39,
		0x32, 0x2E, 0x31, 0x36, 0x38, 0x2E, 0x32, 0x30,
		0x32, 0x2E, 0x39, 0x32, 0x04, 0x83, 0x5E, 0xE7,
		0x3E, 0x25, 0x81, 0xEE, 0x1C, 0x49, 0x4D, 0x7F,
		0x10, 0x66, 0xBA, 0xBD, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF
	};
	hex_print(ihello, sizeof(ihello));

	ihello_chunk_t *p_ihello_chunk = NULL, *p_new_ihello_chunk = NULL;
	p_ihello_chunk = read_chunk_ihello(ihello, &p_ihello_chunk);
	ihello_print(p_ihello_chunk);
	chunk_len = get_chunk_len(p_ihello_chunk);
	uint8_t *p_ihello_data = NULL;
	const uint8_t *p_ihello = write_chunk_ihello(p_ihello_chunk, &p_ihello_data, chunk_len);
	hex_print(p_ihello, chunk_len);
	delete[] p_ihello; p_ihello = NULL;
	
	p_new_ihello_chunk = const_cast<ihello_chunk_t *>(
		chunk_clone(p_ihello_chunk, &p_new_ihello_chunk));
	chunk_len = get_chunk_len(p_new_ihello_chunk);	
	free_chunk_ihello(p_ihello_chunk);
	ihello_print(p_new_ihello_chunk);
	const uint8_t *p_new_ihello = write_chunk_ihello(p_new_ihello_chunk, &p_ihello_data,
													 chunk_len);
	hex_print(p_new_ihello, chunk_len);
	delete[] p_new_ihello; p_new_ihello = NULL;
	free_chunk_ihello(p_new_ihello_chunk);

	return 0;
}
