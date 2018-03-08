// node_relation.cpp : 定义控制台应用程序的入口点。
//
#ifdef WIN32
#include "stdafx.h"
#endif
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <ctime>

using namespace std;

#define MAXVEX 10000 /* 最大顶点数,应由用户定义 */
#define EDGE_DELRATE (10 / 100.0) /* 删除边的概率 */
#define AUC_RANGE 1 /* AUC取值的最大值 */
#define AUC_STEP 0.5 /* 在AUC取值范围内取值的步长 */
typedef char VertexType; /* 顶点类型应由用户定义 */
typedef int EdgeType; /* 边上的权值类型应由用户定义 */

typedef struct EdgeNode/* 边表结点  */
{
	int adjvex;/* 邻接点域,存储该顶点对应的下标 */
	EdgeType weight;/* 用于存储权值,对于非网图可以不需要 */
	struct EdgeNode *next; /* 链域,指向下一个邻接点 */
} EdgeNode;

typedef struct VextexNode/* 顶点表结点 */
{
	VertexType data;/* 顶点域,存储顶点信息,此处顶点信息保存该顶点的度 */
	EdgeNode *firstedge;/* 边表头指针 */
} VextexNode, AdjList[MAXVEX];

typedef struct
{
	AdjList adjList;
	int numNodes, numEdges; /* 图中当前顶点数和边数 */
} GraphAdjList;

static GraphAdjList Gp;
static vector<int> node1, node2;
static bool visited[MAXVEX] = { false };

bool load_node(const char *fname);
bool init_graph();
bool create_graph();
void del_edge_graph(int node_idx1, int node_idx2);
void DFS();
void traverseDFS();
bool graph_connected();
void destroy_graph();

#ifdef WIN32
int _tmain(int argc, _TCHAR* argv[])
#else
int main(int argc, char *argv[])
#endif
{
	srand(time(NULL));

	// 文本数据的读入和储存在node1和node2中
	const int SIZE = 100;
	char filename[SIZE];
    if (argc <= 1)
	{
	    cout << "Please enter the name of data file:";
	    cin.getline(filename, SIZE);
	}
	else if (argc >= 2)
	{
		strncpy(filename, argv[1], SIZE);
	}
	if (!load_node(filename))
	{
		return -1;
	}

	if (!init_graph())
	{
		return -2;
	}

	if (!create_graph())
	{
		return -3;
	}

	if (!graph_connected())
	{
		cout << "the orgin graph isn't connected." << endl;
		return -4;
	}

	// 删除总数为总节点个数比例EDGE_DELRATE的节点
	printf("edges will be deleted as follow: \n");
	const int edge_delnum = EDGE_DELRATE * Gp.numEdges;
	for (int i = 0; i < edge_delnum; ++i)
	{
	    int edge_delidx = rand() % Gp.numEdges;
	    int n1 = node1[edge_delidx], n2 = node2[edge_delidx];
		printf("%05d - %05d\n", n1, n2);
		del_edge_graph(n1, n2);
	}

	if (!graph_connected())
	{
		cout << "graph hasn't been connected after delete some node with a rate." << endl;
		return -5;
	}

	EdgeNode *pe1 = NULL, *pe2 = NULL, *tmp_pe = NULL;
	int degree1 = 0, degree2 = 0;
	float auc = 0.0f;
	for (int j = 0; j < Gp.numNodes; ++j)
	{
		// 不相连的节点1
		pe1 = Gp.adjList[j].firstedge;
		if (pe1 == NULL)
		{
			continue;
		}
		degree1 = Gp.adjList[j].data;

		for (int k = 0; k < Gp.numNodes && k != j; ++k)
		{
			for (tmp_pe = pe1; tmp_pe != NULL; tmp_pe = tmp_pe->next)
			{
				if (k == tmp_pe->adjvex)
				{
					break;
				}
			}
			if (tmp_pe != NULL)
			{
				// 该点与j节点相连
				continue;
			}
			// 找到与j节点不相连的节点
			// 不相连的节点2
			int shared_node_num = 0;
			pe2 = Gp.adjList[k].firstedge;
			degree2 = Gp.adjList[k].data;
			for (; pe1 != NULL; pe1 = pe1->next)
			{
				for (; pe2 != NULL; pe2 = pe2->next)
				{
					if (pe1->adjvex == pe2->adjvex)
					{
						// 不相连的节点1和节点2的共同邻居节点个数
						++shared_node_num;
					}
				}
			}
			if (shared_node_num <= 0)
			{
				continue;
			}
			for (float a = 0; a < AUC_RANGE; a += AUC_STEP)
			{
				for (float b = 0; b < AUC_RANGE; b += AUC_STEP)
				{
					float power = pow(degree1, a) * pow(degree2, b);
					if (power <= 0.0f)
					{
						continue;
					}
					auc = shared_node_num / power;
					printf("auc:\n\tunlink node: %04d - %04d\n\tpower: "
						   "%.2f - %.2f\n\tshared_node_num: %d\n"
						   "value: %.2f\n\n", j, k, a, b, shared_node_num, auc);
				}
			}
		}
	}

	destroy_graph();
	return 0;
}

bool load_node(const char *fname)
{
	ifstream inFile;
	inFile.open(fname);
	if (!inFile.is_open())
	{
		cout << "Could not open the file" << fname << endl;
		cout << "Program terminating.\n";
		return false;
	}
	int a = 0, b = 0, c = 0;
	inFile >> a >> b;
	for (; inFile.good();)
	{
		node1.push_back(a);
		node2.push_back(b);
		cout << c << ' ' << a << ' ' << node1[c] << ' ' << b << ' ' << node2[c] << endl;
		++c;
		inFile >> a >> b;
	}
	// cout<<c<<' '<<node1.size()<<endl;
	if (inFile.eof())
		cout << "End of file reached.\n";
	else if (inFile.fail())
		cout << "Input terminnated by data mismatch.\n";
	else
		cout << "Input terminated for unknown reason.\n";
	if (c == 0)
		cout << "No data processed.\n";
	inFile.close();

	return true;
}

bool init_graph()
{
	if (node2.empty())
	{
		cout << "the number of nodes is zero! maybe has't loaded node firstly!" << endl;
		return false;
	}
	Gp.numNodes = *node2.rbegin();
	Gp.numEdges = node2.size();
	if (Gp.numNodes > MAXVEX)
	{
		cout << "the number (" << Gp.numNodes << ") of nodes is too large (" << MAXVEX << ")!" << endl;
		return false;
	}
	for (int i = 0; i < MAXVEX/*Gp.numNodes*/; i++)
	{
		Gp.adjList[i].data = 0;
		Gp.adjList[i].firstedge = NULL;/* 将边表置为空表 */
	}

	return true;
}

bool create_graph()
{
	int n1 = 0, n2 = 0;
	EdgeNode *pe = NULL;
	for (int k = 0; k < Gp.numEdges; k++)/* 建立边表 */
	{
		n1 = node1[k];
		n2 = node2[k];

		pe = (EdgeNode *)malloc(sizeof(EdgeNode));
		memset(pe, 0, sizeof(EdgeNode));
		pe->adjvex = n2;/* 邻接序号为j */
		pe->weight = 1;
		/* 将pe的指针指向当前顶点上指向的结点 */
		pe->next = Gp.adjList[n1].firstedge;
		Gp.adjList[n1].firstedge = pe;/* 将当前顶点的指针指向pe */
		++Gp.adjList[n1].data;

		pe = (EdgeNode *)malloc(sizeof(EdgeNode));
		memset(pe, 0, sizeof(EdgeNode));
		pe->adjvex = n1;
		pe->weight = 1;
		pe->next = Gp.adjList[n2].firstedge;
		Gp.adjList[n2].firstedge = pe;
		++Gp.adjList[n2].data;
	}
	
	return true;
}

void del_edge_graph(int node_idx1, int node_idx2)
{
	EdgeNode *pe = Gp.adjList[node_idx1].firstedge, *tmp_pe = NULL;
    while (pe != NULL && pe->adjvex == node_idx2)
	{
		tmp_pe = pe;
		pe = pe->next;
	}
	if (pe == NULL)
	{
		return;
	}
    else
	{
    	// 删除该节点
		if (tmp_pe == NULL)
		{
			// firstedge即为要删除的节点
			Gp.adjList[node_idx1].firstedge = pe->next;
		}
		else
		{
	        tmp_pe->next = pe->next;
		}
		free(pe);
		pe = NULL;
	}

	pe = Gp.adjList[node_idx2].firstedge;
	tmp_pe = NULL;
	while (pe != NULL && pe->adjvex == node_idx1)
	{
		tmp_pe = pe;
		pe = pe->next;
	}
	if (pe == NULL)
	{
		return;
	}
    else
	{
    	// 删除该节点
		if (tmp_pe == NULL)
		{
			// firstedge节点即为要删除的节点
			Gp.adjList[node_idx2].firstedge = pe->next;
		}
		else
		{
		    tmp_pe->next = pe->next;
		}
		free(pe);
		pe = NULL;
	}
}

void DFS(int node_idx)
{
	visited[node_idx] = true;
	for (EdgeNode *pe = Gp.adjList[node_idx].firstedge; pe != NULL; pe = pe->next)
	{
		if (!visited[pe->adjvex])
		{
			DFS(pe->adjvex);
		}
	}
}

void traverseDFS()
{
	memset(visited, false, MAXVEX * sizeof(bool));
	for (int i = 0; i < Gp.numNodes; ++i)
	{
		if (!visited[i])
		{
			DFS(i);
		}
	}
}

bool graph_connected()
{
	memset(visited, false, MAXVEX * sizeof(bool));
	DFS(0);
	for (int i = 0; i < Gp.numNodes; ++i)
	{
		if (!visited[i])
		{
			return false;
		}
	}
	return true;
}

void destroy_graph()
{
	for (int i = 0; i < Gp.numNodes; ++i)
	{
		EdgeNode *pe = Gp.adjList[i].firstedge;
		while (pe != NULL)
		{
			pe = pe->next;
			free(pe);
			pe = NULL;
		}
	}
}
