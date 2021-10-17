#ifndef RB_TREE
#define RB_TREE

#include <iostream>
#include <memory>
#include <string>

namespace ft
{
	enum rb_tree_color
	{
		BLACK,
		RED
	};

	template < class T, class Alloc = std::allocator<T> >
	class rb_tree
	{
	public:
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef rb_tree_color node_color;
		typedef std::size_t size_type;
		typedef Alloc allocator_type;

	private:

		typedef struct rb_node
		{
			rb_node* parent;
			rb_node* left;
			rb_node* right;
			value_type item;
			node_color color;
		}				rb_node;

		size_type _size;
		rb_node _root;

		rb_node get_uncle(rb_node *current)
		{
			if (current->parent->parent && current->parent->parent->item > current->parent->item)
				return current->parent->parent->right;
			else if (current->parent->parent && current->parent->parent->item < current->parent->item)
				return current->parent->parent->left;
			return NULL;
		}

		rb_node get_brother(rb_node *current)
		{
			if (current->parent && current->parent->item > current->item)
				return current->parent->right;
			else (current->parent && current->parent->item < current->item)
				return current->parent->left;
			return NULL;
		}

	public:

		rb_tree(void) :
		_size(0)
		{
			_root.parent = NULL;
			_root.left = NULL;
			_root.right = NULL;
			_root.item = value_type();
			_root.color = BLACK;
		}

		~rb_tree(void)
		{}

		void add_node(const value_type &val)
		{
			rb_node *new_child;

			new_child = new rb_node();
			new_child->left = NULL;
			new_child->right = NULL;
			new_child->item = val;
			new_child->color = RED;

			rb_node tmp = _root;
			while (tmp != NULL)
			{
				if (tmp->val && tmp->val > val)
					tmp = tmp->left;
				else
					tmp = tmp->right;
			}
			new_child->parent = tmp->parent;
		}

		void print_tree(void)
		{
			std::string red='\033[0;31m';
			std::string reset='\033[0m';

			rb_node tmp = _root;
			while (tmp->left != NULL)
				tmp = tmp->left;
			std::cout << "------------------------------------------" << std::endl;
			while (tmp != _root)
			{
				std::cout << tmp->item << std::endl;
				if (get_brother(tmp) != NULL)
					std::cout << get_brother(tmp)->item << std::endl;
				tmp = tmp->parent;
			}
			std::cout << "------------------------------------------" << std::endl;
		}
	};
}

// delete node
// rotation
// coloration

#endif