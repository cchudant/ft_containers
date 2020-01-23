/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skybt <skybt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 13:53:48 by skybt             #+#    #+#             */
/*   Updated: 2020/01/22 20:32:39 by skybt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <sstream>
# include <stdexcept>
# include <utility>
# include <iterator>

namespace ft
{
    template < typename T >
    class VectorIterator
    {
        private:
            T* _e;

        public:
            VectorIterator(T* elem);
            T* ptr() const;

            typedef T value_type;
            typedef size_t size_type;
            typedef std::ptrdiff_t difference_type;
            typedef T& reference;
            typedef T* pointer;
            typedef std::random_access_iterator_tag iterator_category;

            // iterator
            VectorIterator(const VectorIterator< T >& other);
            ~VectorIterator();
            VectorIterator< T >& operator=(const VectorIterator< T >& other);
            VectorIterator< T >& operator++(); //prefix increment
            T& operator*() const;
            T* operator->() const;

            // input_iterator
            VectorIterator< T > operator++(int); //postfix increment

            // bidirectional_iterator
            VectorIterator< T >& operator--(); //prefix decrement
            VectorIterator< T > operator--(int); //postfix decrement

            // random_access_iterator
            VectorIterator< T >& operator+=(size_t offset);
            VectorIterator< T >& operator-=(size_t offset);
    };

    // iterator
    template < typename T >
    bool operator==(const VectorIterator< T >& lhs, const VectorIterator< T >& rhs);
    template < typename T >
    bool operator!=(const VectorIterator< T >& lhs, const VectorIterator< T >& rhs);

    // random_access_iterator
    template < typename T >
    bool operator<(const VectorIterator< T >& lhs, const VectorIterator< T >& rhs);
    template < typename T >
    bool operator>(const VectorIterator< T >& lhs, const VectorIterator< T >& rhs);
    template < typename T >
    bool operator<=(const VectorIterator< T >& lhs, const VectorIterator< T >& rhs);
    template < typename T >
    bool operator>=(const VectorIterator< T >& lhs, const VectorIterator< T >& rhs);
    template < typename T >
    VectorIterator< T > operator+(const VectorIterator< T >& ite, size_t offset);
    template < typename T >
    VectorIterator< T > operator+(size_t offset, const VectorIterator< T >& ite);
    template < typename T >
    VectorIterator< T > operator-(const VectorIterator< T >& ite, size_t offset);
    template < typename T >
    std::ptrdiff_t operator-(const VectorIterator< T >& lhs, const VectorIterator< T >& rhs);

    template < typename T >
    class Vector
    {
        private:
            T* _arr;
            size_t _len;
            size_t _cap;

        public:

            typedef T value_type;
            typedef size_t size_type;
            typedef std::ptrdiff_t difference_type;
            typedef T& reference;
            typedef  const T& const_reference;
            typedef T* pointer;
            typedef  const T * const_pointer;
            typedef VectorIterator< T > iterator;
            typedef VectorIterator< const T > const_iterator;
            typedef std::reverse_iterator< VectorIterator< T > > reverse_iterator;
            typedef std::reverse_iterator< VectorIterator< const T > > const_reverse_iterator;

            Vector();
            explicit Vector(size_t count,  const T& value = T());
            template < typename InputIt >
            Vector(InputIt first, InputIt last);
            Vector(const Vector< T >& other);
            ~Vector();
            Vector< T >& operator=(const Vector< T >& other);
            void assign(size_t count,  const T& value);
            template < typename InputIt >
            void assign(InputIt first, InputIt last);

            T& at(size_t pos);
             const T& at(size_t pos) const;
            T& operator[](size_t pos);
             const T& operator[](size_t pos) const;
            T& front();
             const T& front() const;
            T& back();
             const T& back() const;

            VectorIterator< T > begin();
            VectorIterator< const T > begin() const;
            VectorIterator< T > end();
            VectorIterator< const T > end() const;
            std::reverse_iterator< VectorIterator< T > > rbegin();
            std::reverse_iterator< VectorIterator< const T > > rbegin() const;
            std::reverse_iterator< VectorIterator< T > > rend();
            std::reverse_iterator< VectorIterator< const T > > rend() const;

            bool empty() const;
            size_t size() const;
            size_t max_size() const;
            void reserve(size_t new_cap);
            size_t capacity() const;

            void clear();
            VectorIterator< T > insert(VectorIterator< T > pos, const T& value);
            void insert(VectorIterator< T > pos, size_t count, const T& value);
            template < typename InputIt >
            void insert(VectorIterator< T > pos, InputIt first, InputIt last);
            VectorIterator< T > erase(VectorIterator< T > pos);
            VectorIterator< T > erase(VectorIterator< T > first, VectorIterator< T > last);
            void push_back(const T& value);
            void pop_back();
            void resize(size_t count, T value = T());
            void swap(Vector< T >& other);
    
            friend void swap(Vector< T >& lhs, Vector< T >& rhs);
    };

    template < typename T >
    bool operator==(const Vector< T >& lhs, const Vector< T >& rhs);
    template < typename T >
    bool operator!=(const Vector< T >& lhs, const Vector< T >& rhs);
    template < typename T >
    bool operator<(const Vector< T >& lhs, const Vector< T >& rhs);
    template < typename T >
    bool operator<=(const Vector< T >& lhs, const Vector< T >& rhs);
    template < typename T >
    bool operator>(const Vector< T >& lhs, const Vector< T >& rhs);
    template < typename T >
    bool operator>=(const Vector< T >& lhs, const Vector< T >& rhs);

    template < typename T >
    void swap(Vector< T >& lhs, Vector< T >& rhs);

    /*
    ** ------ IMPLEMENTATION ------
    */

    template < typename T >
    Vector< T >::Vector():
        _arr(NULL), _len(0), _cap(0)
    {
    }

    template < typename T >
    Vector< T >::Vector(size_t count,  const T& value):
        _arr(NULL), _len(0), _cap(0)
    {
        for (size_t i = 0; i < count; i++)
            push_back(T(value));
    }

    template < typename T >
    template < typename InputIt >
    Vector< T >::Vector(InputIt first, InputIt last):
        _arr(NULL), _len(0), _cap(0)
    {
        for (; first != last; first++)
            push_back(*first);
    }

    template < typename T >
    Vector< T >::Vector(const Vector< T >& other):
        _arr(NULL), _len(0), _cap(0)
    {
        for (const VectorIterator< T > ite = other.begin();
                ite != other.end(); ite++)
            push_back(*ite);
    }

    template < typename T >
    Vector< T >::~Vector()
    {
        std::allocator< T > alloc;
        for (size_t i = 0; i < _len; i++)
            alloc.destroy(&_arr[i]);
        alloc.deallocate(_arr, _cap);
    }

    template < typename T >
    Vector< T >& Vector< T >::operator=(const Vector< T >& other)
    {
        clear();
        for (const VectorIterator< T > ite = other.begin();
                ite != other.end(); ite++)
            push_back(*ite);

        return *this;
    }

    template < typename T >
    void Vector< T >::assign(size_t count,  const T& value)
    {
        clear();
        for (size_t i = 0; i < count; i++)
            push_back(T(value));
    }

    /* FIELD ACCESS */

    template < typename T >
    T& Vector< T >::at(size_t pos)
    {
        if (pos >= size())
        {
            std::stringstream ss;
            ss << "index " << pos
                << " out of bound (size() is " << size()
                << ")";
            throw std::out_of_range(ss.str());
        }

        return _arr[pos];
    }

    template < typename T >
     const T& Vector< T >::at(size_t pos) const
    {
        if (pos >= _len)
        {
            std::stringstream ss;
            ss << "index " << pos
                << " out of bound (size() is " << size()
                << ")";
            throw std::out_of_range(ss.str());
        }

        return _arr[pos];
    }

    template < typename T >
    T& Vector< T >::operator[](size_t pos)
    {
        return _arr[pos];
    }

    template < typename T >
     const T& Vector< T >::operator[](size_t pos) const
    {
        return _arr[pos];
    }

    template < typename T >
    T& Vector< T >::front()
    {
        return _arr[0];
    }

    template < typename T >
     const T& Vector< T >::front() const
    {
        return _arr[0];
    }

    template < typename T >
    T& Vector< T >::back()
    {
        return _arr[_len - 1];
    }

    template < typename T >
     const T& Vector< T >::back() const
    {
        return _arr[_len - 1];
    }

    /* ITERATORS */

    template < typename T >
    VectorIterator< T > Vector< T >::begin()
    {
        return _arr;
    }

    template < typename T >
    VectorIterator< const T > Vector< T >::begin() const
    {
        return _arr;
    }

    template < typename T >
    VectorIterator< T > Vector< T >::end()
    {
        return _arr + _len;
    }

    template < typename T >
    VectorIterator< const T > Vector< T >::end() const
    {
        return _arr + _len;
    }

    template < typename T >
    std::reverse_iterator< VectorIterator< T > > Vector< T >::rbegin()
    {
        return make_reverse_iterator(begin());
    }

    template < typename T >
    std::reverse_iterator< VectorIterator< const T > > Vector< T >::rbegin() const
    {
        return make_reverse_iterator(begin());
    }

    template < typename T >
    std::reverse_iterator< VectorIterator< T > > Vector< T >::rend()
    {
        return make_reverse_iterator(end());
    }

    template < typename T >
    std::reverse_iterator< VectorIterator< const T > > Vector< T >::rend() const
    {
        return make_reverse_iterator(end());
    }

    /* CAPACITY */

    template < typename T >
    bool Vector< T >::empty() const
    {
        return _len == 0;
    }

    template < typename T >
    size_t Vector< T >::size() const
    {
        return _len;
    }

    template < typename T >
    size_t Vector< T >::max_size() const
    {
        // 64 bit pointers -- 2**64 / sizeof(T)
        return 18446744073709551615uL / sizeof(T);
    }

    template < typename T >
    void Vector< T >::reserve(size_t new_cap)
    {
        if (new_cap <= _cap) // no reallocation when not needed
            return;

        if (!new_cap) // no empty allocation
            return;

        std::allocator< T > alloc;
        T* new_arr = alloc.allocate(new_cap);
        for (size_t i = 0; i < _len; i++)
        {
            alloc.construct(&new_arr[i], _arr[i]); // call copy constructor
            alloc.destroy(&_arr[i]); // call destructor
        }

        alloc.deallocate(_arr, _cap);
        _arr = new_arr;
        _cap = new_cap;
    }

    template < typename T >
    size_t Vector< T >::capacity() const
    {
        return _cap;
    }

    /* MODIFIERS */

    template < typename T >
    void Vector< T >::clear()
    {
        std::allocator< T > alloc;
        for (size_t i = 0; i < _len; i++)
            alloc.destroy(&_arr[i]); // call destructor

        // do not change the capacity

        _arr = NULL;
        _len = 0;
    }

    template < typename T >
    VectorIterator< T > Vector< T >::insert(VectorIterator< T > pos, const T& value)
    {
        return insert(pos, 1, value);
    }

    template < typename T >
    void Vector< T >::insert(VectorIterator< T > pos, size_t count, const T& value)
    {
        reserve(_cap + count);

        size_t index = pos.ptr() - _arr;
        std::allocator< T > alloc;
        for (ssize_t i = _len - 1; i >= index; i++)
        {
            // move elements count times to the right
            alloc.construct(&_arr[i - index], _arr[i]); // copy constructor
            alloc.destroy(&_arr[i]); // call destructor
        }

        for (size_t i = index; i < count; i++)
            alloc.construct(&_arr[i], value); // copy constructor
        _len += count;
        return pos;
    }

    template < typename T >
    template < typename InputIt >
    void Vector< T >::insert(VectorIterator< T > pos, InputIt first, InputIt last)
    {
        size_t count = std::distance(first, last);
        reserve(_cap + count);

        size_t index = pos.ptr() - _arr;
        std::allocator< T > alloc;
        for (size_t i = index; i < _len; i++)
        {
            // move elements count times to the right
            alloc.construct(&_arr[i + count], _arr[i]); // copy constructor
            alloc.destroy(&_arr[i]); // call destructor
        }

        for (InputIt ite = first; ite != last; ++ite)
            alloc.construct(&_arr[i], *ite); // copy constructor
    }

    template < typename T >
    VectorIterator< T > Vector< T >::erase(VectorIterator< T > pos)
    {
        return erase(pos, pos + 1);
    }

    template < typename T >
    VectorIterator< T > Vector< T >::erase(VectorIterator< T > first, VectorIterator< T > last)
    {
        size_t count = std::distance(first, last);
        size_t index = pos.ptr() - _arr;
    
        std::allocator< T > alloc;
        for (size_t i = index; i < count; i++)
            alloc.destroy(&_arr[index + i]); // call destructor

        for (size_t i = index; i < _len; i++)
        {
            // move elements one to the left
            alloc.construct(&_arr[i - count], _arr[i]); // copy constructor
            alloc.destroy(&_arr[i]); // call destructor
        }
    }

    template < typename T >
    void Vector< T >::push_back( const T& value)
    {
        reserve(_cap + 1);
        std::allocator< T > alloc;
        alloc.construct(&_arr[_len], value); // copy constructor
        _len++;
    }

    template < typename T >
    void Vector< T >::pop_back()
    {
        if (_len) // check for length even though standard says it's UB
        {
            std::allocator< T > alloc;
            alloc.destroy(&_arr[_len - 1]);
            _len--;
        }
    }

    template < typename T >
    void Vector< T >::resize(size_t count, T value)
    {
        reserve(count); // realloc if necessary
        std::allocator< T > alloc;
        for (size_t i = _len; i < count; i++)
        {
            // construct new items when count > _len
            alloc.construct(&_arr[i], value); // copy constructor
        }
        _len = count;
    }

    /* NON MEMBER FUNCTIONS */

    template < typename T >
    bool operator==(const Vector< T >& lhs, const Vector< T >& rhs)
    {
        if (lhs.size() != rhs.size())
            return false;

        for (size_t i = 0; i < lhs.size(); i++)
            if (lhs[i] != rhs[i])
                return false;

        return true;
    }

    template < typename T >
    bool operator!=(const Vector< T >& lhs, const Vector< T >& rhs)
    {
        return !(lhs == rhs);
    }
    
    template < typename T >
    bool operator<(const Vector< T >& lhs, const Vector< T >& rhs)
    {
        for (size_t i = 0; i < lhs._len && i < rhs._len; i++)
            if (lhs[i] != rhs[i])
                return lhs[i] < rhs[i];

        if (lhs.size() == rhs.size())
            return false; // lhs == rhs at that point

        return lhs.size() < rhs.size(); // lhs < rhs if lhs is prefix of rhs
    }

    template < typename T >
    bool operator<=(const Vector< T >& lhs, const Vector< T >& rhs)
    {
        for (size_t i = 0; i < lhs._len && i < rhs._len; i++)
            if (lhs[i] != rhs[i])
                return lhs[i] < rhs[i];

        if (lhs.size() == rhs.size())
            return true; // lhs == rhs at that point

        return lhs.size() < rhs.size(); // lhs < rhs if lhs is prefix of rhs
    }
    
    template < typename T >
    bool operator>(const Vector< T >& lhs, const Vector< T >& rhs)
    {
        return !(lhs <= rhs);
    }

    template < typename T >
    bool operator>=(const Vector< T >& lhs, const Vector< T >& rhs)
    {
        return !(lhs < rhs);
    }

    template < typename T >
    void Vector< T >::swap(Vector< T >& other)
    {
        std::swap(_arr, other._arr);
        std::swap(_len, other._len);
        std::swap(_cap, other._cap);
    }

    template < typename T >
    void swap(Vector< T >& lhs, Vector< T >& rhs)
    {
        rhs.swap(lhs);
    }

    /* ITERATOR */

    template < typename T >
    VectorIterator< T >::VectorIterator(T* elem):
        _e(elem)
    {
    }

    template < typename T >
    T* VectorIterator< T >::ptr() const
    {
        return _e;
    }

    template < typename T >
    VectorIterator< T >::VectorIterator(const VectorIterator< T >& other):
        _e(other._e)
    {
    }

    template < typename T >
    VectorIterator< T >::~VectorIterator()
    {
    }

    template < typename T >
    VectorIterator< T > &VectorIterator< T >::operator=(const VectorIterator< T >& other)
    {
        _e = other._e;
        return *this;
    }

    template < typename T >
    VectorIterator< T >& VectorIterator< T >::operator++()
    {
        ++_e;
        return *this;
    }

    template < typename T >
    T& VectorIterator< T >::operator*() const
    {
        return *_e;
    }

    template < typename T >
    T* VectorIterator< T >::operator->() const
    {
        return _e;
    }

    template < typename T >
    VectorIterator< T > VectorIterator< T >::operator++(int)
    {
        VectorIterator< T > ite = *this;
        ++_e;
        return ite;
    }

    template < typename T >
    VectorIterator< T >& VectorIterator< T >::operator--()
    {
        --_e;
        return *this;
    }

    template < typename T >
    VectorIterator< T > VectorIterator< T >::operator--(int)
    {
        VectorIterator< T > ite = *this;
        --_e;
        return ite;
    }

    template < typename T >
    VectorIterator< T >& VectorIterator< T >::operator+=(size_t offset)
    {
        _e += offset;
        return *this;
    }

    template < typename T >
    VectorIterator< T >& VectorIterator< T >::operator-=(size_t offset)
    {
        _e -= offset;
        return *this;
    }

    template < typename T >
    bool operator==(const VectorIterator< T >& lhs, const VectorIterator< T >& rhs)
    {
        return lhs._e == rhs._e;
    }

    template < typename T >
    bool operator!=(const VectorIterator< T >& lhs, const VectorIterator< T >& rhs)
    {
        return lhs._e != rhs._e;
    }

    template < typename T >
    bool operator<(const VectorIterator< T >& lhs, const VectorIterator< T >& rhs)
    {
        return lhs._e < rhs._e;
    }

    template < typename T >
    bool operator>(const VectorIterator< T >& lhs, const VectorIterator< T >& rhs)
    {
        return lhs._e > rhs._e;
    }

    template < typename T >
    bool operator<=(const VectorIterator< T >& lhs, const VectorIterator< T >& rhs)
    {
        return lhs._e <= rhs._e;
    }

    template < typename T >
    bool operator>=(const VectorIterator< T >& lhs, const VectorIterator< T >& rhs)
    {
        return lhs._e >= rhs._e;
    }

    template < typename T >
    VectorIterator< T > operator+(const VectorIterator< T >& ite, size_t offset)
    {
        return ite._e + offset;
    }

    template < typename T >
    VectorIterator< T > operator+(size_t offset, const VectorIterator< T >& ite)
    {
        return offset + ite._e;
    }

    template < typename T >
    VectorIterator< T > operator-(const VectorIterator< T >& ite, size_t offset)
    {
        return ite._e - offset;
    }

    template < typename T >
    std::ptrdiff_t operator-(const VectorIterator< T >& lhs, const VectorIterator< T >& rhs)
    {
        return lhs._e - rhs._e;
    }
}

#endif
