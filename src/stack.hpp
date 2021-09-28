#ifndef STACK
#define STACK

#include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
	public:
		typedef T value_type;
		typedef Container container_type;
		typedef size_t size_type;

		explicit stack (const container_type& ctnr = container_type()) : _stack(ctnr)
		{}

		stack& operator=(const stack& other)
		{
			this->_stack = other.stack;
		}

		bool empty() const
		{
			return this->_stack.empty();
		}

		size_type size() const
		{
			return this->_stack.size();
		}

		value_type& top()
		{
			return this->_stack.back();
		}

		const value_type& top() const
		{
			return this->_stack.back();
		}

		void push(const value_type& val)
		{
			this->_stack.push_back(val);
		}

		void pop()
		{
			this->_stack.pop_back();
		}

		friend bool
		operator==(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
		{
			return lhs._stack == rhs._stack;
		}

		friend bool
		operator!=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
		{
			return !(lhs._stack == rhs._stack);
		}

		friend bool
		operator<(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
		{
			return lhs._stack < rhs._stack;
		}

		friend bool
		operator<=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
		{
			return !(rhs._stack < lhs._stack);
		}

		friend bool
		operator>(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
		{
			return (rhs._stack < lhs._stack);
		}

		friend bool
		operator>=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
		{
			return !(lhs._stack < rhs._stack);
		}

	private:

		container_type _stack;
	};
}

#endif