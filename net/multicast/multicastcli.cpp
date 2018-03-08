/**
 * ============================================================================
 * @file    multicastcli.cpp
 *
 * @brief   
 * @details 
 *
 * @version 1.0  
 * @date    2013-02-25 15:20:30
 *
 * @author  shizhijie, shizhijie@baofeng.com
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAXBUF 256
#define PUERTO 5000
#define GRUPO "224.0.1.1"

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		fprintf(stdout, "usage: %s port\n", argv[0]);
		return 1;
	}
	int s, n, r;
	struct sockaddr_in srv, cli;
	struct ip_mreq mreq;
	char buf[MAXBUF];
	bzero(&srv, sizeof(srv));
	srv.sin_family = AF_INET;
	srv.sin_port = atoi(argv[1]);//htons(PUERTO);
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

	if (bind(s, (struct sockaddr *)&srv, sizeof(srv)) < 0)
	{
		perror("bind");
		return 1;
	}

	if (inet_aton(GRUPO, &mreq.imr_multiaddr) < 0)
	{
		perror("inet_aton");
		return 1;
	}

	mreq.imr_interface.s_addr = htonl(INADDR_ANY);
	if (setsockopt(s, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0)
	{
		perror("setsockopt");
		return 1;
	}

	n = sizeof(cli);
	while (1)
	{
		if ((r = recvfrom(s, buf, MAXBUF, 0, (struct sockaddr *)&cli, (socklen_t*)&n)) < 0)
		{
			perror("recvfrom");
		}
		else
		{
			buf[r] = 0;
			fprintf(stdout, "Mensaje desde %s: %s", inet_ntoa(cli.sin_addr), buf);
		}
	}
}
