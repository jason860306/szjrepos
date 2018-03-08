/**
 * ============================================================================
 * @file    ipconf.c
 *
 * @brief   
 * @details 
 *
 * @version 1.0  
 * @date    2013-03-27 06:36:12
 *
 * @author  shizhijie, shizhijie@baofeng.com
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

static const char szHelp[] = { "help" };
static const char szIpConvType[] = { "ipconv_type" };
static const char szInetType[] = { "inet_type" };
static const char szIpStr[] = { "ipstr" };
static const char szIpNum[] = { "ipnum" };
static const char szOptStr[] = { "h?" };

enum { IPCONV_DEFAULT = -1, IPCONV_NUM2STR, IPCONV_STR2NUM };

static const struct option longOpts[] = {
	{ szHelp, no_argument, NULL, 0 },
	{ szIpConvType, required_argument, NULL, 0 },
	{ szInetType, required_argument, NULL, 0},
	{ szIpStr, required_argument, NULL, 0 },
	{ szIpNum, required_argument, NULL, 0},
	{ NULL, no_argument, NULL, 0}
};

static int usage()
{
	const char help[] = {
		"ipconv - a convert tool for ip ( str_ip -> num_ip | num_ip -> str_ip ).\n"
		"usage: ipconv szIpConvType szInetType ( szIpStr | szIpNum )\n"
		"argument:\n"
		"  -h(?)\n"
		"  --help        display this help message and exit.\n"
		"  --ipconv_type convert type from a string to a number or a number to a string.\n"
		"    avaliable value: (default: %d)\n"
		"    %d - convert from a number to a string\n"
		"    %d - convert from a string to a number\n"
		"  --inet_type   address families.\n"
		"    avaliable value: (default: 0 - AF_INET)\n"
		"    0 - AF_INET\n"
		"    1 - AF_INET6\n"
		"  --ipstr       a string stored ip address\n"
		"  --ipnum       a number stored ip address\n"
	};
	printf(help, IPCONV_STR2NUM, IPCONV_NUM2STR, IPCONV_STR2NUM);
	exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
	if (1 == argc)
	{
		usage();
		return 0;
	}

	int opt = 0, nLongIdx = 0, nIpConvType = IPCONV_DEFAULT, nInetType = AF_INET;
	unsigned long int nIp = 0;
	const char *strIp = NULL;
	while (-1 != (opt = getopt_long(argc, argv, szOptStr, longOpts, &nLongIdx)))
	{
		switch (opt)
		{
		case 'h':
		case '?':
		{
			usage();
			break;
		}
		case 0:
		{
			if (0 == strncmp(szHelp, longOpts[nLongIdx].name, strlen(szHelp)))
			{
				usage();
				break;
			}
			if (0 == strncmp(szIpConvType, longOpts[nLongIdx].name, strlen(szIpConvType)))
			{
				nIpConvType = atoi(optarg);
			}
			if (0 == strncmp(szInetType, longOpts[nLongIdx].name, strlen(szInetType)))
			{
				nInetType = (atoi(optarg) == 0) ? AF_INET : AF_INET6;
			}
			if (0 == strncmp(szIpStr, longOpts[nLongIdx].name, strlen(szIpStr)))
			{
				strIp = optarg;
			}
			if (0 == strncmp(szIpNum, longOpts[nLongIdx].name, strlen(szIpNum)))
			{
				nIp = strtoul(optarg, NULL, 0);
			}
			break;
		}
		default:
			break;
		}
	}
	if (nIpConvType == IPCONV_DEFAULT)
	{
		static const char const *strConvHint[] = {
			"num_ip -> str_ip", "str_ip -> num_ip"
		};
		
		nIpConvType = (strIp != NULL) ? IPCONV_STR2NUM :
			((nIp != 0) ? IPCONV_NUM2STR : IPCONV_DEFAULT);
		printf("no --ipconv_type found, will convert %s.\n", strConvHint[nIpConvType]);
	}
	else if (nIpConvType == IPCONV_STR2NUM && strIp == NULL)
	{
		printf("ipstr is null, use --ipstr to set ipstr.\n");
		exit(EXIT_FAILURE);
	}
	else if (nIpConvType == IPCONV_NUM2STR && nIp == 0)
	{
		printf("ipnum is 0, use --ipnum to set ipnum.\n");
		exit(EXIT_FAILURE);
	}
	
	switch (nIpConvType)
	{
	case IPCONV_STR2NUM:
	{
		struct in_addr ia;
		memset(&ia, 0, sizeof(ia));
		int nRet = 0;
		if ((nRet = inet_pton(nInetType, strIp, &ia)) > 0)
		{
			printf("ipstr = %s\nipnum = %lu (network order) - %lu (host order)\n",
				strIp, (unsigned long int)ia.s_addr, (unsigned long int)ntohl(ia.s_addr));
		}
		else
		{
			printf("convert fail!\n");
		}
		break;
	}
	case IPCONV_NUM2STR:
	{
		struct in_addr ia;
		memset(&ia, 0, sizeof(ia));
		ia.s_addr = htonl(nIp);
		char szDstIp[INET6_ADDRSTRLEN] = { 0 };
		if (NULL != inet_ntop(nInetType, &ia, szDstIp, INET6_ADDRSTRLEN))
		{
			printf("ipnum = %lu (host order) - %lu (network order)\nipstr = %s\n",
				nIp, (unsigned long int)ia.s_addr, szDstIp);
		}
		else
		{
			printf("convert fail!\n");			
		}
		break;
	}
	default:
	{
		printf("convert fail: wrong ipconv_type!");
		break;
	}
	}

	return 0;
}
