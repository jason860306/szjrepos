/**
 * ============================================================================
 * @file    scale.c
 *
 * @brief   
 * @details 
 *
 * @version 1.0  
 * @date    Fri Dec 21 18:18:09 CST 2012
 *
 * @author  shizhijie, shizhijie@baofeng.com
 * ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>

int main()
{
	char a = 0x0f;
	char b = 0xf0;
	char c = 0xf;
	char d = 0x0;

	/* 38 (gdb) x/1tb &a */
	/* 39 0x7fffffffe2dc: 00001111 */
	/* 40 (gdb) x/1tb &b */
	/* 41 0x7fffffffe2dd: 11110000 */
	/* 42 (gdb) x/1tb &c */
	/* 43 0x7fffffffe2de: 00001111 */
	/* 44 (gdb) x/1tb &d */
	/* 45 0x7fffffffe2df: 00000000 */
	
	return 0;
}
