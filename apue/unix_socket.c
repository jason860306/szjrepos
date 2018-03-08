/**
 * ============================================================================
 * @file    unix_socket.c
 *
 * @brief   
 * @details 
 *
 * @version 1.0  
 * @date    2013-10-10 11:37:47
 *
 * @author  shizhijie, shizhijie@baofeng.com
 * ============================================================================
 */

#include "apue.h"
#include "errno.h"
#include <sys/socket.h>
#include <sys/un.h>

int main(void)
{
	int fd, size;
	struct sockaddr_un un;
	un.sun_family = AF_UNIX;
	strcpy(un.sun_path, "foo.socket");
	if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
	{
		fprintf(stderr, "socket failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	size = offsetof(struct sockaddr_un, sun_path) + strlen(un.sun_path); /* size = 12 */
	size = sizeof(struct sockaddr_un); /* size = 110 */
	if (bind(fd, (struct sockaddr *)&un, size) < 0)
	{
		fprintf(stderr, "bind failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	fprintf(stdout, "UNIX domain socket bound\n");
	exit(EXIT_SUCCESS);
}
