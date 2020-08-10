/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skybt <skybt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 10:52:36 by cchudant          #+#    #+#             */
/*   Updated: 2020/08/10 21:45:43 by skybt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
#define LIST_HPP

#include "Utility.hpp"

/*
 * Doubly linked list.
 * Each node in the linked list points to its previous and next node.
 * 
 * A list always has a sentinel node which marks the end of the list, and
 * is the node pointed by the end() iterator.
 */

namespace ft
{
	template <typename T>
	class List;

	template <typename T>
	class ListIterator
	{
	public:
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef T *pointer;
		typedef T &reference;
		typedef BidirectionalIteratorTag iterator_category;

	private:
		typedef ListIterator<T> _Self;
		typedef typename List<T>::_node _node;

		_node *_n;

		ListIterator(_node *node) : _n(node) {}

	public:
		ListIterator(const _Self &o) : _n(o._n) {}

		~ListIterator() {}

		_Self &operator=(const _Self &o)
		{
			_n = o._n;
			return *this;
		}

		_Self &operator++()
		{
			_n = _n->nxt;
			return *this;
		}

		_Self operator++(int)
		{
			_Self cpy = *this;
			++*this;
			return cpy;
		}

		_Self &operator--()
		{
			_n = _n->prv;
			return *this;
		}

		_Self operator--(int)
		{
			_Self cpy = *this;
			--*this;
			return cpy;
		}

		reference operator*() const
		{
			return _n->el;
		}

		pointer operator->() const
		{
			return &_n->el;
		}

		template <typename _T>
		friend class List;

		template <typename _T>
		friend class ListIterator;

		template <typename _T>
		friend bool operator==(const ListIterator<_T> &lhs, const ListIterator<_T> &rhs);
	};

	template <typename T>
	bool operator==(const ListIterator<T> &lhs, const ListIterator<T> &rhs)
	{
		return lhs._n == rhs._n;
	}

	template <typename T>
	bool operator!=(const ListIterator<T> &lhs, const ListIterator<T> &rhs)
	{
		return !(lhs == rhs);
	}

	template <typename T>
	class List
	{
	public:
		typedef T value_type;
		typedef T &reference;
		typedef const T &const_reference;
		typedef T *pointer;
		typedef const T *const_pointer;
		typedef ListIterator<T> iterator;
		typedef ListIterator<const T> const_iterator;
		typedef ReverseIterator<iterator> reverse_iterator;
		typedef ReverseIterator<const_iterator> const_reverse_iterator;
		typedef std::ptrdiff_t difference_type;
		typedef size_t size_type;

	private:
		typedef List<T> _Self;
		struct _node
		{
			_node *prv;
			_node *nxt;
			T el;

			_node(_node *prv_, _node *nxt_)
				: prv(prv_), nxt(nxt_) {}
		};

		_node *_head;
		_node *_tail;
		size_type _len;

	public:
		List() : _len(0)
		{
			_head = new _node(NULL, NULL); // sentinel
			_tail = _head;
		}

		List(size_type n, const value_type &val = value_type()) : _len(0)
		{
			_head = new _node(NULL, NULL); // sentinel
			_tail = _head;
			insert(begin(), n, val);
		}

		template <typename InputIt>
		List(InputIt first, InputIt last) : _len(0)
		{
			_head = new _node(NULL, NULL); // sentinel
			_tail = _head;
			insert(begin(), first, last);
		}

		List(const _Self &other) : _len(0)
		{
			_head = new _node(NULL, NULL); // sentinel
			_tail = _head;
			insert(begin(), other.begin(), other.end());
		}

		_Self &operator=(const _Self &other)
		{
			clear();
			insert(begin(), other.begin(), other.end());
			return *this;
		}

		~List()
		{
			erase(begin(), end());
			delete _tail; // delete sentinel
		}

		iterator begin()
		{
			return iterator(_head);
		}

		const_iterator begin() const
		{
			typedef typename List<const T>::_node const_node;
			return const_iterator(reinterpret_cast<const_node *>(_head));
		}

		iterator end()
		{
			return iterator(_tail);
		}

		const_iterator end() const
		{
			typedef typename List<const T>::_node const_node;
			return const_iterator(reinterpret_cast<const_node *>(_tail));
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}

		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(end());
		}

		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}

		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(begin());
		}

		bool empty() const
		{
			return _len == 0;
		}

		size_type size() const
		{
			return _len;
		}

		size_type max_size() const
		{
			return std::numeric_limits<difference_type>::max() / sizeof(T);
		}

		reference front()
		{
			return _head->el;
		}

		const_reference front() const
		{
			return _head->el;
		}

		reference back()
		{
			// skip sentinel
			return _tail->prv->el;
		}

		const_reference back() const
		{
			// skip sentinel
			return _tail->prv->el;
		}

		template <typename InputIt>
		void assign(InputIt first, InputIt last)
		{
			clear();
			insert(begin(), first, last);
		}

		void assign(size_type n, const value_type &val)
		{
			clear();
			insert(begin(), n, val);
		}

		void push_front(const value_type &val)
		{
			insert(begin(), val);
		}

		void pop_front()
		{
			erase(begin());
		}

		void push_back(const value_type &val)
		{
			insert(end(), val);
		}

		void pop_back()
		{
			iterator ite = end();
			--ite;
			erase(ite);
		}

		iterator insert(iterator position, const value_type &val)
		{
			_node *node = new _node(position._n->prv, position._n);
			node->el = val;
			if (node->prv)
				node->prv->nxt = node;
			else
				_head = node;
			node->nxt->prv = node;
			_len++;
			return iterator(node);
		}

		void insert(iterator position, size_type n, const value_type &val)
		{
			_node *nodeLeft = position._n->prv;
			_node *nodeRight = position._n;

			_node *nn = nodeLeft;
			for (size_t i = 0; i < n; i++)
			{
				_node *tmp = new _node(nn, NULL);
				tmp->el = val;

				if (nn)
					nn->nxt = tmp;
				else
					_head = tmp;
				_len++;
				nn = tmp;
			}

			nodeRight->prv = nn;
			if (nn)
				nn->nxt = nodeRight;
		}

		template <typename InputIt>
		void insert(iterator position, InputIt first, InputIt last)
		{
			_node *nodeLeft = position._n->prv;
			_node *nodeRight = position._n;

			_node *nn = nodeLeft;
			for (InputIt ite = first; ite != last; ++ite)
			{
				_node *tmp = new _node(nn, NULL);
				tmp->el = *ite;

				if (nn)
					nn->nxt = tmp;
				else
					_head = tmp;
				_len++;
				nn = tmp;
			}

			nodeRight->prv = nn;
			if (nn)
				nn->nxt = nodeRight;
		}

		iterator erase(iterator first, iterator last)
		{
			_node *nodeLeft = first._n->prv;
			_node *nodeRight = last._n;

			iterator ite = first;
			while (ite != last)
			{
				iterator tmp(ite);
				_len--;
				ite = ++ite;
				delete tmp._n;
			}

			if (nodeLeft)
				nodeLeft->nxt = nodeRight;
			else
				_head = nodeRight;
			nodeRight->prv = nodeLeft;

			return iterator(nodeRight);
		}

		iterator erase(iterator position)
		{
			iterator nxt = position;
			++nxt;
			return erase(position, nxt);
		}

		void swap(List &x)
		{
			std::swap(_head, x._head);
			std::swap(_tail, x._tail);
			std::swap(_len, x._len);
		}

		void resize(size_type n, value_type val = value_type())
		{
			if (n >= _len)
				insert(end(), n - _len, val);
			else
			{
				iterator ite = begin();
				for (size_t i = 0; i < n; i++)
					++ite;
				erase(ite, end());
			}
		}

		void clear()
		{
			erase(begin(), end());
		}

		void splice(iterator position, _Self &x)
		{
			splice(position, x, x.begin(), x.end());
		}

		void splice(iterator position, _Self &x, iterator i)
		{
			iterator nxt = i;
			++nxt;
			splice(position, x, i, nxt);
		}

		void splice(iterator position, _Self &x, iterator first, iterator last)
		{
			_node *node_right = position._n;
			_node *node_left = node_right->prv;

			_node *node_right_o = last._n;
			_node *node_left_o = first._n->prv;

			size_type count = 0;
			for (; first != last; ++first)
			{
				_node *to_transfer = first._n;

				if (node_left)
					node_left->nxt = to_transfer;
				else
					_head = to_transfer;

				to_transfer->prv = node_left;

				node_left = to_transfer;
				++count;
			}

			node_left->nxt = node_right;
			node_right->prv = node_left;
			node_right_o->prv = node_left_o;
			if (node_left_o)
				node_left_o->nxt = node_right_o;
			else
				x._head = node_right_o;

			_len += count;
			x._len -= count;
		}

		void remove(const value_type &val)
		{
			for (iterator ite = begin(); ite != end();)
			{
				if (*ite == val)
					ite = erase(ite);
				else
					++ite;
			}
		}

		template <typename Predicate>
		void remove_if(Predicate pred)
		{
			for (iterator ite = begin(); ite != end();)
			{
				if (pred(*ite))
					ite = erase(ite);
				else
					++ite;
			}
		}

		void unique()
		{
			unique(Equal<T>());
		}

		template <typename BinaryPredicate>
		void unique(BinaryPredicate binary_pred)
		{
			if (begin() == end())
				return;

			iterator cur = begin();
			iterator nxt = cur;
			++nxt;
			while (nxt != end())
			{
				if (binary_pred(*cur, *nxt))
					nxt = erase(nxt); // remove nxt!
				else
				{
					cur = nxt;
					++nxt;
				}
			}
		}

		void merge(_Self &x)
		{
			return merge(x, Less<T>());
		}

		template <typename Compare>
		void merge(_Self &x, Compare comp)
		{
			iterator self_ite = begin();
			for (iterator ite = x.begin(); ite != x.end();)
			{
				while (self_ite != end() && comp(*self_ite, *ite))
					++self_ite;

				// insert ite._n just before self_ite._n

				iterator tmp = ite;
				++ite;

				if (self_ite._n->prv)
					self_ite._n->prv->nxt = tmp._n;
				else
					_head = tmp._n;
				tmp._n->prv = self_ite._n->prv;
				self_ite._n->prv = tmp._n;
				tmp._n->nxt = self_ite._n;
			}

			_len += x._len;
			x._len = 0;
			x._head = x._tail; // set head to sentinel => no value in list
			x._tail->prv = NULL;
		}

		// void debug()
		// {
		// 	std::cout << "DEBUG" << std::endl;
		// 	_node *cur = _head;
		// 	std::cout << "HEAD = " << _head << std::endl;
		// 	while (cur)
		// 	{
		// 		if (cur->nxt)
		// 			std::cout << "- " << cur << " (" << cur->el.val << ") PRV=" << cur->prv << " NXT=" << cur->nxt << std::endl;
		// 		else
		// 			std::cout << "- " << cur << " (SENTINEL) PRV=" << cur->prv << " NXT=" << cur->nxt << std::endl;
		// 		cur = cur->nxt;
		// 	}
		// 	std::cout << "TAIL = " << _tail << std::endl;
		// 	std::cout << "LEN = " << _len << std::endl;
		// }

		void sort()
		{
			sort(Less<T>());
		}

		template <typename Compare>
		void sort(Compare comp)
		{
			// bubble sort in all its glory

			if (begin() == end())
				return;

			for (size_type i = 0; i < _len; ++i)
			{
				iterator cur = begin();
				iterator nxt = cur;
				++nxt;
				while (nxt != end())
				{
					if (!comp(*cur, *nxt))
					{
						// swap!

						_node *node_left = cur._n->prv;
						_node *node_right = nxt._n->nxt;

						cur._n->prv = nxt._n;
						nxt._n->nxt = cur._n;
						if (node_left)
							node_left->nxt = nxt._n;
						else
							_head = nxt._n;
						nxt._n->prv = node_left;
						node_right->prv = cur._n;
						cur._n->nxt = node_right;

						nxt = cur;
						++nxt;
					}
					else
					{
						cur = nxt;
						++nxt;
					}
				}
			}
		}

		void reverse()
		{
			iterator ite = begin();
			iterator begin = ite;
			while (1)
			{
				iterator tmp = ite;
				++ite;
				if (tmp._n->nxt == _tail)
				{
					tmp._n->nxt = tmp._n->prv;
					tmp._n->prv = NULL;
					_head = tmp._n;
					break;
				}
				else
					std::swap(tmp._n->prv, tmp._n->nxt);
			}
			_tail->prv = begin._n;
			begin._n->nxt = _tail;
		}

		template <typename _T>
		friend class ListIterator;

		template <typename _T>
		friend class List;
	};

	template <typename T>
	bool operator==(const List<T> &lhs, const List<T> &rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		return equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <typename T>
	bool operator!=(const List<T> &lhs, const List<T> &rhs)
	{
		return !(lhs == rhs);
	}

	template <typename T>
	bool operator<(const List<T> &lhs, const List<T> &rhs)
	{
		return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <typename T>
	bool operator<=(const List<T> &lhs, const List<T> &rhs)
	{
		return !(lhs > rhs);
	}

	template <typename T>
	bool operator>(const List<T> &lhs, const List<T> &rhs)
	{
		return rhs < lhs;
	}

	template <typename T>
	bool operator>=(const List<T> &lhs, const List<T> &rhs)
	{
		return !(lhs < rhs);
	}

	template <typename T>
	void swap(List<T> &x, List<T> &y)
	{
		x.swap(y);
	}
} // namespace ft

#endif
