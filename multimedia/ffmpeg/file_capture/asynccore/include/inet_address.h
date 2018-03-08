///////////////////////////////////////////////////////////////////////////////
// inet_address.h
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include "global_defs.h"

///////////////////////////////////////////////////////////////////////////////
// inet_address

class inet_address
{
public:
	inet_address() : ip(0), port(0) {}
	inet_address(UINT32 ip, UINT16 port);
	inet_address(const string& ip, UINT16 port);
	inet_address(const sockaddr_in& sock_addr);

	bool operator == (const inet_address& rhs) const
		{ return (ip == rhs.ip && port == rhs.port); }
	bool operator != (const inet_address& rhs) const
		{ return !((*this) == rhs); }

	sockaddr_in get_sock_addr() const
	{
		sockaddr_in result;
		memset(&result, 0, sizeof(result));
		result.sin_family = AF_INET;
		result.sin_addr.s_addr = htonl(ip);
		result.sin_port = htons(port);
		return result;
	}

	void clear() { ip = 0; port = 0; }
	bool is_empty() const { return (ip == 0) && (port == 0); }
	string get_display_str() const;

public:
	UINT32 ip;     // (host byte order)
	UINT16 port;   // (host byte order)
};
