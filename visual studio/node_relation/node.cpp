// node_relation.cpp : �������̨Ӧ�ó������ڵ㡣
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

#define MAXVEX 10000 /* ��󶥵���,Ӧ���û����� */
#define EDGE_DELRATE (10 / 100.0) /* ɾ���ߵĸ��� */
#define AUC_RANGE 1 /* AUCȡֵ�����ֵ */
#define AUC_STEP 0.5 /* ��AUCȡֵ��Χ��ȡֵ�Ĳ��� */
typedef char VertexType; /* ��������Ӧ���û����� */
typedef int EdgeType; /* ���ϵ�Ȩֵ����Ӧ���û����� */

typedef struct EdgeNode/* �߱���  */
{
	int adjvex;/* �ڽӵ���,�洢�ö����Ӧ���±� */
	EdgeType weight;/* ���ڴ洢Ȩֵ,���ڷ���ͼ���Բ���Ҫ */
	struct EdgeNode *next; /* ����,ָ����һ���ڽӵ� */
} EdgeNode;

typedef struct VextexNode/* ������� */
{
	VertexType data;/* ������,�洢������Ϣ,�˴�������Ϣ����ö���Ķ� */
	EdgeNode *firstedge;/* �߱�ͷָ�� */
} VextexNode, AdjList[MAXVEX];

typedef struct
{
	AdjList adjList;
	int numNodes, numEdges; /* ͼ�е�ǰ�������ͱ��� */
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

	// �ı����ݵĶ���ʹ�����node1��node2��
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

	// ɾ������Ϊ�ܽڵ��������EDGE_DELRATE�Ľڵ�
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
		// �������Ľڵ�1
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
				// �õ���j�ڵ�����
				continue;
			}
			// �ҵ���j�ڵ㲻�����Ľڵ�
			// �������Ľڵ�2
			int shared_node_num = 0;
			pe2 = Gp.adjList[k].firstedge;
			degree2 = Gp.adjList[k].data;
			for (; pe1 != NULL; pe1 = pe1->next)
			{
				for (; pe2 != NULL; pe2 = pe2->next)
				{
					if (pe1->adjvex == pe2->adjvex)
					{
						// �������Ľڵ�1�ͽڵ�2�Ĺ�ͬ�ھӽڵ����
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
		Gp.adjList[i].firstedge = NULL;/* ���߱���Ϊ�ձ� */
	}

	return true;
}

bool create_graph()
{
	int n1 = 0, n2 = 0;
	EdgeNode *pe = NULL;
	for (int k = 0; k < Gp.numEdges; k++)/* �����߱� */
	{
		n1 = node1[k];
		n2 = node2[k];

		pe = (EdgeNode *)malloc(sizeof(EdgeNode));
		memset(pe, 0, sizeof(EdgeNode));
		pe->adjvex = n2;/* �ڽ����Ϊj */
		pe->weight = 1;
		/* ��pe��ָ��ָ��ǰ������ָ��Ľ�� */
		pe->next = Gp.adjList[n1].firstedge;
		Gp.adjList[n1].firstedge = pe;/* ����ǰ�����ָ��ָ��pe */
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
    	// ɾ���ýڵ�
		if (tmp_pe == NULL)
		{
			// firstedge��ΪҪɾ���Ľڵ�
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
    	// ɾ���ýڵ�
		if (tmp_pe == NULL)
		{
			// firstedge�ڵ㼴ΪҪɾ���Ľڵ�
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
