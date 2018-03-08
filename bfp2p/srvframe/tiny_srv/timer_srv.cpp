#include "timer_srv.h"
#include "framecommon/commondef.h"
#include "tiny_srv_def.h"
#include "tiny_class_factory.h"

timer_srv::timer_srv() : m_ptimer_thd_grp(NULL), m_pmain_tain_thd_grp(NULL)
{
}

timer_srv::~timer_srv()
{
    if (NULL != m_ptimer_thd_grp) {
        delete m_ptimer_thd_grp;
        m_ptimer_thd_grp = NULL;
    }

    if (NULL != m_pmain_tain_thd_grp) {
        delete m_pmain_tain_thd_grp;
        m_pmain_tain_thd_grp = NULL;
    }

    if (NULL != m_pontime_synthd_grp) {
        delete m_pontime_synthd_grp;
        m_pontime_synthd_grp = NULL;
    }

    if (NULL != m_pudp_recv_thd_grp) {
        delete m_pudp_recv_thd_grp;
        m_pudp_recv_thd_grp = NULL;
    }

    if (NULL != m_pudp_proc_snd_thd_grp) {
        delete m_pudp_proc_snd_thd_grp;
        m_pudp_proc_snd_thd_grp = NULL;
    }

    if (NULL != m_ptcp_srv_thd_grp) {
        delete m_ptcp_srv_thd_grp;
        m_ptcp_srv_thd_grp = NULL;
    }

    if (NULL != m_ptcp_recv_proc_thd_grp) {
        delete m_ptcp_recv_proc_thd_grp;
        m_ptcp_recv_proc_thd_grp = NULL;
    }
}

int timer_srv::init_server()
{
    int ret = CMyserver::InitServer();
    m_pClassFactory = new tiny_class_factory();
    return ret;
}

int timer_srv::start_server()
{
    m_ptimer_thd_grp = new CThreadGroup(1, TIMERENTITY);
    if (NULL == m_ptimer_thd_grp || 0 != m_ptimer_thd_grp->Init()) {
        return -1;
    }

    m_pmain_tain_thd_grp = new CThreadGroup(1, MAINTAINENTITY);
    if (NULL == m_pmain_tain_thd_grp || 0 != m_pmain_tain_thd_grp->Init()) {
        return -2;
    }
//#if 0
    m_pontime_synthd_grp = new CThreadGroup(1, TINY_SRV_ONTIME_SYN_ENTITY_TYPE);
    if (NULL == m_pontime_synthd_grp || 0 != m_pontime_synthd_grp->Init()) {
        return -3;
    }

    m_pcheck_timeoutthd_grp = new CThreadGroup(1, TINY_SRV_TIMEOUT_CHECK_ENTITY_TYPE);
    if (NULL == m_pcheck_timeoutthd_grp || 0 != m_pcheck_timeoutthd_grp->Init()) {
        return -4;
    }
//#endif
    m_pudp_recv_thd_grp = new CThreadGroup(1, TINY_SRV_UDP_RECV_ENTITY_TYPE);
    if (NULL == m_pudp_recv_thd_grp || 0 != m_pudp_recv_thd_grp->Init()) {
        return -5;
    }

    m_pudp_proc_snd_thd_grp = new CThreadGroup(1, TINY_SRV_UDP_PROC_SND_ENTITY_TYPE);
    if (NULL == m_pudp_proc_snd_thd_grp || 0 != m_pudp_proc_snd_thd_grp->Init()) {
        return -6;
    }

    std::string tmp_data(reinterpret_cast<char *>(&m_baseConf.GetConfigItem().nTcpPort), 4);
    tmp_data.append(m_baseConf.GetConfigItem().sServerAddr);
    m_ptcp_srv_thd_grp = new CThreadGroup(1, LISTENENTITY, tmp_data);
    if (NULL == m_ptcp_srv_thd_grp || 0 != m_ptcp_srv_thd_grp->Init()) {
        return -7;
    }

    m_ptcp_recv_proc_thd_grp = new CThreadGroup(1, RECVANDSENDMSGENTITY);
    if (NULL == m_ptcp_recv_proc_thd_grp || 0 != m_ptcp_recv_proc_thd_grp->Init()) {
        return -8;
    }

    while (true) {
        sleep(1000*10);
    }

    return 0;
}
