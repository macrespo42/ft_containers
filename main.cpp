#include "vector.hpp"
#include "vector_iterator.hpp"
#include <vector>
#include <iostream>
#include <vector>

#define NAMESPACE ft
// #define NAMESPACE std

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
  rendRbegin_test();
  return 0;
}