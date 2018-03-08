
#include<iostream>
#include<fstream>
#include<ctime>
#include<cstdlib>
#include<cstring>
#define N 5000                            //网络的节点数，可变的更大

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	int K[N] = { 0 };                 //将结点度的存入数组中
	float deg_rate[N] = { 0.0f };		//每个节点被新节点相连的概率，会随着新节点的加入而更新其值
	int	k_ba = 0;                       //网络的度数
	srand(int(time(0)));
	ofstream oba, obak, obakx, obaky;
	//ofstream om;
	//om.open("m.txt");
	oba.open("BA.txt");
	obak.open("BA_k.txt");
	obakx.open("BA_k_x.txt");
	obaky.open("BA_k_y.txt");
	cout << "请输入初始网络的规模m0：" << endl;
	int m0;
	cin >> m0;
	cout << "请输入新结点的新生边数m（m<m0）：" << endl;
	int m;
	cin >> m;
	for (int i = 0; i<m0; i++)                                  //生成初始网络（随机网络）
	{
		for (int j = i + 1; j<m0; j++)
		{
			double a = rand() / double(RAND_MAX);
			if (a<0.5)
			{
				oba << i << "\t" << j << "\t" << endl;           //表示结点i,j是相连的
				K[i]++;											 //结点i,j的度分别加1
				K[j]++;
				k_ba += 2;
				deg_rate[i] = K[i] / float(k_ba);
				deg_rate[j] = K[j] / float(k_ba);
			}
		}
	}

	for (int p = m0; p<N; p++)                                 //生成新加结点p的m条边，没条边必须是不同的结点，即p不能与任意节点两次相连！
															   //原来的p-1个结点各自与p相连的概率为k(i)/k（k(i)为结点i的度，即i与k(i)个结点相连，k为p-1个结点的总的度数。）
	{
		int *pp = new int[m];                                  //创建动态指针pp储存每条新增的边的与结点p对应的另一个结点的编号
		memset(pp, 0, sizeof(int) * m);
		for (int n = 0; n<m;)								   //生成m条与新节点p相连的边并记录
		{
			float rate_sum = 0.0f;
			float r = rand() / float(RAND_MAX);
			int q = 0;                                         //搜索b落入的范围，即在哪个结点的度内就与该结点相连
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
			int b = rand() % k_ba;                             //生成随机数b；它落入k_ba的那个结点对应的度范围内，即与该结点相连（k_ba将前p-1个结点的度排开，每个结点度占一部分，这样的b保证了前面链接的概率）
			do
			{
				b -= K[q];
			} while (b > 0 && q++ < N);
			*/
			int a_nod = 0;                                     //用于保证每条新生边不重合（这部分可能有问题！因为输出可能出现两次：5  2； 5  2的现象！）
			for (int k = 0; k<n; k++)                          //a_nod用于判断是否随机数b造成重合
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
				oba << p << "\t" << q << "\t" << endl;             //如果不重合，则输出结点p和q-1结点的连接关系
				K[q]++;
				++n;
			}
		}
		K[p] = m;												//记录生成新结点的初始度m
		k_ba += 2 * m;                                          //结点度总数更新
		delete[] pp;

		/* 更新节点被新节点连接的概率值 */
		for (int i = 0; i < p + 1; ++i)
		{
			deg_rate[i] = K[i] / float(k_ba);
		}
	}
	for (int l = 0; l<N; l++)	                              //输出每个结点和其对应的度数
		obak << l + 1 << "\t" << K[l] << "\t" << endl;
	int M = 0;                                              //下面要记录网络的度分布情况，即统计度是K（i）的结点的个数
	for (int h = 0; h<N; h++)                                  //先将所有结点的度排序，找到最大度，然后从1到最大度搜索每个结点，找到，每个度对应的结点数，如果没有结点有对应值得度，则不输出它。（这是我想的一个方法！可能不太好）
	{
		if (M<K[h])
			M = K[h];
	}
	int *s = new int[M];                                   //用动态指针s记录度为t的结点的个数
	memset(s, 0, sizeof(int) * M);
	for (int t = 0; t < M; t++)
	{
		for (int c = 0; c<N; c++)
		{
			if (K[c] == t)
				s[t]++;
		}
	}
	for (int g = 0; g<M; g++)                                   //输出度分布情况
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