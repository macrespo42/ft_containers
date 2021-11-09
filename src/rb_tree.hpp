#ifndef RB_TREE
#define RB_TREE

#include <iostream>
#include <memory>
#include <string>
#include <queue>
#include "algorithm.hpp"
#include "utility.hpp"
#include "map.hpp"

namespace ft
{
	enum rb_tree_color
	{
		BLACK,
		RED
	};

	template < class T>
	struct rb_node
	{
		rb_node* parent;
		rb_node* left;
		rb_node* right;
		T item;
		rb_tree_color color;

		rb_node(T data)
		{
			this->item = data;
			parent = NULL;
			left = NULL;
			right = NULL;
			this->color = RED;
		}
			
		bool
		is_on_left()
		{ return this == parent->left; }

		rb_node
		*sibling()
		{
			if (parent == NULL)
				return NULL;
			if (is_on_left())
				return parent->right;
			return parent->left;
		}

		bool
		has_red_child()
		{
    		return (left != NULL && left->color == RED) || (right != NULL && right->color == RED);
  		}
	};

	template <class Key, class T, class compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
	class rb_tree
	{
	public:
		typedef ft::pair<const Key, T> value_type;
        typedef Key key_type;
        typedef T mapped_type;
        typedef compare key_compare;
		typedef typename Alloc::template rebind<rb_node>::other allocator_type;
		typedef rb_tree_color node_color;
		typedef std::size_t size_type;
		typedef rb_node<value_type> rb_node;

	private:

		rb_node *_nil;
		allocator_type _allocator;

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
				std::cout << red << current->item.second << reset << " ";
			else
				std::cout << current->item.second << " ";
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
		find_destination(rb_node *current, rb_node *inserted)
		{
			if (inserted->item > current->item)
			{
				if (current->right == NULL)
					return (current);
				else
					return (this->find_destination(current->right, inserted));
			}
			else
			{
				if (current->left == NULL)
					return (current);
				else
					return (this->find_destination(current->left, inserted));
			}
		}

		void
		fix_violation(rb_node *&root, rb_node *&current)
		{
			rb_node *cur_parent = NULL;
			rb_node *cur_grand_parent = NULL;
		
			while ((current != root) && (current->color == RED) && (current->parent->color == RED))
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

		rb_node *
		successor(rb_node *current)
		{
			rb_node *tmp = current;

			while (tmp->left != NULL)
				tmp = tmp->left;
			return tmp;
		}

		rb_node *
		bst_replace(rb_node *current)
		{
			if (current->left != NULL && current->right != NULL)
				return successor(current->right);
			if (current->left == NULL && current->right == NULL)
				return NULL;
			if (current->left != NULL)
				return current->left;
			else
				return current->right;
		}

		void swap_values(rb_node *u, rb_node *v)
		{
			int temp;
			temp = u->item;
			u->item = v->item;
			v->item = temp;
		}

		void delete_node(rb_node *v)
		{
			rb_node *u = bst_replace(v);
			
			bool uvBlack = ((u == NULL or u->color == BLACK) and (v->color == BLACK));
			rb_node *parent = v->parent;
			if (u == NULL)
			{
				if (v == _nil->right)
					_nil->right = NULL;
				else
				{
					if (uvBlack)
						fix_double_black(v);
					else
					{
						if (v->sibling() != NULL)
							v->sibling()->color = RED;
					}
					if (v->is_on_left())
						parent->left = NULL;
					else
						parent->right = NULL;
				}
				_allocator.destroy(v);
				_allocator.deallocate(v, 1);
				return;
			}
			if (v->left == NULL or v->right == NULL)
			{
				if (v == _nil->right)
				{
					v->item = u->item;
					v->left = v->right = NULL;
					_allocator.destroy(u);
					_allocator.deallocate(u, 1);
				}
				else
				{
					if (v->is_on_left())
						parent->left = u;
					else
						parent->right = u;
					_allocator.destroy(v);
					_allocator.deallocate(v, 1);
					u->parent = parent;
					if (uvBlack)
						fix_double_black(u);
					else
						u->color = BLACK;
				}
				return;
			}
			swap_values(u, v);
			delete_node(u);
		}

		void fix_double_black(rb_node *x)
		{
			if (x == _nil->right)
			return;
		
			rb_node *sibling = x->sibling(), *parent = x->parent;
			if (sibling == NULL)
			{
				fix_double_black(parent);
			}
			else
			{
				if (sibling->color == RED)
				{
					parent->color = RED;
					sibling->color = BLACK;
					if (sibling->is_on_left())
						rotate_right(_nil->right, parent);
					else
						rotate_left(_nil->right, parent);
					fix_double_black(x);
				}
				else
				{
					if (sibling->has_red_child())
					{
						if (sibling->left != NULL and sibling->left->color == RED)
						{
							if (sibling->is_on_left())
							{
								sibling->left->color = sibling->color;
								sibling->color = parent->color;
								rotate_right(_nil->right, parent);
							}
							else
							{
								sibling->left->color = parent->color;
								rotate_right(_nil->right, sibling);
								rotate_left(_nil->right, parent);
							}
						}
						else
						{
							if (sibling->is_on_left())
							{
								sibling->right->color = parent->color;
								rotate_left(_nil->right, sibling);
								rotate_right(_nil->right, parent);
							}
							else
							{
								sibling->right->color = sibling->color;
								sibling->color = parent->color;
								rotate_left(_nil->right, parent);
							}
						}
						parent->color = BLACK;
					}
					else
					{
						sibling->color = RED;
						if (parent->color == BLACK)
							fix_double_black(parent);
						else
							parent->color = BLACK;
					}
				}
			}
  		}

		void
		construct_node(rb_node *ptr, value_type val = value_type())
		{
			rb_node tmp(val);
			_allocator.construct(ptr, tmp);
		}

	public:

		rb_tree(void)
		{
			_allocator(allocator_type());
			_nil = _allocator.allocate(1);
			construct_node(_nil);
			_nil->color = BLACK;
		}

		~rb_tree(void)
		{
			_allocator.destroy(_nil);
			_allocator.deallocate(_nil, 1);
		}

		void
		insert_node(const value_type &value)
		{
			rb_node *new_node = _allocator.allocate(1);
			construct_node(new_node);
			
			if (_nil->right)
			{
				rb_node *parent = find_destination(_nil->right, new_node);

				if (new_node->item > parent->item)
					parent->right = new_node;
				else
					parent->left = new_node;
				new_node->parent = parent;
			}
			else
			{
				_nil->right = new_node;
				new_node->parent = _nil;
			}

			fix_violation(_nil->right, new_node);
		}
		
		template<class K>
		rb_node
		*search(K n)
		{
			rb_node *temp = _nil->right;
			while (temp != NULL)
			{
				if (n < temp->item.first)
				{
					if (temp->left == NULL)
						break;
				else
					temp = temp->left;
				}
				else if (n == temp->item.first)
					break;
				else
				{
					if (temp->right == NULL)
					break;
					else
					temp = temp->right;
				}
			}
			return temp;
		}

		template<class K>
		rb_node*
		get_next_node(K n)
		{
			rb_node* tmp = _nil->right;

			while (tmp != NULL)
			{
				if (n < tmp->item.first)
					tmp = tmp->left;
				else if (n > tmp->item.first)
					tmp = tmp->right;
			}
			return tmp;
		}

		void
		delete_by_val(const value_type &n)
		{
			if (_nil->right == NULL)
				return;
			rb_node *v = search(n);
		
			if (v->item && v->item != n)
				return;
			delete_node(v);
		}

		rb_node *
		left_most(void) const
		{
			rb_node *tmp = _nil->right;
			while (tmp->left != NULL)
				tmp = tmp->left;
			return tmp;
		}

		rb_node *
		right_most(void) const
		{
			rb_node *tmp = _nil->right;
			while (tmp->right != NULL)
				tmp = tmp->right;
			return tmp;
		}

		rb_node *
		get_nil_node(void) const
		{
			return _nil;
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
			std::cout << std::endl << "Left most : " << std::endl;
			print_node(left_most());
			std::cout << std::endl << "Right most : " << std::endl;
			print_node(right_most());
		}

		void
		levelOrder()
		{  levelOrderHelper(_nil->right); }
	};
}
#endif