/**
 *    @file       CmdCounter.h
 *
 *    @brief      command recv and send counters
 *    @details
 *
 *    @version    1.0
 *    @date       11/12/2012 05:54:07 PM
 *
 *    @author     wangtiefeng (), wangtf418@163.com
 */
#include "fastcounter.h"
const int INVALID_CMD_COUNTTYPE = 256;
const int COUNTERS_NUMBER = 257;

class CCmdCounter : public CFastCounter
{
private:
	CCmdCounter();
	~CCmdCounter();

public:
	static int Create();
	static int Destory();
	static CCmdCounter* GetHandler()
	{
		return m_hHandler;
	}

public:
	int Init();

private:
	static CCmdCounter* m_hHandler;
};

