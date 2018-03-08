// algo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <iostream>
#include <algorithm>

#define ARRAY_NUM 10

int _tmain(int argc, _TCHAR* argv[])
{
    int nArr[ARRAY_NUM] = {0};
    srand(static_cast<uint32_t>(time(NULL)));
    std::for_each(nArr, nArr + ARRAY_NUM,
        [](int &v)
        {
            v = rand() % ARRAY_NUM;
        }
    );
    std::cout << "before: ";
    std::for_each(nArr, nArr + ARRAY_NUM,
        [](int v)
        {
            std::cout << v << ' ';
        }
    );
    std::cout << std::endl;

    int *pBeg = &nArr[0], *pEnd = &nArr[ARRAY_NUM - 1];
    int nCom = nArr[rand() % ARRAY_NUM];
    std::cout << "compare: " << nCom << std::endl;
    while (pBeg < pEnd)
    {
        if (*pBeg < nCom)
        {
            std::swap(*pBeg, *pEnd);
            --pEnd;
        }
        else
        {
            ++pBeg;
        }
    }
    std::cout << "after: ";
    std::for_each(nArr, nArr + ARRAY_NUM,
        [](int v)
        {
            std::cout << v << ' ';
        }
    );
    std::cout << std::endl;

    std::cout << "boundary elem: " << *pBeg << std::endl;

    std::cin.get();

	return 0;
}