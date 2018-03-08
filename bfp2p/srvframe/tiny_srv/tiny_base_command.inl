#include "commmsg.h"
#include "tiny_srv_def.h"
#include "timer_srv.h"

//----------------------- tiny_base_command_type -------------------------
inline int tiny_base_command_type::encode(CNewBufMgr& buf_mgr)
{
    int ret = 0;
    ret += buf_mgr.PutInt(m_protocol_ver);
    ret += buf_mgr.PutChar(m_cmd);
    return ret;
}

inline int tiny_base_command_type::decode(CNewBufMgr& buf_mgr)
{
    int ret = 0;
    ret += buf_mgr.GetInt(m_protocol_ver);
    ret += buf_mgr.GetChar(m_cmd);
    return ret;
}

//----------------------- tiny_base_command -------------------------
template<typename T1, typename T2>
inline int tiny_base_command<T1, T2>::get_command_id(char* pbuf, int len)
{
    if ((unsigned)len < TINY_SRV_MSG_HEAD_LEN) {
        return INVALID_CMD_ID;
    }

    unsigned char uch_cmd_id;
    memcpy(&uch_cmd_id, pbuf + TINY_SRV_CMDINFO_OFFSET, sizeof(uch_cmd_id));
    return uch_cmd_id;
}

template<typename T1, typename T2>
inline tiny_base_command<T1, T2>::tiny_base_command(char* /*pbuf*/, int /*len*/,
       int client_ip, short client_port, int entity_type, int entity_id)
    : CCommand()
    , m_in_hdr()
    , m_out_hdr()
    , m_in_buf(NULL, 0, 1, 0)
    , m_out_buf(NULL, 0, 0, 0)
    , m_in()
    , m_out()
    , m_entity_type(entity_type)
    , m_entity_id(entity_id)
    , m_ip(client_ip)
    , m_port(client_port)
{
}

template<typename T1, typename T2>
inline tiny_base_command<T1, T2>::~tiny_base_command()
{

}

template<typename T1, typename T2>
inline int tiny_base_command<T1, T2>::Process(int& nresult)
{
    int res = proc_cmd();
    static_cast<void>(res);
    nresult = 0;
    return 0;
}

template<typename T1, typename T2>
inline char* tiny_base_command<T1, T2>::GetResBuf(int& len)
{
    char *res_buf = new char[1024];
    memset(res_buf, 0, 1024);
    strcpy(res_buf, "ok! i've received, welcome!");
    len = strlen(res_buf);
    return static_cast<char*>(res_buf);
}

template<typename T1, typename T2>
inline short tiny_base_command<T1, T2>::GetMsgType()
{
    return 0;
}

template<typename T1, typename T2>
inline void tiny_base_command<T1, T2>::DisAttachBuf()
{

}

template<typename T1, typename T2>
inline int tiny_base_command<T1, T2>::Encode()
{
    return 0;
}

template<typename T1, typename T2>
inline int tiny_base_command<T1, T2>::Decode()
{
    return 0;
}

template<typename T1, typename T2>
inline void tiny_base_command<T1, T2>::trans_msg(char* pkt_buf, unsigned int pkt_len)
{
    TMsg tmsg;
    tmsg.destEntityType = TINY_SRV_ONTIME_SYN_ENTITY_TYPE;
    tmsg.destEntityId = 0;
    tmsg.srcEntityType = m_entity_type;
    tmsg.srcEntityId = m_entity_id;
    tmsg.srcTaskId = 0;
    tmsg.msgType = SYN_MSGTYPE;

    CMsgBody* pmsg_body = new CClientMsgBody(pkt_buf, pkt_len);
    CMsg* pmsg = new CMsg(tmsg, pmsg_body);
    CMyserver::GetInstance()->PutMsgToThread(pmsg);
}
