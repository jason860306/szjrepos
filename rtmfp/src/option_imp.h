/**
 * ============================================================================
 * @file    option_imp.h
 *
 * @brief   
 * @details 
 *
 * @version 1.0  
 * @date    2013-06-08 17:47:04
 *
 * @author  shizhijie, shizhijie@baofeng.com
 * ============================================================================
 */

#ifndef __BFP2P_SERVER_OPTION_IMP_H__
#define __BFP2P_SERVER_OPTION_IMP_H__
#include "rtmfpdef.h"

uint32_t get_option_len(const option_t *p_option);
const option_t *set_option(uint8_t type, uint8_t *p_value, uint8_t len, option_t **pp_option);
const option_t *read_option(const uint8_t *pstr, option_t **pp_option);
const uint8_t *write_option(const option_t *p_option, uint8_t **pp_opdata, uint32_t &opdata_len);
void free_option(option_t *p_op);

#endif //__BFP2P_SERVER_OPTION_IMP_H__
