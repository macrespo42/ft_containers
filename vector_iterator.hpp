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

		vector_iterator(void) : _ptr(nullptr)
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

	private:
		pointer _ptr;

	};
}

#endif