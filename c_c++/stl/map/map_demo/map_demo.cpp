// map_demo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <time.h>
#include <map>

#define Q_SERVER 1
#define Q_SRVNUM 5000000

//struct define////////////////////////////////////////////////////////////
struct TConDstSrvInfo
{
	unsigned char m_nServerType;
	unsigned short m_nServerIndex;
	//function
	TConDstSrvInfo() : m_nServerType(0), m_nServerIndex(0)
	{

	}
	TConDstSrvInfo(unsigned char nServerType, unsigned short nServerIndex)
	{
		m_nServerType = nServerType;
		m_nServerIndex = nServerIndex;
	}
	unsigned int GetWeight() const
	{
		unsigned int nWeight = ((m_nServerType << 16) & 0xffff0000) + m_nServerIndex;
		return nWeight;
	}
	bool operator<(const TConDstSrvInfo& ConDstSrvInfo) const
	{
		return (GetWeight() < ConDstSrvInfo.GetWeight());
	}
	bool operator==(const TConDstSrvInfo& ConDstSrvInfo) const
	{
		return ((m_nServerType == ConDstSrvInfo.m_nServerType) && (m_nServerIndex == ConDstSrvInfo.m_nServerIndex));
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	srand((unsigned int)time(NULL));

	TConDstSrvInfo srvInfo;
	int i = 0;
	std::map<TConDstSrvInfo, int> mapSrvInfo;
	for (; i < Q_SRVNUM; ++i)
	{
		srvInfo.m_nServerType = Q_SERVER;
		srvInfo.m_nServerIndex = i;
		mapSrvInfo.insert(std::make_pair(srvInfo, i));
	}

	std::map<TConDstSrvInfo, int>::size_type num = mapSrvInfo.size();

	i = rand() % Q_SRVNUM;

	for (; i < 2 * Q_SRVNUM; ++i)
	{
		srvInfo.m_nServerType = Q_SERVER;
		srvInfo.m_nServerIndex = i;
		mapSrvInfo.insert(std::make_pair(srvInfo, i));
	}
	num = mapSrvInfo.size();

	return 0;
}
