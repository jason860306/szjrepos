#ifndef TINY_CLASS_FACTORY_H
#define TINY_CLASS_FACTORY_H

#include "classfactory.h"

class CWorkThread;
class CCommand;
class tiny_class_factory : public CClassFactory
{
public:
    tiny_class_factory() : CClassFactory() {}
    virtual ~tiny_class_factory() {}
public:
    virtual CWorkThread* GenWorkThread(int entity_type, int entity_id,
                                       std::string annex_data, void* parg = NULL);
    virtual CSocketTask *GenSocketTask(CNetProcessThread *pwork_thread,
                                       CTcpSocket *ptcp_socket, int task_type,
                                       CTaskArg *ptask_arg = NULL);
public:
    virtual CCommand* GenBaseCommand(char* pbuf, int len, int client_ip, short client_port,
                                     int entity_type, int entity_id);
};

#endif
