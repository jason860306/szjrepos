#ifndef __BFP2P_SZJ0306_NATCHECK_NCTYPE_H__
#define __BFP2P_SZJ0306_NATCHECK_NCTYPE_H__

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

typedef enum
{
	BLOCKED,
	OPENED,
	SYMMETRIC_FIRE_WALL,
	FULL_CONE_NAT,
	SYMMETRIC_NAT,
	PORT_RESTRICTED_CONE_NAT,
	RESTRICTED_CONE_NAT
} TNatType;

typedef enum
{
	CLIENT_REQ_IP_PORT = 10,
	CLIENT_REQ_TRY_OTHER_IP,
	CLIENT_REQ_TRY_OTHER_PORT,
	CLIENT_REQ_TRY_OTHER_IP_PORT,
} TCmdType;

typedef struct
{
	uint32_t ip;
	uint16_t port;
} TAddrType;

typedef struct
{
	TCmdType cmd;
} TReqPkt;

typedef struct
{
	TAddrType addr;
} TResPkt;

#endif //__BFP2P_SZJ0306_NATCHECK_NCTYPE_H__
