/**
 * ============================================================================
 * @file    mcastclient.c
 *
 * @brief   
 * @details 
 *
 * @version 1.0  
 * @date    2013-02-25 18:18:42
 *
 * @author  shizhijie, shizhijie@baofeng.com
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUFLEN 255

int main(int /* argc */, char *argv[])
{
	struct sockaddr_in peeraddr, myaddr;

	int sockfd;
	char recmstg[BUFLEN + 1];
	unsigned int socklen;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0)
	{
		printf("socket creating error\n");
		exit(1);
	}
	socklen = sizeof(struct sockaddr_in);

	memset(&peeraddr, 0, socklen);
	peeraddr.sin_family = AF_INET;
	if (argv[2])
	{
		peeraddr.sin_port = htons(atoi(argv[2]));
	}
	else
	{
		peeraddr.sin_port = htons(7838);
	}

	if (argv[1])
	{
		/* 注意这里设置的对方地址是指组播地址，而不是对方的实际IP地址 */
		if (inet_pton(AF_INET, argv[1], &peeraddr.sin_addr) <= 0)
		{
			printf("wrong group address!\n");
			exit(0);
		}
	}
	else
	{
		printf("no group address!\n");
		exit(0);
	}

	memset(&myaddr, 0, socklen);
	myaddr.sin_family = AF_INET;
	if (argv[4])
	{
		myaddr.sin_port = htons(atoi(argv[4]));
	}
	else
	{
		myaddr.sin_port = htons(23456);
	}

	if (argv[3])
	{
		if (inet_pton(AF_INET, argv[3], &myaddr.sin_addr) <= 0)
		{
			printf("self address error!\n");
			exit(0);
		}
	}
	else
	{
		myaddr.sin_addr.s_addr = INADDR_ANY;
	}

	if (bind(sockfd, (struct sockaddr *)&myaddr, sizeof(struct sockaddr_in)) == -1)
	{
		printf("Bind error\n");
		exit(0);
	}

	for (;;)
	{
		bzero(recmstg, BUFLEN + 1);
		if (fgets(recmstg, BUFLEN, stdin) == (char *)EOF)
		{
			exit(0);
		}
		if (sendto(sockfd, recmstg, strlen(recmstg), 0, (struct sockaddr *)&peeraddr,
				sizeof(struct sockaddr_in)) < 0)
		{
			printf("sendto error!\n");
			exit(3);
		}
		printf("%s' send ok\n", recmstg);
	}
}
