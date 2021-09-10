#ifndef ITERATOR
#define ITERATOR

#include <cstddef>

namespace ft
{
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	template <class Iterator>
	class iterator_traits
	{
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef random_access_iterator_tag iterator_category;
	};

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
	class reverse_iterator
	{
	private:

		typedef Iterator iterator_type;
		typedef iterator_traits<Iterator>::iterator_category iterator_category;
		typedef iterator_traits<Iterator>::value_type value_type;
		typedef iterator_traits<Iterator>::difference_type difference_type;;
		typedef iterator_traits<Iterator>::pointer pointer;
		typedef iterator_traits<Iterator>::reference reference;

	};

	template <bool flag, class IsTrue, class IsFalse>	
	struct is_const {};

	template<class IsTrue, class IsFalse>
	struct is_const<true, IsTrue, IsFalse> { typedef IsTrue value; };

	template<class IsTrue, class IsFalse>
	struct is_const<false, IsTrue, IsFalse> { typedef IsFalse value; };
}

#endif