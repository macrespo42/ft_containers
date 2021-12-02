#ifndef SET_ITERATOR
#define SET_ITERATOR

#include "iterator.hpp"
#include "type_traits.hpp"
#include <iostream>

namespace ft
{
    template<class T, class N, bool isConst>
    class set_iterator
    {
        public:

        typedef std::ptrdiff_t difference_type;
		typedef const T value_type;
		typedef N node_type;
		typedef value_type* pointer;
		typedef value_type& reference;
        typedef node_type*  node_pointer;
		typedef bidirectional_iterator_tag iterator_category;

        private:

        node_pointer _ptr;

        void successor(void)
        {
            // si (current de droite existe)
            //     go a droite puis go le plus a gauche possible
            // sinon
            //     remonte tant que tu viens de la droite
            if (_ptr->right->is_nil() == false)
            {
                _ptr = _ptr->right;
                while (_ptr->left->is_nil() == false) {
                    _ptr = _ptr->left;
                }
            }
            else
            {
				while (_ptr == _ptr->parent->right && _ptr->is_nil() == false) {
                    _ptr = _ptr->parent;
                }
				_ptr = _ptr->parent;
            }
        }

        void predecessor(void)
        {
            // si current de gauche existe 
            //     go a gauche puis le plus a droite possible
            // sinon
            //     remonte tant que tu viens de la gauche
            if (_ptr->is_nil())
            {
                _ptr = _ptr->right;
                while (_ptr->right->is_nil() == false)
                    _ptr = _ptr->right;

            }
            else if (_ptr->left->is_nil() == false)
            {
                _ptr = _ptr->left;
                while (_ptr->right->is_nil() == false)
                    _ptr = _ptr->right;
            }
            else
            {
                while (_ptr == _ptr->parent->left && _ptr->is_nil() == false)
                    _ptr = _ptr->parent;
                _ptr = _ptr->parent;
            }
        }

        public:

        set_iterator(void) : _ptr(NULL)
        { }

        set_iterator(node_pointer ptr) : _ptr(ptr)
        { }

        template<bool B>
		set_iterator(set_iterator<T, N, B> const &src)
		{
			this->_ptr = src.base();
		}

        set_iterator &
        operator=(set_iterator const &src)
        {
            this->_ptr = src._ptr;
            return *this;
        }

        template<bool B>
		bool
		operator==(set_iterator<T, N, B> const &src) const
		{
			return this->_ptr == src.base();
		}

		template<bool B>
		bool
		operator!=(set_iterator<T, N, B> const &src) const
		{
			return !(this->_ptr == src.base());
		}

        node_pointer
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

        set_iterator &
        operator++(void)
        {
            successor();
            return *this;
        }

        set_iterator
        operator++(int)
        {
            set_iterator<T, N, isConst> tmp(*this);
            operator++();
            return tmp;
        }

        set_iterator &
        operator--(void)
        {
            predecessor();
            return *this;
        }

        set_iterator
        operator--(int)
        {
            set_iterator<T, N, isConst> tmp(*this);
            operator--();
            return tmp;
        }
    };
}

#endif