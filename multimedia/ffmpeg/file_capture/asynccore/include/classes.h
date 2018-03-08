///////////////////////////////////////////////////////////////////////////////
// classes.h
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include "global_defs.h"

#include <stdarg.h>
#include <time.h>
#include <sys/timeb.h>
#include <iostream>
#include <fstream>
#include <windows.h>

///////////////////////////////////////////////////////////////////////////////
// noncopyable

class noncopyable
{
protected:
	noncopyable() {}
	~noncopyable() {}
private:
	noncopyable(const noncopyable&);
	const noncopyable& operator=(const noncopyable&);
};

///////////////////////////////////////////////////////////////////////////////
// auto_finalizer

class auto_finalizer : noncopyable
{
public:
	auto_finalizer(const functor& f) : _f(f) {}
	~auto_finalizer() { _f(); }
private:
	functor _f;
};

///////////////////////////////////////////////////////////////////////////////
// scope_guard

class scope_guard
{
public:
	explicit scope_guard(functor on_exit_scope)
		: on_exit_scope_(on_exit_scope), dismissed_(false)
	{ }

	~scope_guard()
	{
		if(!dismissed_)
		{
			on_exit_scope_();
		}
	}

	void dismiss()
	{
		dismissed_ = true;
	}

private:
	functor on_exit_scope_;
	bool dismissed_;

private: // noncopyable
	scope_guard(scope_guard const&);
	scope_guard& operator=(scope_guard const&);
};

#define SCOPEGUARD_LINENAME_CAT(name, line) name##line
#define SCOPEGUARD_LINENAME(name, line) SCOPEGUARD_LINENAME_CAT(name, line)
#define ON_SCOPE_EXIT(callback) scope_guard SCOPEGUARD_LINENAME(EXIT, __LINE__)(callback)

///////////////////////////////////////////////////////////////////////////////
// semaphore

class semaphore : noncopyable
{
public:
	explicit semaphore(UINT init_value = 0);
	virtual ~semaphore();

	void increase();
	void wait();
	void reset();

private:
	void do_create_sem();
	void do_destroy_sem();

private:
	HANDLE _sem;
	UINT _init_value;
};

///////////////////////////////////////////////////////////////////////////////
// mutex

class mutex
{
public:
	mutex();
	virtual ~mutex();

	void lock();
	void unlock();

private:
	CRITICAL_SECTION _criti_sect;
};

///////////////////////////////////////////////////////////////////////////////
// auto_locker

class auto_locker
{
public:
	auto_locker(mutex& mutex) { _mutex = &mutex; _mutex->lock(); }
	auto_locker(mutex *mutex) { _mutex = mutex; _mutex->lock(); }
	~auto_locker() { if (_mutex) _mutex->unlock(); }
private:
	mutex *_mutex;
};

///////////////////////////////////////////////////////////////////////////////
// singleton

template<typename T>
class singleton : noncopyable
{
public:
	static T& instance()
	{
		// DCL with volatile
		if (_instance == NULL)
		{
			auto_locker locker(_mutex);
			if (_instance == NULL)
				_instance = new T();
			return *_instance;
		}
		return *_instance;
	}

	static void destroy_instance()
	{
		delete _instance;
		_instance = NULL;
	}

protected:
	singleton() {}
	~singleton() {}
private:
	static T* volatile _instance;
	static mutex _mutex;
};

template<typename T> T* volatile singleton<T>::_instance = NULL;
template<typename T> mutex singleton<T>::_mutex;

///////////////////////////////////////////////////////////////////////////////
// seq_num_generator

template <typename T>
class seq_num_generator : noncopyable
{
public:
	explicit seq_num_generator(T start_num = 0) : _current_num(start_num) {}

	T generate()
	{
		auto_locker lock(_mutex);
		return _current_num++;
	}

private:
	mutex _mutex;
	T _current_num;
};

///////////////////////////////////////////////////////////////////////////////
