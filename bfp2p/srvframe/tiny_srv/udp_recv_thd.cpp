#include <string>
#include "udp_recv_thd.h"
#include "tiny_srv_def.h"
#include "threadgroup.h"

udp_recv_thd::udp_recv_thd(int entity_type, int entity_id,
                           std::string& ip, unsigned short port)
    : CUdpCommonRecvThread(entity_type, entity_id, ip, port)
{
}

int udp_recv_thd::Run()
{
    while (m_nRunFlag) {
        if (int recv_len = m_UdpSocket.UdpRecv()) {
            printf("%s\n", m_UdpSocket.GetRecvBuf());
            char* ptmp_buf = new char[recv_len];
            memset(ptmp_buf, 0, recv_len);
            unsigned decrypt_len = recv_len;
            mhxy_udp::decrypt((unsigned char*)m_UdpSocket.GetRecvBuf(), recv_len,
                              (unsigned char*)ptmp_buf, decrypt_len);
            printf("%s\n", ptmp_buf);
            CUdpCommonBufMsgBody* pudp_buf_msg_body = new CUdpCommonBufMsgBody(
                ptmp_buf, decrypt_len, m_UdpSocket.GetSocket(),
                ntohl(m_UdpSocket.GetCurSrcAddr().sin_addr.s_addr),
                ntohs(m_UdpSocket.GetCurSrcAddr().sin_port));
            SendMsg(TINY_SRV_UDP_PROC_SND_ENTITY_TYPE, RANDOMENTITYID, 0,
                    UDPCLIENTMSG, pudp_buf_msg_body, 0);
        }
    }

    return 0;
}
