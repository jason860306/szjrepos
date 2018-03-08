#ifndef ONTIME_SYNTHREAD_H
#define ONTIME_SYNTHREAD_H
#include <cstddef>
#include <workthread.h>
#include <synqueue.h>

class timer_srv;
class CMsg;

class ontime_synthread : public CWorkThread
{
public:
    ontime_synthread(int entity_type, int entity_id);
    ~ontime_synthread();
public:
    virtual int Init();
    virtual int Run();
    virtual int PutMsgToInputList(CMsg* pmsg);
private:
    virtual int Process(CMsg* pmsg);
private:
    void trans_msg(const char* buf_ptr, std::size_t buf_size);
    int process_ontime(CMsg* pmsg);
private:
    CQueue m_input_list;
    timer_srv* m_pserver;
    sem_t* m_psyn_sendsem;
};

#endif
