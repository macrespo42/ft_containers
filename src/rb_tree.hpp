#ifndef RB_TREE
#define RB_TREE

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
		typedef struct rb_node rb_node;
		typedef rb_node* node_pointer;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef rb_tree_color node_color;

	private:

		struct rb_node
		{
			node_pointer parent;
			node_pointer left;
			node_pointer right;
			value_type item;
			node_color color;
			bool is_root;
		};

		rb_node root;

	public:

		rb_tree *init_tree(void)
		{
			rb_tree *root;

			root = new rb_tree();
			root->parent = NULL;
			root->left = NULL;
			root->right = NULL;
			root->item = item;
			color = RB_BLACK;
		}
	};
}

// add node
// delete node
// rotation
// coloration

#endif