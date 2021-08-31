#ifndef ITERATOR
#define ITERATOR

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <class T>
class iterator_traits<T*>
{
	typedef std::ptrdiff_t difference_type;
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	typedef random_access_iterator_tag iterator_category;
};

template <class T>
class iterator_traits<const T*>
{
	typedef std::ptrdiff_t difference_type;
	typedef T value_type;
	typedef const T* pointer;
	typedef const T& reference;
	typedef random_access_iterator_tag iterator_category;	
};

template <class Iterator>
class iterator_traits
{
	typedef iterator::difference_type difference_type;
	typedef iterator::value_type value_type;
	typedef iterator::pointer pointer;
	typedef iterator::reference reference;
	typedef iterator_category::iterator_category iterator_category;
};

#endif