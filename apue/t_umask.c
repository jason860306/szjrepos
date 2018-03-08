#include <fcntl.h>
#include "apue.h"

#define RWRWRW (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IROTH)

int main(void)
{
    mode_t mask = umask(0);
	mode_t new_mask = (mask & 0777);
	new_mask = ~(mask & 0777);
    if (creat("foo", RWRWRW) < 0)
    {
        printf("create error for foo");
    }
    umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    if (creat("bar", RWRWRW) < 0)
    {
        printf("create error for bar");
    }
    umask(mask);
    
    exit(0);
}
