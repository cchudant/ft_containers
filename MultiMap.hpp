/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MultiMap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skybt <skybt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 23:30:02 by cchudant          #+#    #+#             */
/*   Updated: 2020/08/10 19:38:45 by skybt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTI_MAP_HPP
#define MULTI_MAP_HPP

#include "Utility.hpp"
#include "AVLTree.hpp"

namespace ft
{
    template <typename Key, typename T, typename Compare = Less<Key>>
    class MultiMap
    {
    public:
        typedef Key key_type;
        typedef T mapped_type;
        typedef Pair<const key_type, mapped_type> value_type;
        typedef Compare key_compare;
        typedef value_type &reference;
        typedef const value_type &const_reference;
        typedef value_type *pointer;
        typedef const value_type *const_pointer;
        typedef ptrdiff_t difference_type;
        typedef size_t size_type;

        class value_compare
        {
        private:
            key_compare _cmp;

            value_compare(key_compare c) : _cmp(c)
            {
            }

            value_compare &operator=(const value_compare &o);

        public:
            typedef bool result_type;
            typedef value_type first_argument_type;
            typedef value_type second_argument_type;

            ~value_compare()
            {
            }

            value_compare(const value_compare &o) : _cmp(o._cmp)
            {
            }

            bool operator()(const value_type &x, const value_type &y) const
            {
                return _cmp(x.first, y.first);
            }

            template <typename _Key, typename _T, typename _Compare>
            friend class MultiMap;
        };

        typedef typename AVLTree<value_type, value_compare, true>::iterator iterator;
        typedef typename AVLTree<value_type, value_compare, true>::const_iterator const_iterator;
        typedef ReverseIterator<iterator> reverse_iterator;
        typedef ReverseIterator<const_iterator> const_reverse_iterator;

    private:
        typedef AVLTree<value_type, value_compare, true> _tree_type;
        typedef MultiMap<Key, T, Compare> _Self;

        _tree_type _tree;

    public:
        MultiMap(const key_compare &cmp = key_compare())
            : _tree(value_compare(cmp)) {}

        template <typename InputIt>
        MultiMap(InputIt first, InputIt last, const key_compare &cmp = key_compare())
            : _tree(first, last, value_compare(cmp)) {}

        MultiMap(const _Self &o)
            : _tree(o._tree) {}

        ~MultiMap() {}

        _Self &operator=(const _Self &o)
        {
            _tree = o._tree;
            return *this;
        }

        iterator begin()
        {
            return _tree.begin();
        }

        const_iterator begin() const
        {
            return _tree.begin();
        }

        iterator end()
        {
            return _tree.end();
        }

        const_iterator end() const
        {
            return _tree.end();
        }

        reverse_iterator rbegin()
        {
            return _tree.rbegin();
        }

        const_reverse_iterator rbegin() const
        {
            return _tree.rbegin();
        }

        reverse_iterator rend()
        {
            return _tree.rend();
        }

        const_reverse_iterator rend() const
        {
            return _tree.rend();
        }

        bool empty() const
        {
            return _tree.empty();
        }

        size_type size() const
        {
            return _tree.size();
        }

        size_type max_size() const
        {
            return _tree.max_size();
        }

        void clear()
        {
            _tree.clear();
        }

        Pair<iterator, bool> insert(const value_type &val)
        {
            return _tree.insert(val);
        }

        iterator insert(iterator hint, const value_type &val)
        {
            return _tree.insert(hint, val).first;
        }

        template <typename InputIt>
        void insert(InputIt first, InputIt last)
        {
            _tree.insert(first, last);
        }

        void erase(iterator position)
        {
            _tree.erase(position);
        }

        size_type erase(const key_type &k)
        {
            iterator ite = find(k);
            if (ite == end())
                return 0;

            _tree.erase(ite);
            return 1;
        }

        void erase(iterator first, iterator last)
        {
            _tree.erase(first, last);
        }

        void swap(_Self &x)
        {
            ft::swap(_tree, x._tree);
        }

        size_type count(const key_type &k) const
        {
            return _tree.count(make_pair(k, mapped_type()));
        }

        iterator find(const key_type &k)
        {
            return _tree.find(make_pair(k, mapped_type()));
        }

        const_iterator find(const key_type &k) const
        {
            return _tree.find(make_pair(k, mapped_type()));
        }

        Pair<iterator, iterator> equal_range(const key_type &k)
        {
            return make_pair(lower_bound(k), upper_bound(k));
        }

        Pair<const_iterator, const_iterator> equal_range(const key_type &k) const
        {
            return make_pair(lower_bound(k), upper_bound(k));
        }

        iterator lower_bound(const key_type &k)
        {
            return _tree.lower_bound(make_pair(k, mapped_type()));
        }

        const_iterator lower_bound(const key_type &k) const
        {
            return _tree.lower_bound(make_pair(k, mapped_type()));
        }

        iterator upper_bound(const key_type &k)
        {
            return _tree.upper_bound(make_pair(k, mapped_type()));
        }

        const_iterator upper_bound(const key_type &k) const
        {
            return _tree.upper_bound(make_pair(k, mapped_type()));
        }

        key_compare key_comp() const
        {
            return _tree.comparator()._cmp;
        }

        value_compare value_comp() const
        {
            return _tree.comparator();
        }

        // void debug() const { _tree.debug(); }
    };

    template <typename Key, typename T, typename Compare>
    void swap(MultiMap<Key, T, Compare> &x, MultiMap<Key, T, Compare> &y)
    {
        x.swap(y);
    }

    template <typename Key, typename T, typename Compare>
    bool operator==(const MultiMap<Key, T, Compare> &lhs, const MultiMap<Key, T, Compare> &rhs)
    {
        if (lhs.size() != rhs.size())
            return false;

        return equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    template <typename Key, typename T, typename Compare>
    bool operator!=(const MultiMap<Key, T, Compare> &lhs, const MultiMap<Key, T, Compare> &rhs)
    {
        return !(lhs == rhs);
    }

    template <typename Key, typename T, typename Compare>
    bool operator<(const MultiMap<Key, T, Compare> &lhs, const MultiMap<Key, T, Compare> &rhs)
    {
        return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), lhs.value_comp());
    }

    template <typename Key, typename T, typename Compare>
    bool operator>=(const MultiMap<Key, T, Compare> &lhs, const MultiMap<Key, T, Compare> &rhs)
    {
        return !(lhs < rhs);
    }

    template <typename Key, typename T, typename Compare>
    bool operator>(const MultiMap<Key, T, Compare> &lhs, const MultiMap<Key, T, Compare> &rhs)
    {
        return rhs < lhs;
    }

    template <typename Key, typename T, typename Compare>
    bool operator<=(const MultiMap<Key, T, Compare> &lhs, const MultiMap<Key, T, Compare> &rhs)
    {
        return !(lhs > rhs);
    }
} // namespace ft

#endif
