#ifndef THREAD_H
#define THREAD_H

/**
 * thread.h
 * create on: 2012年11月9日
 * author: szj0306
 */

#include <pthread.h>

class thread
{
public:
    enum thread_state { IDLE, WORK, BUSY };
public:
    thread();
    virtual ~thread();
    virtual void* run(void) = 0;
    virtual int start(void);
    virtual int cancel(void);
    pthread_t get_pid() const { return m_pid; }
protected:
    thread_state m_ts;
private:
    pthread_t m_pid;
    static void* thread_entry(void* para);
};

#endif
