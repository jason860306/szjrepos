#include <etcp.h>
#include "heartbeat.h"

char *program_name = "hb_server";

int main(int argc, char *argv[])
{
    if (argc != 2) {
        error(1, errno, "need argument!");
    }
    fd_set allfd;
    fd_set readfd;
    msg_t msg;
    struct timeval tv;
    SOCKET s;
    SOCKET s1;
    int rc;
    int missed_heartbeats = 0;
    int cnt = sizeof(msg);

    INIT();
    s = tcp_server(NULL, argv[1]);
    s1 = accept(s, NULL, NULL);
    if (!isvalidsock(s1)) {
        error(1, errno, "accept failed");
    }
    tv.tv_sec = T1 + T2;
    tv.tv_usec = 0;
    FD_ZERO(&allfd);
    FD_SET(s1, &allfd);
    for ( ;; ) {
        readfd = allfd;
        rc = select(s1 + 1, &readfd, NULL, NULL, &tv);
        if (rc < 0) {
            error(1, errno, "select failure");
        } else if (rc == 0) {
            if (++missed_heartbeats > 3) {
                error(1, 0, "connection dead\n");
            }
            error(0, 0, "missed heartbeat #%d\n", missed_heartbeats);
            tv.tv_sec = T2;
            continue;
        }
        if (!FD_ISSET(s1, &readfd)) {
            error(1, 0, "select returned invalid socket\n");
        }
        rc = recv(s1, (char*)&msg + sizeof(msg) - cnt, cnt, 0);
        if (rc == 0) {
            error(1, 0, "client terminated\n");
        } else if (rc < 0) {
            error(1, errno, "recv failure");
        }
        missed_heartbeats = 0;
        tv.tv_sec = T1 + T2;
        cnt -= rc; /* in-line readn */
        if (cnt > 0) {
            continue;
        }
        cnt = sizeof(msg);
        switch (ntohl(msg.type)) {
        case MSG_TYPE1:
            /* process type1 message */
            break;
        case MSG_TYPE2:
            /* process type2 message */
            break;
        case MSG_HEARTBEAT:
            /* process heartbeat message */
            rc = send(s1, (char*)&msg, sizeof(msg), 0);
            if (rc < 0) {
                error(1, errno, "send failure");
            }
            break;
        default:
            error(1, 0, "unknown message type (%d)\n", ntohl(msg.type));
            break;
        }
    }
    EXIT(0);
}
