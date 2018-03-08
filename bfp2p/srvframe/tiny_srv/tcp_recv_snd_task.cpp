#include "tcp_recv_snd_task.h"
#include "tiny_srv_def.h"
#include "HttpRecvAndSendTask.h"
#include "tiny_isrc_online_cmd.h"

tcp_task_proc::tcp_task_proc(CNetProcessThread *pnetprocessthread,
                             CRecvAndSendTask *precv_snd_task, CTcpSocket *psocket)
    : CHttpRecvAndSendTaskProcess(pnetprocessthread, precv_snd_task, psocket)
{

}

tcp_task_proc::~tcp_task_proc()
{

}

int tcp_task_proc::ProcessRecvPacket(const char *ppacket, unsigned int buf_len)
{
    if (NULL == m_pNetProcessThread || NULL == m_pRecvAndSendTask) {
        return -1;
    }

    if (buf_len <= 0) {
        return -2;
    }

    char *pnew_buf = const_cast<char *>(ppacket);
    unsigned int new_buf_len = buf_len;
///    if (!CAESEncryptApplication::AESDncryptEx(pnew_buf, new_buf_len)) {
///        return -3;
///    }

    char cmd_id;
    memcpy(&cmd_id, pnew_buf + CMD_OFF_SET, sizeof(cmd_id));
    int ret = 0;
    int proc_ret = 0;
    switch (cmd_id) {
    case TINY_SRV_ISRC_ONLINE:
    case TINY_SRV_INSERT_RC:
    case TINY_SRV_DELETE_RCLIST:
    case TINY_SRV_DELETE_RCLISTNEW:
    case TINY_SRV_REPORT_RCLIST:
    case TINY_SRV_QUERY_PEER:
    case TINY_SRV_QUERY_PEERNUM:
    default: {
        tiny_lsrc_online tlo(pnew_buf, new_buf_len);
        ret = tlo.Process(proc_ret);
        if (ret != 0) {
            break;
        }
        int res_pkt_len = 0;
        char *pbuf = tlo.GetResBuf(res_pkt_len);
        if (pbuf && res_pkt_len) {
            ((CHttpRecvAndSendTask<tcp_task_proc> *)m_pRecvAndSendTask)->PutMsgToSendList(
                pbuf, res_pkt_len);
            tlo.DisAttachBuf();
        }
        /// trans_msg(pnew_buf, new_buf_len, 1, 2);
    }
        break;
    }
    return 0;
}

void tcp_task_proc::trans_msg(char *pbuf, int len, int machine_index, int type)
{
    if (NULL == m_pNetProcessThread) {
        return;
    }

    timer_srv *pserver = static_cast<timer_srv *>(CMyserver::GetInstance());
    if (NULL == pserver) {
        return;
    }

    sockaddr_in &sockaddr = m_pRecvAndSendTask->GetAddr();
    CTmpBufMgr gen_pkt_helper;
    gen_pkt_helper.SetIfNetTrans(0);
    int tmp_len = sizeof(SERVERINNERCOMMANDPACKET) + len;
    char *ptmp_buf = new char[tmp_len];
    memset(ptmp_buf, 0, tmp_len);
    gen_pkt_helper.AttachBuf(ptmp_buf, tmp_len);

    SERVERINNERCOMMANDPACKET srv_inner_command_pkt;
    srv_inner_command_pkt.ucDestMachineType = type;
    srv_inner_command_pkt.usDestMachineIndex = machine_index;
    srv_inner_command_pkt.serverCommandPacket.usMsgId = htons(CONNECT_SERVER_COMMON);
    srv_inner_command_pkt.serverCommandPacket.uSrcClientIp = sockaddr.sin_addr.s_addr;
    srv_inner_command_pkt.serverCommandPacket.usSrcClientPort = sockaddr.sin_port;
    srv_inner_command_pkt.serverCommandPacket.ullSrcTaskId = htonl(
        m_pRecvAndSendTask->GetTaskId());
    srv_inner_command_pkt.serverCommandPacket.iSrcProcessId = htonl(
        m_pNetProcessThread->GetEntityId());
    srv_inner_command_pkt.serverCommandPacket.iMsgLen = htonl(len);

    gen_pkt_helper.Put(srv_inner_command_pkt);
    gen_pkt_helper.PutCharBuf(pbuf, len);

    TMsg tmsg;
    tmsg.destEntityType = LONGCONNECTEDENTITY;
    tmsg.destEntityId = 0;
    tmsg.srcEntityId = m_pNetProcessThread->GetEntityId();
    tmsg.srcEntityType = m_pNetProcessThread->GetEntityType();
    tmsg.srcTaskId = 0;
    tmsg.msgType = CLIENTMSGTYPE;

    CMsgBody *pmsg_body = new CClientMsgBody(gen_pkt_helper.GetBuf(),
                                             gen_pkt_helper.GetRealBufLen());
    gen_pkt_helper.DisAttachBuf();
    if (NULL == pmsg_body) {
        return;
    }

    CMsg *pmsg = new CMsg(tmsg, pmsg_body);
    if (NULL == pmsg) {
        delete pmsg_body;
        pmsg_body = NULL;
        return;
    }

    CMyserver::GetInstance()->PutMsgToThread(pmsg);
}

const char* tcp_task_proc::ProcessSendPacket(const char *pold_pkt, unsigned int old_buf_len,
                                             unsigned int &new_buf_len)
{
    char *pnew_buf = const_cast<char *>(pold_pkt);
    new_buf_len = old_buf_len;
#if 0
    if (!CAESEncryptApplication::AESEncryptEx(pnew_buf, new_buf_len)) {
        return NULL;
    }
#endif
    return pnew_buf;
}
