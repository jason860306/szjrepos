#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAXLINE 4096
#define SA struct sockaddr

void dg_cli(FILE* fp, int sockfd, const SA* psrvaddr, socklen_t srvlen);

int main(int argc, char* argv[])
{
    int sockfd;
    struct sockaddr_in srvaddr;

    if (argc != 3) {
        printf("usage: udp_cli <ip port>\n");
        return -1;
    }

    bzero(&srvaddr, sizeof(srvaddr));
    srvaddr.sin_family = AF_INET;
    srvaddr.sin_port = htons(atoi(argv[2]));
    inet_pton(AF_INET, argv[1], &srvaddr.sin_addr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    dg_cli(stdin, sockfd, (SA*)&srvaddr, sizeof(srvaddr));

    exit(0);
}

void dg_cli(FILE* fp, int sockfd, const SA* psrvaddr, socklen_t srvlen)
{
    int n;
    char sendline[MAXLINE], recvline[MAXLINE + 1];

    while (fgets(sendline, MAXLINE, fp) != NULL) {
        sendto(sockfd, sendline, strlen(sendline), 0, psrvaddr, srvlen);

        n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);

        recvline[n] = 0;

        fputs(recvline, stdout);
    }
}
