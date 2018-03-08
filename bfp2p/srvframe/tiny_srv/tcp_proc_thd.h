#ifndef TCP_PROC_THD_H
#define TCP_PROC_THD_H

#include "netprocessthread.h"

class tcp_proc_thd : public CNetProcessThread
{
public:
    tcp_proc_thd(int entity_type, int entity_id);
    virtual ~tcp_proc_thd();
protected:
    virtual int Process(CMsg *pmsg);
};

#endif
