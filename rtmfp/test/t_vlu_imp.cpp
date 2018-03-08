/**
 * ============================================================================
 * @file    t_vlu_imp.cpp
 *
 * @brief   
 * @details 
 *
 * @version 1.0  
 * @date    2013-06-09 12:07:52
 *
 * @author  shizhijie, shizhijie@baofeng.com
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "vlu_imp.h"

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "usage: %s value\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	try
	{
		uint32_t src_value32 = strtoul(argv[1], NULL, 10);
		bitset32_t src_bs32(src_value32);
		uint32_t vlu_value32 = write7bit(static_cast<uint32_t>(src_value32));
		bitset32_t vlu_bs32(vlu_value32);
		uint32_t dst_value32 = read7bit(reinterpret_cast<char *>(&vlu_value32));
		bitset32_t dst_bs32(dst_value32);
		fprintf(stdout, "32bit:\n src_value32 = %s\n vlu_value32 = %s\n dst_value32 = %s\n",
		src_bs32.to_string().c_str(), vlu_bs32.to_string().c_str(),
		dst_bs32.to_string().c_str());
		
		uint64_t src_value64 = strtoull(argv[1], NULL, 10);
		bitset64_t src_bs64(src_value64);
		uint64_t vlu_value64 = write7bit_long(static_cast<uint64_t>(src_value64));
		bitset64_t vlu_bs64(vlu_value64);
		uint64_t dst_value64 = read7bit_long(reinterpret_cast<char *>(&vlu_value64));
		bitset64_t dst_bs64(dst_value64);
		fprintf(stdout, "64bit:\n src_value64 = %s\n vlu_value64 = %s\n dst_value64 = %s\n",
		src_bs64.to_string().c_str(), vlu_bs64.to_string().c_str(),
		dst_bs64.to_string().c_str());
	}
	catch (std::exception &ex)
	{
		fprintf(stdout, "exception: %s\n", ex.what());
		exit(EXIT_FAILURE);
	}

	return 0;
}
