/**
 * ============================================================================
 * @file    multi_thd_demo.c
 *
 * @brief   
 * @details 
 *
 * @version 1.0  
 * @date    2013-09-28 16:50:12
 *
 * @author  shizhijie, shizhijie@baofeng.com
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>

#define THD_NUM 3

typedef enum thd_type_e
{
	THD_TYPE_DEFAULT = 0,
	THD_TYPE_FILE_IO,
	THD_TYPE_CALC_PI,
} thd_type_t;

static void *thd_fun(void *arg);
static void normal_fun();
static void file_io();
static void calc_pi();

int main(void)
{
	pthread_t thd_id[THD_NUM] = { 0 };
	pthread_attr_t thd_attr[THD_NUM];
	int ret, i;
	memset(&thd_attr, 0, THD_NUM * sizeof(pthread_attr_t));

	for (i = 0; i < THD_NUM; ++i)
	{
		pthread_attr_init(&thd_attr[i]);
		ret = pthread_create(&thd_id[i], &thd_attr[i], &thd_fun, &i);
		if (ret != 0)
		{
			fprintf(stderr, "Can't create thread: %s - %d\n", strerror(ret), errno);
			return -1;
		}
	}
/*
	for (i = 0; i < THD_NUM; ++i)
	{
		pthread_join(thd_id[i], NULL);
	}
*/
	while (1)
	{
		usleep(2 * 1.0e6);
	}

	return 0;
}

static void *thd_fun(void *arg)
{
	if (NULL == arg)
	{
		return NULL;
	}
	thd_type_t type = *(thd_type_t *)arg;
	switch (type)
	{
	case THD_TYPE_DEFAULT:
		normal_fun();
		break;
	case THD_TYPE_FILE_IO:
		file_io();
		break;
	case THD_TYPE_CALC_PI:
		calc_pi();
		break;
	default:
		break;
	}
	return arg;
}

static void normal_fun()
{
	int i = 0;
	while (++i < 1.0e5);
}

static void file_io()
{
	FILE *file = fopen("/home/szj0306/fdemo", "rw");
	if (NULL == file)
	{
		fprintf(stderr, "Can't create file: %s\n", strerror(errno));
		return;
	}

	while (1)
	{
		if (ftell(file) == 5 * 1024 * 1024)
		{
			(void)fseek(file, 0L, SEEK_CUR);
		}
		const char wbuf[] = "a multi-thread program to indecate the usage of "
			"multi-debugger for gdb.\n";
		fwrite(wbuf, sizeof(const char), sizeof(wbuf), file);
		fflush(file);
	}
	
	fclose(file);
}

static void calc_pi()
{
	const int ARRSIZE = 101000; //定义数组大小，显示位数
	char x[ARRSIZE], z[ARRSIZE]; //x[0] x[1] . x[2] x[3] x[4] .... x[ARRSIZE-1]
	int a=1, b=3, c, d, Run=1, Cnt=0;

	memset(x,0,ARRSIZE);
	memset(z,0,ARRSIZE);

	x[1] = 2;
	z[1] = 2;

	while(Run && (++Cnt<200000000))
	{
		//z*=a;
		d = 0;
		int i;
		for(i=ARRSIZE-1; i>0; i--)
		{
			c = z[i]*a + d;
			z[i] = c % 10;
			d = c / 10;
		}
		//z/=b;
		d = 0;
		for(i=0; i<ARRSIZE; i++)
		{
			c = z[i]+d*10;
			z[i] = c / b;
			d = c % b;
		}
		//x+=z;
		Run = 0;
		for(i=ARRSIZE-1; i>0; i--)
		{
			c = x[i] + z[i];
			x[i] = c%10;
			x[i-1] += c/10;
			Run |= z[i];
		}
		a++;
		b+=2;
	}
	fprintf(stdout, "calc %d times\n", Cnt);
	fprintf(stdout, "Pi=%d%d.\n", x[0],x[1]);
}
