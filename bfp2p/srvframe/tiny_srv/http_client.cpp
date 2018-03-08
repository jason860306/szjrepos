#include <etcp.h>
#include "framecommon/AESEncryptApplication.h"
#include "heartbeat.h"

char *program_name = "http_client";

/* tcp_client - set up for a TCP client */
SOCKET tcp_client( char *hname, char *sname );
/* set_address - fill in a sockaddr_in structure */
void set_address( char *hname, char *sname,
	struct sockaddr_in *sap, char *protocol );
/* error - print a diagnostic and optionally quit */
void error( int status, int err, char *fmt, ... );

int main(int argc, char *argv[])
{
    if (argc != 4) {
        error(1, errno, "need 3 argument!\nexample: %s ip port /index.html", argv[0]);
    }
    fd_set allfd;
    fd_set readfd;
    msg_t msg;
    struct timeval tv;
    SOCKET s;
    int rc;
    int heartbeats = 0;
    int cnt = sizeof(msg);

    INIT();
    s = tcp_client(argv[1], argv[2]);
    FD_ZERO(&allfd);
    FD_SET(s, &allfd);
    tv.tv_sec = T1;
    tv.tv_usec = 0;
    for ( ;; ) {
        readfd = allfd;
        rc = select(s + 1, &readfd, NULL, NULL, &tv);
        if (rc < 0) {
            error(1, errno, "select failure");
        } else if (rc == 0) { /* timeout */
            if (++heartbeats > 3) {
                error(1, 0, "connection dead\n");
            }
            error(0, 0, "sending heartbeat #%d\n", heartbeats);

            static char post_body[1024] = { 0 };
            strcpy(post_body, "hi, i'm http_client, and working with you!");
            unsigned int encrypt_len = strlen(post_body);
///            if (!CAESEncryptApplication::AESEncryptEx(post_body, encrypt_len)) {
///                error(1, errno, "encrypt failed!");
///            }
///            if (!CAESEncryptApplication::AESDnCryptEx(post_body, encrypt_len)) {
///                error(1, errno, "decrypt failed!");
///            }
			memset(msg, 0, sizeof(msg));
			sprintf(msg,
					"POST %s HTTP/1.0\r\n"
					"Host: %s\r\n"
					"Accept: */*\r\n"
                    "Content-Length: %d\r\n"
					"Connection: close\r\n\r\n"
                    "%s",
                    argv[3], argv[1], encrypt_len, post_body);
            /// msg.type = htonl(MSG_HEARTBEAT);
            rc = send(s, (char*)&msg, sizeof(msg), 0);
            if (rc < 0) {
                error(1, errno, "send failure");
            }
            tv.tv_sec = T2;
            continue;
        }

        if (!FD_ISSET(s, &readfd)) {
            error(1, 0, "select returened invalid socket\n");
        }
        rc = recv(s, (char*)&msg + sizeof(msg) - cnt, cnt, 0);
        if (rc == 0) {
            error(1, 0, "server terminated\n");
        }
        heartbeats = 0;
        tv.tv_sec = T1;
        cnt -= rc;
        if (cnt > 0) {
            continue;
        }
        cnt = sizeof(msg);

        /* process message */
    }
}

/* tcp_client - set up for a TCP client */
SOCKET tcp_client( char *hname, char *sname )
{
	struct sockaddr_in peer;
	SOCKET s;

	set_address( hname, sname, &peer, "tcp" );
	s = socket( AF_INET, SOCK_STREAM, 0 );
	if ( !isvalidsock( s ) )
		error( 1, errno, "socket call failed" );

	if ( connect( s, ( struct sockaddr * )&peer,
		 sizeof( peer ) ) )
		error( 1, errno, "connect failed" );

	return s;
}

/* set_address - fill in a sockaddr_in structure */
void set_address( char *hname, char *sname,
	struct sockaddr_in *sap, char *protocol )
{
	struct servent *sp;
	struct hostent *hp;
	char *endptr;
	short port;

	bzero( sap, sizeof( *sap ) );
	sap->sin_family = AF_INET;
	if ( hname != NULL )
	{
		if ( !inet_aton( hname, &sap->sin_addr ) )
		{
			hp = gethostbyname( hname );
			if ( hp == NULL )
				error( 1, 0, "unknown host: %s\n", hname );
			sap->sin_addr = *( struct in_addr * )hp->h_addr;
		}
	}
	else
		sap->sin_addr.s_addr = htonl( INADDR_ANY );
	port = strtol( sname, &endptr, 0 );
	if ( *endptr == '\0' )
		sap->sin_port = htons( port );
	else
	{
		sp = getservbyname( sname, protocol );
		if ( sp == NULL )
			error( 1, 0, "unknown service: %s\n", sname );
		sap->sin_port = sp->s_port;
	}
}

/* error - print a diagnostic and optionally quit */
void error( int status, int err, char *fmt, ... )
{
	va_list ap;

	va_start( ap, fmt );
	fprintf( stderr, "%s: ", program_name );
	vfprintf( stderr, fmt, ap );
	va_end( ap );
	if ( err )
		fprintf( stderr, ": %s (%d)\n", strerror( err ), err );
	if ( status )
		EXIT( status );
}
