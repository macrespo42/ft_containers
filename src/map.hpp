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

        class Value_compare
        {
            friend class map;
            protected:
            compare comp;
            Value_compare (compare c) : comp(c) {}
            public:
            typedef ft::pair<const Key, T> value_type;
            typedef bool result_type;
            typedef value_type first_argument_type;
            typedef value_type second_argument_type;
            bool operator() (const value_type& x, const value_type& y) const
            {
                return comp(x.first, y.first);
            }
        };

        typedef ft::pair<const Key, T> value_type;
        typedef Key key_type;
        typedef T mapped_type;
        typedef compare key_compare;
        typedef Value_compare value_compare;
        typedef Alloc allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef rb_node<value_type> node_type;
        typedef map_iterator<value_type ,node_type, true> iterator;
        typedef map_iterator<value_type ,node_type, false> const_iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef typename iterator_traits<iterator>::difference_type difference_type;
        typedef size_t size_type;

        private:

        size_type _size;
        allocator_type _allocator;
        ft::rb_tree<key_type, mapped_type, key_compare, value_compare, allocator_type> _map;
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
        map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
        _size(0),
        _allocator(alloc),
        _cmp(comp)
        {   
            for (InputIterator current = first; current != last; current++)
            {
                _map.insert_node(*current);
                _size++;
            }
        }

        map(const map& x) :
        _size(0)
        {
            *this = x;
        }

        map&
        operator=(const map& x)
        {
            if (this == &x)
                return *this;
            clear();
            _allocator = x._allocator;
            _cmp = x._cmp;
            for (const_iterator it = x.begin(); it != x.end();  it++)
                insert(*it);
            return *this;
        }

        ~map(void)
        {
            clear();
        }

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
            return _map.get_allocator().max_size();
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
            return (*((this->insert(ft::make_pair(k,mapped_type()))).first)).second;
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
            if (!count(val.first))
            {
                _map.insert_node(val);
                _size++;
                inserted = true;
            }
            return ft::make_pair(iterator(find(val.first)), inserted);
        }

        iterator
        insert(iterator position, const value_type& val)
        {
            (void)position;
            if (!count(val.first))
            {
                _map.insert_node(val);
                _size++;
            }
            return iterator(find(val.first));
        }

        template <class InputIterator>
        void
        insert(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
        {
            while (first != last)
            {
                insert(first.base()->item);
                first++;
            }
        }

        void
        erase(iterator position)
        {
            key_type to_delete = position.base()->item.first;
            if (count(to_delete))
            {
                _size--;
                _map.delete_by_val(to_delete);
            }
        }

        size_type
        erase(const key_type& k)
        {
            if (count(k))
            {
                _map.delete_by_val(k);
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

        void
        swap(map& x)
        {
            ft::swap(_size, x._size);
            ft::swap(_allocator, x._allocator);
            _map.swap_root(x._map);
            ft::swap(_cmp, x._cmp);
        }

        void clear()
        {
            for (iterator prev = begin(), next = ++iterator(begin()); prev != end(); prev = next, ++next)
                erase(prev);
        }

        /*
		 *
		 * Observers
		 *
		 */

        key_compare key_comp() const
        {
            return key_compare();
        }

        value_compare value_comp() const
        {
            return value_compare(_cmp);
        }

		/*
		 *
		 * Operations
		 *
		 */

        iterator
        find(const key_type& k)
        {
            node_type *k_match = _map.search(k);
            if (!k_match)
                return iterator(_map.get_nil_node());
            return iterator(k_match);
        }
      
        const_iterator
        find(const key_type& k) const
        {
            node_type *k_match = _map.search(k);
            if (!k_match)
                return const_iterator(_map.get_nil_node());
            return const_iterator(k_match);
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
                if (tmp.base()->item.first > k)
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
                if (tmp.base()->item.first > k)
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

        pair<iterator,iterator>
        equal_range (const key_type& k)
        {
            return ft::make_pair(lower_bound(k), upper_bound(k));
        }

        pair<const_iterator,const_iterator>
        equal_range (const key_type& k) const
        {
            return ft::make_pair(lower_bound(k), upper_bound(k));
        }

        allocator_type
        get_allocator() const
        {
            return allocator_type();
        }
    };
}

#endif