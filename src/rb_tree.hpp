#ifndef RB_TREE
#define RB_TREE

#include <iostream>
#include <memory>
#include <string>
#include <queue>
#include "algorithm.hpp"
#include "utility.hpp"

namespace ft
{
	enum rb_tree_color
	{
		CBLACK,
		CRED
	};

	template < class T>
	struct rb_node
	{
		rb_node* parent;
		rb_node* left;
		rb_node* right;
		T item;
		rb_tree_color color;

		rb_node(const T & data) : item(data.first, data.second)
		{
			parent = NULL;
			left = NULL;
			right = NULL;
			this->color = CRED;
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
    		return (left != NULL && left->color == CRED) || (right != NULL && right->color == CRED);
  		}
	};

	template <class Key, class T, class keyCompare = std::less<Key>, class valueCompare = std::less<T>, class Alloc = std::allocator<ft::pair<const Key, T> > >
	class rb_tree
	{
	public:
		typedef ft::pair<const Key, T> value_type;
        typedef Key key_type;
        typedef T mapped_type;
        typedef keyCompare key_compare;
		typedef valueCompare value_compare;
		typedef typename Alloc::template rebind<rb_node<value_type> >::other allocator_type;
		typedef rb_tree_color node_color;
		typedef std::size_t size_type;
		typedef rb_node<value_type> rb_node;

	private:

		rb_node *_nil;
		allocator_type _allocator;
		key_compare _comp;

		bool
		equal(key_type a, key_type b) const
		{
			return (!_comp(a, b) && !_comp(b, a));
		}

		void
		change_color(rb_node *node)
		{
			if (node->color == CBLACK)
				node->color = CRED;
			else
				node->color = CBLACK;
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
			if (get_grandfather(current) && get_father(current) == get_grandfather(current)->left)
				return get_grandfather(current)->right;
			else if (get_grandfather(current) && get_grandfather(current) == get_father(current)->right)
				return get_grandfather(current)->left;
			return NULL;
		}

		rb_node*
		get_brother(rb_node *current)
		{
			if (get_father(current) && get_father(current) > current)
				return get_father(current)->right;
			else if (get_father(current) && get_father(current) < current)
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
			if (current->color == CRED)
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
			if (_comp(current->item.first, inserted->item.first))
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
		
			while ((current != root) && (current->color == CRED) && (current->parent->color == CRED))
			{
				cur_parent = get_father(current);
				cur_grand_parent = get_grandfather(current);
				if (cur_parent == cur_grand_parent->left)
				{
					rb_node *cur_uncle = get_uncle(current);

					if (cur_uncle != NULL && cur_uncle->color == CRED)
					{
						cur_grand_parent->color = CRED;
						cur_parent->color = CBLACK;
						cur_uncle->color = CBLACK;
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
		
					if ((cur_uncle != NULL) && (cur_uncle->color == CRED))
					{
						cur_grand_parent->color = CRED;
						cur_parent->color = CBLACK;
						cur_uncle->color = CBLACK;
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
			root->color = CBLACK;
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

		void
		branch_swapper(rb_node *pointing, rb_node *origin, rb_node *destination)
		{
			if (pointing)
			{
				if (pointing == destination)
					destination = origin;
				if (pointing == get_father(origin) && pointing->right == origin)
					pointing->right = destination;
				else if (pointing == get_father(origin) && pointing->left == origin)
					pointing->left = destination;
				else
					pointing->parent = destination;
			}
		}

		void swap_values(rb_node *a, rb_node *b)
		{
			std::cout << "COUCOU JE SWAP" << std::endl;
			branch_swapper(a->parent, a, b);
			branch_swapper(a->left, a, b);
			branch_swapper(a->right, a, b);
			branch_swapper(b->parent, b, a);
			branch_swapper(b->left, b, a);
			branch_swapper(b->right, b, a);
			ft::swap(a->parent, b->parent);
			ft::swap(a->right, b->right);
			ft::swap(a->left, b->left);
			ft::swap(a->color, b->color);
		}

		void delete_node(rb_node *v)
		{
			rb_node *u = bst_replace(v);
			
			bool uvBlack = ((u == NULL or u->color == CBLACK) and (v->color == CBLACK));
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
							v->sibling()->color = CRED;
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
					u->color = CBLACK;
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
				if (sibling->color == CRED)
				{
					parent->color = CRED;
					sibling->color = CBLACK;
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
						if (sibling->left != NULL and sibling->left->color == CRED)
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
						parent->color = CBLACK;
					}
					else
					{
						sibling->color = CRED;
						if (parent->color == CBLACK)
							fix_double_black(parent);
						else
							parent->color = CBLACK;
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

		rb_tree(void) :
		_allocator(allocator_type()),
		_comp(key_compare())
		{
			_nil = _allocator.allocate(1);
			construct_node(_nil);
			_nil->color = CBLACK;
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
			construct_node(new_node, value);
			
			if (_nil->right)
			{
				rb_node *parent = find_destination(_nil->right, new_node);

				if (_comp(parent->item.first, new_node->item.first))
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
		
		rb_node
		*search(const key_type & n) const
		{
			rb_node *temp = _nil->right;
			while (temp != NULL)
			{
				if (equal(n, temp->item.first))
					return temp;
				else if (_comp(n, temp->item.first))
				{
					if (temp->left == NULL)
						return NULL;
					else
						temp = temp->left;
				}
				else
				{
					if (temp->right == NULL)
						return NULL;
					else
						temp = temp->right;
				}
			}
			return temp;
		}

		rb_node*
		get_next_node(const key_type & n)
		{
			rb_node* tmp = _nil->right;

			while (tmp != NULL)
			{
				if (_comp(n, tmp->item.first))
					tmp = tmp->left;
				else if (_comp(tmp->item.first, n))
					tmp = tmp->right;
			}
			return tmp;
		}

		void
		delete_by_val(const key_type &n)
		{
			rb_node *v = search(n);

			if (v)
				delete_node(v);
		}

		rb_node *
		left_most(void) const
		{
			rb_node *tmp = _nil->right;
			if (!tmp)
				return _nil;
			while (tmp && tmp->left)
				tmp = tmp->left;
			return tmp;
		}

		rb_node *
		right_most(void) const
		{
			rb_node *tmp = _nil->right;
			if (!tmp)
				return _nil;
			while (tmp && tmp->right)
				tmp = tmp->right;
			return tmp;
		}

		rb_node *
		get_nil_node(void) const
		{
			return _nil;
		}

		void swap_root(rb_tree &x)
		{
			ft::swap(_nil, x._nil);
		}

		allocator_type
		get_allocator(void) const
		{
			return _allocator;
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