/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MultiSet.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skybt <skybt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 15:03:58 by skybt             #+#    #+#             */
/*   Updated: 2020/08/10 19:38:43 by skybt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTISET_HPP
#define MULTISET_HPP

#include "Utility.hpp"
#include "AVLTree.hpp"

namespace ft
{
    template <typename Key, typename Compare = Less<Key>>
    class MultiSet
    {

    public:
        typedef Key key_type;
        typedef Key value_type;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        typedef Compare key_compare;
        typedef Compare value_compare;
        typedef Key &reference;
        typedef const Key &const_reference;
        typedef Key *pointer;
        typedef const Key *const_pointer;
        typedef typename AVLTree<Key, Compare, true>::iterator iterator;
        typedef typename AVLTree<Key, Compare, true>::const_iterator const_iterator;
        typedef ReverseIterator<iterator> reverse_iterator;
        typedef ReverseIterator<const_iterator> const_reverse_iterator;

    private:
        typedef AVLTree<Key, Compare, true> _tree_type;
        typedef MultiSet<Key, Compare> _Self;

        _tree_type _tree;

    public:
        MultiSet(const Compare &comp = Compare())
            : _tree(comp) {}

        template <typename InputIt>
        MultiSet(InputIt first, InputIt last, const value_compare &comp = value_compare())
            : _tree(first, last, comp) {}

        MultiSet(const _Self &o)
            : _tree(o._tree) {}

        ~MultiSet() {}

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
            return _tree.count(k);
        }

        iterator find(const key_type &k)
        {
            return _tree.find(k);
        }

        const_iterator find(const key_type &k) const
        {
            return _tree.find(k);
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
            return _tree.lower_bound(k);
        }

        const_iterator lower_bound(const key_type &k) const
        {
            return _tree.lower_bound(k);
        }

        iterator upper_bound(const key_type &k)
        {
            return _tree.upper_bound(k);
        }

        const_iterator upper_bound(const key_type &k) const
        {
            return _tree.upper_bound(k);
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

    template <typename Key, typename Compare>
    void swap(MultiSet<Key, Compare> &x, MultiSet<Key, Compare> &y)
    {
        x.swap(y);
    }

    template <typename Key, typename Compare>
    bool operator==(const MultiSet<Key, Compare> &lhs, const MultiSet<Key, Compare> &rhs)
    {
        if (lhs.size() != rhs.size())
            return false;

        return equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    template <typename Key, typename Compare>
    bool operator!=(const MultiSet<Key, Compare> &lhs, const MultiSet<Key, Compare> &rhs)
    {
        return !(lhs == rhs);
    }

    template <typename Key, typename Compare>
    bool operator<(const MultiSet<Key, Compare> &lhs, const MultiSet<Key, Compare> &rhs)
    {
        return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <typename Key, typename Compare>
    bool operator>=(const MultiSet<Key, Compare> &lhs, const MultiSet<Key, Compare> &rhs)
    {
        return !(lhs < rhs);
    }

    template <typename Key, typename Compare>
    bool operator>(const MultiSet<Key, Compare> &lhs, const MultiSet<Key, Compare> &rhs)
    {
        return rhs < lhs;
    }

    template <typename Key, typename Compare>
    bool operator<=(const MultiSet<Key, Compare> &lhs, const MultiSet<Key, Compare> &rhs)
    {
        return !(lhs > rhs);
    }
} // namespace ft

#endif
