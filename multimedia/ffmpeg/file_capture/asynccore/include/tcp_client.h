///////////////////////////////////////////////////////////////////////////////
// tcp_client.h
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include "global_defs.h"
#include "tcp_connection.h"

///////////////////////////////////////////////////////////////////////////////
// tcp_client

class tcp_client : public tcp_connection
{
public:
	bool connect(const string& hostname, unsigned short port);
};
