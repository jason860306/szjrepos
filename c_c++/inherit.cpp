#include <ctime>
#include <iostream>

class A
{
public:
	virtual void print(void)
	{
		std::cout << __FILE__ << ":A:" << __FUNCTION__
			<< ":" << __LINE__ << std::endl;
	}

	virtual void print(double *d)
	{
		std::cout << __FILE__ << ":A:" << __FUNCTION__ << ":"
			<< __LINE__ << ":*d:" << *d << std::endl;
	}

	void print(const char *cstr)
	{
		std::cout << __FILE__ << ":A:" << __FUNCTION__ << ":"
			<< __LINE__ << ":cstr:" << cstr << std::endl;
	}

	virtual ~A()
	{
	}
};

class B : public A
{
public:
	using A::print;
	
	virtual void print(void)
	{
		std::cout << __FILE__ << ":B:" << __FUNCTION__
			<< ":" << __LINE__ << std::endl;
	}

	virtual void print(int n)
	{
		std::cout << __FILE__ << ":B:" << __FUNCTION__ << ":"
			<< __LINE__ << ":n:" << n << std::endl;
	}

	void print(const char *cstr)
	{
		std::cout << __FILE__ << ":B:" << __FUNCTION__ << ":"
			<< __LINE__ << ":cstr:" << cstr << std::endl;
	}

	virtual ~B()
	{
	}
};

int main(void)
{
	double *d = new double(1.0f * std::time(NULL));
	std::time_t t = std::time(NULL);
	B *b = new B();
	b->print();
	b->print(t);
	b->print(d);
	b->print(std::ctime(&t));
	dynamic_cast<A *>(b)->print(std::ctime(&t));
	delete d; d = NULL;
}
