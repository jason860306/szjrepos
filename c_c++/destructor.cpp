#include <iostream>

class destructor
{
public:
    destructor();
    void release();
    ~destructor();
};

destructor::destructor()
{
    std::cout << __FUNCTION__ << std::endl;
}

destructor::~destructor()
{
    std::cout << __FUNCTION__ << std::endl;
}

void destructor::release()
{
    delete this;
    std::cout << __FUNCTION__ << std::endl;
}

int main(void)
{
    // destructor de;
    destructor *de_ptr = new destructor();
    de_ptr->release();
    // delete de_ptr;
    // de_ptr = NULL;

	destructor *pp_des[3] = { NULL, NULL, NULL };
	for (int i = 0; i < 3; ++i)
	{
		pp_des[i] = new destructor();
	}

	delete[] pp_des;
	
	for (int i = 0; i < 3; ++i)
	{
		delete pp_des[i];
		pp_des[i] = NULL;
	}
}
