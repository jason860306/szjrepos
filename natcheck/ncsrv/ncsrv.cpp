#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#ifndef WIN32
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#else
#include <Windows.h>
#include <WinSock2.h>
#endif
#include "nctype.h"
#include "natcheck.h"

int srv_sock_ip1_port1 = -1;
int srv_sock_ip1_port2 = -1;
int srv_sock_ip2_port1 = -1;
int srv_sock_ip2_port2 = -1;

static int CloseAllSock();
static int ChildProc(int sockfd, const struct sockaddr_in* paddr);

int main(int argc, char *argv[])
{
	if (argc != 5)
	{
		printf("usage:\n");
		printf("\t%s ip1 port2 ip2 port2\n", argv[0]);
		return -1;
	}

	struct sockaddr_in srv_addr_ip1_port1;
	struct sockaddr_in srv_addr_ip1_port2;
	struct sockaddr_in srv_addr_ip2_port1;
	struct sockaddr_in srv_addr_ip2_port2;

	pid_t pid_ip1_port1 = 0;
	pid_t pid_ip1_port2 = 0;
	pid_t pid_ip2_port1 = 0;
	pid_t pid_ip2_port2 = 0;

/**
 * server1's address info.
 */
	if (0 != SetAddr(&srv_addr_ip1_port1, argv[1], argv[2]))
	{
		printf("SetAddr failed!");
		fflush(stdout);
		CloseAllSock();
		return -1;
	}
	srv_sock_ip1_port1 = CreateUdpSock(&srv_addr_ip1_port1);
	if (srv_sock_ip1_port1 <= 0)
	{
		printf("CreateUdpSock failed");
		fflush(stdout);
		CloseAllSock();
		return -1;
	}

/**
 * server2's address info
 */	
	if (0 != SetAddr(&srv_addr_ip1_port2, argv[1], argv[4]))
	{
		printf("SetAddr failed!");
		fflush(stdout);
		CloseAllSock();
		return -1;
	}
	srv_sock_ip1_port2 = CreateUdpSock(&srv_addr_ip1_port2);
	if (srv_sock_ip1_port2 <= 0)
	{
		printf("CreateUdpSock failed");
		fflush(stdout);
		CloseAllSock();
		return -1;
	}

/**
 * server3's address info
 */	
	if (0 != SetAddr(&srv_addr_ip2_port1, argv[3], argv[2]))
	{
		printf("SetAddr failed!");
		fflush(stdout);
		CloseAllSock();
		return -1;
	}
	srv_sock_ip2_port1 = CreateUdpSock(&srv_addr_ip2_port1);
	if (srv_sock_ip2_port1 <= 0)
	{
		printf("CreateUdpSock failed");
		fflush(stdout);
		CloseAllSock();
		return -1;
	}

/**
 * server4's address info
 */	
	if (0 != SetAddr(&srv_addr_ip2_port2, argv[3], argv[4]))
	{
		printf("SetAddr failed!");
		fflush(stdout);
		CloseAllSock();
		return -1;
	}
	srv_sock_ip2_port2 = CreateUdpSock(&srv_addr_ip2_port2);
	if (srv_sock_ip2_port2 <= 0)
	{
		printf("CreateUdpSock failed");
		fflush(stdout);
		CloseAllSock();
		return -1;
	}

/**
 * fork some child process to handle the message.
 */
	if ((pid_ip1_port1 = fork()) < 0)
	{
        /** error */
		printf("%s\n", strerror(errno));
		fflush(stdout);
		CloseAllSock();
		return -1;
	}
	else if (pid_ip1_port1 == 0)
	{
		/**
		 * child
		 *
		 * recv with srv_sock_ip1_port1
		 */
		ChildProc(srv_sock_ip1_port1, &srv_addr_ip1_port1);
		CloseAllSock();
		return 0;
	}

	if ((pid_ip1_port2 = fork()) < 0)
	{
		/** error */
		printf("%s\n", strerror(errno));
		fflush(stdout);
		CloseAllSock();
		return -1;
	}
	else if (pid_ip1_port2 == 0)
	{
       /**
		* child
		*
		* recv with srv_sock_ip1_port2
		*/
		ChildProc(srv_sock_ip1_port2, &srv_addr_ip1_port2);
		CloseAllSock();
		return 0;
	}

	if ((pid_ip2_port1 = fork()) < 0)
	{
		/** error */
		printf("%s\n", strerror(errno));
		fflush(stdout);
		CloseAllSock();
		return -1;
	}
	else if (pid_ip2_port1 == 0)
	{
       /**
		* child
		*
		* recv with srv_sock_ip2_port1
		*/
		ChildProc(srv_sock_ip2_port1, &srv_addr_ip2_port1);
		CloseAllSock();
		return 0;
	}

	if ((pid_ip2_port2 = fork()) < 0)
	{
		/** error */
		printf("%s\n", strerror(errno));
		fflush(stdout);
		CloseAllSock();
		return -1;
	}
	else if (pid_ip2_port2 == 0)
	{
       /**
		* child
		*
		* recv with srv_sock_ip2_port2
		*/
		ChildProc(srv_sock_ip2_port2, &srv_addr_ip2_port2);
		CloseAllSock();
		return 0;
	}

	if (pid_ip1_port1 != waitpid(pid_ip1_port1, NULL, 0))
	{
		printf("%s\n", strerror(errno));
		fflush(stdout);
	}
	if (pid_ip1_port2 != waitpid(pid_ip1_port2, NULL, 0))
	{
		printf("%s\n", strerror(errno));
		fflush(stdout);
	}
	if (pid_ip2_port1 != waitpid(pid_ip2_port1, NULL, 0))
	{
		printf("%s\n", strerror(errno));
		fflush(stdout);
	}
	if (pid_ip2_port2 != waitpid(pid_ip2_port2, NULL, 0))
	{
		printf("%s\n", strerror(errno));
		fflush(stdout);
	}

	CloseAllSock();

	return 0;
}

static int CloseAllSock()
{
	CLOSE(srv_sock_ip1_port1);
	CLOSE(srv_sock_ip1_port2);
	CLOSE(srv_sock_ip2_port1);
	CLOSE(srv_sock_ip2_port2);
#ifdef WIN32
	return errno;
#else
    return GetLastError();
#endif
}

static int ChildProc(int sockfd, const struct sockaddr_in* paddr)
{
	assert(NULL != paddr);
	
	TReqPkt req_pkt;
	TResPkt res_pkt;
	struct sockaddr_in tmp_addr;
	uint32_t addr_len = sizeof(struct sockaddr_in);
	int len = 0;
	int snd_sock = -1;

	while (1)
	{
		printf("listenning on: %s\n", FormatAddr1(paddr));

		memset(&req_pkt, 0, sizeof(req_pkt));
		memset(&tmp_addr, 0, sizeof(tmp_addr));
		len = recvfrom(sockfd, (char *)&req_pkt, sizeof(req_pkt), 0,
						   (struct sockaddr *)&tmp_addr, &addr_len);
		if (len < 0 || errno == EAGAIN)
		{
			printf("%s\n", strerror(errno));
			fflush(stdout);
			continue;
		}
		printf("recv from: %s\n", FormatAddr1(&tmp_addr));

		memset(&res_pkt, 0, sizeof(res_pkt));
		res_pkt.addr.ip = tmp_addr.sin_addr.s_addr;
		res_pkt.addr.port = tmp_addr.sin_port;

		switch (req_pkt.cmd)
		{
		case CLIENT_REQ_IP_PORT:
			snd_sock = srv_sock_ip1_port1;
			break;
		case CLIENT_REQ_TRY_OTHER_IP:
			snd_sock = srv_sock_ip2_port1;
			break;
		case CLIENT_REQ_TRY_OTHER_PORT:
			snd_sock = srv_sock_ip1_port2;
			break;
		case CLIENT_REQ_TRY_OTHER_IP_PORT:
			snd_sock = srv_sock_ip2_port2;
			break;
		default:
			return 0;
		}
		len = sendto(snd_sock, (char *)&res_pkt, sizeof(res_pkt), 0,
					 (struct sockaddr *)&tmp_addr, sizeof(tmp_addr));
		if (len < 0)
		{
			printf("%s\n", strerror(errno));
			fflush(stdout);
			continue;
		}
	}
}
