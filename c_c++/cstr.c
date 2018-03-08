/**
 * ============================================================================
 * @file    cstr.c
 *
 * @brief
 * @details
 *
 * @version 1.0
 * @date    Wed Dec 26 17:53:47 CST 2012
 *
 * @author  shizhijie, shizhijie@baofeng.com
 * ============================================================================
 */
#include <stdio.h>
#include <string.h>

int main()
{
	char names[] = "Alan Bob Chris X Dave";
	if (memchr(names, 'X', strlen(names)) == NULL)
	{
		printf("Didn't find an X\n");
	}
	else
	{
		printf("Found an X\n");
	}
	
    return 0;
}
