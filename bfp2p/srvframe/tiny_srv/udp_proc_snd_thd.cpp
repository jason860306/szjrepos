#include "udp_proc_snd_thd.h"
#include "basecommand.h"
#include "timer_srv.h"
#include "tiny_class_factory.h"

udp_proc_snd_thd::udp_proc_snd_thd(int entity_type, int entity_id)
    : CUdpCommonSendThread(entity_type, entity_id)
{
}

udp_proc_snd_thd::~udp_proc_snd_thd()
{
}

int udp_proc_snd_thd::Run()
{
	while (m_nRunFlag) {
        CMsg* pmsg = m_InputList.get();
        if (NULL != pmsg) {
            Process(pmsg);
            if (IfHaveDataToSend()) {
                CUdpCommonBufMsgBody* pmsg_body = (CUdpCommonBufMsgBody*)pmsg->GetMsgBody();
                timer_srv* pserver = (timer_srv*)CMyserver::GetInstance();
                if (NULL != pmsg_body && NULL != pserver && m_pSendBuf != NULL &&
                    m_iSendPackecLen > 0) {
                    char* pencrypt_buf = new char[m_iSendPackecLen + MHXY_ENCRYPT_EXTRA_LEN];
                    int encrypt_len = m_iSendPackecLen + MHXY_ENCRYPT_EXTRA_LEN;
                    int encrypt_algorithm_type = 0;// pserver->GetConf().GetConf().nEncryptType;
                    mhxy_udp::encrypt(encrypt_algorithm_type, (unsigned char*)m_pSendBuf,
                                      m_iSendPackecLen, (unsigned char*)pencrypt_buf,
                                      (unsigned&)encrypt_len);
                    m_UdpSock.UdpSend(pmsg_body->GetSocket(), (char*)pencrypt_buf,
                                      encrypt_len, pmsg_body->GetClientIp(),
                                      pmsg_body->GetCientPort());
//                    DelSendBuf();
                    delete[] pencrypt_buf;
                    pencrypt_buf = NULL;
                }
                ClearSendDataFlag();
            }
            delete pmsg;
            pmsg = NULL;
        }
	}
    return 0;
}

int udp_proc_snd_thd::MsgProcess(CMsg* pmsg)
{
    CUdpCommonBufMsgBody* pbuf_msg_body = (CUdpCommonBufMsgBody*)pmsg->GetMsgBody();
    if (NULL == pbuf_msg_body) {
        return -1;
    }

    char* pbuf = pbuf_msg_body->GetBuf();
    int nlen = pbuf_msg_body->Size();

    timer_srv* pserver = (timer_srv*)CMyserver::GetInstance();
    if (NULL == pserver) {
        return -2;
    }
    tiny_class_factory* pfactory = (tiny_class_factory*)pserver->GetClassFactory();
    if (NULL == pfactory) {
        return -3;
    }

    CCommand* pcmd = pfactory->GenBaseCommand(pbuf, nlen, pbuf_msg_body->GetClientIp(),
                                              pbuf_msg_body->GetCientPort(),
                                              m_nEntityType, m_nEntityId);
    if (NULL == pcmd) {
        return -4;
    }

    int result = 0;
    int res = pcmd->Process(result);
    if (pcmd->GetIfRes() && (0 == res)) {
        m_pSendBuf = pcmd->GetResBuf(m_iSendPackecLen);
        if (m_pSendBuf && m_iSendPackecLen > 0 &&
            m_iSendPackecLen <= MAX_UDP_SEND_PACKET_LEN - MHXY_ENCRYPT_EXTRA_LEN) {
            SetSendDataFlag();
        } else {
            DelSendBuf();
        }
    }

    delete pcmd;
    pcmd = NULL;

    return res;
}
