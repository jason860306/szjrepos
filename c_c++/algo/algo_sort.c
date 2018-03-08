/**
 * ============================================================================
 * @file    algo_sort.c
 *
 * @brief   
 * @details 
 *
 * @version 1.0  
 * @date    2013-04-08 10:00:35
 *
 * @author  shizhijie, shizhijie@baofeng.com
 * ============================================================================
 */

#include <stdio.h>

#define ARRAY_SIZE 10

int main() 
{
    int arr[ARRAY_SIZE] = {51,116,53,120,85,66,71,98,86,100};
    int i, j;
    for(i = 0; i < ARRAY_SIZE; i++)
        for(j = 0; j < ARRAY_SIZE-1; j++)
            if(arr[j] > arr[j+1]) {
                arr[j] ^= arr[j+1];
                arr[j+1] ^= arr[j];
                arr[j] ^= arr[j+1];
            }
    for(i = 0; i < ARRAY_SIZE; i++)
        printf("%c", arr[i],arr[i]);
//		printf("%d ", arr[i],arr[i]);
	
	return 0;
}
