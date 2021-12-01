#ifndef _SET
#define _SET

#include <memory>
#include "iterator.hpp"
#include "algorithm.hpp"
#include <stdexcept>
#include <functional>
#include "utility.hpp"
#include "map_iterator.hpp"
#include "set_rb_tree.hpp"

namespace ft
{
    template < class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
    class set
    {

        public:
        
        class Value_compare
        {
            friend class set;
            protected:
            Compare comp;
            Value_compare (Compare c) : comp(c) {}
            public:
            typedef T value_type;
            typedef bool result_type;
            typedef value_type first_argument_type;
            typedef value_type second_argument_type;
            bool operator() (const value_type& x, const value_type& y) const
            {
                return comp(x.first, y.first);
            }
        };

        typedef T value_type;
        typedef T key_type;
        typedef Value_compare value_compare;
        typedef Compare key_compare;
        typedef Alloc allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef node<value_type> node_type;
        typedef map_iterator<value_type ,node_type, true> iterator;
        typedef map_iterator<value_type ,node_type, false> const_iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef typename iterator_traits<iterator>::difference_type difference_type;
        typedef size_t size_type;

        private:

        size_type _size;
        allocator_type _allocator;
        ft::rb_tree<value_type, Compare, Alloc> _set;
        key_compare _cmp;

        public:

        explicit set (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
        _size(0),
        _allocator(alloc),
        _cmp(comp)
        {}

        template <class InputIterator>
        set (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
        _size(0),
        _allocator(alloc),
        _cmp(comp)
        {
            for (InputIterator current = first; current != last; current++)
                insert(*current);
        }

        set(const set& x) :
        _size(0)
        {
            *this = x;
        }
    };
}

#endif