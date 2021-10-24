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

		void rotate_left(rb_node *root, rb_node *current)
		{
			rb_node *current_right = current->right;

			current->right = current_right->left;
			if (current->right != NULL)
				current->right->parent = current;
			current_right->parent = current->parent;
			if (current->parent == NULL)
				root = current_right;
			else if (current == current->parent->left)
				current->parent->left = current_right;
			else
				current->parent->right = current_right;
			current_right->left = current;
			current->parent = current_right;
		}

		void rotate_right(rb_node *root, rb_node *current)
		{
			rb_node *current_left = current->left;

			current->left = current_left->right;
			if (current->left != NULL)
			    current->left->parent = current;
			current_left->parent = current->parent;
			if (current->parent == NULL)
				root = current_left;
			else if (current == current->parent->left)
				current->parent->left = current_left;
			else
				current->parent->right = current_left;
			current_left->right = current;
			current->parent = current_left;
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

		void rotation(rb_node *root,  rb_node *current)
		{
			rb_node *parent = NULL;
			rb_node *grand_father = NULL;
			rb_node *uncle = NULL;

			while ((current != root) && (current->color != BLACK) && (get_father(current)->color == RED))
			{
				parent = get_father(current);
				grand_father = get_grandfather(current);
				uncle = get_uncle(current);

				if (parent == grand_father->left)
				{
					if (uncle != NULL && uncle->color == BLACK)
					{
						if (current == parent->right)
						{
							rotate_left(root, parent);
							current = parent;
							parent = get_father(current);
						}

						rotate_right(root, grand_father);
						ft::swap(parent->color, grand_father->color);
						current = parent;
					}
				}
				else
				{
					if (uncle != NULL && uncle->color == BLACK)
					{
						if (current == parent->left)
						{
							rotate_right(root, parent);
							current = parent;
							parent = get_father(current);
						}

						rotate_left(root, grand_father);
						ft::swap(parent->color, grand_father->color);
						current = parent;
					}
				}
			}
			root->color = BLACK;
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
			if (new_node == _root)
				_root->color = BLACK;
			recoloration(new_node);
			// rotation(_root, new_node);
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