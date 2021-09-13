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

  NAMESPACE::vector<int>::iterator it = ft.begin();
  (void)it;
  return 0;
}