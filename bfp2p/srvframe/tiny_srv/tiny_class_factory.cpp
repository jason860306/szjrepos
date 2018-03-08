#include "tiny_class_factory.h"
#include "workthread.h"
#include "timer_srv.h"
#include "basecommand.h"
#include "tiny_srv_def.h"
#include "tiny_base_command.h"
#include "tiny_cmd.h"
#include "ontime_synthread.h"
#include "timeout_check_thd.h"
#include "udp_recv_thd.h"
#include "udp_proc_snd_thd.h"

#include "HttpRecvAndSendTask.h"
#include "tcp_recv_snd_task.h"
#include "tcp_proc_thd.h"

CWorkThread* tiny_class_factory::GenWorkThread(
    int entity_type, int entity_id, std::string annex_data, void* parg)
{
    CWorkThread* pwork_thread = NULL;
    timer_srv* pserver = (timer_srv*)CMyserver::GetInstance();
    if (NULL == pserver) {
        return pwork_thread;
    }
    CBaseConf& base_conf = pserver->GetBaseConf();
    switch (entity_type) {
    case TINY_SRV_ONTIME_SYN_ENTITY_TYPE:
        pwork_thread = new ontime_synthread(entity_type, entity_id);
        break;
    case TINY_SRV_TIMEOUT_CHECK_ENTITY_TYPE:
        pwork_thread = new timeout_check_thd(entity_type, entity_id);
        break;
    case TINY_SRV_UDP_RECV_ENTITY_TYPE:
        pwork_thread = new udp_recv_thd(entity_type, entity_id,
                                        base_conf.GetConfigItem().sServerAddr,
                                        base_conf.GetConfigItem().nUdpPort);
        break;
    case TINY_SRV_UDP_PROC_SND_ENTITY_TYPE:
        pwork_thread = new udp_proc_snd_thd(entity_type, entity_id);
        break;
    case RECVANDSENDMSGENTITY:
        pwork_thread = new tcp_proc_thd(entity_type, entity_id);
        break;
    default:
        pwork_thread = CClassFactory::GenWorkThread(entity_type, entity_id,
                                                    annex_data, parg);
        break;
    }
    return pwork_thread;
}

CCommand* tiny_class_factory::GenBaseCommand(char* pbuf, int len, int client_ip,
                                             short client_port, int entity_type,
                                             int entity_id)
{
    CCommand* pcmd = NULL;
    if ((unsigned)len < TINY_SRV_MSG_HEAD_LEN) {
        return pcmd;
    }

    unsigned char cmd_id = tiny_base_command<CDefault, CDefaultRes>::get_command_id(
        pbuf, len);

    char* tmp_buf = new char[len];
    memcpy(tmp_buf, pbuf, len);

    switch (cmd_id) {
    case TINY_SRV_BASE_CMD:
        pcmd = new tiny_cmd(tmp_buf, len, client_ip, client_port, entity_type, entity_id);
        break;
    default:
        pcmd = new tiny_cmd(tmp_buf, len, client_ip, client_port, entity_type, entity_id);
//        delete[] tmp_buf;
//        tmp_buf = NULL;
        break;
    }
    return pcmd;
}

CSocketTask *tiny_class_factory::GenSocketTask(CNetProcessThread *pwork_thread,
                                               CTcpSocket *ptcp_socket,
                                               int task_type, CTaskArg *ptask_arg)
{
    CSocketTask *psocket_task = NULL;
    switch (task_type) {
    case RECVANDSENDTASK:
        psocket_task = new CHttpRecvAndSendTask<tcp_task_proc>(ptcp_socket, pwork_thread,
                                                               0, 4096, 4096);
        break;
    default:
        psocket_task = CClassFactory::GenSocketTask(pwork_thread, ptcp_socket, task_type,
            ptask_arg);
        break;
    }
    return psocket_task;
}
