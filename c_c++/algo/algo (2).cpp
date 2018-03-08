#include <algorithm>
#include <iterator>
#include <iostream>
#include <list>

int main(void)
{
	const int nNum = 6;
	int nArr[nNum] = { 0, 1, 2, 3, 4, 5 };
	int distance = std::distance(nArr, nArr + nNum + 1);
	std::copy(nArr, nArr + nNum, std::ostream_iterator<int>(std::cout, " "));
	printf("\ndistance(nArr, nArr + %d) = %d\n", nNum + 1, distance);

	std::list<int> nList;
	for (int i = 0; i < nNum; ++i)
	{
		nList.push_back(i);
	}
	std::copy(nList.begin(), nList.end(), std::ostream_iterator<int>(std::cout, " "));
	distance = std::distance(nList.begin(), nList.end());
	printf("\ndistance(nList.begin(), nList.end()) = %d\n", distance);

	return 0;
}
