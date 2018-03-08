/**
 * ============================================================================
 * @file    mapsrv.c
 *
 * @brief   
 * @details 
 *
 * @version 1.0  
 * @date    2013-10-30 18:26:34
 *
 * @author  shizhijie, shizhijie@baofeng.com
 * ============================================================================
 */

#include <stdlib.h>
#include <stddef.h>
#include <inttypes.h>
#include <string.h>
#include <assert.h>
#include <strings.h>
#include <arpa/inet.h>
#include "mapsrv.h"

static int cmp_loc(p_loc_t p_loc_lhs, p_loc_t p_loc_rhs)
{
	if (NULL == p_loc_lhs || NULL == p_loc_rhs)
	{
		return -1;
	}
	return (p_loc_lhs->latitude == p_loc_rhs->latitude &&
		p_loc_lhs->longitude == p_loc_rhs->longitude &&
		p_loc_lhs->coordinate == p_loc_rhs->coordinate);
}

static double distance_loc(p_loc_t p_loc_lhs, p_loc_t p_loc_rhs)
{
	(void)p_loc_lhs;
	(void)p_loc_rhs;
	return 0.0f;
}

static int copy_loc(p_loc_t p_loc_dst, p_loc_t p_loc_src)
{
	if (NULL == p_loc_dst || NULL == p_loc_src)
	{
		return -1;
	}
	p_loc_dst->latitude = p_loc_src->latitude;
	p_loc_dst->longitude = p_loc_src->longitude;
	p_loc_dst->coordinate = p_loc_src->coordinate;
	p_loc_dst->loctype = p_loc_src->loctype;
	return 0;
}

static int free_locnode(p_locnode_t p_locnode)
{
	if (NULL != p_locnode)
	{
		if (NULL != p_locnode->p_loc)
		{
			free(p_locnode->p_loc);
			p_locnode->p_loc = NULL;
		}
		free(p_locnode);
		p_locnode = NULL;
	}
	return 0;
}

/*
static int get_loclst_len(const p_loclst_t p_loclst)
{
	if (NULL == p_loclst)
	{
		return 0;
	}
	int loclst_len = 0;
	p_locnode_t node = NULL;
	for (node = p_loclst->p_loc_first; NULL != node; node = node->p_locnode_next)
	{
		loclst_len += sizeof(node->p_loc);
	}
	return loclst_len;
}
*/

/* 为了使问题清晰，先定义个函数 */
double swap_double(double* pdVal)
{
	UINT64 llVal = ntohll(*((UINT64*)pdVal));
	return *((double*)&llVal);
}

number64 swap_number64(number64 n) {

    /* swap 64 bits doubles */
	typedef union __convert_u {
		uint64_t i;
		number64 f;
	} convert_u;

	convert_u c;
	c.f = n;
	c.i = (((c.i & 0x00000000000000FFULL) << 56) |
		((c.i & 0x000000000000FF00ULL) << 40) |
		((c.i & 0x0000000000FF0000ULL) << 24) |
		((c.i & 0x00000000FF000000ULL) << 8)  |
		((c.i & 0x000000FF00000000ULL) >> 8)  |
		((c.i & 0x0000FF0000000000ULL) >> 24) |
		((c.i & 0x00FF000000000000ULL) >> 40) |
		((c.i & 0xFF00000000000000ULL) >> 56));
	return c.f;
}

int loc2buf(p_loc_t p_loc, char **pp_locbuf)
{
	if (NULL == p_loc || NULL == pp_locbuf)
	{
		return 0;
	}
	if (NULL != pp_locbuf && NULL == *pp_locbuf)
	{
		*pp_locbuf = (char *)malloc(sizeof(loc_t));
		if (NULL == *pp_locbuf)
		{
			return 0;
		}
		bzero(*pp_locbuf, sizeof(loc_t));
	}
	double latitude = htond(p_loc->latitude);
	memcpy(*pp_locbuf, (char *)&latitude, sizeof(latitude));
	double longitude = htond(p_loc->longitude);
	memcpy(*pp_locbuf + offsetof(loc_t, longitude), (char *)&longitude, sizeof(longitude));
	int coordinate = htonl(p_loc->coordinate);
	memcpy(*pp_locbuf + offsetof(loc_t, coordinate), (char *)&coordinate, sizeof(coordinate));
	int loctype = htonl(p_loc->loctype);
	memcpy(*pp_locbuf + offsetof(loc_t, loctype), (char *)&loctype, sizeof(loctype));
	return (sizeof(loc_t));
}

p_loc_t buf2loc(const char *p_locbuf, int len, pp_loc_t pp_loc)
{
	assert(len == sizeof(loc_t));
	if (NULL == p_locbuf || 0 == len || NULL == pp_loc)
	{
		return NULL;
	}
	if (NULL != pp_loc && NULL == *pp_loc)
	{
		*pp_loc = (p_loc_t)malloc(sizeof(loc_t));
		if (NULL == *pp_loc)
		{
			return NULL;
		}
		bzero(*pp_loc, sizeof(loc_t));
	}
	p_loc_t p_loc = *pp_loc;
	memcpy((char *)&p_loc->latitude, p_locbuf, sizeof(p_loc->latitude));
	p_loc->latitude = ntohd(p_loc->latitude);
	memcpy((char *)&p_loc->longitude, p_locbuf + offsetof(loc_t, longitude),
		sizeof(p_loc->longitude));
	p_loc->longitude = ntohd(p_loc->longitude);
	memcpy((char *)&p_loc->coordinate, p_locbuf + offsetof(loc_t, coordinate),
		sizeof(p_loc->coordinate));
	p_loc->coordinate = ntohl(p_loc->coordinate);
	memcpy((char *)&p_loc->loctype, p_locbuf + offsetof(loc_t, loctype),
		sizeof(p_loc->loctype));
	p_loc->loctype = ntohl(p_loc->loctype);
	return p_loc;
}

int loclst2buf(p_loclst_t p_loclst, char **pp_loclstbuf)
{
	if (NULL == p_loclst || NULL == pp_loclstbuf)
	{
		return 0;
	}
	if (NULL != pp_loclstbuf && NULL == *pp_loclstbuf)
	{
		*pp_loclstbuf = (char *)malloc(p_loclst->size);
		if (NULL == *pp_loclstbuf)
		{
			return 0;
		}
		bzero(*pp_loclstbuf, p_loclst->size);
	}
	int idx = 0;
	p_locnode_t node = NULL;
	for (node = p_loclst->p_loc_first; NULL != node; node = node->p_locnode_next)
	{
		p_loc_t p_loc = node->p_loc;
		int offset = ((idx++) * sizeof(loc_t));
		char *locbuf = (*pp_loclstbuf + offset);
		loc2buf(p_loc, &locbuf);
	}
	return (p_loclst->size);
}

p_loclst_t buf2loclst(const char *p_loclstbuf, int len, pp_loclst_t pp_loclst)
{
	assert ((len % sizeof(loc_t)) == 0);
	if (NULL == p_loclstbuf || 0 == len || NULL == pp_loclst)
	{
		return NULL;
	}
	if (NULL != pp_loclst && NULL == *pp_loclst)
	{
		*pp_loclst = (p_loclst_t)malloc(sizeof(loclst_t));
		if (NULL == *pp_loclst)
		{
			return NULL;
		}
		bzero(*pp_loclst, sizeof(loclst_t));
	}
	int loc_num = (len / sizeof(loc_t)), i = 0;
	for (i = 0; i < loc_num; ++i)
	{
		int offset = i * sizeof(loc_t);
		p_loc_t p_loc = NULL;
		p_loc = buf2loc(p_loclstbuf + offset, sizeof(loc_t), &p_loc);
		add_loc(*pp_loclst, p_loc);
		free(p_loc); p_loc = NULL;
	}

	return *pp_loclst;
}

int add_loc(p_loclst_t p_loclst, p_loc_t p_loc)
{
	if (NULL == p_loclst || NULL == p_loc)
	{
		return -1;
	}

	p_locnode_t p_node = (p_locnode_t)malloc(sizeof(locnode_t));
	if (NULL != p_node)
	{
		p_node->p_loc = (p_loc_t)malloc(sizeof(loc_t));
		copy_loc(p_node->p_loc, p_loc);
		p_node->p_locnode_next = p_node->p_locnode_prev = NULL;
		if (p_loclst->num == 0)
		{
			p_loclst->p_loc_first = p_loclst->p_loc_last = p_node;
		}
		else
		{
			p_loclst->p_loc_last->p_locnode_next = p_node;
			p_node->p_locnode_prev = p_loclst->p_loc_last;
			p_loclst->p_loc_last = p_node;
		}
		++(p_loclst->num);
		p_loclst->size += sizeof(loc_t);
		return 0;
	}
	return -1;
}

int del_loc(p_loclst_t p_loclst, p_loc_t p_loc)
{
	if (NULL == p_loc)
	{
		return -1;
	}
	p_locnode_t node = NULL;
	for (node = p_loclst->p_loc_first; node != NULL;
		 node = node->p_locnode_next)
	{
		if (cmp_loc(node->p_loc, p_loc) == 0)
		{
			if (node->p_locnode_next != NULL)
			{
				node->p_locnode_next->p_locnode_prev = node->p_locnode_prev;
			}
			if (node->p_locnode_prev != NULL)
			{
				node->p_locnode_prev->p_locnode_next = node->p_locnode_next;
			}
			if (node == p_loclst->p_loc_first)
			{
				p_loclst->p_loc_first = node->p_locnode_next;
			}
			if (node == p_loclst->p_loc_last)
			{
				p_loclst->p_loc_last = node->p_locnode_prev;
			}
			--(p_loclst->num);
			p_loclst->size -= sizeof(loc_t);
			free_locnode(node);
			break;
		}
	}
	return 0;
}

/**
 *@brief 在p_loclst中查找与p_loc距离小于等于distance的所有其它位置信息，
 *       保存在pp_loc中
 */
int find_loc(p_loclst_t p_loclst, p_loc_t p_loc, double distance, pp_loclst_t pp_loclst)
{
	if (NULL == pp_loclst)
	{
		return -1;
	}
	else if (NULL == *pp_loclst)
	{
		*pp_loclst = (p_loclst_t)malloc(sizeof(loclst_t));
		if (NULL == *pp_loclst)
		{
			return -1;
		}
	}
	
	p_locnode_t node = NULL;
	for (node = p_loclst->p_loc_first; node != NULL; node = node->p_locnode_next)
	{
		if (distance_loc(node->p_loc, p_loc) <= distance)
		{
			if (0 != add_loc(*pp_loclst, node->p_loc))
			{
				return -1;
			}
		}
	}
	return 0;
}
