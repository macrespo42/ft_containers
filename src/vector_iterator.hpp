#ifndef VECTOR_ITERATOR
#define VECTOR_ITERATOR

#include "iterator.hpp"

namespace ft
{
	template <class T>
	class vector_iterator
	{

	public:
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
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

		vector_iterator(vector_iterator<T> &src)
		{
			this->_ptr = src._ptr;
		}

		vector_iterator &
		operator=(vector_iterator<T> const &src)
		{
			this->_ptr = src._ptr;
			return *this;
		}

		/*
		 *
		 * Comparaisons
		 *
		 */		

		bool
		operator==(vector_iterator<T> const &src) const
		{
			return this->_ptr == src._ptr;
		}

		bool
		operator!=(vector_iterator<T> const &src) const
		{
			return !(*this == src);
		}

		/*
		 *
		 * Dereference
		 *
		 */

		reference
		operator*(void)
		{
			return *this->_ptr;
		}

		reference
		operator->(void)
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

		vector_iterator &
		operator++(int)
		{
			vector_iterator<T> tmp(*this);
			operator++();
			return tmp;
		}

		vector_iterator &
		operator--(void)
		{
			this->_ptr--;
			return *this;
		}

		vector_iterator &
		operator--(int)
		{
			vector_iterator<T> tmp(*this);
			operator--();
			return tmp;	
		}

		pointer
		operator+(int n) const
		{
			return this->_ptr + n;
		}

		pointer
		operator-(int n) const
		{
			return this->_ptr - n;
		}

		pointer
		operator-(vector_iterator<T> const &x)
		{
			return this->_ptr - x.ptr;
		}

		vector_iterator &
		operator+=(int n)
		{
			vector_iterator<T> tmp(*this);
			for (int i = 0; i < n; i++)
				operator++();
			return tmp;
		}

		vector_iterator &
		operator-=(int n)
		{
			vector_iterator<T> tmp(*this);
			for (int i = 0; i < n; i++)
				operator--();
			return tmp;
		}

		pointer
		operator[](int n)
		{
			return this->_ptr + n;
		}

	private:
		pointer _ptr;

	};
}

#endif