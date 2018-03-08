#ifndef __BFP2P_SZJ0306_NATCHECK_NATCHECK_H__
#define __BFP2P_SZJ0306_NATCHECK_NATCHECK_H__

#ifdef WIN32
#define CLOSE closesocket
#else
#define CLOSE close
#endif

struct TAddrType;
struct sockaddr_in;

/**
 * some function for TNatType
 */
const char* NatType2Name(TNatType nat_type);

/**
 * some function for TAddrType
 */
const char* FormatAddr(const TAddrType* pAddr);
const char* FormatAddr1(const struct sockaddr_in* psi);
int AddrCmp(const TAddrType* pAddr1, const TAddrType* pAddr2);

/**
 * some function for socket
 */
int SetAddr(struct sockaddr_in* paddr, const char* ip, const char* port);
int CreateUdpSock(const struct sockaddr_in* paddr);

#endif //__BFP2P_SZJ0306_NATCHECK_NATCHECK_H__
