/**
 * ============================================================================
 * @file    multicastsrv.cpp
 *
 * @brief   
 * @details 
 *
 * @version 1.0  
 * @date    2013-02-25 15:12:45
 *
 * @author  shizhijie, shizhijie@baofeng.com
 * ============================================================================
 */

#include <stdio.h>
#include <netdb.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAXBUF 256
#define PUERTO 5000
#define GRUPO "224.0.1.1"

int main(void)
{
	int s;
	struct sockaddr_in srv;
	char buf[MAXBUF];
	bzero(&srv, sizeof(srv));
	srv.sin_family = AF_INET;
	srv.sin_port = htons(PUERTO);
	if (inet_aton(GRUPO, &srv.sin_addr) < 0)
	{
		perror("inet_aton");
		return 1;
	}

	if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("socket");
		return 1;
	}

	while (fgets(buf, MAXBUF, stdin))
	{
		if (sendto(s, buf, strlen(buf), 0, (struct sockaddr *)&srv, sizeof(srv)) < 0)
		{
			perror("recvfrom");
		}
		else
		{
			fprintf(stdout, "Enviado a %s: %s", GRUPO, buf);
		}
	}
}
