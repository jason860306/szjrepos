/**
 * create on: 2012年11月9日
 * author: szj0306
 */

#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include "timer_thread.h"

timer_thread* timer_thread::m_instance = NULL;

timer_thread::timer_thread()
{

}

timer_thread::~timer_thread()
{

}

void* timer_thread::run(void)
{
    while (true) {
        unsigned int start_clock = get_system_clock();
        this->m_timer_lst.sort();
        std::list<my_timer>::iterator iter;
        for (iter = this->m_timer_lst.begin(); iter != this->m_timer_lst.end(); ++iter) {
            --iter->m_leftsecs;
            if (iter->m_leftsecs == 0) {
                iter->m_callback();
                iter->m_leftsecs = iter->m_interval;
            }
        }
        unsigned int end_clock = get_system_clock();

        usleep(1000 - start_clock + end_clock);
    }
    return (void*) 0;
}

void timer_thread::registe(my_timer t)
{
    this->m_timer_lst.push_back(t);
}

void timer_thread::unregist(my_timer t)
{
    this->m_timer_lst.remove(t);
}

timer_thread* timer_thread::get_instance()
{
    if (m_instance == NULL) {
        m_instance = new timer_thread();
    }
    return m_instance;
}

unsigned int get_system_clock()
{
    struct timeval now;
    gettimeofday(&now, NULL);
    return (now.tv_sec * 1000 + now.tv_usec / 1000);
}
