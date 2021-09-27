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
			this->_stack.push_back();
		}

		void pop()
		{
			this->_stack.pop_back();
		}

	private:

		container_type _stack;
	};
}

#endif