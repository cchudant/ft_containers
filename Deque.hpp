/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Deque.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skybt <skybt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 17:29:23 by skybt             #+#    #+#             */
/*   Updated: 2020/08/10 19:38:52 by skybt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEQUE_HPP
#define DEQUE_HPP

#define _DEQUE_BUF_SIZE 512
#define _DEQUE_BUF_SIZE_FOR(T) \
    (sizeof(T) < _DEQUE_BUF_SIZE ? size_t(_DEQUE_BUF_SIZE / sizeof(T)) : size_t(1))
#define _DEQUE_INITIAL_MAP_SIZE 8

#include "Utility.hpp"

/*
 * This implementation is heavily inspired by libstdcpp's implementation of deque.
 * See <https://gcc.gnu.org/onlinedocs/libstdc++/latest-doxygen/a00533_source.html> (stl_deque.h)
 */

namespace ft
{
    template <typename T>
    class DequeIterator
    {

    public:
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        typedef T value_type;
        typedef T *pointer;
        typedef T &reference;
        typedef RandomAccessIteratorTag iterator_category;

    private:
        typedef T **_map_pointer;
        typedef DequeIterator<T> _Self;

        pointer _cur;
        pointer _first;
        pointer _last;
        _map_pointer _node;

        static size_t _buffer_size()
        {
            return _DEQUE_BUF_SIZE_FOR(T);
        }

        // _cur should be set by the caller immediatly after
        void _set_node(_map_pointer new_node)
        {
            _node = new_node;
            _first = *new_node;
            _last = _first + difference_type(_buffer_size());
        }

        DequeIterator(pointer x, _map_pointer y)
            : _cur(x),
              _first(*y),
              _last(*y + _buffer_size()),
              _node(y) {}

    public:
        template <typename Self>
        DequeIterator(const Self &other)
            : _cur(other._cur),
              _first(other._first),
              _last(other._last),
              _node(const_cast<_map_pointer>(other._node)) {}

        DequeIterator()
            : _cur(), _first(), _last(), _node() {}

        ~DequeIterator() {}

        _Self &operator=(const _Self &other)
        {
            _cur = other._cur;
            _first = other._first;
            _last = other._last;
            _node = other._node;
            return *this;
        }

        reference operator*() const
        {
            return *_cur;
        }

        pointer operator->() const
        {
            return _cur;
        }

        // prefix increment
        _Self &operator++()
        {
            ++_cur;
            if (_cur == _last)
            {
                _set_node(_node + 1);
                _cur = _first;
            }
            return *this;
        }

        // postfix increment
        _Self operator++(int)
        {
            _Self tmp = *this;
            ++*this;
            return tmp;
        }

        // prefix decrement
        _Self &operator--()
        {
            if (_cur == _first)
            {
                _set_node(_node - 1);
                _cur = _last;
            }
            --_cur;
            return *this;
        }

        // postfix decrement
        _Self operator--(int)
        {
            _Self tmp = *this;
            --*this;
            return tmp;
        }

        _Self &operator+=(difference_type n)
        {
            difference_type offset = n + (_cur - _first);
            if (offset >= 0 && offset < difference_type(_buffer_size()))
            {
                // easy case - just add n, no node change
                _cur += n;
            }
            else
            {
                // harder case, we need to change current node
                difference_type node_offset =
                    offset > 0
                        ? offset / difference_type(_buffer_size())
                        : -difference_type((-offset - 1) / _buffer_size()) - 1;

                _set_node(_node + node_offset);
                _cur = _first + (offset - node_offset * difference_type(_buffer_size()));
            }
            return *this;
        }

        _Self operator+(difference_type n) const
        {
            _Self tmp = *this;
            return tmp += n;
        }

        _Self &operator-=(difference_type n)
        {
            return *this += -n;
        }

        _Self operator-(difference_type n) const
        {
            _Self tmp = *this;
            return tmp -= n;
        }

        difference_type operator-(_Self o) const
        {
            return difference_type(
                _buffer_size() * (_node - o._node - 1) +
                (_cur - _first) + (o._last - o._cur));
        }

        reference operator[](difference_type n) const
        {
            return *(*this + n);
        }

        void swap(_Self &other)
        {
            std::swap(_cur, other._cur);
            std::swap(_first, other._first);
            std::swap(_last, other._last);
            std::swap(_node, other._node);
        }

        template <typename _T>
        friend class Deque;

        template <typename _T>
        friend class DequeIterator;

        template <typename _T>
        friend bool operator==(const DequeIterator<_T> &x, const DequeIterator<_T> &y);

        template <typename _T>
        friend bool operator<(const DequeIterator<_T> &x, const DequeIterator<_T> &y);
    };

    template <typename T>
    bool operator==(const DequeIterator<T> &x, const DequeIterator<T> &y)
    {
        return x._cur == y._cur;
    }

    template <typename T>
    bool operator!=(const DequeIterator<T> &x, const DequeIterator<T> &y)
    {
        return !(x == y);
    }

    template <typename T>
    bool operator<(const DequeIterator<T> &x, const DequeIterator<T> &y)
    {
        return x._node == y._node ? x._cur < y.curr : x._node < y._node;
    }

    template <typename T>
    bool operator>(const DequeIterator<T> &x, const DequeIterator<T> &y)
    {
        return y < x;
    }

    template <typename T>
    bool operator<=(const DequeIterator<T> &x, const DequeIterator<T> &y)
    {
        return !(y < x);
    }

    template <typename T>
    bool operator>=(const DequeIterator<T> &x, const DequeIterator<T> &y)
    {
        return !(x < y);
    }

    template <typename T>
    bool operator+(size_t n, const DequeIterator<T> &x)
    {
        return x + n;
    }

    template <typename T>
    bool operator-(const DequeIterator<T> &lhs, const DequeIterator<T> &rhs)
    {
        return lhs - rhs;
    }

    template <typename T>
    void swap(DequeIterator<T> &x, DequeIterator<T> &y)
    {
        x.swap(y);
    }

    template <typename T>
    class Deque
    {

    public:
        typedef T value_type;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        typedef T &reference;
        typedef const T &const_reference;
        typedef T *pointer;
        typedef const T *const_pointer;
        typedef DequeIterator<T> iterator;
        typedef DequeIterator<const T> const_iterator;
        typedef ReverseIterator<iterator> reverse_iterator;
        typedef ReverseIterator<const_iterator> const_reverse_iterator;

    private:
        typedef T **_map_pointer;
        typedef Deque<T> _Self;

        _map_pointer _map;
        size_type _map_size;
        iterator _begin;
        iterator _end;

        static size_t _buffer_size()
        {
            return _DEQUE_BUF_SIZE_FOR(T);
        }

        void _initialize_map(size_type num_elems)
        {
            std::allocator<T *> map_alloc;
            size_type num_nodes = num_elems / _buffer_size() + 1;

            _map_size = max(size_type(_DEQUE_INITIAL_MAP_SIZE), size_type(num_nodes + 2));
            _map = map_alloc.allocate(_map_size);

            _map_pointer begin = _map + (_map_size - num_nodes) / 2;
            _map_pointer end = begin + num_nodes;

            // allocate nodes
            std::allocator<T> alloc;
            for (_map_pointer cur = begin; cur < end; ++cur)
                *cur = alloc.allocate(_buffer_size());

            _begin._set_node(begin);
            _begin._cur = _begin._first;
            _end._set_node(end - 1);
            _end._cur = _end._first + num_elems % _buffer_size();
        }

        void _reallocate_map(size_type nodes_to_add, bool add_at_front)
        {
            std::allocator<T *> map_alloc;

            size_type old_num_nodes = _end._node - _begin._node + 1;
            size_type new_num_nodes = old_num_nodes + nodes_to_add;

            _map_pointer new_nstart;
            if (_map_size > 2 * new_num_nodes)
            {
                new_nstart = _map + (_map_size - new_num_nodes) / 2 + (add_at_front ? nodes_to_add : 0);
                if (new_nstart < _begin._node)
                    copy(_begin._node, _end._node + 1, new_nstart);
                else
                    copy_backward(_begin._node, _end._node + 1, new_nstart + old_num_nodes);
            }
            else
            {
                size_type new_map_size = _map_size + max(_map_size, nodes_to_add) + 2;

                _map_pointer new_map = map_alloc.allocate(new_map_size);
                new_nstart = new_map + (new_map_size - new_num_nodes) / 2 + (add_at_front ? nodes_to_add : 0);
                copy(_begin._node, _end._node + 1, new_nstart);

                map_alloc.deallocate(_map, _map_size);

                _map = new_map;
                _map_size = new_map_size;
            }

            _begin._set_node(new_nstart);
            _end._set_node(new_nstart + old_num_nodes - 1);
        }

        iterator _reserve_front(size_type n)
        {
            std::allocator<T> alloc;

            size_type vacancies = _begin._cur - _begin._first;
            if (n > vacancies)
            {
                size_type new_nodes = ((n + _buffer_size() - 1) / _buffer_size());

                // reserve map front
                if (new_nodes > size_type(_begin._node - _map))
                    _reallocate_map(new_nodes, true);

                for (size_type i = 1; i <= new_nodes; ++i)
                    *(_begin._node - i) = alloc.allocate(_buffer_size());
            }
            return _begin - difference_type(n);
        }

        iterator _reserve_back(size_type n)
        {
            std::allocator<T> alloc;

            size_type vacancies = _end._last - _end._cur - 1;
            if (n > vacancies)
            {
                size_type new_nodes = ((n + _buffer_size() - 1) / _buffer_size());

                // reserve map back
                if (new_nodes + 1 > _map_size - (_end._node - _map))
                    _reallocate_map(new_nodes, false);

                for (size_type i = 1; i <= new_nodes; ++i)
                    *(_end._node + i) = alloc.allocate(_buffer_size());
            }
            return _end + difference_type(n);
        }

        void _destroy_data(iterator first, iterator last)
        {
            std::allocator<T> alloc;

            // call destructors on full nodes
            for (_map_pointer node = first._node + 1; node < last._node; ++node)
                for (pointer p = *node; p < *node + _buffer_size(); p++)
                    alloc.destroy(p); // call destructor

            if (first._node != last._node)
            {
                // call destructor on first page
                for (pointer p = first._cur; p < first._last; p++)
                    alloc.destroy(p); // call destructor
                // call destructor on last page
                for (pointer p = last._first; p < last._cur; p++)
                    alloc.destroy(p); // call destructor
            }
            else
            {
                // there is only one page
                for (pointer p = first._cur; p < last._cur; p++)
                    alloc.destroy(p); // call destructor
            }
        }

        void _destroy_nodes(_map_pointer first, _map_pointer last)
        {
            std::allocator<T> alloc;
            for (_map_pointer cur = first; cur < last; ++cur)
                alloc.deallocate(*cur, _buffer_size());
        }

    public:
        Deque()
            : _map(), _map_size(0), _begin(), _end()
        {
            _initialize_map(0);
        }

        Deque(size_type count, const value_type &value = value_type())
            : _map(), _map_size(0), _begin(), _end()
        {
            _initialize_map(0);
            insert(begin(), count, value);
        }

        Deque(const _Self &other)
            : _map(), _map_size(0), _begin(), _end()
        {
            _initialize_map(0);
            insert(begin(), other.begin(), other.end());
        }

        template <typename InputIt>
        Deque(InputIt first, InputIt last)
        {
            _initialize_map(0);
            insert(begin(), first, last);
        }

        ~Deque()
        {
            clear();
            _destroy_nodes(_begin._node, _end._node + 1);
            std::allocator<T *> map_alloc;
            map_alloc.deallocate(_map, _map_size);
        }

        _Self &operator=(const _Self &other)
        {
            clear();
            insert(begin(), other.begin(), other.end());
            return *this;
        }

        void assign(size_type count, const T &value)
        {
            clear();
            insert(begin(), count, value);
        }

        template <typename InputIt>
        void assign(InputIt first, InputIt last)
        {
            clear();
            insert(begin(), first, last);
        }

        reference at(size_type pos)
        {
            if (pos >= size())
            {
                std::stringstream ss;
                ss << "index " << pos
                   << " out of bound (size() is " << size()
                   << ")";
                throw std::out_of_range(ss.str());
            }

            return (*this)[pos];
        }

        const_reference at(size_type pos) const
        {
            if (pos >= size())
            {
                std::stringstream ss;
                ss << "index " << pos
                   << " out of bound (size() is " << size()
                   << ")";
                throw std::out_of_range(ss.str());
            }

            return *(_begin + pos);
        }

        reference operator[](size_type n)
        {
            return _begin[difference_type(n)];
        }

        const_reference
        operator[](size_type n) const
        {
            return _begin[difference_type(n)];
        }

        reference front()
        {
            return *_begin;
        }

        const_reference front() const
        {
            return *_begin;
        }

        reference back()
        {
            return *(_end - 1);
        }

        const_reference back() const
        {
            return *(_end - 1);
        }

        iterator begin()
        {
            return _begin;
        }

        const_iterator begin() const
        {
            return _begin;
        }

        iterator end()
        {
            return _end;
        }

        const_iterator end() const
        {
            return _end;
        }

        reverse_iterator rbegin()
        {
            return reverse_iterator(_end);
        }

        const_reverse_iterator rbegin() const
        {
            return reverse_iterator(_end);
        }

        reverse_iterator rend()
        {
            return reverse_iterator(_begin);
        }

        const_reverse_iterator rend() const
        {
            return reverse_iterator(_begin);
        }

        bool empty() const
        {
            return _end == _begin;
        }

        size_type size() const
        {
            return _end - _begin;
        }

        size_type max_size() const
        {
            return std::numeric_limits<difference_type>::max() / sizeof(T);
        }

        void clear()
        {
            erase(_begin, _end);
        }

        // see <https://gcc.gnu.org/onlinedocs/libstdc++/latest-doxygen/a00326_source.html#l00638>
        iterator insert(iterator pos, const value_type &val)
        {
            if (pos._cur == _begin._cur)
            {
                push_front(val);
                return _begin;
            }
            else if (pos._cur == _end._cur)
            {
                push_back(val);
                return _end - 1;
            }

            value_type val_cpy = val;
            difference_type index = pos - _begin;
            if (size_type(index) < size() / 2)
            {
                // insert front

                push_front(front());
                iterator front1 = _begin + 1;
                iterator front2 = front1 + 1;
                pos = _begin + index;
                move(front2, pos + 1, front1);
            }
            else
            {
                // insert back

                push_back(back());
                iterator back1 = _end - 1;
                iterator back2 = back1 - 1;
                pos = _begin + index;
                move_backward(pos, back2, back1);
            }
            *pos = val_cpy;
            return pos;
        }

        // see <https://gcc.gnu.org/onlinedocs/libstdc++/latest-doxygen/a00326_source.html#l00672>
        void insert(iterator pos, size_type n, const value_type &val)
        {
            value_type val_cpy = val;
            difference_type elemsbefore = pos - _begin;
            size_type len = size();

            if (size_type(elemsbefore) < len / 2)
            {
                // insert front

                iterator new_start = _reserve_front(n);
                iterator old_start = _begin;
                pos = _begin + elemsbefore;

                if (elemsbefore >= difference_type(n))
                {
                    iterator start_n = old_start + difference_type(n);
                    uninitialized_move(old_start, start_n, new_start);
                    _begin = new_start;
                    move(start_n, pos, old_start);
                    fill(pos - difference_type(n), pos, val_cpy);
                }
                else
                {
                    iterator midway = uninitialized_move(old_start, pos, new_start);
                    uninitialized_fill(midway, old_start, val_cpy);
                    _begin = new_start;
                    fill(old_start, pos, val_cpy);
                }
            }
            else
            {
                // insert back

                iterator new_finish = _reserve_back(n);
                iterator old_finish = _end;

                difference_type elemsafter = len - elemsbefore;
                pos = _end - elemsafter;

                if (elemsafter > difference_type(n))
                {
                    iterator finish_n = old_finish - difference_type(n);
                    uninitialized_move(finish_n, old_finish, old_finish);
                    _end = new_finish;
                    move_backward(pos, finish_n, old_finish);
                    fill(pos, pos + difference_type(n), val_cpy);
                }
                else
                {
                    iterator midway = pos + difference_type(n);
                    uninitialized_fill(old_finish, midway, val_cpy);
                    uninitialized_move(pos, old_finish, midway);
                    _end = new_finish;
                }
            }
        }

        // see <https://gcc.gnu.org/onlinedocs/libstdc++/latest-doxygen/a00326_source.html#l00758>
        template <typename InputIt>
        void insert(iterator pos, InputIt first, InputIt last)
        {
            size_type n = distance(first, last);
            difference_type elemsbefore = pos - _begin;
            size_type len = size();

            if (size_type(elemsbefore) < len / 2)
            {
                // insert front

                iterator new_start = _reserve_front(n);
                iterator old_start = _begin;
                pos = _begin + elemsbefore;

                if (elemsbefore >= difference_type(n))
                {
                    iterator start_n = old_start + difference_type(n);
                    uninitialized_move(old_start, start_n, new_start);
                    _begin = new_start;
                    move(start_n, pos, old_start);
                    copy(first, last, pos - n);
                }
                else
                {
                    InputIt mid_in = first;
                    advance(mid_in, difference_type(n) - elemsbefore);
                    iterator midway = uninitialized_move(old_start, pos, new_start);
                    uninitialized_copy(first, mid_in, midway);
                    _begin = new_start;
                    copy(mid_in, last, old_start);
                }
            }
            else
            {
                // insert back

                iterator new_finish = _reserve_back(n);
                iterator old_finish = _end;

                difference_type elemsafter = len - elemsbefore;
                pos = _end - elemsafter;

                if (elemsafter > difference_type(n))
                {
                    iterator finish_n = old_finish - difference_type(n);
                    uninitialized_move(finish_n, old_finish, old_finish);
                    _end = new_finish;
                    std::move_backward(pos, finish_n, old_finish);
                    copy(first, last, pos);
                }
                else
                {
                    InputIt mid_in = first;
                    advance(mid_in, elemsafter);
                    iterator midway = uninitialized_copy(mid_in, last, old_finish);
                    uninitialized_move(pos, old_finish, midway);
                    _end = new_finish;
                    copy(first, mid_in, pos);
                }
            }
        }

        iterator erase(iterator pos)
        {
            return erase(pos, pos + 1);
        }

        // see <https://gcc.gnu.org/onlinedocs/libstdc++/latest-doxygen/a00326_source.html#l00233>
        iterator erase(iterator first, iterator last)
        {
            if (first == last)
                return first;

            difference_type n = last - first;
            difference_type elems_before = first - _begin;
            if (size_type(elems_before) <= (size() - n) / 2)
            {
                if (first != _begin)
                    move_backward(_begin, first, last);
                // erase front
                iterator pos = _begin + n;
                _destroy_data(_begin, pos);
                _destroy_nodes(_begin._node, pos._node);
                _begin = pos;
            }
            else
            {
                if (last != _end)
                    move(last, _end, first);
                // erase back
                iterator pos = _end - n;
                _destroy_data(pos, _end);
                _destroy_nodes(pos._node + 1, _end._node + 1);
                _end = pos;
            }
            return _begin + elems_before;
        }

        void push_back(const T &val)
        {
            std::allocator<T> alloc;
            iterator ite = _reserve_back(1) - 1;

            alloc.construct(ite._cur, val); // copy constructor
            _end = ite + 1;
        }

        void pop_back()
        {
            erase(_end - 1);
        }

        void push_front(const T &val)
        {
            std::allocator<T> alloc;
            iterator ite = _reserve_front(1);

            alloc.construct(ite._cur, val); // copy constructor
            _begin = ite;
        }

        void pop_front()
        {
            erase(_begin);
        }

        void resize(size_t count, T value = T())
        {
            if (count >= size())
                insert(end(), count - size(), value);
            else
                erase(begin() + count, end());
        }

        void swap(_Self &other)
        {
            std::swap(_map, other._map);
            std::swap(_map_size, other._map_size);
            ft::swap(_begin, other._begin);
            ft::swap(_end, other._end);
        }
    };

    template <typename T>
    bool operator==(const Deque<T> &lhs, const Deque<T> &rhs)
    {
        if (lhs.size() != rhs.size())
            return false;
        return equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    template <typename T>
    bool operator!=(const Deque<T> &lhs, const Deque<T> &rhs)
    {
        return !(lhs == rhs);
    }

    template <typename T>
    bool operator<(const Deque<T> &lhs, const Deque<T> &rhs)
    {
        return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <typename T>
    bool operator<=(const Deque<T> &lhs, const Deque<T> &rhs)
    {
        return !(lhs > rhs);
    }

    template <typename T>
    bool operator>(const Deque<T> &lhs, const Deque<T> &rhs)
    {
        return rhs < lhs;
    }

    template <typename T>
    bool operator>=(const Deque<T> &lhs, const Deque<T> &rhs)
    {
        return !(lhs < rhs);
    }

    template <typename T>
    void swap(Deque<T> &lhs, Deque<T> &rhs)
    {
        rhs.swap(lhs);
    }
} // namespace ft

#endif
