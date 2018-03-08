#ifndef TIMER_H
#define TIMER_H

class timeout_callback
{
public:
    virtual ~timeout_callback() {}
    /**
     * 纯虚接口，所有定制的callback都继承
     * timeout_callback并实现自己的cakkback_func.
     */
    virtual void callback_func() = 0;
};

class time_event
{
public:
    time_t m_schedule; ///< 预计下一次的执行时间
    time_t m_interval; ///< 如果是repeatable，事件的执行间隔
    bool m_repeatable; ///< 是不是需要重复执行
    int m_count; ///< 该事件被触发的次数
    timeout_callback *m_callback; ///< 绑定的事件回调类实例
};

class timer_server
{
public:
    void registe(time_event *event_inst); ///< 将一个事件加入执行队列
    void release(timeevent *event_inst); ///< 将一个事件从执行队列中移走
    void start_server();
    void shutdown();
private:
    std::list<time_event*> m_events; ///< 事件的执行队列
    pthread_t m_thread; ///< 保存执行函数的thread_id，以便执行join操作
    pthread_attr_t m_attr;
    pthread_cond_t m_cond;
    pthread_mutex_t m_mutex; ///< 用于保护event_queue
    bool m_shutdown; ///< 关闭标志
private:
    static void* execute_func(void *ptr); ///< 执行函数
}

#endif
