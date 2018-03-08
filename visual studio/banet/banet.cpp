// banet.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#if 0

#include<math.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

const int N=20;
int n;
int select(float bit[]);
class BA
{
public:
	int s,v,h;
	float max;					/* �ڵ㱻����ѡ�е������� */
	int a[N + 1][N + 1];		/* ����ba������� */
	int b[N + 1][N + 1];		/* �����½ڵ����¾��� */
	int k[(N + 1)*(N + 1)];		/* ÿ����Ķ��� */
	float num[(N + 1)*(N + 1)];	/* ÿ���ڵ㱻����ѡ�еĴ��� */
	float p[(N + 1)*(N + 1)];	/* ������ÿ���ڵ㱻�½ڵ����ӵĸ��� = �õ�Ķ� / ��������Ķ����ܺ� */
	void begin(BA &t);			/* �����ʼ���磬��ʼ�ڵ�����ͽڵ�Ķ�����Ϊ3 */
	void Getp(BA &t);			/* ���ÿ���ڵ㱻�½ڵ����ӵĸ��� */
	void Getsv(BA &t);
	void GetMaxNum(BA &t,int s,int v);
	void add(BA &t);
	void jlxs();
};

/* �������һ������ֵ��Ȼ���p[(N + 1)*(N + 1)]��ѡ���ǰ�����ۼӳ�������������ֵ�Ľڵ���� */
int select(float bit[])
{
	float bet=(float)rand()/RAND_MAX;
	int j=0;
	float psum=0.0;
	while (psum<bet)
	{
		psum=psum+bit[j];
		j=j+1;
	}
	return(j-1);
}

/* �����ʼ���磬��ʼ�ڵ�����ͽڵ�Ķ�����Ϊ3 */
void BA::begin(BA &t)
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(i==j)
				t.a[i][j]=0;
			else
				t.a[i][j]=1;
		}
	}
}

/* ���ÿ���ڵ㱻�½ڵ����ӵĸ��� */
void BA::Getp(BA &t)
{
	int sum = 0; /* ����ba����Ķ����ܺ� */
	for (int i = 0; i<n; i++)
	{
		t.k[i] = 0;
		for (int j = 0; j<n; j++)
		{
			sum += t.a[i][j];
			t.k[i] += t.a[i][j]; /* ���ÿ����Ķ��� */
		}
	}
	for (int i = 0; i<n; i++)
	{
		/*�����ÿ���㱻���ĸ��� = �õ�Ķ��� / ��������Ķ����ܺ͡�*/
		t.p[i] = float(t.k[i]) / float(sum);
	}
}

void BA::Getsv(BA &t)
{
	int i, j, k = 0;
	for (i = 0; i<10; i++)
	{
		t.num[i] = 0;
	}
	srand(1);
	for (j = 1; j <= 10; j++)
	{
		k = select(t.p);
		t.num[k] = t.num[k] + 1;
	}
}
void BA::GetMaxNum(BA &t, int s, int v)
{
	t.max = t.num[0];
	for (int i = 0; i<n; i++)
	{
		if (t.max <= t.num[i])
		{
			t.max = t.num[i];
			t.s = i;
		}
	}
	t.num[t.s] = 0;
	t.max = num[0];
	for (int i = 0; i<n; i++)
	{
		if (max <= num[i])
		{
			max = num[i];
			t.v = i;
		}
	}
}
void BA::add(BA &t)
{
	for (int i = 0; i<n + 1; i++)
	{
		for (int j = 0; j<n + 1; j++)
		{
			b[i][j] = 0;
			if (i<n&&j<n)
			{
				t.b[i][j] = t.a[i][j];
			}
			else if (i == n&&j == t.s)
			{
				t.b[i][j] = 1;
			}
			else if (i == t.s&&j == n)
			{
				t.b[i][j] = 1;
			}
			else if (i == n&&j == t.v)
			{
				t.b[i][j] = 1;
			}
			else if (i == t.v&&j == n)
			{
				t.b[i][j] = 1;
			}
			t.a[i][j] = t.b[i][j];
		}
	}
}
void BA::jlxs()
{
	double C;
	C = 9 * (log(1.5) - 1.0 / 3.0)*log(N - 2)*log(N - 2) / (N - 2);
	cout << "����ϵ����" << C << endl;
}

int main()
{
	BA t;
	t.begin(t);
	cout << "BA������ڽӾ���Ϊ:" << endl;
	for (n = 3; n<N; n++)
	{
		t.Getp(t);
		t.Getsv(t);
		t.GetMaxNum(t, t.s, t.v);
		t.add(t);
	}
	for (int i = 0; i<N; i++)
	{
		for (int j = 0; j<N; j++)
		{
			cout << t.b[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	t.jlxs();
}

#endif

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