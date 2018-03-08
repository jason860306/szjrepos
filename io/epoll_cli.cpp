#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <iostream>

int main(int argc, char* argv[])
{
	int cli_fd = socket(AF_INET, SOCK_STREAM, 0);
	printf("client fd=%d\n", cli_fd);

	int port = 40713;
	if (argc == 2) {
		port = atoi(argv[1]);
	}

	// bind & listen
	sockaddr_in sin;
	bzero(&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr("127.0.0.1");
	sin.sin_port = htons(port);

	connect(cli_fd, (sockaddr*)&sin, sizeof(sin));
	send(cli_fd, "hello\n", strlen("hello\n") + 1, 0);
	char recv_buf[128];
	int len = recv(cli_fd, recv_buf, sizeof(recv_buf), 0);
	printf("recv: %s[len=%d]\n", recv_buf, len);
	close(cli_fd);

	return 0;
}
