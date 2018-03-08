/**
 * ============================================================================
 * @file    vlu_imp.h
 *
 * @brief   
 * @details 
 *
 * @version 1.0  
 * @date    2013-06-08 17:09:28
 *
 * @author  shizhijie, shizhijie@baofeng.com
 * ============================================================================
 */

#ifndef __BFP2P_SERVER_VLU_IMP_H__
#define __BFP2P_SERVER_VLU_IMP_H__
#include <stdint.h>
#include <bitset>

typedef std::bitset<sizeof(uint64_t) * 8> bitset64_t;
typedef std::bitset<sizeof(uint32_t) * 8> bitset32_t;

uint32_t read7bit(const char *pstr);
uint64_t read7bit_long(const char *pstr);

uint32_t write7bit(uint32_t value);
uint64_t write7bit_long(uint64_t value);

#endif //__BFP2P_SERVER_VLU_IMP_H__

