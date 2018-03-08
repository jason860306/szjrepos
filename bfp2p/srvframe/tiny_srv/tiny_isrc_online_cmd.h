#ifndef TINY_ISRC_ONLINE_CMD_H
#define TINY_ISRC_ONLINE_CMD_H

#include "tiny_base_command.h"

struct tiny_isrc_online_cmd
{
    std::string m_peer_id;
    int decode(CBufMgr &buf_mgr) {
        if (buf_mgr.GetString(m_peer_id) != 0) {
            return -1;
        }
        if (m_peer_id.size() != PEERLENGTH) {
            return -1;
        }
        return 0;
    }
};

struct tiny_lsrc_online_res_cmd
{
    char m_result;
    int m_breport;

    int encode(CBufMgr &buf_mgr) {
        int ret = 0;
        ret += buf_mgr.PutChar(m_result);
        ret += buf_mgr.PutInt(m_breport);
        return ret;
    }

    int get_size() {
        int len = 0;
        len += sizeof(m_result);
        len += sizeof(m_breport);
        return len;
    }
};

class tiny_lsrc_online
    : public tiny_base_command<tiny_isrc_online_cmd, tiny_lsrc_online_res_cmd>
{
public:
    tiny_lsrc_online(char *pbuf, int len)
        : tiny_base_command<tiny_isrc_online_cmd, tiny_lsrc_online_res_cmd>(
            pbuf, len, 0, 0, 0, 0) {
        /// m_out_hdr.m_cmd = TINY_SRV_ISRC_ONLINE_RES;
    }

    ~tiny_lsrc_online() {}

protected:
    virtual int proc_cmd();
};

#endif
