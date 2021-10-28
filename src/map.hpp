#ifndef MAP
#define MAP

#include <memory>
#include "iterator.hpp"
#include "algorithm.hpp"
#include <stdexcept>
#include <functional>
#include "utility.hpp"

namespace ft
{
    template <class Key, class T, class compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
    class map
    {
        public:

        typedef ft::pair<const Key, T> value_type;
        typedef Key key_type;
        typedef T mapped_type;
        typedef compare key_compare;
        // value_compare;
        typedef Alloc allocator_type;
        typedef allocator_type::reference reference;
        typedef allocator_type::const_reference const_reference;
        typedef allocator_type::pointer pointer;
        typedef allocator_type::const_pointer pointer;
        typedef size_t size_type;

        private:

        size_type _size;
        allocator_type _allocator;
        ft::rb_tree<value_type> _map;
    };
}

#endif