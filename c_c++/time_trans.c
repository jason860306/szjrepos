/**
 * ============================================================================
 * @file    time_trans.c
 *
 * @brief   
 * @details 
 *
 * @version 1.0  
 * @date    2013-04-10 12:38:31
 *
 * @author  shizhijie, shizhijie@baofeng.com
 * ============================================================================
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(void)
{
#if 0	
	time_t nTmValue = time(NULL);
	srand(nTmValue);
	struct tm* pTmLocal = localtime(&nTmValue);
	printf("%s", asctime(pTmLocal));
	pTmLocal->tm_hour = 2;
	pTmLocal->tm_sec += 2000 * (rand() % 100) / 100;
	pTmLocal->tm_yday += 1;
	time_t nNextDay = mktime(pTmLocal);
	printf("%s", asctime(localtime(&nNextDay)));
#endif	

//#if 0
	struct tm *tmLocal = NULL;
	time_t tTime = time(NULL), nCurTime = tTime;
	tmLocal = localtime(&tTime);
	printf("%s", asctime(tmLocal));	
	tmLocal->tm_hour = 2;
	tmLocal->tm_min = 0;
	tmLocal->tm_sec = 0;
	int nPlanStartTime = (int)mktime(tmLocal);
	srand(nCurTime);
	unsigned int nRandomTime = 2000 * (rand() % 100) / 100;
	time_t nTrueStartTime = nPlanStartTime + nRandomTime;
	if (nTrueStartTime <= nCurTime)
	{
		nTrueStartTime += 86400;
	}
	printf("%s", asctime(localtime(&nTrueStartTime)));
	
	//if (nCurTime >= nTrueStartTime)
	{
		tTime = time(NULL);
		tmLocal = localtime(&tTime);
		tmLocal->tm_hour = 2;
		tmLocal->tm_min = 0;
		tmLocal->tm_sec = 0;
		nPlanStartTime = (int)mktime(tmLocal);
		nRandomTime = 2000 * (rand() % 100) / 100;
		nTrueStartTime = nPlanStartTime + 2 * 86400 + nRandomTime;
		time_t tPlanTime = nTrueStartTime;
		tmLocal = localtime(&tPlanTime);
		printf("%s", asctime(tmLocal));
	}
//#endif	
	
#if 0	
	time_t nTmValue = time(NULL);
	printf("nTmValue = %ld\n", nTmValue);

	srand(nTmValue);

	struct tm* pTmLocal = localtime(&nTmValue);
	printf("pTmLocal = %s", asctime(pTmLocal));
	
	pTmLocal->tm_hour = 2;
	pTmLocal->tm_min = 0;
	pTmLocal->tm_sec = 0;
	printf("pTmLocal = %s", asctime(pTmLocal));	

	time_t nStartTime = mktime(pTmLocal);
	printf("nStartTime = %ld\n", nStartTime);

	time_t nSpanTime = 3000;
	size_t nRandom = rand();
	printf("nRandom = %lu\nnRandom%%100 = %lu\n", nRandom, nRandom % 100);
	time_t nRandomTime = nSpanTime * (nRandom % 100) / 100;
	printf("nRandomTime = %ld\n", nRandomTime);

	time_t nPlanTime = nStartTime + 24 * 60 * 60 + nRandomTime;
	printf("nPlanTime = %ld\n", nPlanTime);
	printf("nPlanTime = %s\n", asctime(localtime(&nPlanTime)));
#endif
	
	return 0;
}
