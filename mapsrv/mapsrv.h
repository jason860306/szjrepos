/**
 * ============================================================================
 * @file    mapsrv.h
 *
 * @brief   
 * @details 
 *
 * @version 1.0  
 * @date    2013-10-30 18:26:26
 *
 * @author  shizhijie, shizhijie@baofeng.com
 * ============================================================================
 */

#ifndef __BFP2P_SERVER_MAPSRV_H__
#define __BFP2P_SERVER_MAPSRV_H__

#ifndef __cplusplus
#define NULL ((void *)0)
#endif

/* 转换8字节整型： */
typedef unsigned long long UINT64;
#define ntohll(x) ( ((UINT64)x & 0xff00000000000000LL)>>56 | \
		((UINT64)x & 0x00ff000000000000LL)>>40 |			 \
		((UINT64)x & 0x0000ff0000000000LL)>>24 |			 \
		((UINT64)x & 0x000000ff00000000LL)>>8 |				 \
		((UINT64)x & 0x00000000ff000000LL)<<8 |				 \
		((UINT64)x & 0x0000000000ff0000LL)<<24 |			 \
		((UINT64)x & 0x000000000000ff00LL)<<40 |			 \
		((UINT64)x & 0x00000000000000ffLL)<<56 )
/* 为了使问题清晰，先定义个函数 */
double swap_double(double* pdVal);
#define ntohd(x) (swap_double(&(x)))

typedef
#if SIZEOF_FLOAT == 8
float
#elif SIZEOF_DOUBLE == 8
double
#elif SIZEOF_LONG_DOUBLE == 8
long double
#else
uint64_t
#endif
number64, number64_le, number64_be;
number64 swap_number64(number64 n);
#define htond(x) (swap_number64((x)))

typedef enum __proto_type_s
{
	LOCATION_REPORT,   /* B/C端用户向服务器上报他们的地理位置 */
	LOCATION_REQUEST,  /* C端用户向服务器查询拥有有效wifi信号的B端用户地理位置 */
	LOCATION_RESPONSE, /* 服务器返回满足C端用户搜索条件的B端用户地理位置 */
} proto_type_t;

typedef enum __loctype
{
	LOCTYPE_GPS = 61,      /* placed by gps. */
	LOCTYPE_NETWORK = 161, /* placed by network(eg. wifi, base station etc.) */
	LOCTYPE_CACHE = 65     /* placed from local cache. */
} loctype_t;

typedef enum __coordinate
{
	COORDINATE_WGS84, /* 地球坐标系，国际上通用的坐标系 */
	COORDINATE_GCJ02, /* 火星坐标系，WGS84坐标系经加密后的坐标系 */
	COORDINATE_BD09,  /* 百度坐标系，GCJ02坐标系经加密后的坐标系 */
	COORDINATE_OTHER, /* 搜狗坐标系、图吧坐标系等，估计也是在GCJ02基础上加密而成的 */
} coordinate_t;

typedef struct __loc_s
{
	double latitude;
	double longitude;
	coordinate_t coordinate;
	loctype_t loctype;
} loc_t, *p_loc_t, **pp_loc_t;

typedef struct __locnode_s locnode_t, *p_locnode_t, **pp_locnode_t;
struct __locnode_s
{
	p_loc_t p_loc;
	p_locnode_t p_locnode_next;
	p_locnode_t p_locnode_prev;
};

typedef struct __loclst_s
{
	int num;
	int size;
	p_locnode_t p_loc_first;
	p_locnode_t p_loc_last;
} loclst_t, *p_loclst_t, **pp_loclst_t;

/* the protocol between mapcli and mapsrv */

/* the user(b/c) report their loc to mapsrv. */
typedef struct __locreport_s
{
	proto_type_t proto_type;
	int length;
	loc_t loc;
} locreport_t, *p_locreport_t, **pp_locreport_t;

/* the user(c) request all the users's loc who owned valid wifi signal. */
typedef struct __locrequest_s
{
	proto_type_t proto_type;
	int length;
	double radius;
	loc_t loc;
} locrequest_t, *p_locrequest_t, **pp_locrequest_t;

/* mapsrv return all the valid users(b) to user(c). */
typedef struct __locresponse_s
{
	proto_type_t proto_type;
	int length;
	p_loclst_t p_loclst;
} locresponse_t, *p_locresponse_t, **pp_locresponse_t;

int loc2buf(p_loc_t p_loc, char **pp_locbuf);
p_loc_t buf2loc(const char *p_locbuf, int len, pp_loc_t pp_loc);
int loclst2buf(p_loclst_t p_loclst, char **pp_loclstbuf);
p_loclst_t buf2loclst(const char *p_loclstbuf, int len, pp_loclst_t pp_loclst);

int add_loc(p_loclst_t p_loclst, p_loc_t p_loc);
int del_loc(p_loclst_t p_loclst, p_loc_t p_loc);
/**
 *@brief 在p_loclst中查找与p_loc距离小于等于distance的所有其它位置信息，
 *       保存在pp_loc中
 */
int find_loc(p_loclst_t p_loclst, p_loc_t p_loc, double distance, pp_loclst_t pp_loc);

#endif //__BFP2P_SERVER_MAPSRV_H__
