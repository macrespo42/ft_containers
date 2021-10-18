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

		rb_node*
		get_uncle(rb_node *current)
		{
			if (current->parent->parent && current->parent->parent->item > current->parent->item)
				return current->parent->parent->right;
			else if (current->parent->parent && current->parent->parent->item < current->parent->item)
				return current->parent->parent->left;
			return NULL;
		}

		rb_node*
		get_brother(rb_node *current)
		{
			if (current->parent && current->parent->item > current->item)
				return current->parent->right;
			else if (current->parent && current->parent->item < current->item)
				return current->parent->left;
			return NULL;
		}

		rb_node*
		get_grandfather(rb_node *current)
		{
			if (current->parent && current->parent->parent)
				return current->parent->parent;
			return NULL;
		}

		void
		print_node(rb_node *current)
		{
			std::string red="\033[0;31m";
			std::string reset="\033[0m";

			if (current->color == RED)
				std::cout << red << current->item << reset << std::endl;
			else
				std::cout << current->item << std::endl;
		}

		void
		recoloration(rb_node *current)
		{
			rb_node *tmp = current;
			while (tmp->parent && tmp->parent->color != BLACK && get_uncle(tmp)->color == RED)
			{
				get_uncle(tmp)->color = BLACK;
				tmp->parent->color = BLACK;
				if (get_grandfather(tmp) != _root)
				{
					get_grandfather(tmp)->color = RED;
					tmp = get_grandfather(tmp);
				}
			}
		}

		rb_node*
		create_node(const value_type &value)
		{
			rb_node *new_child;

			new_child = new rb_node();
			new_child->left = NULL;
			new_child->right = NULL;
			new_child->item = value;
			new_child->color = RED;
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

		void
		insert_node(const value_type &value)
		{
			rb_node new_node = create_node(value);
			rb_node tmp = _root;

			while (tmp != NULL)
			{
				if (tmp->item && tmp->item > value)
					tmp = tmp->left;
				else
					tmp = tmp->right;
			}
			new_node->parent = tmp->parent;
			recoloration(new_child);
		}

		void
		print_tree(void)
		{
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
			tmp = _root;
			std::cout << "------------------------------------------" << std::endl;
		}
	};
}

// delete node
// rotation
// coloration

#endif