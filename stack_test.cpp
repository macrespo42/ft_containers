#include "unit_test.hpp"

void stack_stackConstructor_test(void)
{
  std::deque<int> mydeque (3,100);
  vector<int> myvector (2,200);     
  stack<int> first;
  stack<int> second (mydeque);
  stack<int,vector<int> > third;
  stack<int,vector<int> > fourth (myvector);
  std::cout << "size of first: " << first.size() << '\n';
  std::cout << "size of second: " << second.size() << '\n';
  std::cout << "size of third: " << third.size() << '\n';
  std::cout << "size of fourth: " << fourth.size() << '\n';
}

void stack_empty_test(void)
{
  stack<int> mystack;
  int sum (0);
  for (int i=1;i<=10;i++) mystack.push(i);
    while (!mystack.empty())
    {
     sum += mystack.top();
     mystack.pop();
   }
  std::cout << "total: " << sum << '\n';
}

void stack_size_test(void)
{
  stack<int> myints;
  std::cout << "0. size: " << myints.size() << '\n';
  for (int i=0; i<5; i++) myints.push(i);
    std::cout << "1. size: " << myints.size() << '\n';
  myints.pop();
  std::cout << "2. size: " << myints.size() << '\n';
}

void stack_top_test(void)
{
  stack<int> mystack;
  mystack.push(10);
  mystack.push(20);
  mystack.top() -= 5;
  std::cout << "mystack.top() is now " << mystack.top() << '\n';
}

void stack_push_test(void)
{
  stack<int> mystack;
  for (int i=0; i<5; ++i) mystack.push(i);
    std::cout << "Popping out elements...";
 while (!mystack.empty())
 {
    std::cout << ' ' << mystack.top();
    mystack.pop();
  }
  std::cout << '\n';
}

void stack_pop_test(void)
{
  stack<int> mystack;
  for (int i=0; i<5; ++i) mystack.push(i);
    std::cout << "Popping out elements...";
  while (!mystack.empty())
  {
    std::cout << ' ' << mystack.top();
    mystack.pop();
  }
  std::cout << '\n';
}

int stack_unit_test(void)
{
  stack_stackConstructor_test();
  stack_empty_test();
  stack_size_test();
  stack_top_test();
  stack_push_test();
  stack_pop_test();
  return 0;
}