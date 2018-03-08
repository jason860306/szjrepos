/**
 * ============================================================================
 * @file    iov_demo.c
 *
 * @brief   
 * @details 
 *
 * @version 1.0  
 * @date    2013-09-22 11:21:46
 *
 * @author  shizhijie, shizhijie@baofeng.com
 * ============================================================================
 */

#include <string.h>
#include <stdlib.h>
#include <sys/uio.h>
#include <sys/unistd.h>

int main(void)
{
	char part1[] = "This is iov";
	char part2[] = " and ";
	char part3[] = " writev test\n";

	struct iovec iov[3];
	iov[0].iov_base = part1;
	iov[0].iov_len = strlen(part1);
	iov[1].iov_base = part2;
	iov[1].iov_len = strlen(part2);
	iov[2].iov_base = part3;
	iov[2].iov_len = strlen(part3);
	writev(1, iov, 3);

	size_t buf_len = strlen(part1) + strlen(part2) + strlen(part3);
	char *p_buf = (char *)malloc(sizeof(char) * (buf_len + 1));
	p_buf[buf_len] = '\0';
	memcpy(p_buf, part1, strlen(part1));
	memcpy(p_buf + strlen(part1), part2, strlen(part2));
	memcpy(p_buf + strlen(part1) + strlen(part2), part3, strlen(part3));
	write(1, p_buf, buf_len);
	free(p_buf); p_buf = NULL;

	return 0;
}
