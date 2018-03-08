// poly_demo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

class Base
{
public:
    Base() : pStr("this is base class: "), index(100) {}
    virtual void func(int x) { cout << pStr << x <<endl; }
    virtual const char * getStr() const { return pStr; }
    virtual int getIndex() const { return index; }

    const char *pStr;
    const int index;
};

class SubBase:public Base
{
public:
    SubBase() : pStr("this is the sub base: "), idx(101) {}
    void func(int x) { cout << pStr << x << endl; }
    virtual const char * getStr() const { return pStr; }
    virtual int getIndex() const { return idx; }

    const char *pStr;
    const int idx;
}; 
void test(/*const */Base &c)
{
    c.func(5);
    const char *pStr = c.getStr();
    std::cout << c.getStr() << std::endl;
    int index = c.getIndex();
    std::cout << c.getIndex() << std::endl;

    const char *pName = typeid(c).name();
    if (0 == strcmp(pName, "class SubBase"))
    {
        SubBase &subC = dynamic_cast<SubBase &>(c);
        subC.func(6);
        std::cout << subC.pStr << std::endl;
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
    Base bc;
    SubBase sc;
    test(bc);
    test(sc);
    getchar();

    return 0;
}