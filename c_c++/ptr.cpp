#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char buf1[20];
	char *buf2 = new char[20];
	buf2 = buf1;
//	buf1 = buf2;

	const char *ptr = "helloworld";
	char parray[20] = "helloworld";

	ptr = buf2;
//	parray = buf1;

	char *c1 = "abc";
	char c2[] = "abcd";
	char *c3 = (char*)malloc(10);
    char *tmp_c3 = c3;
	c3 = "abc";
//	strcpy(c3, "12");
//	c3[0] = 'g';

	c2[1] = '0';
//	c1[1] = 'a';

    printf("%020x %020x %s\n", &c1, c1, c1);
    printf("%020x %020x %s\n", &c2, c2, c2);
    printf("%020x %020x %s\n", &c3, c3, c3);

    free(tmp_c3);
    tmp_c3 = NULL;
}
