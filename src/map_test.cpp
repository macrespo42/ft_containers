#include "map.hpp"
#include <map>
#include <string>

int main(void)
{
    // ft::pair <std::string,double> product1;                     // default constructor
    // ft::pair <std::string,double> product2 ("tomatoes",2.30);   // value init
    // ft::pair <std::string,double> product3 (product2);          // copy constructor

    // product1 = product2;

    std::map<int, int> test;

    test[1] = 18;
    test[2] = 3;
    test[3] = 42;
    test[4] = 1;

    std::cout << test.begin()->second << std::endl;
    // if (test.empty())
    //     std::cout << "empty" << std::endl;
    // else
    //     std::cout << "not empty" << std::endl;
    
    // std::cout << test.size() << std::endl;
    // std::cout << test.max_size() << std::endl;
    return 0;
}