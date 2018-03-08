#ifndef TINY_BASE_COMMAND_H
#define TINY_BASE_COMMAND_H

#include "framecommon/framecommon.h"
#include "basecommand.h"

struct tiny_base_command_type
{
    int m_protocol_ver;
    char m_cmd;
    tiny_base_command_type() : m_protocol_ver(256), m_cmd(0) {}
    int encode(CNewBufMgr& buf_mgr);
    int decode(CNewBufMgr& buf_mgr);
};

template<typename T1, typename T2 = CDefaultRes>
class tiny_base_command : public CCommand
{
public:
    static int get_command_id(char* pbuf, int len);
public:
    tiny_base_command(char* pbuf, int len, int client_ip, short client_port,
                      int entity_type, int entity_id);
    virtual ~tiny_base_command();
public:
    virtual int Process(int& nresult);
    virtual char* GetResBuf(int& len);
    virtual short GetMsgType();
    virtual void DisAttachBuf();
protected:
    virtual int Encode();
    virtual int Decode();
protected:
    virtual int proc_cmd() = 0;
protected:
    void trans_msg(char* pkt_buf, unsigned int pkt_len);
private:
    tiny_base_command_type m_in_hdr;
    tiny_base_command_type m_out_hdr;

    CBufMgr m_in_buf;
    CTmpBufMgr m_out_buf;
    T1 m_in;
    T2 m_out;

    int m_entity_type;
    int m_entity_id;

    int m_ip;
    short m_port;
};

#include "tiny_base_command.inl"

#endif //TINY_BASE_COMMAND_H
