#ifndef UDP_PROC_SND_THD_H
#define UDP_PROC_SND_THD_H

#include "udpcommonsendthread.h"

class udp_proc_snd_thd : public CUdpCommonSendThread
{
public:
    udp_proc_snd_thd(int entity_type, int entity_id);
    ~udp_proc_snd_thd();
public:
    virtual int MsgProcess(CMsg* pmsg);
    virtual int Run();
};

#endif
