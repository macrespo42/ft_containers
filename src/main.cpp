#include "tree.hpp"

int main(void)
{
    ft::rb_tree<int, int> tree;
    tree.insert(std::make_pair(33, 12));
    tree.insert(std::make_pair(53, 12));
    tree.insert(std::make_pair(13, 12));
    tree.insert(std::make_pair(11, 12));
    tree.insert(std::make_pair(21, 12));
    tree.insert(std::make_pair(15, 12));
    tree.insert(std::make_pair(31, 12));
    tree.printTree();
    return 0;
}