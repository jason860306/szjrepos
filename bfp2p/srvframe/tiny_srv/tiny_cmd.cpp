#include "tiny_cmd.h"

int tiny_cmd_type::decode(CBufMgr& buf_mgr)
{
    if (0 != buf_mgr.GetString(m_peer_id)) {
        return -1;
    }
    if (m_peer_id.size() != PEERLENGTH) {
        return -2;
    }

    if (0 != buf_mgr.GetInt(m_internal_ip)) {
        return -3;
    }
    m_internal_ip = ntohl(m_internal_ip);

    if (0 != buf_mgr.GetInt(m_sub_mask)) {
        return -4;
    }
    m_sub_mask = ntohl(m_sub_mask);

    if (0 != buf_mgr.GetShort(m_tcp_port)) {
        return -5;
    }

    if (0 != buf_mgr.GetInt(m_nat_type)) {
        return -6;
    }

    if (0 != buf_mgr.GetInt(m_upnp_map_ip)) {
        return -7;
    }
    m_upnp_map_ip = ntohl(m_upnp_map_ip);

    if (0 != buf_mgr.GetShort(m_upnp_map_prot)) {
        return -8;
    }

    return 0;
}

tiny_cmd::tiny_cmd(char* pbuf, int len, int public_ip, short public_port,
                   int entity_type, int entity_id)
    : tiny_base_command<tiny_cmd_type>(pbuf, len, public_ip, public_port,
                                       entity_type, entity_id)
{
}

tiny_cmd::~tiny_cmd()
{
}

int tiny_cmd::proc_cmd()
{
    char* pbuf = new char[128];
    memset(pbuf, 0, 128);
    strcpy(pbuf, "ok, i've received!");
    trans_msg(pbuf, strlen(pbuf));
    return 0;
}
