/**
 * ============================================================================
 * @file    offset_demo.c
 *
 * @brief   
 * @details 
 *
 * @version 1.0  
 * @date    Thu Dec 20 10:30:58 CST 2012
 *
 * @author  shizhijie, shizhijie@baofeng.com
 * ============================================================================
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	struct s
	{
		int i;
		char c;
		double d;
		char a[];
	};

	/**
	 * Output is compiler dependent
	 */
	printf("offsets: i = %ld; c = %ld; d = %ld; a = %ld\n",
		   (long)offsetof(struct s, i),
		   (long)offsetof(struct s, c),
		   (long)offsetof(struct s, d),
		   (long)offsetof(struct s, a));
	printf("sizeof(struct s) = %ld\n", (long)sizeof(struct s));

	exit(EXIT_SUCCESS);
}
