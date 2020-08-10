/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Queue.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skybt <skybt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 23:06:04 by cchudant          #+#    #+#             */
/*   Updated: 2020/08/10 19:38:41 by skybt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "List.hpp"

namespace ft
{
	template <typename T, typename Container = List<T>>
	class Queue
	{
	public:
		typedef T value_type;
		typedef Container container_type;
		typedef size_t size_type;

	private:
		typedef Queue<T, Container> _Self;

		container_type _ctnr;

	public:
		Queue(const container_type &ctnr = container_type())
			: _ctnr(ctnr) {}

		~Queue() {}

		Queue(const _Self &o)
			: _ctnr(o._ctnr) {}

		_Self &operator=(const _Self &o)
		{
			_ctnr = o._ctnr;
			return *this;
		}

		bool empty() const
		{
			return _ctnr.empty();
		}

		size_type size() const
		{
			return _ctnr.size();
		}

		value_type &front()
		{
			return _ctnr.front();
		}

		const value_type &front() const
		{
			return _ctnr.front();
		}

		value_type &back()
		{
			return _ctnr.back();
		}

		const value_type &back() const
		{
			return _ctnr.back();
		}

		void push(const value_type &val)
		{
			return _ctnr.push_back(val);
		}

		void pop()
		{
			_ctnr.pop_front();
		}

		template <typename _T, typename _Container>
		friend void swap(Queue<_T, _Container> &lhs, Queue<_T, _Container> &rhs);

		template <typename _T, typename _Container>
		friend bool operator==(const Queue<_T, _Container> &lhs, const Queue<_T, _Container> &rhs);

		template <typename _T, typename _Container>
		friend bool operator<(const Queue<_T, _Container> &lhs, const Queue<_T, _Container> &rhs);
	};

	template <typename T, typename Container>
	void swap(Queue<T, Container> &lhs, Queue<T, Container> &rhs)
	{
		ft::swap(lhs._ctnr, rhs._ctnr);
	}

	template <typename T, typename Container>
	bool operator==(const Queue<T, Container> &lhs, const Queue<T, Container> &rhs)
	{
		return lhs._ctnr == rhs._ctnr;
	}

	template <typename T, typename Container>
	bool operator!=(const Queue<T, Container> &lhs, const Queue<T, Container> &rhs)
	{
		return !(lhs == rhs);
	}

	template <typename T, typename Container>
	bool operator<(const Queue<T, Container> &lhs, const Queue<T, Container> &rhs)
	{
		return lhs._ctnr < rhs._ctnr;
	}

	template <typename T, typename Container>
	bool operator<=(const Queue<T, Container> &lhs, const Queue<T, Container> &rhs)
	{
		return !(lhs > rhs);
	}

	template <typename T, typename Container>
	bool operator>(const Queue<T, Container> &lhs, const Queue<T, Container> &rhs)
	{
		return rhs < lhs;
	}

	template <typename T, typename Container>
	bool operator>=(const Queue<T, Container> &lhs, const Queue<T, Container> &rhs)
	{
		return !(lhs < rhs);
	}
} // namespace ft

#endif
