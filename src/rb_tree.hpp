#ifndef RB_TREE
#define RB_TREE

#include <memory>

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
	};
}

// delete node
// rotation
// coloration

#endif