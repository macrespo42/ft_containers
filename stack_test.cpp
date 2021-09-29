#include "stack_test.hpp"

namespace sta
{
  void stackConstructor_test(void)
  {
    // std::deque<int> mydeque (3,100);
    // NAMESPACE::vector<int> myvector (2,200);

    // NAMESPACE::stack<int> first;
    // NAMESPACE::stack<int> second (mydeque);

    // NAMESPACE::stack<int,NAMESPACE::vector<int> > third;
    // NAMESPACE::stack<int,NAMESPACE::vector<int> > fourth (myvector);

    // std::cout << "size of first: " << first.size() << '\n';
    // std::cout << "size of second: " << second.size() << '\n';
    // std::cout << "size of third: " << third.size() << '\n';
    // std::cout << "size of fourth: " << fourth.size() << '\n';
  }

  void empty_test(void)
  {
    NAMESPACE::stack<int> mystack;
    int sum (0);

    for (int i=1;i<=10;i++) mystack.push(i);

      while (!mystack.empty())
      {
       sum += mystack.top();
       mystack.pop();
     }

     std::cout << "total: " << sum << '\n';
   }

   void size_test(void)
   {
    NAMESPACE::stack<int> myints;
    std::cout << "0. size: " << myints.size() << '\n';

    for (int i=0; i<5; i++) myints.push(i);
      std::cout << "1. size: " << myints.size() << '\n';

    myints.pop();
    std::cout << "2. size: " << myints.size() << '\n';
  }

  void top_test(void)
  {
    NAMESPACE::stack<int> mystack;

    mystack.push(10);
    mystack.push(20);

    mystack.top() -= 5;

    std::cout << "mystack.top() is now " << mystack.top() << '\n';
  }

  void push_test(void)
  {
    NAMESPACE::stack<int> mystack;

    for (int i=0; i<5; ++i) mystack.push(i);

      std::cout << "Popping out elements...";
    while (!mystack.empty())
    {
     std::cout << ' ' << mystack.top();
     mystack.pop();
   }
   std::cout << '\n';
 }

 void pop_test(void)
 {
  NAMESPACE::stack<int> mystack;

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
      // stackConstructor_test();
  empty_test();
  size_test();
  top_test();
  push_test();
  pop_test();
  return 0;
}
}