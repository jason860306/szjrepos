#ifndef UDP_RECV_THD_H
#define UDP_RECV_THD_H

#include "udpcommonrecvthread.h"

class udp_recv_thd : public CUdpCommonRecvThread
{
public:
    udp_recv_thd(int entity_type, int entity_id, std::string& ip, unsigned short port);
public:
    virtual int Run();
};

#endif
