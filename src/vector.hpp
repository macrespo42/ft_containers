#ifndef VECTOR
#define VECTOR

#include <memory>
#include "iterator.hpp"
#include "vector_iterator.hpp"
#include "type_traits.hpp"
#include <stdexcept>

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
	public:

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
		typedef vector_iterator<T, true> iterator;
		typedef vector_iterator<T, false> const_iterator;
		typedef std::ptrdiff_t difference_type;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef std::size_t size_type;

	private:
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
			for (size_t i = 0; i < n; i++)
				this->_allocator.construct(this->_vector + i, val);
		}

		// range
		template <class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), 
			typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0 ) :
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
			this->_size = x._size;
			this->_capacity = x._capacity;
			this->_vector = this->_allocator.allocate(this->_capacity);

			for (size_type i = 0 ; i < this->_size ; i++)
				this->_allocator.construct(_vector + i, x[i]);
		}

		~vector(void)
		{
			for (size_type i = 0; i < this->_size; i++)
			{
				this->_allocator.destroy(this->_vector + i);
			}
			this->_allocator.deallocate(this->_vector, this->_capacity);
		}

		vector &
		operator=(const vector& x)
		{
			this->_allocator = x._allocator;
			this->_size = x._size;
			this->reserve(x._size);
			for (size_type i = 0; i < x._size; i++)
				this->_allocator.construct(this->_vector + i, x[i]);
			return *this;
		}

		/*
		 *
		 * Iterators
		 *
		 */

		iterator
		begin()
		{
			iterator first(this->_vector);
			return first;
		}

		const_iterator
		begin() const
		{
			const_iterator first(this->_vector);
			return first;
		}

		iterator
		end()
		{
			iterator last(this->_vector + this->_size);
			return last;
		}

		const_iterator
		end() const
		{
			const_iterator last(this->_vector + this->_size);
			return last;
		}

		reverse_iterator
		rbegin()
		{
			reverse_iterator first(this->end());
			return first;
		}

		const_reverse_iterator
		rbegin() const
		{
			const_reverse_iterator first(this->end());
			return first;
		}

		reverse_iterator
		rend()
		{
			reverse_iterator last(this->begin());
			return last;
		}

		const_reverse_iterator
		rend() const
		{
			reverse_iterator last(this->begin());
			return last;
		}

		/*
		 *
		 * Capacity
		 *
		 */

		size_type
		size() const
		{
			return this->_size;
		}

		size_type
		capacity() const
		{
			return this->_capacity;
		}

		void
		reserve(size_type n)
		{
			if (n <= this->_capacity)
				return ;
			pointer vector;

			vector = this->_allocator.allocate(n);
			this->_capacity = n;
			for (size_type i = 0; i < this->_size; i++)
			{
				this->_allocator.construct(vector + i, this->_vector[i]);
				this->_allocator.destroy(this->_vector + i);
			}
			this->_allocator.deallocate(this->_vector, this->_capacity);
			this->_vector = vector;
		}

		size_type
		max_size() const
		{
			return this->_allocator.max_size();
		}

		void
		resize(size_type n, value_type val = value_type())
		{
			bool inf = false;
			while (this->_size > n)
			{
				this->pop_back();
				inf = true;
			}
			if (inf == true)
				return ;
			if (this->_capacity < n)
				this->reserve(n);
			while (this->_size < n)
				this->push_back(val);
		}

		bool empty() const
		{
			return this->_size == 0;
		}

		/*
		 *
		 * Element access methods
		 *
		 */

		reference
		operator[] (size_type n)
		{
			return this->_vector[n];
		}

		const_reference
		operator[] (size_type n) const
		{
			return this->_vector[n];
		}

		reference
		at(size_type n)
		{
			if (n > this->_size)
				throw std::out_of_range("");
			return this->_vector[n];
		}

		const_reference
		at(size_type n) const
		{
			if (n > this->_size)
				throw std::out_of_range("");
			return this->_vector[n];
		}

		reference
		front(void)
		{
			return this->at(0);
		}

		const_reference
		front() const
		{
			return this->at(0);
		}

		reference
		back()
		{
			return this->at(this->_size - 1);
		}

		const_reference
		back() const
		{
			return this->at(this->_size - 1);
		}

		/*
		 *
		 * Modifiers
		 *
		 */

        template <class InputIterator>
		void
		assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
		{
			this->clear();
			size_type diff = 0;
			for (InputIterator it = first; it != last; it++)
				diff++;
			if (diff > this->_capacity)
			{
				this->reserve(diff);
				this->_size = this->_capacity;
				size_type i = 0;
				while (first != last)
				{
					this->_vector[i] = *first;
					i++;
					first++;
				}
				return ;
			}
			while (first != last)
			{
				this->push_back(*first);
				first++;
			}
		}

		void
		assign(size_type n, const value_type& val)
		{
			this->clear();
			if (n > this->_capacity)
			{
				this->reserve(n);
				this->_size = this->_capacity;
				for (size_type i = 0; i < n; i++)
					this->_vector[i] = val;
				return ;
			}
			for (size_type i = 0; i < n; i++)
				this->push_back(val);
		}

		void
		push_back(const value_type& val)
		{
			if (this->_size + 1 > this->_capacity)
			{
				if (this->_capacity == 0)
					reserve(1);
				else
					reserve(this->_capacity * 2);
			}
			this->_vector[this->_size++] = val;
		}

		void
		pop_back()
		{
			if (this->_size > 0)
			{
				this->_allocator.destroy(this->_vector + this->_size - 1);
				this->_size -= 1;
			}
		}

		iterator
		insert(iterator position, const value_type& val)
		{
			pointer tmp;

			tmp = this->_allocator.allocate(this->_size + 1);
			iterator it = this->begin();
			size_type i = 0;
			size_type ret = 0;
			while (it != this->end())
			{
				if (it == position)
				{
					ret = i;
					this->_allocator.construct(tmp + i, val);
					this->_size++;
					i++;
				}
				this->_allocator.construct(tmp + i, *it);
				i++;
				it++;
			}
			if (position == this->end())
			{
				ret = i;
				this->_allocator.construct(tmp + i, val);
				i++;
				this->_size++;
			}
			if (this->_size + 1 > this->_capacity && this->_capacity == 0)
				this->reserve(1);
			else if (this->_size + 1 > this->_capacity)
				this->reserve(this->_capacity * 2);
			this->_vector = tmp;
			return tmp + ret;
		}

		void
		insert(iterator position, size_type n, const value_type& val)
		{
			pointer tmp;

			tmp = this->_allocator.allocate(this->_size + n);
			iterator it = this->begin();
			size_type i = 0;
			while (it != this->end())
			{
				if (it == position)
				{
					for (size_type fill = 0; fill < n; fill++)
					{
						this->_allocator.construct(tmp + i, val);
						i++;
					}
				}
				this->_allocator.construct(tmp + i, *it);
				i++;
				it++;
			}
			if (position == this->end())
			{
				for (size_type fill = 0; fill < n; fill++)
				{
					this->_allocator.construct(tmp + i, val);
					i++;
				}
			}
			this->_size = i;
			this->reserve(this->_size);
			this->_vector = tmp;
		}

		template <class InputIterator>
		void
		insert(iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
		{
			pointer tmp;
			size_type n = 0;

			for (InputIterator len = first; len != last; len++)
				n++;
			tmp = this->_allocator.allocate(this->_size + n);
			iterator it = this->begin();
			size_type i = 0;
			while (it != this->end())
			{
				if (it == position)
				{
					for (InputIterator fill = first; fill != last; fill++)
					{
						this->_allocator.construct(tmp + i, *fill);
						i++;
					}
				}
				this->_allocator.construct(tmp + i, *it);
				i++;
				it++;
			}
			if (position == this->end())
			{
				for (InputIterator fill = first; fill != last; fill++)
				{
					this->_allocator.construct(tmp + i, *fill);
					i++;
				}
			}
			this->_size = i;
			if (this->_size + 1 > this->_capacity && this->_capacity == 0)
				this->reserve(this->_size);
			else if (this->_size + 1 > this->_capacity * 2)
				this->reserve(this->_size);
			else if (this->_size + 1 > this->_capacity)
				this->reserve(this->_capacity * 2);
			this->_vector = tmp;
		}

		iterator
		erase(iterator position)
		{
			iterator cursor = position;
			while (cursor + 1 != end())
			{
				*cursor = *(cursor + 1);
				cursor++;
			}
			this->_size--;
			return (iterator(position));
		}

		iterator
		erase(iterator first, iterator last)
		{
			while (first != last)
			{
				erase(first);
				last--;
			}
			return (iterator(first));
		}

		void
		clear()
		{
			this->_size = 0;
		}
	};
}
#endif