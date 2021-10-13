#ifndef RB_TREE
#define RB_TREE

#include <memory>

namespace ft
{
	enum rb_tree_color
	{
		RB_BLACK,
		RB_RED
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

	private:

		typedef struct rb_node
		{
			rb_node* parent;
			rb_node* left;
			rb_node* right;
			value_type item;
			node_color color;
			bool is_root;
		}				rb_node;

		size_type _size;
		rb_node _root;

	public:

		rb_tree(void) :
		_size(0)
		{
			_root.parent = NULL;
			_root.left = NULL;
			_root.right = NULL;
			_root.item = value_type();
			_root.color = RB_BLACK;
			_root.is_root = true;
		}
	};
}

// add node
// delete node
// rotation
// coloration

#endif