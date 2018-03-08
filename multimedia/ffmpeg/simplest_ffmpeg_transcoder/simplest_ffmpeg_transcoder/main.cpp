// live_media_encoder.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vld.h>
#include <vldapi.h>
#include <stdlib.h>
#include <crtdbg.h>
#include <liveupstrm.h>
#include "getopt.h"
#include "live_upload_stream.h"
#ifdef WIN32
#include <Windows.h>
#endif

static const char help[] = { "help" };
static const char channel_id[] = { "channel_id" };
static const char addr[] = { "addr" };
static const char fname[] = { "file" };

static const char* const opt = "hc:a:f:";
static const struct option long_opts[] = {
	{ help,			no_argument,	   NULL, 'h' },
	{ channel_id,	required_argument, NULL, 'c' },
	{ addr,			required_argument, NULL, 'a' },
	{ fname,		required_argument, NULL, 'f' },
	{ NULL,			no_argument,	   NULL,  0  },
};

static void usage(const char *app);
static int parse_addr(const char *addr_str, std::string &host, uint16_t &port);
#ifdef WIN32
static BOOL ctrl_handler(DWORD fdw_ctrl_type);
#endif

/**
 * @brief µ÷ÊÔ²ÎÊý
 * arg1: -c D096AED4718E79B97F2E3A58B0FC2183 -a 103.15.202.149:6081 -f D:\Media\Videos\123.mp4
 * arg2: -c D096AED4718E79B97F2E3A58B0FC2183 -a 192.168.200.81:6081 -f D:\Media\Videos\123.mp4
 */

int _tmain(int argc, _TCHAR* argv[])
{
#ifdef WIN32
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	VLDEnable();
#endif

	if (argc < 2)
	{
		usage(argv[0]);
		return -1;
	}

#ifdef WIN32
	if (!SetConsoleCtrlHandler((PHANDLER_ROUTINE)ctrl_handler, TRUE))
	{
		fprintf(stderr, "\nERROR: Could not set control handler"); 
		return 1;
	}
#endif

	srand(static_cast<uint32_t>(time(NULL)));

	std::string channel_id, media_file, uploadmgr_host;
	uint16_t uploadmgr_port = 0;

	int c = 0, idx = 0;
	while ((c = getopt(argc, argv, opt)) != -1)
	{
		switch (c)
		{
		case 'h':
			usage(argv[0]);
			return 0;
		case 'c':
			channel_id.assign(optarg);
			break;
		case 'a':
			if (0 != parse_addr(optarg, uploadmgr_host, uploadmgr_port))
			{
				return -1;
			}
			break;
		case 'f':
			media_file.assign(optarg);
			break;
		default:
			usage(argv[0]);
			return 0;
		}
	}

	if (optind < argc)
	{
		fprintf(stderr, "non-option ARGV-elements: ");
		while (optind < argc)
		{
			fprintf(stderr, "%s ", argv[optind++]);
		}
		return -1;
	}

	live_upload_stream::instance()->init(channel_id,
		uploadmgr_host, uploadmgr_port, media_file);
	live_upload_stream::instance()->wait();

	return 0;
}

static void usage(const char *app)
{
	fprintf(stderr,
		"usage: %s\n"
		"  -h --help display the help msg and quit.\n"
		"  -c --channel_id the channel id to push stream\n"
		"  -a --addr uploadmgr's address\n"
		"  -f --file the file to read.\n"
		,app);
}

static int parse_addr(const char *addr_str, std::string &host, uint16_t &port)
{
	if (NULL == addr_str)
	{
		return -1;
	}
	const char *p = NULL;
	if (NULL == (p = strstr(addr_str, ":")))
	{
		return -1;
	}
	host.assign(addr_str, p);
	port = atoi(p + 1);
	return 0;
}

#ifdef WIN32
static BOOL ctrl_handler(DWORD fdw_ctrl_type)
{
	switch (fdw_ctrl_type)
	{
// 	case CTRL_CLOSE_EVENT:
// 		fprintf(stdout, "got close event, live_upload_stream exit.\n" );
	case CTRL_C_EVENT:
		fprintf(stdout, "got Ctrl-C event, live_upload_stream exit.\n" );
		live_upload_stream::instance()->close();
		return TRUE;
	default:
		return FALSE;
	}
}
#endif
