// server.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <winsock2.h>
#include <windows.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

int _tmain(int argc, _TCHAR* argv[])
{
    if (argc != 2)
    {
        printf("usage: %s port\n", argv[0]);
        return -1;
    }

	WSADATA wsd;
	SOCKET server;

	if ( WSAStartup( MAKEWORD(2, 2), &wsd) != 0 )
	{
		printf("WSAStartup failed.\n");
		return 0;
	}

	server = ::socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

	if( server == INVALID_SOCKET )
	{
		DWORD error_code = ::WSAGetLastError();
		printf("create socket failed.\n");
		return -1;
	}

	sockaddr_in sock_addr;
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_port = htons( atoi(argv[1] ));
	sock_addr.sin_addr.s_addr = INADDR_ANY;
	int ret = ::bind( server, (const sockaddr*)&sock_addr, sizeof(sockaddr_in) );
	if( ret == SOCKET_ERROR )
	{
		DWORD error_code = WSAGetLastError();
		printf("bind failed.\n");
		return 0;
	}

	ret = ::listen( server, 10);
	if( ret == SOCKET_ERROR )
	{
		DWORD error_code = WSAGetLastError();
		printf("listen failed.\n");
		return 0;
	}

	struct sockaddr_in client_addr;
	int size=sizeof(client_addr);
	SOCKET acceptfd;
    char *read_buf = new char[1024 * 1024];
    memset(read_buf, 0, 1024 * 1024);

    printf("%s listen on %s, waiting for a new connection.\n", argv[0], argv[1]);

	for (;;) 
	{
		acceptfd = accept(server, (sockaddr *)&client_addr,&size);

		if (acceptfd < 0) 
		{
			printf("accept failed.\n");
		}
		else if (acceptfd > 0) 
		{
            //::getpeername(acceptfd, &client_addr, &size);
			printf("a new client connected: %s:%d\n", inet_ntoa(client_addr.sin_addr),
                client_addr.sin_port);
            while (true)
            {
                int rsize = ::recv(acceptfd, read_buf, 1024 * 1024, 0);
                if (rsize <= 0)
                {
                    printf("recv error: %d\n", GetLastError());
                    break;
                }
                static unsigned int cnt = 0;
                printf("recv: %d, size: %d\n", ++cnt, rsize);
                Sleep(5);
            }
			//break;
		}
		else
		{
		}

		Sleep(1000);
	}

	return 0;
}

