// lambda.cpp : Defines the entry point for the console application.
//
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

#include "stdafx.h"
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

		// �޺������������1 2
		{
			std::for_each(vctTmp.begin(), vctTmp.end(),
						  [](int v)
						  {
							  std::cout << v << std::endl;
						  }
				);
		}

		// ��ֵ��ʽ���f�����������пɼ��ľֲ�����������this���������11 12
		{
			int a = 10;
			std::for_each(vctTmp.begin(), vctTmp.end(),
						  [=](int v)
						  {
							  std::cout << v + a << std::endl;
						  }
				);
		}

		// �����÷�ʽ���������������пɼ��ľֲ�����������this���������11 13 12
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

		// ��ֵ��ʽ���ݾֲ�����a�������11 13 10
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

		// �����÷�ʽ���ݾֲ�����a�������11 13 12
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

		// ����this�������21 22
		{
			std::for_each(vctTmp.begin(), vctTmp.end(),
						  [this](int v)
						  {
							  std::cout << v + m_nData << std::endl;
						  }
				);
		}

		// ��b�����ô����⣬��������ֵ���ݣ������11 12 17
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

		// ���������غ������������ô��ݣ������2 3
		{
			std::for_each(vctTmp.begin(), vctTmp.end(), [](int &v) { ++v; });
			std::for_each(vctTmp.begin(), vctTmp.end(),
						  [](int v)
						  {
							  std::cout << v << std::endl;
						  }
				);
		}

		// �յ�Lambda���ʽ
		{
			[](){}();
			[]{}();
		}
	}
	
private:
	int m_nData;
};

int _tmain(int argc, _TCHAR* argv[])
{
    CTest tmpTest;
    tmpTest.TestLambda();

    return 0;
}