#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char *p = NULL;
	fprintf(stdout, "*p = %c", *p);

	p = (char *)malloc(8);
	fprintf(stderr, "p10: %c\n", p[10]);
	p[12] = 'a';
	/*free(p);*/
	
	return 0;
}
