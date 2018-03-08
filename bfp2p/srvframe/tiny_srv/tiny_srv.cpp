#include "timer_srv.h"

int main(int /*argc*/, char */*argv*/[])
{
    timer_srv ts;
    CMyserver::SetServer(&ts);
    if (0 == ts.init_server()) {
        ts.start_server();
    }
    return 0;
}
