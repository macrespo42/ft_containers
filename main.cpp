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

void beginEnd_test(void)
{
  std::vector<int> myvector;
  for (int i=1; i<=5; i++) myvector.push_back(i);

    std::cout << "myvector contains:";
  for (std::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';
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

void size_test(void)
{
  std::vector<int> myints;
  std::cout << "0. size: " << myints.size() << '\n';

  for (int i=0; i<10; i++) myints.push_back(i);
    std::cout << "1. size: " << myints.size() << '\n';

  // myints.insert (myints.end(),10,100);
  // std::cout << "2. size: " << myints.size() << '\n';

  // myints.pop_back();
  // std::cout << "3. size: " << myints.size() << '\n';
}

void reserve_test(void)
{
  std::vector<int>::size_type sz;

  std::vector<int> foo;
  sz = foo.capacity();
  std::cout << "making foo grow:\n";
  for (int i=0; i<100; ++i) {
    foo.push_back(i);
    if (sz!=foo.capacity()) {
      sz = foo.capacity();
      std::cout << "capacity changed: " << sz << '\n';
    }
  }

  NAMESPACE::vector<int> bar;
  sz = bar.capacity();
  bar.reserve(100);   // this is the only difference with foo above
  std::cout << "making bar grow:\n";
  for (int i=0; i<100; ++i) {
    bar.push_back(i);
    if (sz!=bar.capacity()) {
      sz = bar.capacity();
      std::cout << "capacity changed: " << sz << '\n';
    }
  }
}

void empty_test(void)
{
  NAMESPACE::vector<int> myvector;
  int sum (0);

  for (int i=1;i<=10;i++) myvector.push_back(i);

    while (!myvector.empty())
    {
      sum += myvector.back();
      myvector.pop_back();
    }

    std::cout << "total: " << sum << '\n';
  }

  void resize_test(void)
  {
    NAMESPACE::vector<int> myvector;

  // set some initial content:
    for (int i=1;i<10;i++) myvector.push_back(i);

      myvector.resize(5);
    myvector.resize(8,100);
    myvector.resize(12);

    std::cout << "myvector contains:";
    for (size_t i=0;i<myvector.size();i++)
      std::cout << ' ' << myvector[i];
    std::cout << '\n';
  }

  void push_back_test(void)
  {
    NAMESPACE::vector<int> myvector;

    for (int i = 0; i < 10; i++)
      myvector.push_back(i);  
    std::cout << "myvector stores " << int(myvector.size()) << " numbers.\n";
  }

  void pop_back_test(void)
  {
    NAMESPACE::vector<int> myvector;
    int sum (0);
    myvector.push_back (100);
    myvector.push_back (200);
    myvector.push_back (300);

    while (!myvector.empty())
    {
      sum+=myvector.back();
      myvector.pop_back();
    }

    std::cout << "The elements of myvector add up to " << sum << '\n';
  }

  void at_test(void)
  {
  NAMESPACE::vector<int> myvector (10);   // 10 zero-initialized ints

  // assign some values:
  for (unsigned i=0; i<myvector.size(); i++)
    myvector.at(i)=i;

  std::cout << "myvector contains:";
  for (unsigned i=0; i<myvector.size(); i++)
    std::cout << ' ' << myvector.at(i);
  std::cout << '\n';
}

void front_test(void)
{
  NAMESPACE::vector<int> myvector;

  myvector.push_back(78);
  myvector.push_back(16);

  // now front equals 78, and back 16

  myvector.front() -= myvector.back();

  std::cout << "myvector.front() is now " << myvector.front() << '\n';
}

void back_test(void)
{
  NAMESPACE::vector<int> myvector;

  myvector.push_back(10);

  while (myvector.back() != 0)
  {
    myvector.push_back ( myvector.back() -1 );
  }

  std::cout << "myvector contains:";
  for (unsigned i=0; i<myvector.size() ; i++)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';
}

void comparaison_test(void)
{
  NAMESPACE::vector<int> foo (3,100);   // three ints with a value of 100
  NAMESPACE::vector<int> bar (2,200);   // two ints with a value of 200

  if (foo==bar) std::cout << "foo and bar are equal\n";
  // if (foo!=bar) std::cout << "foo and bar are not equal\n";
  // if (foo< bar) std::cout << "foo is less than bar\n";
  // if (foo> bar) std::cout << "foo is greater than bar\n";
  // if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
  // if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
}

int main ()
{
    // vectorConstructor_test();
    // vectorAssignation_test();
    // beginEnd_test();
    // rendRbegin_test();
    // size_test();
    // reserve_test();
  // empty_test();
  // push_back_test();
  // pop_back_test();
  // at_test();
  // front_test();
  // back_test();
  comparaison_test();
  return 0;
}