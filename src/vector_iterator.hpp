#ifndef VECTOR_ITERATOR
#define VECTOR_ITERATOR

#include "iterator.hpp"
#include "type_traits.hpp"
#include <iostream>

namespace ft
{
	template <class T, bool IsConst>
	class vector_iterator
	{

	public:
		typedef std::ptrdiff_t difference_type;
		typedef typename ft::is_const<IsConst, T*, const T*>::value value_type;
		typedef typename ft::is_const<IsConst, T*, const T*>::value pointer;
		typedef typename ft::is_const<IsConst, T&, const T&>::value reference;
		typedef random_access_iterator_tag iterator_category;

		/*
		 *
		 * Constructors
		 *
		 */

		vector_iterator(void) : _ptr(nullptr)
		{}

		vector_iterator(pointer ptr) : _ptr(ptr)
		{}

		template<bool B>
		vector_iterator(vector_iterator< T, B > const &src, typename ft::enable_if<B>::type* = 0)
		{
			this->_ptr = src.getPtr();
		}

		vector_iterator &
		operator=(vector_iterator const &src)
		{
			this->_ptr = src._ptr;
			return *this;
		}

		/*
		 *
		 * Comparaisons
		 *
		 */		

		template<bool B>
		bool
		operator==(vector_iterator<T, B> const &src) const
		{
			return this->_ptr == src.getPtr();
		}

		template<bool B>
		bool
		operator!=(vector_iterator<T, B> const &src) const
		{
			return !(this->_ptr == src.getPtr());
		}

		/*
		 *
		 * Dereference
		 *
		 */

		pointer
		getPtr(void) const
		{
			return this->_ptr;
		}

		reference
		operator*(void) const
		{
			return *this->_ptr;
		}

		pointer
		operator->(void) const
		{
			return this->_ptr;
		}

		/*
		 *
		 * Arithmetic Operations
		 *
		 */

		vector_iterator &
		operator++(void)
		{
			this->_ptr++;
			return *this;
		}

		vector_iterator
		operator++(int)
		{
			vector_iterator<T, IsConst> tmp(*this);
			operator++();
			return tmp;
		}

		vector_iterator &
		operator--(void)
		{
			this->_ptr--;
			return *this;
		}

		vector_iterator
		operator--(int)
		{
			vector_iterator<T, IsConst> tmp(*this);
			operator--();
			return tmp;	
		}

		vector_iterator
		operator+(int n) const
		{
			return this->_ptr + n;
		}

		vector_iterator
		operator-(int n) const
		{
			return this->_ptr - n;
		}

		template<bool B>
		difference_type
		operator-(vector_iterator<T, B> const &x) const
		{
			return (this->getPtr() - x.getPtr());
		}

		vector_iterator&
		operator+=(int n)
		{
			for (int i = 0; i < n; i++)
				operator++();
			return *this;
		}

		vector_iterator&
		operator-=(int n)
		{
			for (int i = 0; i < n; i++)
				operator--();
			return *this;
		}

		reference
		operator[](int n) const
		{
			return this->_ptr[n];
		}

		/*
		 *
		 * Non member oveloads
		 *
		 */

		friend bool
		operator<(vector_iterator<T, IsConst> const &a, vector_iterator<T, IsConst> const &b)
		{
			return a._ptr < b._ptr;
		}

		friend bool
		operator>(vector_iterator<T, IsConst> const &a, vector_iterator<T, IsConst> const &b)
		{
			return a._ptr > b._ptr;
		}

		friend bool
		operator<=(vector_iterator<T, IsConst> const &a, vector_iterator<T, IsConst> const &b)
		{
			return a._ptr <= b._ptr;
		}

		friend bool
		operator>=(vector_iterator<T, IsConst> const &a, vector_iterator<T, IsConst> const &b)
		{
			return a._ptr >= b._ptr;
		}

		friend vector_iterator
		operator+(int n, vector_iterator const &it)
		{
			return it.getPtr() + n;
		}

	private:
		pointer _ptr;

	};
}

#endif