#ifndef __TIMEOUT_CHECK_THD_H__
#define __TIMEOUT_CHECK_THD_H__
#include <workthread.h>

class timer_srv;
class CMsg;

class timeout_check_thd : public CWorkThread
{
public:
    timeout_check_thd(int entity_type, int entity_id);
    ~timeout_check_thd();
public:
    virtual int Init();
    virtual int Run();
    virtual int PutMsgToInputList(CMsg* pmsg);
private:
    virtual int Process(CMsg* pmsg);
private:
    void trans_msg(const char* buf_ptr, std::size_t buf_size);
private:
    timer_srv* m_pserver;
    int m_check_interval;
    int m_syn_interval;
};

#endif //__TIMEOUT_CHECK_THD_H__
