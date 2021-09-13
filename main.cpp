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

  NAMESPACE::vector<int>::iterator it;
  NAMESPACE::vector<int>::iterator truc = ft.end();
  (void)truc;
  // truc = ft.begin();
  (void)it;
  return 0;
}