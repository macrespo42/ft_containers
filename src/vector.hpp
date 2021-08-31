#ifndef VECTOR
#define VECTOR

#include <memory>

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
		/* TO DO
		iterator
		const_iterator
		reverse_iterator
		const_reverse_iterator
		difference_type
		*/
		typedef std::size_t size_type;

		size_type _size;
		size_type _capacity;
		pointer  _vector;
		allocator_type allocator;

	public:

		/*
		 *
		 * CONSTRUCTORS
		 *
		 */

		explicit vector (const allocator_type& alloc = allocator_type()) : _size(0), _capacity(0), allocator(alloc)
		{
			this->_vector = allocator.allocate(0);
		}
	};
}
#endif