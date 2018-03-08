/**
 * ============================================================================
 * @file    c011_lambda.cpp
 *
 * @brief   
 * @details 
 *
 * @version 1.0  
 * @date    2013-02-18 17:22:02
 *
 * @author  shizhijie, shizhijie@baofeng.com
 * ============================================================================
 */

#include <algorithm>
#include <vector>
#include <iostream>

class CTest
{
public:
	CTest() : m_nData(20) {}

public:
	void TestLambda()
	{
		std::vector<int> vctTmp;
		vctTmp.push_back(1);
		vctTmp.push_back(2);

		// 无函数对象，输出：1 2
		{
			std::for_each(vctTmp.begin(), vctTmp.end(),
						  [](int v)
						  {
							  std::cout << v << std::endl;
						  }
				);
		}

		// 以值方式傳遞作用域内所有可见的局部变量（包括this），输出：11 12
		{
			int a = 10;
			std::for_each(vctTmp.begin(), vctTmp.end(),
						  [=](int v)
						  {
							  std::cout << v + a << std::endl;
						  }
				);
		}

		// 以引用方式传递作用域内所有可见的局部变量（包括this），输出：11 13 12
		{
			int a = 10;
			std::for_each(vctTmp.begin(), vctTmp.end(),
						  [&](int v) mutable
						  {
							  std::cout << v + a++ << std::endl;
						  }
				);
			std::cout << a << std::endl;
		}

		// 以值方式传递局部变量a，输出：11 13 10
		{
			int a = 10;
			std::for_each(vctTmp.begin(), vctTmp.end(),
						  [a](int v) mutable
						  {
							  std::cout << v + a++ << std::endl;
						  }
				);
			std::cout << a << std::endl;
		}

		// 以引用方式传递局部变量a，输出：11 13 12
		{
			int a = 10;
			std::for_each(vctTmp.begin(), vctTmp.end(),
						  [&a](int v)
						  {
							  std::cout << v + a++ << std::endl;
						  }
				);
			std::cout << a << std::endl;
		}

		// 传递this，输出：21 22
		{
			std::for_each(vctTmp.begin(), vctTmp.end(),
						  [this](int v)
						  {
							  std::cout << v + m_nData << std::endl;
						  }
				);
		}

		// 除b按引用传递外，其它均按值传递，输出：11 12 17
		{
			int a = 10, b = 15;
			std::for_each(vctTmp.begin(), vctTmp.end(),
						  [=, &b](int v)
						  {
							  std::cout << v + a << std::endl;
							  ++b;
						  }
				);
			std::cout << b << std::endl;
		}

		// 操作数重载函数参数按引用传递，输出：2 3
		{
			std::for_each(vctTmp.begin(), vctTmp.end(), [](int &v) { ++v; });
			std::for_each(vctTmp.begin(), vctTmp.end(),
						  [](int v)
						  {
							  std::cout << v << std::endl;
						  }
				);
		}

		// 空的Lambda表达式
		{
			[](){}();
			[]{}();
		}
	}
	
private:
	int m_nData;
};

int main(void)
{
	CTest tmpTest;
	tmpTest.TestLambda();

	return 0;
}
