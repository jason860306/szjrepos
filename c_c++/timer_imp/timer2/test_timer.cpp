#include <stdio.h>
#include <iostream>
#include <string>
#include <sys/types.h>
#include "timer_thread.h"

int handle_timeout()
{
    unsigned int time = get_system_clock();
    printf("time out, %u\n", time);
    return 0;
}

int main(int argc, char* argv[])
{
    my_timer t;
    t.open(1, handle_timeout);
    TIMER_MANAGE->registe(t);
    TIMER_MANAGE->start();
    getchar();
    return 0;
}
