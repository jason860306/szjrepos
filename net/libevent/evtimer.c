/**
 * ============================================================================
 * @file    evtimer.c
 *
 * @brief   
 * @details 
 *
 * @version 1.0  
 * @date    2013-09-24 17:30:55
 *
 * @author  shizhijie, shizhijie@baofeng.com
 * ============================================================================
 */

#include <stdio.h>
#include <event.h>

static struct event ev;
static struct timeval tv;

void time_cb(int fd, short event, void *arg)
{
	printf("fd = %d, event = %u, argv = 0x%d, timer wakeup\n", fd, event, arg);
	event_add(&ev, &tv);
}

int main()
{
	struct event_base *base = event_init();

	tv.tv_sec = 3;
	tv.tv_usec = 0;
	evtimer_set(&ev, time_cb, NULL);
	event_add(&ev, &tv);
	event_base_dispatch(base);

	return 0;
}
