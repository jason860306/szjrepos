#ifndef TIMER_SRV_H
#define TIMER_SRV_H

#include <unistd.h>
#include <semaphore.h>
#include "myserver.h"
#include "threadgroup.h"

class timer_srv : public CMyserver
{
public:
    timer_srv();
    virtual ~timer_srv();
public:
    virtual int init_server();
    virtual int start_server();
public:
    sem_t* GetSynSendSem() { return &m_sem_syn_send; }
private:
    CThreadGroup *m_ptimer_thd_grp;
    CThreadGroup *m_pmain_tain_thd_grp;
    CThreadGroup *m_pontime_synthd_grp;
    CThreadGroup *m_pcheck_timeoutthd_grp;
    CThreadGroup *m_pudp_recv_thd_grp;
    CThreadGroup *m_pudp_proc_snd_thd_grp;

    CThreadGroup *m_ptcp_srv_thd_grp;
    CThreadGroup *m_ptcp_recv_proc_thd_grp;

    sem_t m_sem_syn_send;
};

#endif
