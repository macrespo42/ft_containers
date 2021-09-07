#ifndef VECTOR
#define VECTOR

#include <memory>
#include "vector_iterator.hpp"

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
	private:

		/*
		 *
		 * member types of vector
		 * it's basically typedef for
		 * data structures
		 *
		 */

		typedef T value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef vector_iterator<T> iterator;
		typedef std::ptrdiff_t difference_type;
		/* TO DO
		const_iterator
		reverse_iterator
		const_reverse_iterator
		*/
		typedef std::size_t size_type;

		size_type _size;
		size_type _capacity;
		pointer  _vector;
		allocator_type _allocator;

	public:

		/*
		 *
		 * CONSTRUCTORS
		 *
		 */

		// default
		explicit vector(const allocator_type& alloc = allocator_type()) :
		_size(0),
		_capacity(0),
		_allocator(alloc)
		{
			this->_vector = this->_allocator.allocate(0);
		}

		// fill
		explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : 
		_size(n),
		_capacity(n),
		_allocator(alloc)
		{
			this->_vector = this->_allocator.allocate(this->_capacity);
			this->_allocator.construct(this->_vector, val);
		}

		// range
		template <class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()):
		_allocator(alloc)
		{
			InputIterator firstCpy = first;
			size_type iteratorDiff = 0;
			int index = 0;

			while(firstCpy != last)
			{
				firstCpy++;
				iteratorDiff++;
			}
			this->_size = iteratorDiff;
			this->_capacity = iteratorDiff;
			this->_vector = this->_allocator.allocate(this->_capacity);
			while (first != last)
			{
				this->_vector[index] = *first;
				first++;
				index++; 
			}
		}

		//copy
		vector (const vector& x)
		{
			this->_allocator = x._allocator;
			*this = x;
		}

		~vector(void)
		{
			for (size_type i = 0; i < this->_size; i++)
			{
				if (this->_vector[i])
					this->_allocator.destroy(this->_vector + i);
			}
			this->_allocator.deallocate(this->_vector, this->_capacity);
		}

		vector &operator=(const vector& x)
		{
			this->_size = x._size;
			this->_capacity = x._capacity;
			this->_vector = this->_allocator.allocate(this->_capacity);
			for (size_type i = 0; i < x._size; i++)
				this->_vector[i] = x[i];
			return *this;
		}

		/*
		 *
		 * Element access methods
		 *
		*/

		reference
		operator[] (size_type n)
		{ return this->_vector[n]; }

		const_reference
		operator[] (size_type n) const
		{ return this->_vector[n]; };
	};
}
#endif