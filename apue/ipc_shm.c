/**
 * ============================================================================
 * @file    ipc_shm.c
 *
 * @brief   a test program to learn shm
 * @details 
 *
 * @version 1.0  
 * @date    Tue Dec 18 12:07:34 CST 2012
 *
 * @author  shizhijie, shizhijie@baofeng.com
 * ============================================================================
 */
#include <sys/shm.h>
#include "apue.h"

#define ARRAY_SIZE  40000
#define MALLOC_SIZE 100000
#define SHM_SIZE    100000
#define SHM_MODE    0600   /* user read/write */

#define err_sys printf

char array[ARRAY_SIZE];    /* uninitialized data = bss */

int main(void)
{
	int  shmid;
	char *ptr, *shmptr;
	
	printf("array[] from %1x to %1x\n", (unsigned long)&array[0],
		   (unsigned long)&array[ARRAY_SIZE]);
	printf("stack around %1x\n", (unsigned long)&shmid);
	
	if ((ptr = malloc(MALLOC_SIZE)) == NULL)
	{
		err_sys("malloc error");
	}
	printf("malloced from %1x to %1x\n", (unsigned long)ptr,
		   (unsigned long)ptr + MALLOC_SIZE);
	
	if ((shmid = shmget(IPC_PRIVATE, SHM_SIZE, SHM_MODE)) < 0)
	{
		err_sys("shmget error");
	}
	if ((shmptr = shmat(shmid, 0, 0)) == (void*)-1)
	{
		err_sys("shmat error");
	}
	printf("shared memory attached from %1x to %1x\n",
		   (unsigned long)shmptr, (unsigned long)shmptr + SHM_SIZE);
	
	if (shmctl(shmid, IPC_RMID, 0) < 0)
	{
		err_sys("shmctl error");
	}
	exit(0);
}
