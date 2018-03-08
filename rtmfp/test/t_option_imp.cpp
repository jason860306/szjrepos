/**
 * ============================================================================
 * @file    t_option_imp.cpp
 *
 * @brief   
 * @details 
 *
 * @version 1.0  
 * @date    2013-06-09 12:09:41
 *
 * @author  shizhijie, shizhijie@baofeng.com
 * ============================================================================
 */

#include <string.h>
#include "option_imp.h"

int main(int /*argc*/, char */*argv*/[])
{
	option_t *p_op = NULL;
	uint32_t oplen = get_option_len(p_op);
	p_op = const_cast<option_t *>(set_option(0x1D, (uint8_t *)&"hello, world!"[0], 16, &p_op));
	oplen = get_option_len(p_op);
	uint8_t *p_data = NULL;
	const uint8_t *p_opdata = write_option(p_op, &p_data, oplen);
	free_option(p_op);
	p_op = const_cast<option_t *>(read_option(p_opdata, &p_op));
	free_option(p_op);
	delete[] p_data; p_data = NULL;
	
	return 0;
}
