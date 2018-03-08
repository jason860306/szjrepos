#include "commmsg.h"
#include "tiny_srv_def.h"
#include "timer_srv.h"
#include "ontime_synthread.h"

ontime_synthread::ontime_synthread(int entity_type, int entity_id)
    : CWorkThread(entity_type, entity_id)
    , m_input_list()
    , m_pserver(NULL)
    , m_psyn_sendsem(NULL)
{

}

ontime_synthread::~ontime_synthread()
{

}

int ontime_synthread::Init()
{
    if (NULL == (m_pserver = (timer_srv*)CMyserver::GetInstance())) {
        return -1;
    }

    if (NULL == (m_psyn_sendsem = m_pserver->GetSynSendSem())) {
        return -1;
    }

    return 0;
}

int ontime_synthread::Run()
{
    while (m_nRunFlag) {
        if (CMsg* pmsg = m_input_list.get()) {
            Process(pmsg);
///            delete pmsg;
///            pmsg = NULL;
        }
    }
    return 0;
}

int ontime_synthread::PutMsgToInputList(CMsg* pmsg)
{
    m_input_list.put(pmsg);
    return 0;
}

int ontime_synthread::Process(CMsg* pmsg)
{
    TMsg* ptmsg = pmsg->GetTMsg();
    if (NULL == ptmsg) {
        return -1;
    }

    switch (ptmsg->msgType) {
    case ONTIMESYN_MSGTYPE:
    case SYN_MSGTYPE:
        process_ontime(pmsg);
        break;
    default:
        break;
    }

    return 0;
}

int ontime_synthread::process_ontime(CMsg* pmsg)
{
    if (NULL == pmsg) {
        return -1;
    }

    CClientMsgBody* pbuf_msg_body = (CClientMsgBody*)pmsg->GetMsgBody();
    if (NULL == pbuf_msg_body) {
        return -1;
    }
    const char* pbuf = pbuf_msg_body->GetBuffer();
    std::size_t buf_len = pbuf_msg_body->GetLen();
    if (buf_len < (int)(sizeof(char) + sizeof(short)) || (NULL == pbuf)) {
        return -1;
    }

    printf("%s\n", pbuf);

    return 0;
}

void ontime_synthread::trans_msg(const char* buf_ptr, std::size_t buf_size)
{
    TMsg tmsg;
    tmsg.destEntityType = TINY_SRV_ONTIME_SYN_ENTITY_TYPE;
    tmsg.destEntityId = 0;
    tmsg.srcEntityId = GetEntityId();
    tmsg.srcEntityType = GetEntityType();
    tmsg.srcTaskId = 0;
    tmsg.msgType = SYN_MSGTYPE;

    CMsgBody* pmsg_body = new CBufMsgBody((char*)buf_ptr, buf_size);
    CMsg* pmsg = new CMsg(tmsg, pmsg_body);
    CMyserver::GetInstance()->PutMsgToThread(pmsg);
}
