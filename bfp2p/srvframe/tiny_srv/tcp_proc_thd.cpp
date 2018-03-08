#include "tcp_proc_thd.h"

tcp_proc_thd::tcp_proc_thd(int entity_type, int entity_id)
    : CNetProcessThread(entity_type, entity_id)
{

}

tcp_proc_thd::~tcp_proc_thd()
{

}

int tcp_proc_thd::Process(CMsg *pmsg)
{
    TMsg *ptmsg = pmsg->GetTMsg();
    if (NULL == ptmsg) {
        return 0;
    }

    if (LISTENENTITY == ptmsg->srcEntityType) {
        if (RECVMSGTYPE == ptmsg->msgType) {
            CRecvMsgBody *pbody = (CRecvMsgBody *)pmsg->GetMsgBody();
            CTcpSocket *psocket = new CTcpSocket(pbody->GetSockAddr(), sizeof(sockaddr_in),
                                                 pbody->GetSocket());
            CSocketTask *ptmp_sock_task = NULL;
            ptmp_sock_task = CMyserver::GetInstance()->GetClassFactory()->GenSocketTask(
                this, psocket, RECVANDSENDTASK);
            if (NULL != ptmp_sock_task) {
                ptmp_sock_task->Init();
                ptmp_sock_task->SetTimeStat(pbody->GetTimeStat());
            }
        }
    } else {
        CNetProcessThread::Process(pmsg);
    }

    return 0;
}
