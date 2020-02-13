/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchudant <cchudant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 16:40:50 by cchudant          #+#    #+#             */
/*   Updated: 2020/02/13 18:15:26 by cchudant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

# include <cstddef>

namespace ft
{
	// Pair

	template <typename T1, typename T2>
	struct Pair
	{
		T1 first_type;
		T2 second_type;

		Pair():
			first_type(), second_type()
		{
		}

		~Pair()
		{
		}

		Pair(const T1& x, const T2& y):
			first_type(x), second_type(y)
		{
		}

		template <typename U1, typename U2>
		Pair(const Pair<U1, U2>& c):
			first_type(c.first_type), second_type(c.second_type)
		{
		}

		Pair(const Pair<T1, T2>& c):
			first_type(c.first_type), second_type(c.second_type)
		{
		}

		template <typename U1, typename U2>
		Pair<T1, T2>& operator=(const Pair<U1, U2>& c)
		{
			first_type = c.first_type;
			second_type = c.second_type;
			return *this;
		}

		Pair<T1, T2>& operator=(const Pair<T1, T2>& c)
		{
			first_type = c.first_type;
			second_type = c.second_type;
			return *this;
		}
	};

	template <typename T1, typename T2>
	Pair<T1, T2> make_pair(T1 t, T2 u)
	{
		return Pair<T1, T2>(t, u);
	}

	template <typename T1, typename T2>
	bool operator==(const Pair<T1, T2>& lhs, const Pair<T1, T2>& rhs)
	{
		return lhs.first == rhs.first && lhs.second == rhs.second;;
	}

	template <typename T1, typename T2>
	bool operator<(const Pair<T1, T2>& lhs, const Pair<T1, T2>& rhs)
	{
		return lhs.first < rhs.first && lhs.second < rhs.second;
	}

	template <typename T1, typename T2>
	bool operator!=(const Pair<T1, T2>& lhs, const Pair<T1, T2>& rhs)
	{
		return !(lhs == rhs);
	}

	template <typename T1, typename T2>
	bool operator<=(const Pair<T1, T2>& lhs, const Pair<T1, T2>& rhs)
	{
		return !(lhs > rhs);
	}

	template <typename T1, typename T2>
	bool operator>(const Pair<T1, T2>& lhs, const Pair<T1, T2>& rhs)
	{
		return rhs < lhs;
	}

	template <typename T1, typename T2>
	bool operator>=(const Pair<T1, T2>& lhs, const Pair<T1, T2>& rhs)
	{
		return !(lhs < rhs);
	}

	// Iterator tags

	struct InputIteratorTag {};
	struct OutputIteratorTag {};
	struct ForwardIteratorTag: public InputIteratorTag {};
	struct BidirectionalIteratorTag: public ForwardIteratorTag {};
	struct RandomAccessIteratorTag: public BidirectionalIteratorTag {};

	// Iterator traits

	template <typename Iter>
	struct IteratorTraits
	{
		typedef typename Iter::difference_type difference_type;
		typedef typename Iter::value_type value_type;
		typedef typename Iter::pointer pointer;
		typedef typename Iter::reference reference;
		typedef typename Iter::iterator_category iterator_category;
	};

	template <typename T>
	struct IteratorTraits<T*>
	{
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef RandomAccessIteratorTag iterator_category;
	};

	template <typename T>
	struct IteratorTraits<const T*>
	{
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef const T* pointer;
		typedef const T& reference;
		typedef RandomAccessIteratorTag iterator_category;
	};

	// Iterator distance

	// note: could be optimized if InputIt is random access
	template <typename InputIt>
	typename IteratorTraits<InputIt>::difference_type distance(InputIt first, InputIt last)
	{
		std::ptrdiff_t len = 0;
		for (InputIt ite = first; ite != last; ++ite)
			len++;
		return len;
	}

	// Reverse iterator

	template <typename Iter>
	class ReverseIterator
	{
		private:
			Iter _base;

			ReverseIterator();

		public:
			typedef Iter iterator_type;
			typedef typename IteratorTraits<Iter>::difference_type difference_type;
			typedef typename IteratorTraits<Iter>::value_type value_type;
			typedef typename IteratorTraits<Iter>::pointer pointer;
			typedef typename IteratorTraits<Iter>::reference reference;
			typedef typename IteratorTraits<Iter>::iterator_category iterator_category;

			ReverseIterator(Iter base):
				_base(base)
			{
			}

			ReverseIterator(const ReverseIterator<Iter>& other):
				_base(other._base)
			{
			}

			~ReverseIterator()
			{
			}

			Iter base() const
			{
				return _base;
			}

			ReverseIterator<Iter>& operator=(const ReverseIterator<Iter>& other)
			{
				_base = other._base;
				return *this;
			}

			ReverseIterator<Iter>& operator++()
			{
				--_base;
				return *this;
			}

			ReverseIterator<Iter> operator++(int)
			{
				ReverseIterator<Iter> ite(_base--);
				return ite;
			}

			reference operator*() const
			{
				Iter ite(_base);
				--ite;
				return *ite;
			}

			pointer operator->() const
			{
				Iter ite(_base);
				--ite;
				return ite.operator->();
			}

			ReverseIterator<Iter>& operator--()
			{
				++_base;
				return *this;
			}

			ReverseIterator<Iter> operator--(int)
			{
				ReverseIterator<Iter> ite(_base++);
				return ite;
			}

			ReverseIterator<Iter>& operator+=(difference_type offset)
			{
				_base -= offset;
				return *this;
			}

			ReverseIterator<Iter>& operator-=(difference_type offset)
			{
				_base += offset;
				return *this;
			}
	};

	template <typename Iter>
	bool operator==(const ReverseIterator<Iter>& lhs, const ReverseIterator<Iter>& rhs)
	{
		return lhs.base() == rhs.base();
	}

	template <typename Iter>
	bool operator!=(const ReverseIterator<Iter>& lhs, const ReverseIterator<Iter>& rhs)
	{
		return lhs.base() != rhs.base();
	}

	template <typename Iter>
	bool operator<(const ReverseIterator<Iter>& lhs, const ReverseIterator<Iter>& rhs)
	{
		return lhs.base() > rhs.base();
	}

	template <typename Iter>
	bool operator>(const ReverseIterator<Iter>& lhs, const ReverseIterator<Iter>& rhs)
	{
		return lhs.base() < rhs.base();
	}

	template <typename Iter>
	bool operator<=(const ReverseIterator<Iter>& lhs, const ReverseIterator<Iter>& rhs)
	{
		return lhs.base() >= rhs.base();
	}

	template <typename Iter>
	bool operator>=(const ReverseIterator<Iter>& lhs, const ReverseIterator<Iter>& rhs)
	{
		return lhs.base() <= rhs.base();
	}

	template <typename Iter>
	ReverseIterator<Iter> operator+(const ReverseIterator<Iter>& ite, size_t offset)
	{
		ReverseIterator<Iter> r(ite.base() - offset);
		return r;
	}

	template <typename Iter>
	ReverseIterator<Iter> operator+(typename ReverseIterator<Iter>::difference_type  offset, const ReverseIterator<Iter>& ite)
	{
		ReverseIterator<Iter> r(ite.base() - offset);
		return r;
	}

	template <typename Iter>
	ReverseIterator<Iter> operator-(const ReverseIterator<Iter>& ite, typename ReverseIterator<Iter>::difference_type offset)
	{
		ReverseIterator<Iter> r(ite.base() + offset);
		return r;
	}

	template <typename Iter>
	std::ptrdiff_t operator-(const ReverseIterator<Iter>& lhs, const ReverseIterator<Iter>& rhs)
	{
		return rhs.base() - lhs.base();
	}
}

#endif