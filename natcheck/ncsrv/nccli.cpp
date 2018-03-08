#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "nctype.h"
#include "natcheck.h"

static TNatType g_NatType = BLOCKED;

int main(int argc, char *argv[])
{
	if (argc != 7)
	{
		printf("usage:\n");
		printf("\t%s cli_ip cli_port srv_ip1 srv_port2 srv_ip2 srv_port2\n", argv[0]);
		fflush(stdout);
		return -1;
	}

/**
 * client's address info.
 */
	struct sockaddr_in cli_si;
	if (0 != SetAddr(&cli_si, argv[1], argv[2]))
	{
		printf("SetAddr failed!");
		fflush(stdout);
		return -1;
	}

	TAddrType cli_addr;
	memset(&cli_addr, 0, sizeof(cli_addr));
	cli_addr.ip = cli_si.sin_addr.s_addr;
	cli_addr.port = atoi(argv[2]);

	printf("loc_addr: %s\n", FormatAddr(&cli_addr));
	fflush(stdout);

	int cli_sock = CreateUdpSock(&cli_si);
	if (cli_sock <= 0)
	{
		printf("%s\n", strerror(errno));
		fflush(stdout);
		close(cli_sock);
		return -1;
	}

	struct timeval timeout = { 30, 0 };
	int ret = setsockopt(cli_sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
	if (ret < 0)
	{
		printf("%s\n", strerror(errno));
		fflush(stdout);
		close(cli_sock);
		return -1;
	}
	
/**
 * server's address info.
 */
	struct sockaddr_in srv_addr;
	if (0 != SetAddr(&srv_addr, argv[3], argv[4]))
	{
		printf("SetAddr failed!\n");
		fflush(stdout);
		close(cli_sock);
		return -1;
	}

	struct sockaddr_in srv_addr1;
	if (0 != SetAddr(&srv_addr1, argv[5], argv[6]))
	{
		printf("SetAddr failed!\n");
		fflush(stdout);
		close(cli_sock);
		return -1;
	}

	struct sockaddr_in tmp_srv_addr;
	memset(&tmp_srv_addr, 0, sizeof(tmp_srv_addr));
	TAddrType CliMapAddr;
	memset(&CliMapAddr, 0, sizeof(CliMapAddr));

/**
 * natcheck begin.
 */
	while (1)
	{
/**
 * 1. first step
 *    check whether it is blocked.
 */
		TReqPkt req_pkt;
		req_pkt.cmd = CLIENT_REQ_IP_PORT;
		int len = sendto(cli_sock, (char *)&req_pkt, sizeof(req_pkt), 0,
						 (struct sockaddr *)&srv_addr, sizeof(srv_addr));
		if (len < 0)
		{
			printf("%s\n", strerror(errno));
			fflush(stdout);
			close(cli_sock);
			return -1;
		}
		TResPkt  res_pkt;
		memset(&res_pkt, 0, sizeof(res_pkt));
		unsigned int addr_len = sizeof(tmp_srv_addr);
		len = recvfrom(cli_sock, (char *)&res_pkt, sizeof(res_pkt), 0,
					   (struct sockaddr *)&tmp_srv_addr, &addr_len);
		
		if (len < 0 || errno == EAGAIN)
		{
			g_NatType = BLOCKED;
			printf("%s\n", strerror(errno));
			printf("Your network is %s\n", NatType2Name(g_NatType));
			fflush(stdout);
			close(cli_sock);
			return -1;
		}

		memcpy(&CliMapAddr, &res_pkt.addr, sizeof(res_pkt.addr));

		printf("loc_map_addr: %s, recv from %s\n", FormatAddr(&res_pkt.addr),
			   FormatAddr1(&tmp_srv_addr));
		fflush(stdout);
		
/**
 * 2. second step
 *    check whether it is opened or not(symmetric_udp_fire_wall).
 */
		if (0 == AddrCmp(&res_pkt.addr, &cli_addr))
		{
			printf("Congratulation! your network is public with no NAT.\n");
			fflush(stdout);

			memset(&req_pkt, 0, sizeof(req_pkt));
			req_pkt.cmd = CLIENT_REQ_TRY_OTHER_IP_PORT;
			len = sendto(cli_sock, (char *)&req_pkt, sizeof(req_pkt), 0,
						 (struct sockaddr *)&srv_addr, sizeof(srv_addr));
			if (len < 0)
			{
				printf("%s\n", strerror(errno));
				fflush(stdout);
				close(cli_sock);
				return -1;
			}
			memset(&res_pkt, 0, sizeof(res_pkt));
			addr_len = sizeof(tmp_srv_addr);
			len = recvfrom(cli_sock, (char *)&res_pkt, sizeof(res_pkt), 0,
						   (struct sockaddr *)&tmp_srv_addr, &addr_len);
			if (len < 0 || errno == EAGAIN)
			{
				g_NatType = SYMMETRIC_FIRE_WALL;
				printf("Your network is %s.\n", NatType2Name(g_NatType));
				printf("%s\n", strerror(errno));
				fflush(stdout);
				close(cli_sock);
				return -1;
			}
			printf("loc_map_addr: %s, recv from %s\n", FormatAddr(&res_pkt.addr),
				   FormatAddr1(&tmp_srv_addr));
			g_NatType = OPENED;
			printf("Congratulation!, your network is %s.\n", NatType2Name(g_NatType));
			fflush(stdout);
			close(cli_sock);

			return 0;
		}
		else
		{
/**
 * 3. third step
 *    check FULL_CONE or not.
 */
			memset(&req_pkt, 0, sizeof(req_pkt));
			req_pkt.cmd = CLIENT_REQ_TRY_OTHER_IP_PORT;
			len = sendto(cli_sock, (char *)&req_pkt, sizeof(req_pkt), 0,
						 (struct sockaddr *)&srv_addr, sizeof(srv_addr));
			if (len < 0)
			{
				printf("%s\n", strerror(errno));
				fflush(stdout);
				close(cli_sock);
				return -1;
			}
			memset(&res_pkt, 0, sizeof(res_pkt));
			addr_len = sizeof(tmp_srv_addr);
			len = recvfrom(cli_sock, (char *)&res_pkt, sizeof(res_pkt), 0,
						   (struct sockaddr *)&tmp_srv_addr, &addr_len);
			if (len < 0 || errno == EAGAIN)
			{
/**
 * 4. forth step
 *    check symmetric nat or not.
 */
				printf("%s\n", strerror(errno));
				fflush(stdout);
				memset(&req_pkt, 0, sizeof(req_pkt));
				req_pkt.cmd = CLIENT_REQ_IP_PORT;
				len = sendto(cli_sock, (char *)&req_pkt, sizeof(req_pkt), 0,
							 (struct sockaddr *)&srv_addr1, sizeof(srv_addr1));
				if (len < 0)
				{
					printf("%s\n", strerror(errno));
					fflush(stdout);
					close(cli_sock);
					return -1;
				}
				memset(&res_pkt, 0, sizeof(res_pkt));
				addr_len = sizeof(tmp_srv_addr);
				len = recvfrom(cli_sock, (char *)&res_pkt, sizeof(res_pkt), 0,
							   (struct sockaddr *)&tmp_srv_addr, &addr_len);
				if (len < 0 || errno == EAGAIN)
				{
					printf("%s\n", strerror(errno));
					fflush(stdout);
					close(cli_sock);
					return -1;
				}
				if (0 != AddrCmp(&CliMapAddr, &res_pkt.addr))
				{
					g_NatType = SYMMETRIC_NAT;
					printf("loc_map_addr: %s, recv from %s\n", FormatAddr(&res_pkt.addr),
						   FormatAddr1(&tmp_srv_addr));
					printf("your network is %s.\n", NatType2Name(g_NatType));
					fflush(stdout);
					close(cli_sock);

					return 0;
				}

/**
 * 5. fifth step
 *    check port restricted cone nat or not.
 */
				memset(&req_pkt, 0, sizeof(req_pkt));
				len = sendto(cli_sock, (char *)&req_pkt, sizeof(req_pkt), 0,
							 (struct sockaddr *)&srv_addr, sizeof(srv_addr));
				if (len < 0)
				{
					printf("%s\n", strerror(errno));
					fflush(stdout);
					close(cli_sock);
					return -1;
				}
				memset(&res_pkt, 0, sizeof(&res_pkt));
				addr_len = sizeof(tmp_srv_addr);
				len = recvfrom(cli_sock, (char *)&res_pkt, sizeof(res_pkt), 0,
							   (struct sockaddr *)&tmp_srv_addr, &addr_len);
				if (len < 0 || errno == EAGAIN)
				{
					g_NatType = PORT_RESTRICTED_CONE_NAT;
					printf("loc_map_addr: %s, recv from %s\n", FormatAddr(&res_pkt.addr),
						   FormatAddr1(&tmp_srv_addr));
					printf("your network is %s.\n", NatType2Name(g_NatType));
					fflush(stdout);
					close(cli_sock);

					return 0;
				}
/**
 * 6. sixth step
 *    determinate: it's restricted cone nat.
 */
				g_NatType = RESTRICTED_CONE_NAT;
				printf("loc_map_addr: %s, recv from %s\n", FormatAddr(&res_pkt.addr),
					   FormatAddr1(&tmp_srv_addr));
				printf("your network is %s.\n", NatType2Name(g_NatType));
				fflush(stdout);
				close(cli_sock);

/**
 * nat check end here.
 */
				return 0;
			}
			printf("loc_map_addr: %s, recv from %s\n", FormatAddr(&res_pkt.addr),
				   FormatAddr1(&tmp_srv_addr));
			g_NatType = FULL_CONE_NAT;
			printf("your network is %s.\n", NatType2Name(g_NatType));
			fflush(stdout);
			close(cli_sock);

			return 0;
		}
	}
}
