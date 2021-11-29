#include "tree.hpp"

int main(void)
{
    ft::rb_tree<int, int> tree;
    tree.insert_node(ft::make_pair(55, 12));
    tree.insert_node(ft::make_pair(40, 12));
    tree.insert_node(ft::make_pair(65, 12));
    tree.insert_node(ft::make_pair(60, 12));
    tree.insert_node(ft::make_pair(75, 12));
    tree.insert_node(ft::make_pair(57, 12));
    tree.printTree();
    return 0;
}