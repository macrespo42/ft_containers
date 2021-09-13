#include "vector.hpp"
#include "vector_iterator.hpp"
#include <vector>
#include <iostream>
#include <vector>

#define NAMESPACE ft
// #define NAMESPACE std

void vectorConstructor_test(void)
{
  // constructors used in the same order as described above:
  NAMESPACE::vector<int> first;                                // empty vector of ints
  NAMESPACE::vector<int> second (4,100);                       // four ints with value 100
  NAMESPACE::vector<int> third (second.begin(),second.end());  // iterating through second
  NAMESPACE::vector<int> fourth (third);                       // a copy of third

  // the iterator constructor can also be used to construct from arrays:
  int myints[] = {16,2,77,29};
  NAMESPACE::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

  std::cout << "The contents of fifth are:";
  for (NAMESPACE::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';
}

void vectorAssignation_test(void)
{
  std::vector<int> foo (3,0);
  std::vector<int> bar (5,0);

  bar = foo;
  foo = std::vector<int>();

  std::cout << "Size of foo: " << int(foo.size()) << '\n';
  std::cout << "Size of bar: " << int(bar.size()) << '\n';
}

void rendRbegin_test(void)
{
  NAMESPACE::vector<int> myvector (5);  // 5 default-constructed ints

  NAMESPACE::vector<int>::reverse_iterator rit = myvector.rbegin();

  int i=0;
  for (rit = myvector.rbegin(); rit!= myvector.rend(); ++rit)
    *rit = ++i;

  std::cout << "myvector contains:";
  for (NAMESPACE::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';
}

int main ()
{
  vectorConstructor_test();
  vectorAssignation_test();
  rendRbegin_test();
  return 0;
}