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

	private:

		container_type _stack;
	};
}

#endif