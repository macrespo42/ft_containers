#include "set.hpp"
#include <iostream>

bool fncomp (int lhs, int rhs) {return lhs<rhs;}

struct classcomp {
  bool operator() (const int& lhs, const int& rhs) const
  {return lhs<rhs;}
};

int set_constructor_test(void)
{
  ft::set<int> first;                           // empty set of ints

  int myints[]= {10,20,30,40,50};
  ft::set<int> second (myints,myints+5);        // range

  ft::set<int> third (second);                  // a copy of second

  ft::set<int> fourth (second.begin(), second.end());  // iterator ctor.

  ft::set<int,classcomp> fifth;                 // class as Compare

  bool(*fn_pt)(int,int) = fncomp;
  ft::set<int,bool(*)(int,int)> sixth (fn_pt);  // function pointer as Compare

  return 0;
}

int set_assignation_test(void)
{
  int myints[]={ 12,82,37,64,15 };
  ft::set<int> first (myints,myints+5);   // set with 5 ints
  ft::set<int> second;                    // empty set

  second = first;                          // now second contains the 5 ints
  first = std::set<int>();                 // and first is empty

  std::cout << "Size of first: " << int (first.size()) << '\n';
  std::cout << "Size of second: " << int (second.size()) << '\n';
  return 0;
}

int set_begin_end_test(void)
{
  int myints[] = {75,23,65,42,13};
  ft::set<int> myset (myints,myints+5);

  std::cout << "myset contains:";
  for (ft::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
    std::cout << ' ' << *it;

  std::cout << '\n';

  return 0;
}

int main(void)
{
    set_constructor_test();
    set_assignation_test();
    set_begin_end_test();
    return 0;
}