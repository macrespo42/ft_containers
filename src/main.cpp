#include "tree.hpp"

int main(void)
{
    ft::rb_tree<int, int> tree;
    tree.insert(std::make_pair(1, 12));
    tree.insert(std::make_pair(2, 12));
    tree.insert(std::make_pair(0, 12));
    tree.insert(std::make_pair(3, 12));
    tree.printTree();
    return 0;
}