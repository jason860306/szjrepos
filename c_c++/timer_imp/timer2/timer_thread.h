#ifndef TIMER_THREAD_H
#define TIMER_THREAD_H

/**
 * create on: 2012年11月9日
 * author: szj0306
 */

#include <list>
#include "thread.h"

struct my_timer
{
    void* m_args;
    int (*m_callback)();
    int m_interval;
    int m_leftsecs;

    void open(int interval, int (*callback)()) {
        m_interval = interval * 1000;
        m_leftsecs = m_interval;
        m_callback = callback;
    }

    bool operator< (my_timer t) {
        return (t.m_leftsecs < this->m_leftsecs);
    }

    bool operator== (my_timer t) {
        return (t.m_leftsecs == this->m_leftsecs);
    }
};

/*
inline my_timer::open(int interval, int (*callback)())
{
    m_interval = interval * 1000;
    m_leftsecs = m_interval;
    m_callback = callback;
}

inline bool my_timer::operator< (my_timer t)
{
    return (t.m_leftsecs < this->m_leftsecs);
}

inline bool my_timer::operator== (my_timer t)
{
    return (t.m_leftsecs == this->m_leftsecs);
}
*/

class timer_thread : public thread
{
public:
    static timer_thread* m_instance;
    static timer_thread* get_instance();

    virtual ~timer_thread();
    virtual void* run(void);

    void registe(my_timer t);
    void unregist(my_timer t);
private:
    timer_thread();
    std::list<my_timer> m_timer_lst;
};

extern unsigned int get_system_clock();

#define TIMER_MANAGE timer_thread::get_instance()

#endif
