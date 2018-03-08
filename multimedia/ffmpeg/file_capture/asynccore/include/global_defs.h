///////////////////////////////////////////////////////////////////////////////
// global_defs.h
///////////////////////////////////////////////////////////////////////////////

#pragma once

///////////////////////////////////////////////////////////////////////////////
// global includes

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cassert>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <algorithm>

#include <basetsd.h>
#include <functional>

#include <winsock2.h>
#include <windows.h>

using std::string;
using std::vector;
using std::list;
using std::map;
using std::set;

using namespace std::tr1::placeholders;

///////////////////////////////////////////////////////////////////////////////
// type defines

#if 0
typedef INT8      int8_t;
typedef INT16     int16_t;
typedef INT32     int32_t;
typedef INT64     int64_t;
typedef UINT8     uint8_t;
typedef UINT16    uint16_t;
typedef UINT32    uint32_t;
typedef UINT64    uint64_t;
#endif

typedef intptr_t  socket_t;

typedef UINT32 THREAD_ID;
typedef INT64 TIMER_ID;

typedef void* POINTER;

typedef vector<string> string_array;
typedef map<string, string> string_map;

typedef std::tr1::function<void()> functor;
typedef std::tr1::function<void()> timer_callback;

///////////////////////////////////////////////////////////////////////////////
// const defines

const char PATH_DELIM               = '\\';
const char DRIVER_DELIM             = ':';
const char FILE_EXT_DELIM           = '.';
const char* const S_CRLF            = "\r\n";

// range values
#define MAXCHAR     0x7f
#define MAXSHORT    0x7fff
#define MAXLONG     0x7fffffff
#define MAXBYTE     0xff
#define MAXWORD     0xffff
#define MAXDWORD    0xffffffff
#if 0
#define MAXUINT64   0xffffffffffffffff
#endif

#define TRUE_STR                    "true"
#define FALSE_STR                   "false"

const int TIMEOUT_INFINITE = -1;

const int RET_SUCCESS = 0;
const int RET_FAILURE = -1;

///////////////////////////////////////////////////////////////////////////////
// macro defines

#define SAFE_DELETE(x)          { delete x; x = NULL; }
#define CATCH_ALL_EXCEPTION(x)  try { x; } catch(...) {}

///////////////////////////////////////////////////////////////////////////////
// compiler defines

#pragma warning(disable: 4355)
#pragma warning(disable: 4996)

///////////////////////////////////////////////////////////////////////////////
