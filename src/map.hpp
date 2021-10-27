#ifndef MAP
#define MAP

#include <memory>
#include "iterator.hpp"
#include "algorithm.hpp"
#include <stdexcept>
#include <functional>

namespace ft
{
    template <class Key, class T, class compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key, T> > >
    class map
    {

    };
}

#endif