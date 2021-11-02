#ifndef MAP_ITERATOR
#define MAP_ITERATOR

#include "iterator.hpp"
#include "type_traits.hpp"
#include <iostream>

namespace ft
{
    template<class T, bool isConst>
    class map_iterator
    {
        public:

        typedef std::ptrdiff_t difference_type;
		typedef typename ft::is_const<IsConst, T*, const T*>::value value_type;
		typedef typename value_type* pointer;
		typedef typename value_type& reference;
		typedef bidirectional_iterator_tag iterator_category;

        private:


    };
}

#endif