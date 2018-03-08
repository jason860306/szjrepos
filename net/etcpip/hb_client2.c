#include "etcp.h"
#include "heartbeat.h"

char *program_name = "hb_client2";

int main(int argc, char *argv[])
{
    if (argc != 3) {
        error(1, 0, "need two argument of ip and port to connect to tcp_server.");
    }
    fd_set allfd;
    fd_set readfd;
    char msg[1024];
    struct timeval tv;
    struct sockaddr_in hblisten;
    SOCKET sdata;
    SOCKET shb;
    SOCKET slisten;
    int rc;
    int hblistenlen = sizeof(hblisten);
    int heartbeats = 0;
    int maxfd1;
    char hbmsg[1];

    INIT();
    slisten = tcp_server(NULL, "0");
    rc = getsockname(slisten, (struct sockaddr *)&hblisten, &hblistenlen);
    if (rc) {
        error(1, errno, "getsockname failure");
    }
    sdata = tcp_client(argv[1], argv[2]);
    rc = send(sdata, (char *)&hblisten.sin_port, sizeof(hblisten.sin_port), 0);
    if (rc < 0) {
        error(1, errno, "send failure sending port");
    }
    shb = accept(slisten, NULL, NULL);
    if (!isvalidsock(shb)) {
        error(1, errno, "accept failure");
    }
    FD_ZERO(&allfd);
    FD_SET(sdata, &allfd);
    FD_SET(shb, &allfd);
    maxfd1 = (sdata > shb ? sdata : shb) + 1;
    tv.tv_sec = T1;
    tv.tv_usec = 0;

    for ( ;; ) {
        readfd = allfd;
        rc = select(maxfd1, &readfd, NULL, NULL, &tv);
        if (rc < 0) {
            error(1, errno, "select failure");
        } else if (rc == 0) {
            if (++heartbeats > 3) {
                error(1, 0, "connection dead\n");
            }
            error(0, 0, "sending heartbeat #%d\n", heartbeats);
            rc = send(shb, "", 1, 0);
            if (rc < 0) {
                error(1, errno, "send failure");
            }
            tv.tv_sec = T2;
            continue;
        }
        if (FD_ISSET(shb, &readfd)){
            rc = recv(shb, hbmsg, 1, 0);
            if (rc == 0) {
                error(1, 0, "server terminated (shb)\n");
            } else if (rc < 0) {
                error(1, errno, "bad recv on shb");
            }
        }
        if (FD_ISSET(sdata, &readfd)) {
            rc = recv(sdata, msg, sizeof(msg), 0);
            if (rc == 0) {
                error(1, 0, "server terminated (sdata)\n");
            } else if (rc < 0) {
                error(1, errno, "recv failure");
                /* process data*/
            }
        }

        heartbeats = 0;
        tv.tv_sec = T1;
    }
}
