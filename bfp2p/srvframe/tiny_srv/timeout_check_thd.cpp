#include "timer_srv.h"
#include "commmsg.h"
#include "tiny_srv_def.h"
#include "timeout_check_thd.h"

timeout_check_thd::timeout_check_thd(int entity_type, int entity_id)
    : CWorkThread(entity_type, entity_id)
    , m_pserver(NULL)
    , m_check_interval(0)
    , m_syn_interval(0)
{

}

timeout_check_thd::~timeout_check_thd()
{

}

int timeout_check_thd::Init()
{
    return 0;
    m_pserver = (timer_srv*)CMyserver::GetInstance();
    if (NULL == m_pserver) {
        return -1;
    }
}

int timeout_check_thd::Run()
{
    struct timeval tmp_tv;
    gettimeofday(&tmp_tv, NULL);
    unsigned long long ulllast_check_time;
    unsigned long long ulllast_syn_time;
    while (m_nRunFlag) {
        usleep(100000);

        gettimeofday(&tmp_tv, NULL);
        if (tmp_tv.tv_sec - ulllast_check_time >= (unsigned)m_check_interval) {
            ulllast_check_time = tmp_tv.tv_sec;
//            Process(NULL);
        }

        gettimeofday(&tmp_tv, NULL);
        if (tmp_tv.tv_sec - ulllast_syn_time >= (unsigned)m_syn_interval) {
            ulllast_syn_time = tmp_tv.tv_sec;
//            SendMsg(TINY_SRV_ONTIME_SYN_ENTITY_TYPE, RANDOMENTITYID,
//                    0, ONTIMESYN_MSGTYPE, NULL);
        }
    }
    return 0;
}

int timeout_check_thd::PutMsgToInputList(CMsg* pmsg)
{
    static_cast<void>(pmsg);
    return 0;
}

int timeout_check_thd::Process(CMsg* /*pmsg*/)
{
    char* msg_buf = new char[128];
    memset(msg_buf, 0, 128);
    strcpy(msg_buf, "msg from timeout_check_thd");
    trans_msg(msg_buf, strlen(msg_buf));
    return 0;
}

void timeout_check_thd::trans_msg(const char* buf_ptr, std::size_t buf_size)
{
    TMsg tmsg;
    tmsg.destEntityType = TINY_SRV_ONTIME_SYN_ENTITY_TYPE; /// LONGCONNECTEDENTITY;
    tmsg.destEntityId = 0;
    tmsg.srcEntityId = GetEntityId();
    tmsg.srcEntityType = GetEntityType();
    tmsg.srcTaskId = 0;
    tmsg.msgType = SYN_MSGTYPE;

    CMsgBody* pmsg_body = new CBufMsgBody((char*)buf_ptr, buf_size);
    CMsg* pmsg = new CMsg(tmsg, pmsg_body);
    CMyserver::GetInstance()->PutMsgToThread(pmsg);
}
