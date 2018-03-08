#include <pthread.h>
#include "timer.h"

void timer_server::registe(time_event *event_inst)
{
}

void timer_server::release(time_event *event_inst)
{

}

void timer_server::start_server()
{
    if (0 == pthread_attr_init(&m_attr)) {
        if (0 == pthread_attr_setdetachstate(&m_attr, PTHREAD_CREATE_JOINABLE)) {
            if (0 != pthread_create(&m_thread, &m_attr, execute_func, this)) {
                pthread_attr_destroy(&m_attr);
            }
        } else {
            pthread_attr_destroy(&m_attr);
        }
    }
}

void timer_server::shutdown()
{
    if (m_shutdown) {
        return;
    }
    m_shutdown = true;
    m_cond.signal();
    pthread_join(m_thread);
    pthread_attr_destroy(&m_attr);
}

void* timer_server::execute_func(void* ptr)
{
    timer_server* self = (timer_server*)ptr;
    while (!self->m_shutdown) {
        time_t now = time(NULL);
        std::list<time_event*>::iterator iter = m_events.begin();
        for (; iter != m_events.end(); ++iter) {
            time_event* cur = *iter;
            if (now < cur->m_schedule) {
                continue; ///< 未来事件，暂时跳过
            }
            if (cur->m_repeatable || cur->m_count <= 0) {
                if (cur->m_callback) {
                    cur->m_callback->callback_func();
                    ++cur->m_count;
                    if (cur->repeatable) {
                        cur->m_schedule += cur->m_interval;
                    }
                }
            }
        }

        while (!self->m_shutdown) {
            if (m_cond.wait(m_kSleep))
        }
    }
}
