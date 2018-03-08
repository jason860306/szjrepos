/**
 * ============================================================================
 * @file    option_imp.cpp
 *
 * @brief   
 * @details 
 *
 * @version 1.0  
 * @date    2013-06-08 17:05:45
 *
 * @author  shizhijie, shizhijie@baofeng.com
 * ============================================================================
 */

#include <stdint.h>
#include <string.h>
#include <stddef.h>
#include "option_imp.h"
#include "vlu_imp.h"

uint32_t get_option_len(const option_t *p_option)
{
	return (NULL == p_option) ? 0 : (sizeof(*p_option) + p_option->oplen);
}

const option_t *set_option(uint8_t type, uint8_t *p_value, uint8_t len, option_t **pp_option)
{
	option_t *p_op = NULL;
	if (NULL != pp_option)
	{
		p_op = *pp_option;
	}
	if (NULL == p_op)
	{
		uint16_t opsize = sizeof(option_t) + len;
		p_op = reinterpret_cast<option_t *>(new char[opsize]);
		memset(p_op, 0xff, opsize);
	}
	p_op->oplen = len;
	if (len > 0)
	{
		p_op->optype = type;
		memcpy(p_op->opvalue, p_value, len);
	}
	return p_op;
}

const option_t *read_option(const uint8_t *pstr, option_t **pp_option)
{
	option_t *p_op = NULL;
	if (NULL != pp_option)
	{
		p_op = *pp_option;
	}
	if (NULL == pstr)
	{
		return (p_op == NULL) ? NULL : p_op;
	}
	uint32_t len = read7bit(reinterpret_cast<const char *>(pstr));
	if (NULL == p_op)
	{
		uint16_t opsize = sizeof(option_t) + len;
		p_op = reinterpret_cast<option_t *>(new char[opsize]);
		memset(p_op, 0xff, opsize);
	}
	p_op->oplen = len;
	if (len > 0)
	{
		p_op->optype = read7bit(reinterpret_cast<const char *>(
									pstr + offsetof(option_t, optype)));
		memcpy(p_op->opvalue, pstr + offsetof(option_t, opvalue), len);
	}
	return p_op;
}

const uint8_t *write_option(const option_t *p_option, uint8_t **pp_opdata, uint32_t &opdata_len)
{
	uint16_t oplen = get_option_len(p_option);
	if (NULL == p_option || (NULL != pp_opdata && NULL != *pp_opdata && oplen > opdata_len))
	{
		return NULL;
	}
	uint8_t *p_opdata = *pp_opdata;
	if (NULL == p_opdata)
	{
		p_opdata = new uint8_t[oplen];
		memset(p_opdata, 0xff, oplen);
		opdata_len = oplen;
	}
	uint8_t len = write7bit(p_option->oplen), type = write7bit(p_option->optype);
	memcpy(p_opdata, &len, sizeof(len));
	memcpy(p_opdata + offsetof(option_t, optype), &type, sizeof(type));
	memcpy(p_opdata + offsetof(option_t, opvalue), p_option->opvalue, p_option->oplen);
	return p_opdata;
}

void free_option(option_t *p_op)
{
	if (NULL != p_op)
	{
		delete p_op; p_op = NULL;
	}
}
