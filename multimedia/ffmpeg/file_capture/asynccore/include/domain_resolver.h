///////////////////////////////////////////////////////////////////////////////
// domain_resolver.h
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include "global_defs.h"

struct evdns_getaddrinfo_request;
struct evutil_addrinfo;

///////////////////////////////////////////////////////////////////////////////
// domain_resolver

class domain_resolver
{
public:
	typedef std::tr1::function<void (bool success,
		const std::string& domain, const std::string& ip)> resolve_callback;

	struct resolve_task 
	{
		string domain;
		string ip;
		struct evdns_getaddrinfo_request *resolve_req;
		domain_resolver *resolver;
	};

public:
	domain_resolver();
	virtual ~domain_resolver();

	void resolve_domain(const string& domain);
	void cancel(const string& domain);

	void set_resolve_callback(const resolve_callback& callback);

private:
	static void resolve_complete(int errcode, addrinfo *addr, void *ptr);

	resolve_task* find_task(const string& domain);
	void remove_task(const string& domain);
	void cancel_all_tasks();
	void clear();

private:
	typedef list<resolve_task*> resolve_task_list;

	resolve_task_list _task_list;
	resolve_callback _resolve_callback;
};
