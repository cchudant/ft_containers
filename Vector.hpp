/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skybt <skybt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 13:53:48 by skybt             #+#    #+#             */
/*   Updated: 2020/08/10 19:38:32 by skybt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <sstream>
#include <stdexcept>
#include "Utility.hpp"

namespace ft
{
	template <typename T>
	class Vector;

	template <typename T>
	class VectorIterator
	{
	public:
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T *pointer;
		typedef T &reference;
		typedef RandomAccessIteratorTag iterator_category;

	private:
		typedef VectorIterator<T> _Self;

		pointer _e;

		VectorIterator(pointer elem) : _e(elem) {}

	public:
		VectorIterator() : _e(NULL) {}

		VectorIterator(const _Self &other) : _e(other._e) {}

		~VectorIterator() {}

		_Self &operator=(const _Self &other)
		{
			_e = other._e;
			return *this;
		}

		// prefix increment
		_Self &operator++()
		{
			++_e;
			return *this;
		}

		// postfix increment
		_Self operator++(int)
		{
			_Self ite = *this;
			++_e;
			return ite;
		}

		reference operator*() const
		{
			return *_e;
		}

		pointer operator->() const
		{
			return _e;
		}

		// prefix decrement
		_Self &operator--()
		{
			--_e;
			return *this;
		}

		// postfix decrement
		_Self operator--(int)
		{
			_Self ite = *this;
			--_e;
			return ite;
		}

		_Self &operator+=(size_type offset)
		{
			_e += offset;
			return *this;
		}

		_Self &operator-=(size_type offset)
		{
			_e -= offset;
			return *this;
		}

		reference operator[](difference_type n) const
		{
			return *(*this + n);
		}

		template <typename _T>
		friend bool operator==(const VectorIterator<_T> &lhs, const VectorIterator<_T> &rhs);

		template <typename _T>
		friend bool operator<(const VectorIterator<_T> &lhs, const VectorIterator<_T> &rhs);

		template <typename _T>
		friend ptrdiff_t operator-(const VectorIterator<_T> &lhs, const VectorIterator<_T> &rhs);

		template <typename _T>
		friend class Vector;
	};

	template <typename T>
	bool operator==(const VectorIterator<T> &lhs, const VectorIterator<T> &rhs)
	{
		return lhs._e == rhs._e;
	}

	template <typename T>
	bool operator!=(const VectorIterator<T> &lhs, const VectorIterator<T> &rhs)
	{
		return !(lhs == rhs);
	}

	template <typename T>
	bool operator<(const VectorIterator<T> &lhs, const VectorIterator<T> &rhs)
	{
		return lhs._e < rhs._e;
	}

	template <typename T>
	bool operator>(const VectorIterator<T> &lhs, const VectorIterator<T> &rhs)
	{
		return rhs < lhs;
	}

	template <typename T>
	bool operator<=(const VectorIterator<T> &lhs, const VectorIterator<T> &rhs)
	{
		return !(lhs > rhs);
	}

	template <typename T>
	bool operator>=(const VectorIterator<T> &lhs, const VectorIterator<T> &rhs)
	{
		return !(lhs < rhs);
	}

	template <typename T>
	VectorIterator<T> operator+(const VectorIterator<T> &ite, size_t offset)
	{
		VectorIterator<T> res = ite;
		return res += offset;
	}

	template <typename T>
	VectorIterator<T> operator+(size_t offset, const VectorIterator<T> &ite)
	{
		return ite + offset;
	}

	template <typename T>
	VectorIterator<T> operator-(const VectorIterator<T> &ite, size_t offset)
	{
		VectorIterator<T> res = ite;
		return res -= offset;
	}

	template <typename T>
	ptrdiff_t operator-(const VectorIterator<T> &lhs, const VectorIterator<T> &rhs)
	{
		return lhs._e - rhs._e;
	}

	template <typename T>
	class Vector
	{
	public:
		typedef T value_type;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef T &reference;
		typedef const T &const_reference;
		typedef T *pointer;
		typedef const T *const_pointer;
		typedef VectorIterator<T> iterator;
		typedef VectorIterator<const T> const_iterator;
		typedef ReverseIterator<iterator> reverse_iterator;
		typedef ReverseIterator<const_iterator> const_reverse_iterator;

	private:
		typedef Vector<T> _Self;

		pointer _arr;
		size_type _len;
		size_type _cap;

	public:
		Vector() : _arr(NULL), _len(0), _cap(0) {}

		Vector(size_type count, const value_type &value = value_type())
			: _arr(NULL), _len(0), _cap(0)
		{
			insert(begin(), count, value);
		}

		template <typename InputIt>
		Vector(InputIt first, InputIt last)
			: _arr(NULL), _len(0), _cap(0)
		{
			insert(begin(), first, last);
		}

		Vector(const _Self &other)
			: _arr(NULL), _len(0), _cap(0)
		{
			insert(begin(), other.begin(), other.end());
		}

		~Vector()
		{
			std::allocator<T> alloc;
			for (size_type i = 0; i < _len; i++)
				alloc.destroy(&_arr[i]);
			alloc.deallocate(_arr, _cap);
		}

		_Self &operator=(const _Self &other)
		{
			clear();
			insert(begin(), other.begin(), other.end());
			return *this;
		}

		iterator begin()
		{
			return _arr;
		}

		const_iterator begin() const
		{
			return _arr;
		}

		iterator end()
		{
			return _arr + _len;
		}

		const_iterator end() const
		{
			return _arr + _len;
		}

		reverse_iterator rbegin()
		{
			return ReverseIterator<VectorIterator<T>>(end());
		}

		const_reverse_iterator rbegin() const
		{
			return ReverseIterator<VectorIterator<T>>(end());
		}

		reverse_iterator rend()
		{
			return ReverseIterator<VectorIterator<T>>(begin());
		}

		const_reverse_iterator rend() const
		{
			return ReverseIterator<VectorIterator<T>>(begin());
		}

		size_type size() const
		{
			return _len;
		}

		size_type max_size() const
		{
			return std::numeric_limits<difference_type>::max() / sizeof(T);
		}

		void resize(size_type count, T value = T())
		{
			if (count >= _len)
				insert(end(), count - _len, value);
			else
				erase(begin() + count, end());
		}

		size_type capacity() const
		{
			return _cap;
		}

		bool empty() const
		{
			return _len == 0;
		}

		void reserve(size_type new_cap)
		{
			if (new_cap <= _cap) // no reallocation when not needed
				return;

			if (!new_cap) // no empty allocation
				return;

			std::allocator<T> alloc;
			T *new_arr = alloc.allocate(new_cap);
			for (size_type i = 0; i < _len; i++)
			{
				alloc.construct(&new_arr[i], _arr[i]); // call copy constructor
				alloc.destroy(&_arr[i]);			   // call destructor
			}

			alloc.deallocate(_arr, _cap);
			_arr = new_arr;
			_cap = new_cap;
		}

		reference operator[](size_type pos)
		{
			return _arr[pos];
		}

		const_reference operator[](size_type pos) const
		{
			return _arr[pos];
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

			return _arr[pos];
		}

		const_reference at(size_type pos) const
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

		reference front()
		{
			return _arr[0];
		}

		const_reference front() const
		{
			return _arr[0];
		}

		reference back()
		{
			return _arr[_len - 1];
		}

		const_reference back() const
		{
			return _arr[_len - 1];
		}

		void assign(size_type count, const value_type &value)
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

		void push_back(const value_type &value)
		{
			insert(end(), value);
		}

		void pop_back()
		{
			erase(end() - 1);
		}

		iterator insert(iterator pos, const value_type &value)
		{
			insert(pos, 1, value);
			return pos;
		}

		void insert(iterator pos, size_type count, const value_type &value)
		{
			size_type index = pos._e - _arr;
			if (!count)
				return;

			reserve(_len + count); // reserve after calculating the index!
			// (otherwhise iterator `pos` is invalidated)

			std::allocator<T> alloc;

			for (ptrdiff_t i = _len - 1; i >= (ptrdiff_t)index; i--)
			{
				// move elements count times to the right
				alloc.construct(&_arr[i + count], _arr[i]); // copy constructor
				alloc.destroy(&_arr[i]);					// call destructor
			}

			for (size_type i = index; i < index + count; i++)
				alloc.construct(&_arr[i], value); // copy constructor

			_len += count;
		}

		template <typename InputIt>
		void insert(iterator pos, InputIt first, InputIt last)
		{
			size_type index = pos._e - _arr;
			size_type count = distance(first, last);
			if (!count)
				return;

			reserve(_len + count); // reserve after calculating the index!
			// (otherwhise iterator `pos` is invalidated)

			std::allocator<T> alloc;

			for (ptrdiff_t i = _len - 1; i >= (ptrdiff_t)index; i--)
			{
				// move elements count times to the right
				alloc.construct(&_arr[i + count], _arr[i]); // copy constructor
				alloc.destroy(&_arr[i]);					// call destructor
			}

			for (InputIt ite = first; ite != last; ++ite)
				alloc.construct(&_arr[index++], *ite); // copy constructor

			_len += count;
		}

		iterator erase(iterator pos)
		{
			return erase(pos, pos + 1);
		}

		iterator erase(iterator first, iterator last)
		{
			size_type count = last - first;
			if (count <= 0)
				return last;

			size_type index = first._e - _arr;

			std::allocator<T> alloc;
			for (size_type i = index; i < index + count; i++)
				alloc.destroy(&_arr[i]); // call destructor

			for (size_type i = index + count; i < _len; i++)
			{
				// move elements count to the left
				alloc.construct(&_arr[i - count], _arr[i]); // copy constructor
				alloc.destroy(&_arr[i]);					// call destructor
			}
			_len -= count;
			return first;
		}

		void swap(Vector<T> &other)
		{
			std::swap(_arr, other._arr);
			std::swap(_len, other._len);
			std::swap(_cap, other._cap);
		}

		void clear()
		{
			erase(begin(), end());
		}
	};

	template <typename T>
	bool operator==(const Vector<T> &lhs, const Vector<T> &rhs)
	{
		if (lhs.size() != rhs.size())
			return false;

		return equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <typename T>
	bool operator!=(const Vector<T> &lhs, const Vector<T> &rhs)
	{
		return !(lhs == rhs);
	}

	template <typename T>
	bool operator<(const Vector<T> &lhs, const Vector<T> &rhs)
	{
		return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <typename T>
	bool operator<=(const Vector<T> &lhs, const Vector<T> &rhs)
	{
		return !(lhs > rhs);
	}

	template <typename T>
	bool operator>(const Vector<T> &lhs, const Vector<T> &rhs)
	{
		return rhs < lhs;
	}

	template <typename T>
	bool operator>=(const Vector<T> &lhs, const Vector<T> &rhs)
	{
		return !(lhs < rhs);
	}

	template <typename T>
	void swap(Vector<T> &lhs, Vector<T> &rhs)
	{
		rhs.swap(lhs);
	}
} // namespace ft

#endif
