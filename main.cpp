#include "vector.hpp"
#include "vector_iterator.hpp"
#include <vector>
#include <iostream>
#include <vector>

#define NAMESPACE ft
// #define NAMESPACE std

int main ()
{
  NAMESPACE::vector<int> ft;

  NAMESPACE::vector<int>::reverse_iterator it;
  NAMESPACE::vector<int>::reverse_iterator truc = ft.rend();
  (void)truc;
  // truc = ft.begin();
  (void)it;
  return 0;
}