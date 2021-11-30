#include "tree.hpp"

int main(void)
{
    ft::rb_tree<int, int> tree;
    tree.insert_node(ft::make_pair(42, 12));
    tree.insert_node(ft::make_pair(50, 12));
    tree.insert_node(ft::make_pair(25, 12));
    tree.insert_node(ft::make_pair(46, 12));
    tree.insert_node(ft::make_pair(21, 12));
    tree.insert_node(ft::make_pair(30, 12));
    tree.insert_node(ft::make_pair(55, 12));
    tree.insert_node(ft::make_pair(18, 12));
    tree.insert_node(ft::make_pair(23, 12));
    tree.insert_node(ft::make_pair(28, 12));
    tree.insert_node(ft::make_pair(35, 12));
    tree.insert_node(ft::make_pair(44, 12));
    tree.insert_node(ft::make_pair(48, 12));
    tree.insert_node(ft::make_pair(53, 12));
    tree.insert_node(ft::make_pair(80, 12));
    tree.insert_node(ft::make_pair(12, 12));
    tree.insert_node(ft::make_pair(20, 12));
    tree.insert_node(ft::make_pair(22, 12));
    tree.insert_node(ft::make_pair(24, 12));
    tree.insert_node(ft::make_pair(27, 12));
    tree.insert_node(ft::make_pair(29, 12));
    tree.insert_node(ft::make_pair(33, 12));
    tree.insert_node(ft::make_pair(38, 12));
    tree.insert_node(ft::make_pair(43, 12));
    tree.insert_node(ft::make_pair(45, 12));
    tree.insert_node(ft::make_pair(47, 12));
    tree.insert_node(ft::make_pair(49, 12));
    tree.insert_node(ft::make_pair(51, 12));
    tree.insert_node(ft::make_pair(54, 12));
    tree.insert_node(ft::make_pair(60, 12));
    tree.insert_node(ft::make_pair(90, 12));

    tree.delete_by_key(25);
    tree.delete_by_key(55);
    tree.delete_by_key(24);
    tree.delete_by_key(54);
    tree.delete_by_key(22);
    tree.delete_by_key(51);
    tree.delete_by_key(21);
    tree.delete_by_key(53);
    tree.delete_by_key(20);
    tree.delete_by_key(23);
    tree.delete_by_key(42);
    tree.delete_by_key(38);
    tree.delete_by_key(35);
    tree.delete_by_key(33);
    tree.printTree();
    return 0;
}