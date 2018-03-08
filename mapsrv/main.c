/**
 * ============================================================================
 * @file    main.c
 *
 * @brief   
 * @details 
 *
 * @version 1.0  
 * @date    2013-10-31 14:58:32
 *
 * @author  shizhijie, shizhijie@baofeng.com
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>
#include <errno.h>

#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "mapsrv.h"

static int parse_report(const char *proto_buf, int len, pp_locreport_t pp_locreport);
static int parse_request(const char *proto_buf, int len, pp_locrequest_t pp_request);

static void print_loc(p_loc_t loc);
static void print_loclst(p_loclst_t p_loclst);
static void print_locreport(p_locreport_t locreport);
static void print_locrequest(p_locrequest_t locrequest);
static void print_locresponse(p_locresponse_t locresponse);

static p_loclst_t g_p_loclst;

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "usage: %s port\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	g_p_loclst = (p_loclst_t)malloc(sizeof(loclst_t));
	if (NULL == g_p_loclst)
	{
		fprintf(stderr, "malloc g_p_loclst failure.\n");
		exit(EXIT_FAILURE);
	}
	bzero(g_p_loclst, sizeof(loclst_t));
	
	int listenfd, connfd, n;
	struct sockaddr_in srvaddr, cliaddr;
	socklen_t clilen;
	pid_t childpid;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&srvaddr, sizeof(srvaddr));
	srvaddr.sin_family = AF_INET;
	srvaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	srvaddr.sin_port = htons(atoi(argv[1]));
	bind(listenfd, (struct sockaddr *)&srvaddr, sizeof(srvaddr));

	listen(listenfd, 1024);

	for (;;)
	{
		clilen = sizeof(cliaddr);
		connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);

//		if ((childpid = fork()) == 0)
		{
//			close(listenfd);

//			for (;;)
			{
				proto_type_t proto_type;
				n = recv(connfd, (char *)&proto_type, sizeof(proto_type), 0);
				if (-1 == n || 0 == n)
				{
					fprintf(stderr, "recv err: %s\n", strerror(errno));
					close(connfd);
					break;
				}
				else if (0 == n)
				{
					usleep(2000);
					continue;
				}
				proto_type = ntohl(proto_type);
				int length;
				n = recv(connfd, (char *)&length, sizeof(length), 0);
				length = ntohl(length);
				int buflen = (length - sizeof(proto_type_t) - sizeof(int));
				char *proto_buf = (char *)malloc(buflen);
				n = recv(connfd, proto_buf, buflen, 0);
				int recv_tms = 0;
				while (n != buflen)
				{
					fprintf(stdout, "recv %d bytes %d times.\n", n, ++recv_tms);
					char *pbuf = proto_buf + n;
					n += recv(connfd, pbuf, buflen - n, 0);
				}
				fprintf(stdout, "recv %d bytes %d times.\n", n, ++recv_tms);

				switch (proto_type)
				{
				case LOCATION_REPORT:
				{
					locreport_t locreport;
					locreport.proto_type = LOCATION_REPORT;
					locreport.length = buflen + offsetof(locreport_t, loc);
					p_locreport_t p_locreport = &locreport;
					if (0 == parse_report(proto_buf, buflen, &p_locreport))
					{
						add_loc(g_p_loclst, &locreport.loc);
//					print_loclst(g_p_loclst);
					}
					break;
				}
				case LOCATION_REQUEST:
				{
					locrequest_t locrequest;
					locrequest.proto_type = LOCATION_REQUEST;
					locrequest.length = (buflen + offsetof(locrequest_t, radius));
					p_locrequest_t p_locrequest = &locrequest;
					if (0 == parse_request(proto_buf, buflen, &p_locrequest))
					{
						p_loclst_t p_loclst = (p_loclst_t)malloc(sizeof(loclst_t));
						find_loc(g_p_loclst, &locrequest.loc, locrequest.radius, &p_loclst);
						if (p_loclst->num <= 0)
						{
							break;
						}

						locresponse_t locresponse;
						locresponse.proto_type = LOCATION_RESPONSE;
						locresponse.length = (offsetof(locresponse_t, p_loclst) +
							p_loclst->size);
						locresponse.p_loclst = p_loclst;

						char *resbuf = (char *)malloc(locresponse.length);
						int type = htonl(locresponse.proto_type);
						memcpy(resbuf, (char *)&type, sizeof(type));
						int length = htonl(locresponse.length);
						memcpy(resbuf + offsetof(locresponse_t, length),
							(char *)&length, sizeof(length));
						char *loclstbuf = (resbuf + offsetof(locresponse_t, p_loclst));
						int size = loclst2buf(locresponse.p_loclst,	&loclstbuf);

						print_locresponse(&locresponse);

						if (-1 == send(connfd, resbuf, size, 0))
						{
							fprintf(stderr, "send err: %s\n", strerror(errno));
						}
					}
					break;
				}
				default:
					break;
				}
				free(proto_buf); proto_buf = NULL;
				close(connfd);
			}
		}
	}

	return 0;
}

static int parse_report(const char *proto_buf, int len, pp_locreport_t pp_locreport)
{
	assert(len == sizeof(loc_t));
	if (NULL == pp_locreport || 0 == len)
	{
		return -1;
	}
	else if (NULL == *pp_locreport)
	{
		*pp_locreport = (p_locreport_t)malloc(sizeof(locreport_t));
		if (NULL == *pp_locreport)
		{
			return -1;
		}
		bzero(*pp_locreport, sizeof(locreport_t));
		(*pp_locreport)->proto_type = LOCATION_REPORT;
		(*pp_locreport)->length = len + offsetof(locreport_t, loc);
	}
	p_loc_t p_loc = &(*pp_locreport)->loc;
	buf2loc(proto_buf, len, &p_loc);
	print_locreport(*pp_locreport);

	return 0;
}

static int parse_request(const char *proto_buf, int len, pp_locrequest_t pp_locrequest)
{
	assert(len == sizeof(locrequest_t) - offsetof(locrequest_t, radius));
	if (NULL == pp_locrequest)
	{
		return -1;
	}
	else if (NULL == *pp_locrequest)
	{
		*pp_locrequest = (p_locrequest_t)malloc(sizeof(locrequest_t));
		if (NULL == *pp_locrequest)
		{
			return -1;
		}
		bzero(*pp_locrequest, sizeof(locrequest_t));
		(*pp_locrequest)->proto_type = LOCATION_REQUEST;
		(*pp_locrequest)->length = (len + offsetof(locrequest_t, radius));
	}
	memcpy((char *)&(*pp_locrequest)->radius, proto_buf, sizeof((*pp_locrequest)->radius));
	(*pp_locrequest)->radius = ntohd((*pp_locrequest)->radius);
	p_loc_t p_loc = &(*pp_locrequest)->loc;
	const char *pbuf = proto_buf + sizeof((*pp_locrequest)->radius);
	buf2loc(pbuf, len - sizeof((*pp_locrequest)->radius), &p_loc);
	print_locrequest(*pp_locrequest);

	return 0;
}

static void print_loc(p_loc_t p_loc)
{
	if (NULL == p_loc)
	{
		return;
	}
	fprintf(stdout, "location:\n");
	fprintf(stdout, "latitude: %lf\n", p_loc->latitude);
	fprintf(stdout, "longitude: %lf\n", p_loc->longitude);
	fprintf(stdout, "coordinate: %d\n", p_loc->coordinate);
	fprintf(stdout, "loctype: %d\n", p_loc->loctype);
	fprintf(stdout, "\n");
}

static void print_loclst(p_loclst_t p_loclst)
{
	if (NULL == p_loclst)
	{
		return;
	}
	fprintf(stdout, "loclst:\n");
	p_locnode_t node = NULL;
	int i = 0;
	for (node = p_loclst->p_loc_first; node != NULL;
		 node = node->p_locnode_next)
	{
		fprintf(stdout, "%d.\n", ++i);
		print_loc(node->p_loc);
	}
	fprintf(stdout, "\n");
}

static void print_locreport(p_locreport_t p_locreport)
{
	if (NULL == p_locreport)
	{
		return;
	}
	fprintf(stdout, "locreport:\n");
	fprintf(stdout, "proto_type: %d\n", p_locreport->proto_type);
	fprintf(stdout, "length: %d\n", p_locreport->length);
	print_loc(&p_locreport->loc);
	fprintf(stdout, "\n");
}

static void print_locrequest(p_locrequest_t p_locrequest)
{
	if (NULL == p_locrequest)
	{
		return;
	}
	fprintf(stdout, "locrequest:\n");
	fprintf(stdout, "proto_type: %d\n", p_locrequest->proto_type);
	fprintf(stdout, "length: %d\n", p_locrequest->length);
	fprintf(stdout, "radius: %lf\n", p_locrequest->radius);
	print_loc(&p_locrequest->loc);
	fprintf(stdout, "\n");
}

static void print_locresponse(p_locresponse_t p_locresponse)
{
	if (NULL == p_locresponse)
	{
		return;
	}
	fprintf(stdout, "locresponse:\n");
	fprintf(stdout, "proto_type: %d\n", p_locresponse->proto_type);
	fprintf(stdout, "peer num: %d\n", p_locresponse->p_loclst->num);
	print_loclst(p_locresponse->p_loclst);
	fprintf(stdout, "\n");
}
