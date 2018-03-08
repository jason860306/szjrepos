#ifndef TINY_CMD_H
#define TINY_CMD_H

#include "tiny_base_command.h"

struct tiny_cmd_type
{
    std::string m_peer_id;
    int m_internal_ip;
    int m_sub_mask;
    short m_tcp_port;
    int m_nat_type;
    int m_upnp_map_ip;
    short m_upnp_map_prot;
    /// etc....

    int decode(CBufMgr& buf_mgr);
};

class tiny_cmd : public tiny_base_command<tiny_cmd_type>
{
public:
    tiny_cmd(char* pbuf, int len, int public_ip, short public_port,
             int entity_type, int entiti_id);
    ~tiny_cmd();
protected:
    virtual int proc_cmd();
};

#endif
