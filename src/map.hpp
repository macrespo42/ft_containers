#ifndef MAP
#define MAP

#include <memory>
#include "iterator.hpp"
#include "algorithm.hpp"
#include <stdexcept>
#include <functional>
#include "utility.hpp"
#include "rb_tree.hpp"
#include "map_iterator.hpp"

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
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef map_iterator<T, true> iterator;
        typedef map_iterator<T, false> const_iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef typename iterator_traits<iterator>::difference_type difference_type;
        typedef size_t size_type;

        private:

        size_type _size;
        allocator_type _allocator;
        ft::rb_tree<value_type> _map;
        compare _cmp;

        public:

		/*
		 *
		 * CONSTRUCTORS
		 *
		 */


        // default
        explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
        _size(0),
        _allocator(alloc),
        _cmp(comp)
        {}

        //range
        template <class InputIterator>
        map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
        {
            size_type size;

            size = 0;
            for (InputIterator current = first; current != last; current++)
            {
                _map->insert_node(*current);
                size++;
            }
            _size = size;
        }

        map(const map& x);

		/*
		 *
		 * CAPACITY
		 *
		 */

        bool
        empty() const
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
            return _allocator.max_size();
        }

		/*
		 *
		 * Iterators
		 *
		 */

        iterator
        begin()
        {
            return (iterator(_map.left_most()));
        }

        const_iterator
        begin() const
        {
            return (const_iterator(_map.left_most()));
        }

        iterator
        end()
        {
            return (iterator(_map.get_nil_node()));
        }

        const_iterator
        end()const
        {
            return (const_iterator(_map.get_nil_node()));
        }

        reverse_iterator
        rbegin()
        {
            return (reverse_iterator(_map.get_nil_node()));
        }

        const_reverse_iterator
        rbegin() const
        {
            return (const_reverse_iterator(_map.get_nil_node()));
        }

        reverse_iterator
        rend()
        {
            return (reverse_iterator(_map.left_most()));
        }

        const_reverse_iterator
        rend() const
        {
            return (const_reverse_iterator(_map.left_most()));
        }

		/*
		 *
		 * Element Access
		 *
		 */

        mapped_type&
        operator[](const key_type& k)
        {
            return (*((this->insert(make_pair(k,mapped_type()))).first)).second;
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
            if (!count(val))
            {
                _map.insert_node(val);
                _size++;
                inserted = true;
            }
            return ft::make_pair(iterator(find(val.first), inserted));
        }

        iterator
        insert(iterator position, const value_type& val)
        {
            (void)position;
            if (!count(val))
            {
                _map.insert_node(val);
                _size++;
            }
            return iterator(val);
        }

        template <class InputIterator>
        void
        insert(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
        {
            while (first != last)
            {
                insert(first.base());
                first++;
            }
        }

		/*
		 *
		 * Operations
		 *
		 */

        iterator
        find(const key_type& k)
        {
            return iterator(_map.search(k));
        }
      
        const_iterator
        find(const key_type& k) const
        {
            return const_iterator(_map.search(k));
        }

        size_type
        count(const key_type& k) const
        {
            if (!_map.search(k))
                return 0;
            return 1;
        }

        iterator
        lower_bound(const key_type& k)
        {
            iterator it(_map.search(k));
            if (it.base() == NULL)
            {
                iterator tmp(_map.get_next_node(k));
                if (tmp->item.first > k)
                    tmp++;
                it = tmp;
            }
            return it;
        }

        const_iterator
        lower_bound(const key_type& k) const
        {
            const_iterator it(_map.search(k));
            if (it.base() == NULL)
            {
                const_iterator tmp(_map.get_next_node(k));
                if (tmp->item.first > k)
                    tmp++;
                it = tmp;
            }
            return it;
        }

        iterator
        upper_bound(const key_type& k)
        {
            iterator it(_map.search(k));
            if (it.base() == NULL)
                return iterator(_map.get_next_node(k));
            return ++it;
        }

        const_iterator
        upper_bound(const key_type& k) const
        {
            const_iterator it(_map.search(k));
            if (it.base() == NULL)
                return const_iterator(_map.get_next_node(k));
            return ++it;
        }

        allocator_type
        get_allocator() const
        {
            return allocator_type();
        }
    };
}

#endif