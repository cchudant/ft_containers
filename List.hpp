/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchudant <cchudant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 10:52:36 by cchudant          #+#    #+#             */
/*   Updated: 2020/01/24 15:40:47 by cchudant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
# define LIST_HPP

namespace ft
{
	template <typename T>
	class ListIterator
	{
		private:
			List<T>::node* _prv;
			List<T>::node* _nxt;

		public:
			ListIterator(List<T>::node* prv, List<T>::node* nxt):
				_prv(prv), _nxt(nxt)
			{
			}

			List<T>::node* prv() const
			{
				return _prv;
			}

			List<T>::node* nxt() const
			{
				return _nxt;
			}

			typedef T value_type;
			typedef size_t size_type;
			typedef std::ptrdiff_t difference_type;
			typedef T& reference;
			typedef T* pointer;
			typedef std::double_ended_iterator iterator_category;

			ListIterator(const ListIterator<T>& other):
				_prv(other._prv), _nxt(other._nxt)
			{
			}

			~ListIterator()
			{
			}

			ListIterator<T>& operator=(const ListIterator<T>& other)
			{
				_prv = other._prv;
				_nxt = other._nxt;
			}

			ListIterator<T>& operator++()
			{
				_prv = _nxt;
				_nxt = _nxt->nxt;
				return *this;
			}

			ListIterator<T> operator++(int)
			{
				ListIterator<T> cpy = *this;
				_prv = _nxt;
				_nxt = _nxt->nxt;
				return cpy;
			}

			ListIterator<T>& operator--()
			{
				_nxt = _prv;
				_prv = _prv->prv;
				return *this;
			}

			ListIterator<T> operator--(int)
			{
				ListIterator<T> cpy = *this;
				_nxt = _prv;
				_prv = _prv->prv;
				return cpy;
			}

			T& operator*() const
			{
				return _nxt->el;
			}

			T* operator->() const
			{
				return _nxt->el;
			}
	};

	template < typename T >
    bool operator==(const ListIterator< T >& lhs, const ListIterator< T >& rhs)
	{
		return lhs._prv == rhs._prv && lhs._nxt == rhs._nxt;
	}

    template < typename T >
    bool operator!=(const ListIterator< T >& lhs, const ListIterator< T >& rhs)
	{
		return lhs._prv != rhs._prv || lhs._nxt != rhs._nxt;
	}


	template <typename T>
	class List
	{
		private:
			struct node
			{
				node(node* prv_, node* nxt_, const T &el_):
					prv(prv_), nxt(nxt_), el(el_) {};

				node* prv;
				node* nxt;
				T el;
			};

			node *_head;
			node *_tail;
			size_t _len;

		public:
			/* MEMBER TYPES */

			typedef T value_type;
			typedef &T reference;
			typedef const &T const_reference;
			typedef *T pointer;
			typedef const *T const_pointer;
			typedef iterator ListIterator<T>;
			typedef const_iterator ListIterator<const T>;
			typedef reverse_iterator std::reverse_iterator<iterator>;
			typedef const_reverse_iterator std::reverse_iterator<const_iterator>;
			typedef difference_type std::ptrdiff_t;
			typedef size_type size_t;

			/* CONSTRUCTORS */

			explicit List():
				_head(NULL), _tail(NULL), _len(0)
			{
			}

			explicit List(size_type n, const value_type& val = value_type())
			{
				insert(begin(), n, val);
			}

			template <typename InputIt>
			explicit List(InputIt first, InputIt last)
			{
				insert(begin(), first, last);
			}

			List(const List& other):
				_head(NULL), _tail(NULL), _len(0)
			{
				insert(begin(), other.begin(), other.end())
			}

			List &operator=(const List<T>& other)
			{
				clear();
				insert(begin(), other.begin(), other.end())
			}

			~List()
			{
				erase(begin(), end())
			}

			/* ITERATORS */

			iterator begin()
			{
				return iterator(NULL, _head);
			}

			const_iterator begin() const
			{
				return iterator(NULL, _head);
			}

			iterator end()
			{
				return iterator(_tail, NULL);
			}

			const_iterator end() const
			{
				return iterator(_tail, NULL);
			}

			reverse_iterator rbegin()
			{
				return reverse_iterator(end());
			}

			const_reverse_iterator rbegin() const
			{
				return reverse_iterator(end());
			}

			reverse_iterator rend()
			{
				return reverse_iterator(begin());
			}

			const_reverse_iterator rend() const
			{
				return reverse_iterator(begin());
			}

			/* CAPACITY */

			bool empty() const
			{
				return _len == 0;
			}

			size_type size() const
			{
				return _len;
			}

			size_type max_size() const;

			/* ELEMENT ACCESS */

			reference front()
			{
				return head->el;
			}

			const_reference front() const
			{
				return head->el;
			}

			reference back()
			{
				return tail->el;
			}

			const_reference back() const
			{
				return tail->el;
			}

			/* MODIFIERS */

			template <typename InputIt>
			void assign(InputIt first, InputIt last)
			{
				clear();
				insert(begin(), first, last);
			}

			void assign(size_type n, const value_type& val)
			{
				clear();
				insert(begin(), n, val);
			}

			void push_front(const value_type& val)
			{
				insert(begin(), val);
			}

			void pop_front()
			{
				erase(begin());
			}

			void push_back(const value_type& val)
			{
				insert(begin(), val);
			}

			void pop_back()
			{
				erase(--end());
			}

			iterator insert(iterator position, const value_type& val)
			{
				insert(position, 1, val);
				
				node* nodeLeft = position.prv;
				node* nodeRight = nodeLeft ? nodeLeft->nxt : _head;
				return iterator(nodeLeft, nodeRight);
			}

			void insert(iterator position, size_type n, const value_type& val)
			{
				node* nodeLeft = position.prv;
				node* nodeRight = position.nxt;

				node* node = nodeLeft;
				for (size_t i = 0; i < n; i++)
				{
					node *tmp = new node(node, NULL, val);
					if (node)
						node->nxt = tmp;
					else
						_head = tmp;
					node = tmp;
				}

				if (nodeRight)
				{
					nodeRight->prv = node;
					node->nxt = nodeRight;
				}
				else
					_tail = node;
			}

			template <typename InputIt>
			void insert(iterator position, InputIt first, InputIt last)
			{
				node* nodeLeft = position.prv;
				node* nodeRight = position.nxt;

				node* node = nodeLeft;
				for (InputIt ite = first; ite != last; ++ite)
				{
					node *tmp = new node(node, NULL, *ite);
					if (node)
						node->nxt = tmp;
					else
						_head = tmp;
					node = tmp;
				}

				if (nodeRight)
				{
					nodeRight->prv = node;
					node->nxt = nodeRight;
				}
				else
					_tail = node;
			}

			iterator erase(iterator position)
			{
				return erase(position, position + 1);
			}

			iterator erase(iterator first, iterator last)
			{
				node* nodeLeft = first->prv;
				node* nodeRight = last->nxt;

				iterator ite = first;
				while (first != last)
					delete first->nxt;

				if (nodeLeft)
					nodeLeft->nxt = nodeRight;
				else
					_head = nodeRight;
				if (nodeRight)
					nodeRight->prv = nodeLeft;
				else
					_tail = nodeLeft;
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
					insert(end(), val);
				else
				{
					iterator ite = begin();
					for (int i = 0; i < n; i++)
						++ite;
					erase(ite, end());
				}
			}

			void clear()
			{
				erase(begin(), end());
			}

			/* OPERATIONS */

			void splice(iterator position, List& x)
			{
				splice(position, x, x.begin(), x.end());
			}

			void splice(iterator position, List& x, iterator i)
			{
				splice(position, x, i, ++i);
			}

			void splice(iterator position, List& x, iterator first, iterator last);

			void remove(const value_type& val);
			template <typename Predicate>
			void remove_if(Predicate pred);
			void unique();
			template <typename BinaryPredicate>
			void unique(BinaryPredicate binary_pred);
			void merge(List& x);
			template <typename Compare>
			void merge(List& x, Compare comp);
			void sort();
			template <typename Compare>
			void sort(Compare comp);
			void reverse();
	};

	template <typename T>
	bool operator==(const List<T>& lhs, const List<T>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;

		List<T>::iterator ite1 = lhs.begin();
		List<T>::iterator ite2 = rhs.begin();
		while (ite1 != lhs.end() && ite2 != rhs.end())
		{
			if (*ite1 != *ite2)
				return false;

			++ite1;
			++ite2;
		}
		return true;
	}

	template <typename T>
	bool operator!=(const List<T>& lhs, const List<T>& rhs)
	{
		return !(lhs == rhs);
	}

	template <typename T>
	bool operator<(const List<T>& lhs, const List<T>& rhs)
	{
		List<T>::iterator ite1 = lhs.begin();
		List<T>::iterator ite2 = rhs.begin();
		while (ite1 != lhs.end() && ite2 != rhs.end())
		{
			if (*ite1 != *ite2)
				return *ite1 < *ite2;

			++ite1;
			++ite2;
		}
		
		if (lhs.size() == rhs.size())
            return false; // lhs == rhs at that point

        return lhs.size() < rhs.size(); // lhs < rhs if lhs is prefix of rhs

	}

	template <typename T>
	bool operator<=(const List<T>& lhs, const List<T>& rhs)
	{
		return !(lhs > rhs);
	}

	template <typename T>
	bool operator>(const List<T>& lhs, const List<T>& rhs)
	{
		return rhs < lhs;
	}

	template <typename T>
	bool operator>=(const List<T>& lhs, const List<T>& rhs)
	{
		return !(lhs < rhs);
	}

	template <typename T>
	void swap(List<T>& x, List<T>& y)
	{
		x.swap(y);
	}
}

#endif
