// demo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
// remove algorithm example
#include <iostream>     // std::cout
#include <algorithm>    // std::remove

#include "range.h"
#include "range_queue.h"

int _tmain(int argc, _TCHAR* argv[])
{
    //std::vector<range> rng_vec;
    //rng_vec.push_back(range::zero_range());
    //rng_vec.push_back(range(10, 200));
    //rng_vec.push_back(range(300, 500));
    //rng_vec.push_back(range(3, 81));
    //rng_vec.push_back(range(30, 91));
    //rng_vec.push_back(range(300, 391));

    //range_queue rng_q(rng_vec), res_rng_q;

    //range_sub_range_queue(rng_vec[2], rng_q, res_rng_q);

    //range_queue rq;
    //range r;

    //r.set(1587582, 2045);
    //rq += r;

    //r.set(1648998, 39068);
    //rq += r;

    //printf("rq = %s\n", rq.to_string().c_str());

    //r.set(1633420, 15578);
    //rq += r;

    //printf("rq = %s\n", rq.to_string().c_str());

    //printf("don't delete it until it download completely or timeout to become");

    int myints[] = {10,20,30,30,20,10,10,20};      // 10 20 30 30 20 10 10 20

    // bounds of range:
    int* pbegin = myints;                          // ^
    int* pend = myints+sizeof(myints)/sizeof(int); // ^                       ^
    std::vector<int> intv(pbegin, pend);

    //pend = std::remove (pbegin, pend, 20);         // 10 30 30 10 10 ?  ?  ?
    //                                               // ^              ^

    //for (int* p=pbegin; p!=pbegin + 8; ++p)
    //    std::cout << ' ' << *p;
    //std::cout << '\n';

    //std::cout << "range contains:";
    //for (int* p=pbegin; p!=pend; ++p)
    //    std::cout << ' ' << *p;
    //std::cout << '\n';

    for (std::vector<int>::const_iterator citer = intv.begin(); citer != intv.end(); ++citer)
    {
        std::cout << ' ' << *citer;
    }
    std::cout << '\n';

    std::vector<int>::iterator iend = std::remove (intv.begin(), intv.end(), 20);
    for (std::vector<int>::const_iterator citer = intv.begin(); citer != intv.end(); ++citer)
    {
        std::cout << ' ' << *citer;
    }
    std::cout << '\n';

    for (std::vector<int>::const_iterator citer = intv.begin(); citer != iend; ++citer)
    {
        std::cout << ' ' << *citer;
    }
    std::cout << '\n';

    return 0;
}