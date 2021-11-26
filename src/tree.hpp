#ifndef TREE
#define TREE

#include <iostream>
#include <memory>
#include <string>
#include <queue>
#include <string>
#define CBLACK 1;
#define CRED 0;

namespace ft
{
    template<class T>
    struct node
    {
        node *parent;
        node *left;
        node *right;
        T item;
        int color;

        node(const T & data) : item(data.first, data.second)
        {
            parent = NULL;
            left = NULL;
            right = NULL;
            color = CBLACK;
        }

        void
        change_color(void)
        {
            if (this->color == 1)
                this->color = 0;
            else
                this->color = 1; 
        }
    };

    template <class Key, class T, class keyCompare = std::less<Key>, class valueCompare = std::less<T>, class Alloc = std::allocator<std::pair<const Key, T> > >
    class rb_tree
    {
        public:
        typedef std::pair<const Key, T> value_type;
        typedef Key key_type;
        typedef T mapped_type;
        typedef keyCompare key_compare;
        typedef valueCompare value_compare;
        typedef std::size_t size_type;
        typedef typename Alloc::template rebind<node<value_type> >::other allocator_type;
        typedef node<value_type> node;

        rb_tree(void) :
        _alloc(allocator_type()),
        _cmp(key_compare())
        {
            _nil = _alloc.allocate(1);
            construct_node(_nil);
            _nil->color = CBLACK;
        }

        virtual ~rb_tree(void)
		{
			_alloc.destroy(_nil);
			_alloc.deallocate(_nil, 1);
		}

        void insert(const value_type &value)
        {
            node *new_node = _alloc.allocate(1);
            construct_node(new_node, value);
            if (_nil->right == _nil)
            {
                _nil->right = new_node;
                new_node->parent = _nil;
            }
            else
            {
                node *new_parent = insertion_destination(_nil->right, new_node);
                if (_cmp(new_parent->item.first, new_node->item.first))
                    new_parent->right = new_node;
                else
                    new_parent->left = new_node;
                new_node->parent = new_parent;
                new_node->color = CRED;
            }
            // insert_fix(new_node);
        }

        void delete_node_helper(node *root, const key_type &key)
        {
            node *z = search(key);
            node *x;
            node *y;

            if (!z)
                return;
            y = z;
            int original_color = y->color;
            if (z->left == NULL)
            {
                x = z->right;
                transplant(z, z->right);
            }
            else if (z->right == NULL)
            {
                x = z->left;
                transplant(z, z->left);
            }
            else
            {
                y = minimum(z->right);
                original_color = y->color;
                x = y->right;
                if (y->parent == z)
                {
                    if (x)
                        x->parent = y;
                }
                else
                {
                    transplant(y, y->right);
                    y->right = z->right;
                    y->right->parent = y;
                }
                transplant(z, y);
                y->left = z->left;
                y->left->parent = y;
                y->color = z->color;
            }
			_alloc.destroy(z);
			_alloc.deallocate(z, 1);
            if (original_color == 1)
                delete_fix(x);
        }

        void delete_node(const key_type &key)
        {
            delete_node_helper(_nil->right, key);
        }

        void printTree()
        {
            if (_nil->right)
            printHelper(_nil->right, "", true);
        }

        private:

        node *_nil;
        allocator_type _alloc;
        key_compare _cmp;

        void
        construct_node(node *ptr, value_type val = value_type())
        {
            node tmp(val);
            tmp.left = _nil;
            tmp.right = _nil;
            _alloc.construct(ptr, tmp);
        }

        void delete_fix(node *x)
        {
            (void)x;
        }

        node
		*search(const key_type & n) const
		{
			node *temp = _nil->right;
			while (temp != NULL)
			{
				if (equal(n, temp->item.first))
					return temp;
				else if (_cmp(n, temp->item.first))
				{
					if (temp->left == NULL)
						return NULL;
					else
						temp = temp->left;
				}
				else
				{
					if (temp->right == NULL)
						return NULL;
					else
						temp = temp->right;
				}
			}
			return temp;
		}

        void transplant(node *u, node *v)
        {
            if (u->parent == NULL)
                _nil->right = v;
            else if (u == u->parent->left)
                u->parent->left = v;
            else
                u->parent->right = v;
            if (v && u)
                v->parent = u->parent;
        }

        node *minimum(node *node)
        {
            while (node->left != NULL)
                node = node->left;
            return node;
        }

        node *maximum(node *node)
        {
            while (node->right != NULL)
                node = node->right;
            return node;
        }

        void left_rotate(node *x)
        {
            node *y = x->right;
            x->right = y->left;
            if (y->left != NULL)
                y->left->parent = x;
            y->parent = x->parent;
            if (x->parent == NULL)
                _nil->right = y;
            else if (x == x->parent->left)
                x->parent->left = y;
            else
                x->parent->right = y;
            y->left = x;
            x->parent = y;
        }

        void right_rotate(node *x)
        {
            node *y = x->left;
            x->left = y->right;
            if (y->right != NULL)
                y->right->parent = x;
            y->parent = x->parent;
            if (x->parent == NULL)
                _nil->right = y;
            else if (x == x->parent->right)
                x->parent->right = y;
            else
                x->parent->left = y;
            y->right = x;
            x->parent = y;
        }

        node *recoloration(node *uncle, node *parent)
        {
            uncle->color = 1;
            parent->color = 1;
            parent->parent->color = 0;
            return parent->parent;
        }

        void insert_fix(node *z)
        {
            // red = 0 et black = 1
            while (z->parent->color == 0)
            {
                if (z->parent == z->parent->parent->left)
                {
                    node *uncle = z->parent->parent->right;
                    if (uncle->color == 0)
                        z = recoloration(uncle, z->parent);
                    else
                    {
                        if (z == z->parent->left)
                        {
                            z = z->parent;
                            right_rotate(z);
                        }
                        z->parent->color = 1;
                        z->parent->parent->color = 0;
                        left_rotate(z->parent->parent);
                    }
                }
                else
                {
                    node *uncle = z->parent->parent->left;
                    if (uncle->color == 0)
                        z = recoloration(uncle, z->parent);
                    else
                    {
                        if (z == z->parent->right)
                        {
                            z = z->parent;
                            left_rotate(z);
                        }
                        z->parent->color = 1;
                        z->parent->parent->color = 0;
                        right_rotate(z->parent->parent);
                    }
                }
            }
            _nil->right->color = 1;
        }

        node *insertion_destination(node *position, node *new_node)
        {
            while (position != _nil)
            {
                if (_cmp(position->item.first, new_node->item.first))
                {
                    if (position->right == _nil)
                        return position;
                    position = position->right;
                }
                else
                {
                    if (position->left == _nil)
                        return position;
                    position = position->left;
                }
            }
            return position;
        }

		bool
		equal(key_type a, key_type b) const
		{
			return (!_cmp(a, b) && !_cmp(b, a));
		}

        void printHelper(node *root, std::string indent, bool last)
        {
            if (root != _nil)
            {
                std::cout << indent;
                if (last)
                {
                    std::cout << "R----";
                    indent += "   ";
                }
                else
                {
                    std::cout << "L----";
                    indent += "|  ";
                }
                std::string sColor;
                if (root->color == 1)
                    sColor = "BLACK";
                else
                    sColor = "RED";
                std::cout << root->item.first << "(" << sColor << ")" << std::endl;
                printHelper(root->left, indent, false);
                printHelper(root->right, indent, true);
            }
        }
    };

}

#endif