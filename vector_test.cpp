#include "unit_test.hpp"
  void vec_vectorConstructor_test(void)
  {
  // constructors used in the same order as described above:
  vector<int> first;                                // empty vector of ints
  vector<int> second (4,100);                       // four ints with value 100
  vector<int> third (second.begin(),second.end());  // iterating through second
  vector<int> fourth (third);                       // a copy of third

  // the iterator constructor can also be used to construct from arrays:
  int myints[] = {16,2,77,29};
  vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

  std::cout << "The contents of fifth are:";
  for (vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';
}

  void vec_vectorAssignation_test(void)
  {
    vector<int> foo (3,0);
    vector<int> bar (5,0);

    bar = foo;
    foo = vector<int>();

    std::cout << "Size of foo: " << int(foo.size()) << '\n';
    std::cout << "Size of bar: " << int(bar.size()) << '\n';
  }

  void vec_beginEnd_test(void)
  {
    vector<int> myvector;
    for (int i=1; i<=5; i++) myvector.push_back(i);

      std::cout << "myvector contains:";
    for (vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
      std::cout << ' ' << *it;
    std::cout << '\n';
  }

  void vec_rendRbegin_test(void)
  {
    vector<int> myvector (5);  // 5 default-constructed ints

    vector<int>::reverse_iterator rit = myvector.rbegin();

    int i=0;
    for (rit = myvector.rbegin(); rit!= myvector.rend(); ++rit)
      *rit = ++i;

    std::cout << "myvector contains:";
    for (vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
      std::cout << ' ' << *it;
    std::cout << '\n';
  }

  void vec_size_test(void)
  {
    vector<int> myints;
    std::cout << "0. size: " << myints.size() << '\n';

    for (int i=0; i<10; i++) myints.push_back(i);
      std::cout << "1. size: " << myints.size() << '\n';

    myints.insert (myints.end(),10,100);
    std::cout << "2. size: " << myints.size() << '\n';

    myints.pop_back();
    std::cout << "3. size: " << myints.size() << '\n';
  }

  void vec_max_size_test(void)
  {
    vector<int> myvector;

    // set some content in the vector:
    for (int i=0; i<100; i++) myvector.push_back(i);

    std::cout << "size: " << myvector.size() << "\n";
    std::cout << "capacity: " << myvector.capacity() << "\n";
    std::cout << "max_size: " << myvector.max_size() << "\n";
  }

  void vec_resize_test(void)
  {
    vector<int> myvector;

    // set some initial content:
    for (size_t i=1;i<10;i++) myvector.push_back(i);

      myvector.resize(5);
    myvector.resize(8,100);
    myvector.resize(12);

    std::cout << "myvector contains:";
    for (size_t i=0;i<myvector.size();i++)
      std::cout << ' ' << myvector[i];
    std::cout << '\n';
  }

  void vec_capacity_test(void)
  {
    vector<int> myvector;

    // set some content in the vector:
    for (int i=0; i<100; i++) myvector.push_back(i);

    std::cout << "size: " << (int) myvector.size() << '\n';
    std::cout << "capacity: " << (int) myvector.capacity() << '\n';
    std::cout << "max_size: " << (int) myvector.max_size() << '\n';
  }

  void vec_reserve_test(void)
  {
    vector<int>::size_type sz;

    vector<int> foo;
    sz = foo.capacity();
    std::cout << "making foo grow:\n";
    for (int i=0; i<100; ++i) {
      foo.push_back(i);
      if (sz!=foo.capacity()) {
        sz = foo.capacity();
        std::cout << "capacity changed: " << sz << '\n';
      }
    }

    vector<int> bar;
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

  void vec_empty_test(void)
  {
    vector<int> myvector;
    int sum (0);

    for (int i=1;i<=10;i++) myvector.push_back(i);

      while (!myvector.empty())
      {
        sum += myvector.back();
        myvector.pop_back();
      }

      std::cout << "total: " << sum << '\n';
    }

  void vec_at_test(void)
  {
    vector<int> myvector (10);   // 10 zero-initialized ints

    // assign some values:
    for (unsigned i=0; i<myvector.size(); i++)
      myvector.at(i)=i;

    std::cout << "myvector contains:";
    for (unsigned i=0; i<myvector.size(); i++)
      std::cout << ' ' << myvector.at(i);
    std::cout << '\n';
  }

  void vec_front_test(void)
  {
    vector<int> myvector;

    myvector.push_back(78);
    myvector.push_back(16);

    // now front equals 78, and back 16

    myvector.front() -= myvector.back();

    std::cout << "myvector.front() is now " << myvector.front() << '\n';
  }

  void vec_back_test(void)
  {
    vector<int> myvector;

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

  void vec_assign_test(void)
  {
    vector<int> first;
    vector<int> second;
    vector<int> third;

    first.assign (7,100);             // 7 ints with a value of 100

    vector<int>::iterator it;
    it=first.begin()+1;

    second.assign (it,first.end()-1); // the 5 central values of first

    int myints[] = {1776,7,4};
    third.assign (myints,myints+3);   // assigning from array.

    std::cout << "Size of first: " << int (first.size()) << '\n';
    std::cout << "Size of second: " << int (second.size()) << '\n';
    std::cout << "Size of third: " << int (third.size()) << '\n';
  }

  void vec_push_back_test(void)
  {
    vector<int> myvector;

    for (int i = 0; i < 10; i++)
      myvector.push_back(i);  
    std::cout << "myvector stores " << int(myvector.size()) << " numbers.\n";
  }

  void vec_pop_back_test(void)
  {
    vector<int> myvector;
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

  void vec_erase_test(void)
  {
    vector<int> myvector;

    // set some values (from 1 to 10)
    for (int i=1; i<=10; i++) myvector.push_back(i);

    // erase the 6th element
      myvector.erase (myvector.begin()+5);

    // erase the first 3 elements:
    myvector.erase (myvector.begin(),myvector.begin()+3);

    std::cout << "myvector contains:";
    for (unsigned i=0; i<myvector.size(); ++i)
      std::cout << ' ' << myvector[i];
    std::cout << '\n';
  }

  void vec_swap_test(void)
  {
    vector<int> foo (3,100);   // three ints with a value of 100
    vector<int> bar (5,200);   // five ints with a value of 200

    foo.swap(bar);

    std::cout << "foo contains:";
    for (unsigned i=0; i<foo.size(); i++)
      std::cout << ' ' << foo[i];
    std::cout << '\n';

    std::cout << "bar contains:";
    for (unsigned i=0; i<bar.size(); i++)
      std::cout << ' ' << bar[i];
    std::cout << '\n';  
  }

  void vec_clear_test(void)
  {
    vector<int> myvector;
    myvector.push_back (100);
    myvector.push_back (200);
    myvector.push_back (300);

    std::cout << "myvector contains:";
    for (unsigned i=0; i<myvector.size(); i++)
      std::cout << ' ' << myvector[i];
    std::cout << '\n';

    myvector.clear();
    myvector.push_back (1101);
    myvector.push_back (2202);

    std::cout << "myvector contains:";
    for (unsigned i=0; i<myvector.size(); i++)
      std::cout << ' ' << myvector[i];
    std::cout << '\n';
  }

  void vec_comparaison_test(void)
  {
    vector<int> foo (3,100);   // three ints with a value of 100
    vector<int> bar (2,200);   // two ints with a value of 200

    if (foo==bar) std::cout << "foo and bar are equal\n";
    if (foo!=bar) std::cout << "foo and bar are not equal\n";
    if (foo< bar) std::cout << "foo is less than bar\n";
    if (foo> bar) std::cout << "foo is greater than bar\n";
    if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
    if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
  }

  int vec_vector_unit_tests(void)
  {
    #ifdef FT
      std::cout << "FT" << std::endl;
    #else
      std::cout << "STD" << std::endl;
    #endif
    vec_vectorConstructor_test();
    vec_vectorAssignation_test();
    vec_beginEnd_test();
    vec_rendRbegin_test();
    vec_size_test();
    vec_max_size_test();
    vec_resize_test();
    vec_capacity_test();
    vec_reserve_test();
    vec_empty_test();
    vec_assign_test();
    vec_erase_test();
    vec_swap_test();
    vec_push_back_test();
    vec_pop_back_test();
    vec_at_test();
    vec_front_test();
    vec_back_test();
    vec_clear_test();
    vec_comparaison_test();
    return 0;
  }