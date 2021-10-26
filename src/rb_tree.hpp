#ifndef RB_TREE
#define RB_TREE

#include <iostream>
#include <memory>
#include <string>
#include <queue>
#include "algorithm.hpp"

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

			rb_node(value_type data)
			{
				this->item = data;
				parent = left = right = NULL;
				this->color = RED;
			}
		}				rb_node;

		rb_node *_root;

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
			
			if (!current)
				return ;
			if (current->color == RED)
				std::cout << red << current->item << reset << " ";
			else
				std::cout << current->item << " ";
		}

		void
		rotate_left(rb_node *&root, rb_node *&pt)
		{
			rb_node *pt_right = pt->right;
		
			pt->right = pt_right->left;
			if (pt->right != NULL)
				pt->right->parent = pt;
			pt_right->parent = pt->parent;
			if (pt->parent == NULL)
				root = pt_right;
			else if (pt == pt->parent->left)
				pt->parent->left = pt_right;
			else
				pt->parent->right = pt_right;
			pt_right->left = pt;
			pt->parent = pt_right;
		}
		
		void
		rotate_right(rb_node *&root, rb_node *&pt)
		{
			rb_node *pt_left = pt->left;

			pt->left = pt_left->right;
			if (pt->left != NULL)
				pt->left->parent = pt;		
			pt_left->parent = pt->parent;
			if (pt->parent == NULL)
				root = pt_left;
			else if (pt == pt->parent->left)
				pt->parent->left = pt_left;
			else
				pt->parent->right = pt_left;
			pt_left->right = pt;
			pt->parent = pt_left;
		}

		rb_node *
		bst_insert(rb_node *root ,rb_node *new_node)
		{
			if (root == NULL)
				return new_node;
			if (new_node->item < root->item)
			{
				root->left = bst_insert(root->left, new_node);
				root->left->parent = root;
			}
			else if (new_node->item > root->item)
			{
				root->right = bst_insert(root->right, new_node);
				root->right->parent = root;
			}
			return root;
		}

		void
		fix_violation(rb_node *&root, rb_node *&current)
		{
			rb_node *cur_parent = NULL;
			rb_node *cur_grand_parent = NULL;
		
			while ((current != root) && (current->color != BLACK) && (current->parent->color == RED))
			{
				cur_parent = get_father(current);
				cur_grand_parent = get_grandfather(current);
				if (cur_parent == cur_grand_parent->left)
				{
					rb_node *cur_uncle = get_uncle(current);

					if (cur_uncle != NULL && cur_uncle->color == RED)
					{
						cur_grand_parent->color = RED;
						cur_parent->color = BLACK;
						cur_uncle->color = BLACK;
						current = cur_grand_parent;
					}
					else
					{
						if (current == cur_parent->right)
						{
							rotate_left(root, cur_parent);
							current = cur_parent;
							cur_parent = current->parent;
						}
						rotate_right(root, cur_grand_parent);
						ft::swap(cur_parent->color, cur_grand_parent->color);
						current = cur_parent;
					}
				}
				else
				{
					rb_node *cur_uncle = get_uncle(current);
		
					if ((cur_uncle != NULL) && (cur_uncle->color == RED))
					{
						cur_grand_parent->color = RED;
						cur_parent->color = BLACK;
						cur_uncle->color = BLACK;
						current = cur_grand_parent;
					}
					else
					{
						if (current == cur_parent->left)
						{
							rotate_right(root, cur_parent);
							current = cur_parent;
							cur_parent = current->parent;
						}
						rotate_left(root, cur_grand_parent);
						ft::swap(cur_parent->color, cur_grand_parent->color);
						current = cur_parent;
					}
				}
			}
			root->color = BLACK;
		}

		rb_node*
		bst_delete(rb_node *root, const value_type &item)
		{
			if (!root)
				return NULL;
			if (item < root->item)
				root->left = bst_delete(root->left, item);
			else if (item > root->item)
				root->right = bst_delete(root->right, item);
			else
			{
				if (root->left == NULL && root->right == NULL)
					return NULL;
				else if (root->left == NULL)
				{
					rb_node *tmp = root->left;
					free(root);
					return tmp;
				}
				else if (root->right == NULL)
				{
					rb_node *tmp = root->right;
					free(root);
					return tmp;
				}

				rb_node *temp;

				temp = root->right;
				while (temp && temp->left != NULL)
					temp = temp->left;
				root->item = temp->item;
				root->right = bst_delete(root->right, temp->item);
			}
			return root;
		}

	public:

		rb_tree(void)
		{
			_root = NULL;
		}

		~rb_tree(void)
		{}

		void
		insert_node(const value_type &value)
		{
			rb_node *new_node = new rb_node(value);

			_root = bst_insert(_root, new_node);
			fix_violation(_root, new_node);
		}

		void
		delete_node(const value_type &value)
		{
			bst_delete(_root, value);
		}

		void
		levelOrderHelper(rb_node *root)
		{
			if (root == NULL)
				return;
		
			std::queue<rb_node *> q;
			q.push(root);
		
			while (!q.empty())
			{
				rb_node *temp = q.front();
				print_node(temp);
				q.pop();
		
				if (temp->left != NULL)
					q.push(temp->left);
		
				if (temp->right != NULL)
					q.push(temp->right);
			}
		}

		void
		levelOrder()
		{  levelOrderHelper(_root); }
	};
}

// delete node
// rotation

#endif