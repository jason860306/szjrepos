/**
 * ============================================================================
 * @file    defconstructor.cpp
 *
 * @brief   
 * @details 
 *
 * @version 1.0  
 * @date    2013-02-26 13:22:03
 *
 * @author  shizhijie, shizhijie@baofeng.com
 * ============================================================================
 */

#include <stdio.h>
#include <iostream>
#include <string>

struct tmpa
{
	char a;
	short b;
	int c;
	std::string d;
//	long e;

	void print()
	{
		printf("internal: a = %d, b = %d, c = %d, d = %s, e = ld\n", a, b, c, d.c_str()/*, e*/);
	}
	
} g_tmpa;

int main(void)
{
//	printf("g_tmpa: a = %d, b = %d, c = %d, d = %s, e = ld\n",
//		   g_tmpa.a, g_tmpa.b, g_tmpa.c, g_tmpa.d.c_str()/*, g_tmpa.e*/);

	{
		char a[128];
		for (unsigned int i = 0; i < sizeof(a); ++i)
			a[i] = -1;
	}
	{
	tmpa loca;
	printf("loca: a = %d, b = %d, c = %d, d = %s, e = ld\n",
		   loca.a, loca.b, loca.c, loca.d.c_str()/*, loca.e*/);

	loca.print();
	}
}
