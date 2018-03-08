///////////////////////////////////////////////////////////////////////////////
// exception_msgs.h
///////////////////////////////////////////////////////////////////////////////

#ifndef _EXCEPTION_MSGS_H_
#define _EXCEPTION_MSGS_H_

///////////////////////////////////////////////////////////////////////////////

const char* const SEM_OUT_OF_MEMORY               = "Out of memory.";
const char* const SEM_INIT_WINSOCK_ERROR          = "Init winsock error.";
const char* const SEM_SEM_INIT_ERROR              = "semaphore object init error.";
const char* const SEM_THREAD_RUN_ONCE             = "thread::run() can be call only once.";
const char* const SEM_CREATE_PIPE_ERROR           = "Fail to create pipe.";
const char* const SEM_CURL_MULTI_WAIT_ERROR       = "curl_multi_wait error.";
const char* const SEM_STREAM_READ_ERROR           = "Stream read error.";
const char* const SEM_STREAM_WRITE_ERROR          = "Stream write error.";
const char* const SEM_CANNOT_CREATE_FILE          = "Cannot create file '%s'. %s.";
const char* const SEM_CANNOT_OPEN_FILE            = "Cannot open file '%s'. %s.";
const char* const SEM_SET_FILE_STREAM_SIZE_ERR    = "Error setting file stream size.";

///////////////////////////////////////////////////////////////////////////////

#endif  // _EXCEPTION_MSGS_H_
