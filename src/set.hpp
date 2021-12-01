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

		/*
		 *
		 * CONSTRUCTORS
		 *
		 */

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

        ~set()
        {
            clear();
        }

        set& operator= (const set& x)
        {
            if (this == &x)
                return *this;
            clear();
            _allocator = x._allocator;
            _cmp = x._cmp;
            for (const_iterator it = x.begin(); it != x.end(); it++)
                insert(*it);
            return *this;
        }

		/*
		 *
		 * Iterators
		 *
		 */

        iterator begin()
        {
            return (iterator(_set.left_most()));
        }

        const_iterator
        begin() const
        {
            return (const_iterator(_set.left_most()));
        }

        iterator end()
        {
            return (iterator(_map.get_nil_node()));
        }

        const_iterator end() const
        {
            return (const_iterator(_map.get_nil_node()));
        }

        reverse_iterator rbegin()
        {
            return (reverse_iterator(_map.get_nil_node()));
        }

        const_reverse_iterator rbegin() const
        {
            return (const_reverse_iterator(_map.get_nil_node()));
        }

		/*
		 *
		 * CAPACITY
		 *
		 */

        bool empty() const
        {
            return _size == 0;
        }

        size_type
        size() const
        {
            return _size;
        }

        size_type
        max_size() const
        {
            return _set.get_allocator().max_size();
        }

		/*
		 *
		 * Modifiers
		 *
		 */

        pair<iterator,bool>
        insert(const value_type& val)
        {
            bool inserted = false;
            if (count(val) == 0)
            {
                _set.insert_node(val);
                _size++;
                inserted = true;
            }
            return ft::make_pair(iterator(find(val)), inserted);
        }

        iterator
        insert(iterator position, const value_type& val)
        {
            (void)position;
            if (count(val) == 0)
            {
                _set.insert_node(val);
                _size++;
            }
            return iterator(find(val));
        }

        template <class InputIterator>
        void
        insert(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
        {
            while (first != last)
            {
                insert(first);
                first++;
            }
        }

        void
        erase(iterator position)
        {
            key_type to_delete = position.base()->item;
            if (count(to_delete))
            {
                _size--;
                _set.delete_by_key(to_delete);
            }
        }

        size_type
        erase(const value_type& k)
        {
            if (count(k))
            {
                _set.delete_by_key(k);
                _size--;
                return 1;
            }
            return 0;
        }

        void
        erase(iterator first, iterator last)
        {
            for (iterator prev = first, next = ++iterator(first); prev != last; prev = next, ++next)
                erase(prev);
        }

        void swap (set& x)
        {
            ft::swap(_size, x._size);
            ft::swap(_allocator, x._allocator);
            _set.swap_root(x._set);
            ft::swap(_cmp, x._cmp);
        }

        void clear()
        {
            for (iterator prev = begin(), next = ++iterator(begin()); prev != end(); prev = next, ++next) {
                erase(prev);
            }
        }
    };
}

#endif