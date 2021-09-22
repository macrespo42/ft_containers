#ifndef ITERATOR
#define ITERATOR

#include <cstddef>
#include <iostream>

namespace ft
{
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	template <class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef random_access_iterator_tag iterator_category;
	};

	template <class T>
	struct iterator_traits<T*>
	{
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef random_access_iterator_tag iterator_category;
	};

	template <class T>
	struct iterator_traits<const T*>
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
	public:

		typedef Iterator iterator_type;
		typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
		typedef typename iterator_traits<Iterator>::value_type value_type;
		typedef typename iterator_traits<Iterator>::difference_type difference_type;;
		typedef typename iterator_traits<Iterator>::pointer pointer;
		typedef typename iterator_traits<Iterator>::reference reference;

		reverse_iterator(void)
		{
			this->_it = Iterator();
		}

		explicit reverse_iterator (iterator_type it)
		{
			this->_it = it;
		}

		template <class Iter>
  		reverse_iterator (const reverse_iterator<Iter>& rev_it)
  		{
  			this->_it = rev_it.base();
  		}

  		reverse_iterator &operator=(reverse_iterator const &x)
  		{
  			this->_it = x._it;
  			return *this;
  		}

  		iterator_type
  		base(void) const
  		{
  			Iterator cpy = this->_it;
  			return cpy;
  		}

  		reference
  		operator*(void) const
  		{
  			iterator_type tmp;
  			tmp = this->_it;
  			return *--tmp;
  		}

  		reverse_iterator
  		operator+(difference_type n) const
  		{
  			return reverse_iterator(this->base() - n);
  		}

  		reverse_iterator
  		operator-(difference_type n) const
  		{
  			return reverse_iterator(this->base() + n);
  		}

  		reverse_iterator&
  		operator++(void)
  		{
  			this->_it--;
  			return *this;
  		}

  		reverse_iterator
  		operator++(int)
  		{
  			reverse_iterator<Iterator> tmp(*this);
  			this->_it--;
  			return tmp;
  		}

  		reverse_iterator&
  		operator--(void)
  		{
  			this->_it.operator++();
  			return *this;
  		}

		reverse_iterator
		operator--(int)
		{
			reverse_iterator<Iterator> tmp(*this);
  			this->_it.operator++(0);
  			return tmp;
		}

		reverse_iterator&
		operator+=(difference_type n)
		{
			this->_it.operator-=(n);
			return *this;
		}

		reverse_iterator&
		operator-=(difference_type n)
		{
			this->_it.operator+=(n);
			return *this;
		}

		reference
		operator[](difference_type n) const
		{
			return base()[-n-1];
		}

		pointer
		operator->() const
		{
			return &(operator*());
		}

		template< class Iterator1, class Iterator2 >
		friend bool
		operator==(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
		{
			return lhs.base() == rhs.base();
		}

		template< class Iterator1, class Iterator2 >
		friend bool
		operator!=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
		{
			return lhs.base() != rhs.base();
		}

		template< class Iterator1, class Iterator2 >
		friend bool
		operator<(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
		{
			return lhs.base() > rhs.base();
		}

		template< class Iterator1, class Iterator2 >
		friend bool
		operator<=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
		{
			return lhs.base() >= rhs.base();
		}

		template< class Iterator1, class Iterator2 >
		friend bool
		operator>(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
		{
			return lhs.base() < rhs.base();
		}

		template< class Iterator1, class Iterator2 >
		friend bool
		operator>=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
		{
			return lhs.base() <= rhs.base();
		}

		friend reverse_iterator
		operator+(int n, reverse_iterator const& rhs)
		{
			return reverse_iterator(rhs.base() - n);
		}

	private:

		Iterator _it;

	};

	template <bool flag, class IsTrue, class IsFalse>	
	struct is_const {};

	template<class IsTrue, class IsFalse>
	struct is_const<true, IsTrue, IsFalse> { typedef IsTrue value; };

	template<class IsTrue, class IsFalse>
	struct is_const<false, IsTrue, IsFalse> { typedef IsFalse value; };
}

#endif