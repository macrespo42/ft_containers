#ifndef RB_TREE
#define RB_TREE

namespace ft
{
	enum rb_tree_color
	{
		RB_BLACK,
		RB_RED
	};

	typedef struct rb_tree_node
	{
		struct rb_tree_node *parent;
		struct rb_tree_node *left;
		struct rb_tree_node *right;
		void 				*data;
		enum 				rb_tree_color;

	}			   rb_tree_node;
}

#endif