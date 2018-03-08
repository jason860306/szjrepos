#ifndef TCP_RECV_SND_TASK_H
#define TCP_RECV_SND_TASK_H

#include "HttpRecvAndSendTaskProcess.h"
#include "framecommon/framecommon.h"

class CNetProcessThread;
class CRecvAndSendTask;
class tcp_task_proc : public CHttpRecvAndSendTaskProcess
{
public:
    tcp_task_proc(CNetProcessThread *pnetprocessthread, CRecvAndSendTask *precv_snd_task,
                  CTcpSocket *psocket);
    ~tcp_task_proc();
public:
    virtual int ProcessRecvPacket(const char *ppacket, unsigned int buf_len);
    virtual const char *ProcessSendPacket(const char *pold_packet, unsigned int old_buf_len,
                                          unsigned int &new_buf_len);
private:
    void trans_msg(char *pbuf, int len, int machine_index, int type);
};

#endif
