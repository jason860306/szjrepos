/**
 *    @file       fastcounter.h
 *
 *    @brief      a fast counter for statistics
 *    @details    this is a multidimensional counter in multithread
 *
 *    @version    1.0
 *    @date       11/06/2012 02:12:37 PM
 *
 *    @author     wangtiefeng (), wangtf418@163.com
 */
#ifndef _FASTCOUNT_H_014A7681_50EC_4DCD_A1A8_730C21D76ECF_
#define _FASTCOUNT_H_014A7681_50EC_4DCD_A1A8_730C21D76ECF_
#include "framecommon/framecommon.h"
#include <string>

using namespace std;
using namespace MYFRAMECOMMON;

const int WRITE_LOG_INTERVAL_ONE_MIN = 60;
const int WRITE_LOG_INTERVAL_FIVE_MIN = 300;
const int WRITE_LOG_INTERVAL_TEN_MIN = 600;
const int WRITE_LOG_INTERVAL_ONE_HOUR = 3600;
const int WRITE_LOG_INTERVAL_ONE_DAY = 86400;

/**
 * @brief class CCounter
 * @details Counter for long long int with thread_mutex lock
 */
class CCounter
{
public:
	/**
	 * @brief constructor
	 * @details set m_Count = 0
	 * @param[in] nType, Counter type
	 * @param[in] strTypeName, Counter name
	 */
	CCounter(unsigned int nType, const string& strTypeName)
		: m_nType(nType), m_strTypeName(strTypeName)
	{

	}

	/**
	 * @brief destructor
	 */
	~CCounter()
	{

	}
public:
	/**  
	 * @brief add count num to m_Count
	 * @param[in] nCount, add count num
	 */
	inline void Count(int nCount)
	{
		m_Count.Add(nCount);
	}

	/**  
	 * @brief get value of m_Count
	 * @param[in] bIfClear, set m_Count = 0 if bIfClear is true
	 * @return the value of m_Count before clear
	 */
	long long GetCount(bool bIfClear)
	{
		long long nCount = m_Count.Get();
		if (bIfClear)
		{
			m_Count.Set(0);
		}
		return nCount;
	}

	/**
	 * @brief get Counter type
	 * @return the value of m_nType
	 */
	unsigned int GetType()
	{
		return m_nType;
	}

	/**
	 * @brief get Counter type
	 * @return the value of m_strTypeName
	 */
	string GetTypeName()
	{
		return m_strTypeName;
	}
private:
	unsigned int m_nType;	/**< Counter Type */
	string m_strTypeName;	/**< Counter Name */
	CAtomic32 m_Count;		/**< Total Count */
};


/**
 * @brief class CFastCounter
 * @details this class is a Counter group which is consisted of certern num CCounter
 * @see 
 */
class CFastCounter
{
public:
	/**
	 * @brief constructor
	 * @details set m_nCounterNum = 0, m_pCounters = NULL
	 */
	CFastCounter() : m_nCounterNum(0), m_pCounters(NULL)
	{

	}

	/**
	 * @brief destructor
	 * @details free array pointed by m_pCounters if m_pCounters is not NULL
	 */
	virtual ~CFastCounter()
	{
		m_rwLock.GetWriteLock();
		if (m_pCounters)
		{
			for(unsigned int nA = 0; nA < m_nCounterNum; nA ++)
			{
				if (m_pCounters[nA])
				{
					delete m_pCounters[nA];
				}
			}
			delete [] m_pCounters;
		}
		m_rwLock.ReleaseLock();
	}

	/** 
	 * @brief Init CFastCounter
	 * @details create counter array m_pCounters which has m_nCounterNum elements
	 * @param[in] strCounterName, Counter Name
	 * @param[in] nCounterNum, the length of counter array
	 * @retval 0, succeed
	 * @retval -1, fail, nCounterNum <= 0
	 */
	int Init(const string& strCounterName, int nCounterNum)
	{
		if (nCounterNum <= 0)
		{
			return -1;
		}
		CCounter** pCounters = new CCounter*[nCounterNum];
		memset(pCounters, 0, sizeof(CCounter*) * nCounterNum);

		m_rwLock.GetWriteLock();
		m_nCounterNum = nCounterNum;
		m_pCounters = pCounters;
		m_strCounterName = strCounterName;
		m_rwLock.ReleaseLock();

		struct timeval tvTmp;
		gettimeofday(&tvTmp, NULL);
		m_nBeginTime = tvTmp.tv_sec;
		return 0;
	}

	/**
	 * @brief add a new Counter to CFastCounter
	 * @details add a Counter which counter type is nType and counter name is strTypeName
	 * @param[in] nType, counter type
	 * @param[in] strTypeName, counter type
	 * @return 0, succeed; -1, fail
	 */
	inline int AddCounter(unsigned int nType, const string& strTypeName)
	{
		int nRet = -1;
		m_rwLock.GetWriteLock();
		if (nType < m_nCounterNum && m_pCounters[nType] == NULL)
		{
			m_pCounters[nType] = new CCounter(nType, strTypeName);
			nRet = 0;
		}
		m_rwLock.ReleaseLock();
		return nRet;
	}

	/**
	 * @brief add count to counter witch type is nType
	 * @param[in] nType, type of counter
	 * @param[in] nCount, number added to counter, the default value of nCount is 1
	 */
	void Count(unsigned int nType, long long nCount = 1)
	{
		m_rwLock.GetReadLock();
		if ((nType < m_nCounterNum) && m_pCounters[nType])
		{
			m_pCounters[nType]->Count(nCount);
		}
		m_rwLock.ReleaseLock();
	}

	/**
	 * @brief write the content of counters to log file
	 * @param[in] nLogType, the type of log which is writed to
	 * @param[in] bIfClean, flag to clear counter, the default value of bIfClear is true
	 */
	void WriteLog(int nLogType, bool bIfClear = false, int nIgnoreWindown = 100)
	{
		stringstream statStr;
		statStr.str("");
		statStr << "<<" << m_strCounterName << ">>:";

		struct timeval tvTmp;
		gettimeofday(&tvTmp, NULL);

		long long nStatSec = tvTmp.tv_sec - m_nBeginTime;
		statStr << "last " << nStatSec << " sec:";
		if (bIfClear)
		{
			m_nBeginTime = tvTmp.tv_sec;
		}

		m_rwLock.GetReadLock();
		long long nCountTmp = 0;
		for (unsigned int nA = 0; nA < m_nCounterNum; nA ++)
		{
			if (m_pCounters[nA])
			{
				nCountTmp = m_pCounters[nA]->GetCount(bIfClear);
				if (nCountTmp >= nIgnoreWindown)
				{
					statStr << "[" << m_pCounters[nA]->GetTypeName() << ":" << nCountTmp << "]";
				}
			}
		}
		m_rwLock.ReleaseLock();
		WRITE_ALL_LOG(nLogType, "%s", statStr.str().c_str());
	}

private:
	long long m_nBeginTime;
	string m_strCounterName;
	unsigned int m_nCounterNum;
	CCounter** m_pCounters;
	CThreadRwLock m_rwLock;
};

#endif



