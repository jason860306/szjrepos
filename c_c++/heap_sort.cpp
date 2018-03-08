/**
 * ============================================================================
 * @file    heap_sort.cpp
 *
 * @brief   
 * @details 
 *
 * @version 1.0  
 * @date    2013-04-08 10:48:27
 *
 * @author  shizhijie, shizhijie@baofeng.com
 * ============================================================================
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <iterator>
using namespace std;

void print_ivec(vector<int>::iterator begin, vector<int>::iterator end)
{
    for(;begin != end; ++begin)
        cout << *begin << '\t';
    cout << endl;
}

int main(/*int argc, char* argv[]*/)
{
	int A[] = {1, 4, 2, 8, 5, 7};
	const int N = sizeof(A) / sizeof(int);
	cout << "orgin: \t\t";
	copy(A, A+N, ostream_iterator<int>(cout, " "));
	cout << endl;

	cout << "make_heap: \t";
	make_heap(A, A+N);
	copy(A, A+N, ostream_iterator<int>(cout, " "));
	cout << endl;

	cout << "sort_heap: \t";
	sort_heap(A, A+N);
	copy(A, A+N, ostream_iterator<int>(cout, " "));
	cout << endl;
	
#if 0
    int a[] = {99, 76, 1, 12, 43, 32, 15, 22, 20, 30};

    vector<int> ivec(a, a + sizeof(a) / sizeof(a[0]));
    print_ivec(ivec.begin(), ivec.end());

    make_heap(ivec.begin(), ivec.end(), greater<int>());
//	  sort_heap(ivec.begin(), ivec.end(), greater<int>());
    print_ivec(ivec.begin(), ivec.end());
#if 0
    pop_heap(ivec.begin(), ivec.end());
    ivec.pop_back();
    print_ivec(ivec.begin(), ivec.end());

    ivec.push_back(99);
    push_heap(ivec.begin(), ivec.end());
    print_ivec(ivec.begin(), ivec.end());

    sort_heap(ivec.begin(), ivec.end());
    print_ivec(ivec.begin(), ivec.end());
#endif

#endif
    return 0;
}

#if 0
int main(int argc, char* argv[])
{
    priority_queue<int, vector<int>, greater<int>() > pq;
    pq.push(676);
    pq.push(34);
    pq.push(23);
    while(!pq.empty())
    {
        cout << pq.top() << endl;
        pq.pop();
    }

    return 0;
}
#endif
