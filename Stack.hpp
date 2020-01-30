/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchudant <cchudant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 21:49:22 by cchudant          #+#    #+#             */
/*   Updated: 2020/01/30 23:01:56 by cchudant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "Vector.hpp"

namespace ft
{
	template <typename T, typename Container = Vector<T> >
	class Stack
	{
		private:
			Container _ctnr;

		public:
			typedef T value_type;
			typedef Container container_type;
			typedef size_t size_type;

			explicit Stack(const container_type& ctnr = container_type()):
				_ctnr(ctnr)
			{
			}

			~Stack()
			{
			}

			Stack(const Stack<T, Container>& o):
				_ctnr(o._ctnr)
			{
			}

			Stack<T, Container>& operator=(const Stack<T, Container>& o)
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

			value_type& top()
			{
				return _ctnr.back();
			}

			const value_type& top() const
			{
				return _ctnr.back();
			}

			void push(const value_type& val)
			{
				return _ctnr.push_back(val);
			}

			void pop()
			{
				_ctnr.pop_back();
			}

			template <typename T2, typename Container2>
			friend void swap(Stack<T2, Container2>& lhs, Stack<T2, Container2>& rhs);
			template <typename T2, typename Container2>
			friend bool operator==(const Stack<T2, Container2>& lhs, const Stack<T2, Container2>& rhs);
			template <typename T2, typename Container2>
			friend bool operator<(const Stack<T2, Container2>& lhs, const Stack<T2, Container2>& rhs);
	};

	template <typename T, typename Container>
	void swap(Stack<T, Container>& lhs, Stack<T, Container>& rhs)
	{
		ft::swap(lhs._ctnr, rhs._ctnr);
	}

	template <typename T, typename Container>
	bool operator==(const Stack<T, Container>& lhs, const Stack<T, Container>& rhs)
	{
		return lhs._ctnr == rhs._ctnr;
	}

	template <typename T, typename Container>
	bool operator!=(const Stack<T, Container>& lhs, const Stack<T, Container>& rhs)
	{
		return !(lhs == rhs);
	}

	template <typename T, typename Container>
	bool operator<(const Stack<T, Container>& lhs, const Stack<T, Container>& rhs)
	{
		return lhs._ctnr < rhs._ctnr;
	}

	template <typename T, typename Container>
	bool operator<=(const Stack<T, Container>& lhs, const Stack<T, Container>& rhs)
	{
		return !(lhs > rhs);
	}

	template <typename T, typename Container>
	bool operator>(const Stack<T, Container>& lhs, const Stack<T, Container>& rhs)
	{
		return rhs < lhs;
	}

	template <typename T, typename Container>
	bool operator>=(const Stack<T, Container>& lhs, const Stack<T, Container>& rhs)
	{
		return !(lhs < rhs);
	}
}

#endif
