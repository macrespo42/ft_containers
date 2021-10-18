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

		void
		change_color(rb_node *node)
		{
			if (node->color == BLACK)
				node->color = RED;
			else
				node->color = BLACK;
		}

		rb_node*
		get_father(rb_node *current)
		{
			if (current->parent)
				return current->parent;
			return NULL;
		}

		rb_node*
		get_grandfather(rb_node *current)
		{
			if (get_father(current) && current->parent->parent)
				return current->parent->parent;
			return NULL;
		}

		rb_node*
		get_uncle(rb_node *current)
		{
			if (get_grandfather(current) && get_grandfather(current)->item > get_father(current)->item)
				return get_grandfather(current)->right;
			else if (get_grandfather(current) && get_grandfather(current)->item < get_father(current)->item)
				return get_grandfather(current)->left;
			return NULL;
		}

		rb_node*
		get_brother(rb_node *current)
		{
			if (get_father(current) && get_father(current)->item > current->item)
				return get_father(current)->right;
			else if (get_father(current) && get_father(current)->item < current->item)
				return get_father(current)->left;
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
			while (get_father(tmp) && get_father(tmp)->color != BLACK && get_uncle(tmp)->color == RED)
			{
				change_color(get_uncle(tmp));
				change_color(get_father(tmp));
				if (get_grandfather(tmp) != _root)
				{
					change_color(get_grandfather(tmp));
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

		void
		ll_rotation(rb_node *current)
		{
			rb_node *tmp;
			rb_node *tmp2;

			tmp = get_father(current);
			get_father(current)->parent = get_grandfather(get_father(current));
			tmp2 = get_father(current)->left;
			get_father(current)->left = tmp;
			get_father(current)->left->left = tmp2;
			change_color(get_father(current));
			change_color(get_uncle(current));
		}

		void
		lr_rotation(rb_node *current)
		{
			rb_node *p_cpy = get_father(current);
			rb_node *t1_cpy = current->right;
			rb_node *t2_cpy = current->left;
			rb_node *t3_cpy = get_father(current)->left;
			rb_node *g_cpy = get_grandfather(current);

			get_grandfather(current)->left = current;
			current->right = t3_cpy;
			current->left = p_cpy;
			get_father(current)->left = t1_cpy;
			get_father(current)->right = t2_cpy;
			current->parent = g_cpy;
			ll_rotation(current);
		}

		void
		rr_rotation(rb_node *current)
		{
			rb_node *tmp;
			rb_node *tmp2;

			tmp = get_father(current)->left;
			get_father(current)->left = get_grandfather(current);
			tmp2 = get_grandfather(get_father(current));
			get_grandfather(current)->parent = get_father(current);
			get_uncle(current)->right = tmp;
			get_father(current)->parent = tmp2;
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
			get_father(new_node) = get_father(tmp);
			recoloration(new_node);
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

#endif