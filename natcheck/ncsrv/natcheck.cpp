#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "nctype.h"

/**
 * some function for TNatType
 */
const char* NatType2Name(TNatType nat_type)
{
	static const char const *szNatType[] = {
		"BLOCKED",
		"OPENED",
		"SYMMETRIC_FIRE_WALL",
		"FULL_CONE_NAT",
		"SYMMETRIC_NAT",
		"PORT_RESTRICTED_CONE_NAT",
		"RESTRICTED_CONE_NAT",
		NULL
	};
	if (nat_type < RESTRICTED_CONE_NAT)
	{
		return szNatType[nat_type];
	}
	return "no such nat found!";
}

/**
 * some function for TAddrType
 */
const char* FormatAddr(const TAddrType* pAddr)
{
	assert(NULL != pAddr);
	char addr_buf[INET_ADDRSTRLEN] = { 0 };
	if (0 == inet_ntop(AF_INET, (struct in_addr *)&pAddr->ip, addr_buf, sizeof(addr_buf)))
	{
		printf("%s\n", strerror(errno));
		return "";
	}

	static char addrinfo[128] = { 0 };
	snprintf(addrinfo, sizeof(addrinfo), "%s:%d", addr_buf, ntohs(pAddr->port));

	return addrinfo;
}

const char* FormatAddr1(const struct sockaddr_in* psi)
{
	assert(NULL != psi);
	char addr_buf[INET_ADDRSTRLEN] = { 0 };
	if (0 == inet_ntop(AF_INET, (struct in_addr *)&psi->sin_addr, addr_buf, sizeof(addr_buf)))
	{
		printf("%s\n", strerror(errno));
		return "";
	}

	static char addrinfo[128] = { 0 };
	snprintf(addrinfo, sizeof(addrinfo), "%s:%d", addr_buf, ntohs(psi->sin_port));
	
	return addrinfo;
}

int AddrCmp(const TAddrType* pAddr1, const TAddrType* pAddr2)
{
	assert(NULL != pAddr1 && NULL != pAddr2);
	if (pAddr1->ip == pAddr2->ip && pAddr1->port == pAddr2->port)
	{
		return 0;
	}
	return -1;
}

/**
 * some function for socket
 */
int SetAddr(struct sockaddr_in* paddr, const char* ip, const char* port)
{
	assert(NULL != paddr && NULL != ip && NULL != port);
	memset(paddr, 0, sizeof(*paddr));
	paddr->sin_family = AF_INET;
	paddr->sin_port = htons(atoi(port));
	if (0 == inet_pton(AF_INET, ip, &paddr->sin_addr))
	{
		printf("%s\n", strerror(errno));
		fflush(stdout);
		return -1;
	}
	return 0;
}

int CreateUdpSock(const struct sockaddr_in* paddr)
{
	assert(NULL != paddr);
	
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0)
	{
		printf("%s\n", strerror(errno));
		fflush(stdout);
		return -1;
	}
	if (0 != bind(sockfd, (struct sockaddr *)paddr, sizeof(*paddr)))
	{
		printf("%s\n", strerror(errno));
		fflush(stdout);
		return -1;
	}
	return sockfd;
}
