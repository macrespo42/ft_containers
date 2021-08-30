#ifndef VECTOR
#define VECTOR

#include <memory>

template < class T, class Alloc = std::allocator<T> >
class vector
{
private:
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

};

#endif