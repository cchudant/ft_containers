/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skybt <skybt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 21:49:22 by cchudant          #+#    #+#             */
/*   Updated: 2020/08/10 19:38:36 by skybt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "Vector.hpp"

namespace ft
{
	template <typename T, typename Container = Vector<T>>
	class Stack
	{

	public:
		typedef T value_type;
		typedef Container container_type;
		typedef size_t size_type;

	private:
		typedef Stack<T, Container> _Self;

		container_type _ctnr;

	public:
		Stack(const container_type &ctnr = container_type())
			: _ctnr(ctnr) {}

		~Stack() {}

		Stack(const _Self &o)
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

		value_type &top()
		{
			return _ctnr.back();
		}

		const value_type &top() const
		{
			return _ctnr.back();
		}

		void push(const value_type &val)
		{
			return _ctnr.push_back(val);
		}

		void pop()
		{
			_ctnr.pop_back();
		}

		template <typename _T, typename _Container>
		friend void swap(Stack<_T, _Container> &lhs, Stack<_T, _Container> &rhs);

		template <typename _T, typename _Container>
		friend bool operator==(const Stack<_T, _Container> &lhs, const Stack<_T, _Container> &rhs);

		template <typename _T, typename _Container>
		friend bool operator<(const Stack<_T, _Container> &lhs, const Stack<_T, _Container> &rhs);
	};

	template <typename T, typename Container>
	void swap(Stack<T, Container> &lhs, Stack<T, Container> &rhs)
	{
		ft::swap(lhs._ctnr, rhs._ctnr);
	}

	template <typename T, typename Container>
	bool operator==(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs)
	{
		return lhs._ctnr == rhs._ctnr;
	}

	template <typename T, typename Container>
	bool operator!=(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs)
	{
		return !(lhs == rhs);
	}

	template <typename T, typename Container>
	bool operator<(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs)
	{
		return lhs._ctnr < rhs._ctnr;
	}

	template <typename T, typename Container>
	bool operator<=(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs)
	{
		return !(lhs > rhs);
	}

	template <typename T, typename Container>
	bool operator>(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs)
	{
		return rhs < lhs;
	}

	template <typename T, typename Container>
	bool operator>=(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs)
	{
		return !(lhs < rhs);
	}
} // namespace ft

#endif
