#ifndef MAP_ITERATOR
#define MAP_ITERATOR

#include "iterator.hpp"
#include "type_traits.hpp"
#include <iostream>

namespace ft
{
    template<class T, bool isConst>
    class map_iterator
    {
        public:

        typedef std::ptrdiff_t difference_type;
		typedef typename ft::is_const<IsConst, T*, const T*>::value value_type;
		typedef typename value_type* pointer;
		typedef typename value_type& reference;
		typedef bidirectional_iterator_tag iterator_category;

        private:

        rb_node<T> *_ptr;

        void successor(void)
        {
            // si (current de droite existe)
            //     go a droite puis go le plus a gauche possible
            // sinon
            //     remonte tant que tu viens de la droite
            if (_ptr->right != NULL)
            {
                _ptr = _ptr->right;
                while (_ptr->left != NULL)
                    _ptr = _ptr->left;
            }
            else
            {
                rb_node *tmp;
                tmp = _ptr;
                _ptr = _ptr->parent;
                while (_ptr->left != tmp)
                {
                    tmp = _ptr;
                    _ptr = _ptr->parent;
                }
            }
        }

        public:

        map_iterator(void) : _ptr(NULL)
        { }

        map_iterator(rb_node *ptr) : _ptr(ptr)
        { }

        template<bool B>
		map_iterator(map_iterator< T, B > const &src, typename ft::enable_if<B>::type* = 0)
		{
			this->_ptr = src.base();
		}

        map_iterator &
        operator=(map_iterator const &src)
        {
            this->_ptr = src._ptr;
            return *this;
        }

        template<bool B>
		bool
		operator==(map_iterator<T, B> const &src) const
		{
			return this->_ptr == src.base();
		}

		template<bool B>
		bool
		operator!=(map_iterator<T, B> const &src) const
		{
			return !(this->_ptr == src.base());
		}

        pointer
        base(void) const
        {
            return this->_ptr;
        }

        reference
        operator*(void) const
        {
            return this->_ptr->item;
        }

        pointer
        operator->(void) const
        {
            return &(this->_ptr->item);
        }

        map_iterator &
        operator++(void)
        {
            successor()
            return *this;
        }

        map_iterator
        operator++(int)
        {
            map_iterator<T, isConst> tmp(*this);
            operator++();
            return tmp;
        }
    };
}

#endif