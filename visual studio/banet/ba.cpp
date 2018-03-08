
#include<iostream>
#include<fstream>
#include<ctime>
#include<cstdlib>
#include<cstring>
#define N 5000                            //����Ľڵ������ɱ�ĸ���

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	int K[N] = { 0 };                 //�����ȵĴ���������
	float deg_rate[N] = { 0.0f };		//ÿ���ڵ㱻�½ڵ������ĸ��ʣ��������½ڵ�ļ����������ֵ
	int	k_ba = 0;                       //����Ķ���
	srand(int(time(0)));
	ofstream oba, obak, obakx, obaky;
	//ofstream om;
	//om.open("m.txt");
	oba.open("BA.txt");
	obak.open("BA_k.txt");
	obakx.open("BA_k_x.txt");
	obaky.open("BA_k_y.txt");
	cout << "�������ʼ����Ĺ�ģm0��" << endl;
	int m0;
	cin >> m0;
	cout << "�������½�����������m��m<m0����" << endl;
	int m;
	cin >> m;
	for (int i = 0; i<m0; i++)                                  //���ɳ�ʼ���磨������磩
	{
		for (int j = i + 1; j<m0; j++)
		{
			double a = rand() / double(RAND_MAX);
			if (a<0.5)
			{
				oba << i << "\t" << j << "\t" << endl;           //��ʾ���i,j��������
				K[i]++;											 //���i,j�Ķȷֱ��1
				K[j]++;
				k_ba += 2;
				deg_rate[i] = K[i] / float(k_ba);
				deg_rate[j] = K[j] / float(k_ba);
			}
		}
	}

	for (int p = m0; p<N; p++)                                 //�����¼ӽ��p��m���ߣ�û���߱����ǲ�ͬ�Ľ�㣬��p����������ڵ�����������
															   //ԭ����p-1����������p�����ĸ���Ϊk(i)/k��k(i)Ϊ���i�Ķȣ���i��k(i)�����������kΪp-1�������ܵĶ�������
	{
		int *pp = new int[m];                                  //������ָ̬��pp����ÿ�������ıߵ�����p��Ӧ����һ�����ı��
		memset(pp, 0, sizeof(int) * m);
		for (int n = 0; n<m;)								   //����m�����½ڵ�p�����ı߲���¼
		{
			float rate_sum = 0.0f;
			float r = rand() / float(RAND_MAX);
			int q = 0;                                         //����b����ķ�Χ�������ĸ����Ķ��ھ���ý������
			for (; q < p + 1; ++q)
			{
				rate_sum += deg_rate[q];
				if (rate_sum > r)
				{
					break;
				}
			}
			if (q == p + 1)
			{
				continue;
			}

			/*
			int b = rand() % k_ba;                             //���������b��������k_ba���Ǹ�����Ӧ�Ķȷ�Χ�ڣ�����ý��������k_ba��ǰp-1�����Ķ��ſ���ÿ������ռһ���֣�������b��֤��ǰ�����ӵĸ��ʣ�
			do
			{
				b -= K[q];
			} while (b > 0 && q++ < N);
			*/
			int a_nod = 0;                                     //���ڱ�֤ÿ�������߲��غϣ��ⲿ�ֿ��������⣡��Ϊ������ܳ������Σ�5  2�� 5  2�����󣡣�
			for (int k = 0; k<n; k++)                          //a_nod�����ж��Ƿ������b����غ�
			{
				if (pp[k] == q)
				{
					a_nod++;
					break;
				}
			}
			if (a_nod == 0)
			{
				pp[n] = q;
				oba << p << "\t" << q << "\t" << endl;             //������غϣ���������p��q-1�������ӹ�ϵ
				K[q]++;
				++n;
			}
		}
		K[p] = m;												//��¼�����½��ĳ�ʼ��m
		k_ba += 2 * m;                                          //������������
		delete[] pp;

		/* ���½ڵ㱻�½ڵ����ӵĸ���ֵ */
		for (int i = 0; i < p + 1; ++i)
		{
			deg_rate[i] = K[i] / float(k_ba);
		}
	}
	for (int l = 0; l<N; l++)	                              //���ÿ���������Ӧ�Ķ���
		obak << l + 1 << "\t" << K[l] << "\t" << endl;
	int M = 0;                                              //����Ҫ��¼����Ķȷֲ��������ͳ�ƶ���K��i���Ľ��ĸ���
	for (int h = 0; h<N; h++)                                  //�Ƚ����н��Ķ������ҵ����ȣ�Ȼ���1����������ÿ����㣬�ҵ���ÿ���ȶ�Ӧ�Ľ���������û�н���ж�Ӧֵ�öȣ���������������������һ�����������ܲ�̫�ã�
	{
		if (M<K[h])
			M = K[h];
	}
	int *s = new int[M];                                   //�ö�ָ̬��s��¼��Ϊt�Ľ��ĸ���
	memset(s, 0, sizeof(int) * M);
	for (int t = 0; t < M; t++)
	{
		for (int c = 0; c<N; c++)
		{
			if (K[c] == t)
				s[t]++;
		}
	}
	for (int g = 0; g<M; g++)                                   //����ȷֲ����
	{
		if (s[g] != 0)
		{
			obakx << g + 1 << endl;
			obaky << s[g] << endl;
		}
	}
	oba.close();
	obak.close();
	obakx.close();
	obaky.close();
	delete[] s;
	cout << k_ba << endl;

	system("pause");

	return 0;
}