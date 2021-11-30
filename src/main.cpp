#include "tree.hpp"

int main(void)
{
    ft::rb_tree<char, int> tree;
    tree.insert_node(ft::make_pair('a', 12));
    tree.insert_node(ft::make_pair('b', 12));
    tree.insert_node(ft::make_pair('c', 12));
    tree.insert_node(ft::make_pair('d', 12));
    tree.insert_node(ft::make_pair('e', 12));
    tree.insert_node(ft::make_pair('f', 12));
    tree.delete_by_key('b');
    // tree.delete_by_key('c');
    // tree.delete_by_key('e');
    // tree.delete_by_key('d');
    // tree.delete_by_key('a');
    tree.printTree();
    return 0;
}