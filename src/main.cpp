#include "set_rb_tree.hpp"

int main(void)
{
    ft::rb_tree<int> tree;
    tree.insert_node(42);
    tree.insert_node(50);
    tree.insert_node(25);
    tree.insert_node(46);
    tree.insert_node(21);
    tree.insert_node(30);
    tree.insert_node(55);
    tree.insert_node(18);
    tree.insert_node(23);
    tree.insert_node(28);
    tree.insert_node(35);
    tree.insert_node(44);
    tree.insert_node(48);
    tree.insert_node(53);
    tree.insert_node(80);
    tree.insert_node(12);
    tree.insert_node(20);
    tree.insert_node(22);
    tree.insert_node(24);
    tree.insert_node(27);
    tree.insert_node(29);
    tree.insert_node(33);
    tree.insert_node(38);
    tree.insert_node(43);
    tree.insert_node(45);
    tree.insert_node(47);
    tree.insert_node(49);
    tree.insert_node(51);
    tree.insert_node(54);
    tree.insert_node(60);
    tree.insert_node(90);

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