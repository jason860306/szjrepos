// addressof.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

/**
 * ============================================================================
 * @file    addressof.cpp
 *
 * @brief   
 * @details 
 *
 * @version 1.0  
 * @date    2013-08-26 17:18:07
 *
 * @author  shizhijie, shizhijie@baofeng.com
 * ============================================================================
 */

#include <memory>

class obj
{
public:
	int operator &() const { return 1; }
};

int _tmain(int argc, _TCHAR* argv[])
{
    obj o;
    printf("address of o 1: 0x%x\n", &o);
    printf("address of o 2: 0x%x\n", std::addressof(o));

    getchar();

	return 0;
}

