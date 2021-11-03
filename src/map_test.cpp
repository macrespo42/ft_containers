#include "map.hpp"
#include <map>
#include <string>

int main(void)
{
    // ft::pair <std::string,double> product1;                     // default constructor
    // ft::pair <std::string,double> product2 ("tomatoes",2.30);   // value init
    // ft::pair <std::string,double> product3 (product2);          // copy constructor

    // product1 = product2;

    // std::map<int, int> test;
    // if (test.empty())
    //     std::cout << "empty" << std::endl;
    // else
    //     std::cout << "not empty" << std::endl;
    
    // std::cout << test.size() << std::endl;
    // std::cout << test.max_size() << std::endl;
    ft::rb_tree<int> tamere;

    tamere.insert_node(10);
    tamere.insert_node(14);
    tamere.insert_node(12);
    tamere.levelOrder();
    return 0;
}