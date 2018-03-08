#include <iostream>     // std::cout
#include <iterator>     // std::distance
#include <list>         // std::list

int main () {
  std::list<int> mylist;
  for (int i=0; i<10; i++) mylist.push_back (i*10);
  std::ostream_iterator<int> out_it (std::cout,", ");
  std::copy(mylist.begin(), mylist.end(), out_it);
  std::cout << std::endl;

  std::list<int>::iterator first = mylist.begin();
  std::list<int>::iterator last = mylist.end();
  std::list<int>::iterator iter = std::find(mylist.begin(), mylist.end(), 40);
  if (iter == mylist.end())
  {
	  std::cout << "don't find the value 40" << std::endl;
	  return 0;
  }

  std::cout << "The distance is: " << distance(first,last) << '\n';
  std::cout << "The distance from " << *first << " to " << *iter << " is: " << distance(first, iter) << std::endl;

  return 0;
}
