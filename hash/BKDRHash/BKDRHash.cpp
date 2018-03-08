// BKDRHash.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define STRLEN 15
#define DICLEN 10000

typedef char* TYPE;
typedef int BOOL;

typedef struct _NODE{
	TYPE data;
	struct _NODE* next;
}NODE;

typedef struct _HASH_TABLE{
	NODE* phead;           //此变量可以不用，这里使用是为了减少其他函数中的重新定义过程
	NODE** chainhash;
}HASH_TABLE;

static unsigned int BKDRhash(TYPE key);
static NODE* create_node();
static HASH_TABLE* create_hash();
static BOOL insert_data(HASH_TABLE* hash, NODE* phead, TYPE data);
static NODE* find_data(HASH_TABLE* hash, NODE* phead, TYPE data);
static BOOL del_data(HASH_TABLE* hash, NODE* phead, TYPE data);
static BOOL alter_data(HASH_TABLE* hash, NODE* phead, TYPE data, TYPE new_data);

int _tmain(int argc, _TCHAR* argv[])
{
	unsigned int m_uiHashBase[100] = { 0 };
	int m_uiHashLen = 100, m_uiHashTime = 10, uiSqrt = 0, flag = 0;
	uiSqrt = (unsigned int)::sqrt((double)m_uiHashLen);
	int i = 0, j = 0, k = 0;

	for (i = m_uiHashLen, j = 0; j < m_uiHashTime; i--)
	{
		flag = 1;

		for (k = 2; k <= uiSqrt; k++)
		{
			if (i%k == 0)
			{
				flag = 0;
				break;
			}
		}

		if (flag == 1)
		{
			m_uiHashBase[j] = i;
			printf("CMultiHash::%s m_uiHashBase[%u]: %u\n", __FUNCTION__, j, m_uiHashBase[j]);
			j++;
		}
	}

#if 0
	int i = 0;
	char* testdata = "//////////////////\n";
	char data[STRLEN + 2] = { 0 };

	HASH_TABLE* dic = create_hash();

	FILE* fp = fopen("ReadMe.txt", "r+");
	assert(fp != 0);

	while (i < DICLEN){
		fgets(data, STRLEN + 2, fp);
		insert_data(dic, dic->phead, data);
		i++;
	}

	//查找测试
	if (find_data(dic, dic->phead, testdata) != NULL)
		printf("find it: %s\n", (find_data(dic, dic->phead, testdata))->data);
	else
		printf("no this data!\n");

	//删除再查找测试
	if (del_data(dic, dic->phead, testdata) == 1)
		printf("delete it!\n");
	else
		printf("try again!\n");

	if (find_data(dic, dic->phead, testdata) != NULL)
		printf("find it: %s\n", (find_data(dic, dic->phead, testdata))->data);
	else
		printf("no this data!\n");

	//修改数据测试
	testdata = "fpwdwpk";
	char* newdata = "bibibibibiu\n";

	if (alter_data(dic, dic->phead, testdata, newdata) == 1){

		if (find_data(dic, dic->phead, newdata) != NULL)
			printf("find it: %s\n", (find_data(dic, dic->phead, newdata))->data);
		else
			printf("no this data!\n");
	}

	fclose(fp);
	free(dic);
#endif

	return 0;
}

static unsigned int BKDRhash(TYPE key)
{//BKDRhash函数
	unsigned int seed = 131;
	unsigned int hash = 0;

	while (*key != '\n' && *key != 0)      //通常使用时，判别条件为*key != 0即可，此处的*key != '\n'是因笔者程序需要
		hash = hash * seed + (*key++);

	return hash % DICLEN;
}

static NODE* create_node()
{//开辟节点
	NODE* pnode = (NODE*)malloc(sizeof(NODE));
	memset(pnode, 0, sizeof(NODE));

	pnode->data = (char*)malloc(STRLEN * sizeof(char));
	memset(pnode->data, 0, STRLEN * sizeof(char));
	pnode->next = NULL;

	return pnode;
}

static HASH_TABLE* create_hash()
{//创建hash表
	HASH_TABLE* new_hash_table = (HASH_TABLE*)malloc(sizeof(HASH_TABLE));
	memset(new_hash_table, 0, sizeof(HASH_TABLE));

	new_hash_table->phead = create_node();
	new_hash_table->chainhash = (NODE**)malloc(DICLEN * sizeof(NODE*));

	for (int i = 0; i < DICLEN; i++){
		new_hash_table->chainhash[i] = (NODE*)malloc(sizeof(NODE));
		memset(new_hash_table->chainhash[i], 0, sizeof(NODE));
	}

	return new_hash_table;
}

static BOOL insert_data(HASH_TABLE* hash, NODE* phead, TYPE data)
{//插入新数据
	if (hash == NULL)
		return 0;

	if (hash->chainhash[BKDRhash(data)]->data == NULL){
		NODE* newnode = create_node();

		strcpy(newnode->data, data);
		newnode->next = NULL;
		hash->chainhash[BKDRhash(data)]->data = newnode->data;
		hash->chainhash[BKDRhash(data)]->next = newnode->next;

		free(newnode);
		return 1;
	}

	else{
		phead = hash->chainhash[BKDRhash(data)];

		while (phead->next != NULL)
			phead = phead->next;

		phead->next = create_node();

		strcpy(phead->next->data, data);
		phead->next->next = NULL;

		return 1;
	}
}

static NODE* find_data(HASH_TABLE* hash, NODE* phead, TYPE data)
{//查找数据
	phead = hash->chainhash[BKDRhash(data)];

	if (hash == NULL)
		return NULL;

	while (phead != NULL){

		if ((phead->data != NULL) && (strncmp(phead->data, data, STRLEN) == 0))
			return phead;
		else
			phead = phead->next;
	}

	return NULL;
}

static BOOL del_data(HASH_TABLE* hash, NODE* phead, TYPE data)
{//删除数据

	phead->next = create_node();
	phead->next = hash->chainhash[BKDRhash(data)];

	if (hash == NULL)
		return 0;

	while (phead->next != NULL){

		if (strncmp(phead->next->data, data, STRLEN) == 0){

			if (phead->next->data == hash->chainhash[BKDRhash(data)]->data)
				hash->chainhash[BKDRhash(data)] = phead->next->next;
			else
				phead->next = phead->next->next;

			return 1;
		}
		else
			phead->next = phead->next->next;
	}

	free(phead->next);

	return 0;
}

static BOOL alter_data(HASH_TABLE* hash, NODE* phead, TYPE data, TYPE new_data)
{//修改数据
	if (hash == NULL)
		return 0;

	if (data == new_data)
		return 1;

	if (del_data(hash, phead, data) == 1){

		if (insert_data(hash, phead, new_data) == 1)
			return 1;
		else
			return 0;
	}

	else
		return 0;
}