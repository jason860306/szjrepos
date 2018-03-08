/**
 * thread.cpp
 * create on: 2012年11月9日
 * author: szj0306
 */
#include "thread.h"


thread::thread()
{

}


thread::~thread()
{

}


void* thread::thread_entry(void* para)
{
    thread* pthread = static_cast<thread*>(para);
    return pthread->run();
}

int thread::start(void)
{
    if (pthread_create(&m_pid, 0, thread_entry, static_cast<void*>(this)) < 0) {
        pthread_detach(this->m_pid);
        return -1;
    }
    return 0;
}

int thread::cancel(void)
{
    pthread_cancel(this->m_pid);
    return 0;
}
