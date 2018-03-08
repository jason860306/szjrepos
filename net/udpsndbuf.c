/**
 * ============================================================================
 * @file    udpsndbuf.c
 *
 * @brief   
 * @details 
 *
 * @version 1.0  
 * @date    2013-09-18 18:18:42
 *
 * @author  shizhijie, shizhijie@baofeng.com
 * ============================================================================
 */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <netdb.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

static int new_socket(struct addrinfo *ai);
static void maximize_sndbuf(const int sfd);

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		printf("%s interface port\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	int sfd = -1;
	struct addrinfo *ai = 0, *next = 0, hints = { .ai_flags = AI_PASSIVE,
												  .ai_family = AF_UNSPEC };
	int error = 0, flags = 1;

	hints.ai_socktype = SOCK_DGRAM;
	error = getaddrinfo(argv[1], argv[2], &hints, &ai);
	if (error != 0)
	{
		if (error != EAI_SYSTEM)
		{
			fprintf(stderr, "getaddrinfo(): %s\n", gai_strerror(error));
		}
		else
		{
			perror("getaddrinfo()");
		}
		return 1;
	}

	for (next = ai; next; next = next->ai_next)
	{
		if ((sfd = new_socket(next)) == -1)
		{
			if (errno == EMFILE)
			{
				perror("server_socket");
				exit(EXIT_FAILURE);
			}
			continue;
		}
	}
	setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, (void *)&flags, sizeof(flags));
	maximize_sndbuf(sfd);

	return 0;
}

static int new_socket(struct addrinfo *ai)
{
	int sfd = -1, flags = 0;

	if ((sfd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol)) == -1)
	{
		return -1;
	}

	if ((flags = fcntl(sfd, F_GETFL, 0)) < 0 || fcntl(sfd, F_SETFL, flags | O_NONBLOCK) < 0)
	{
		perror("setting O_NONBLOCK");
		close(sfd);
		return -1;
	}

	return sfd;
}

static void maximize_sndbuf(const int sfd)
{
	socklen_t intsize = sizeof(int);
	unsigned long long last_good = 0, min, max, avg, old_size;

	if (getsockopt(sfd, SOL_SOCKET, SO_SNDBUF, &old_size, &intsize) != 0)
	{
		perror("getsockopt(SO_SNDBUF)");
		return;
	}

	min = old_size, max = 256 * 1024 * 1024;
	avg = max; /*((unsigned int)(min + max)) / 2;*/

	while (1/*min <= max*/)
	{
		/*avg = ((unsigned int)(min + max)) / 2;*/
		if (setsockopt(sfd, SOL_SOCKET, SO_SNDBUF, (void *)&avg, intsize) == 0)
		{
			last_good = avg;
			/*min = avg + 1;*/
			avg += old_size;
		}
		else
		{
			/*max = avg - 1;*/
			--avg;
			break;
		}
	}

	fprintf(stderr, "%d send buffer was %llu, now %llu\n", sfd, old_size, last_good);
}
