/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skybt <skybt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 16:40:50 by cchudant          #+#    #+#             */
/*   Updated: 2020/08/10 20:53:01 by skybt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
#define PAIR_HPP

#include <cstddef>
#include <limits>
#include <iostream>

namespace ft
{
	// Pair

	template <typename T1, typename T2>
	struct Pair
	{
		typedef T1 first_type;
		typedef T2 second_type;

		T1 first;
		T2 second;

		Pair() : first(), second()
		{
		}

		~Pair()
		{
		}

		Pair(const T1 &x, const T2 &y) : first(x), second(y)
		{
		}

		template <typename U1, typename U2>
		Pair(const Pair<U1, U2> &c) : first(c.first), second(c.second)
		{
		}

		Pair(const Pair<T1, T2> &c) : first(c.first), second(c.second)
		{
		}

		template <typename U1, typename U2>
		Pair<T1, T2> &operator=(const Pair<U1, U2> &c)
		{
			first = c.first;
			second = c.second;
			return *this;
		}

		Pair<T1, T2> &operator=(const Pair<T1, T2> &c)
		{
			first = c.first;
			second = c.second;
			return *this;
		}
	};

	template <typename T1, typename T2>
	Pair<T1, T2> make_pair(T1 t, T2 u)
	{
		return Pair<T1, T2>(t, u);
	}

	template <typename T1, typename T2>
	bool operator==(const Pair<T1, T2> &lhs, const Pair<T1, T2> &rhs)
	{
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}

	template <typename T1, typename T2>
	bool operator<(const Pair<T1, T2> &lhs, const Pair<T1, T2> &rhs)
	{
		return lhs.first < rhs.first && lhs.second < rhs.second;
	}

	template <typename T1, typename T2>
	bool operator!=(const Pair<T1, T2> &lhs, const Pair<T1, T2> &rhs)
	{
		return !(lhs == rhs);
	}

	template <typename T1, typename T2>
	bool operator<=(const Pair<T1, T2> &lhs, const Pair<T1, T2> &rhs)
	{
		return !(lhs > rhs);
	}

	template <typename T1, typename T2>
	bool operator>(const Pair<T1, T2> &lhs, const Pair<T1, T2> &rhs)
	{
		return rhs < lhs;
	}

	template <typename T1, typename T2>
	bool operator>=(const Pair<T1, T2> &lhs, const Pair<T1, T2> &rhs)
	{
		return !(lhs < rhs);
	}

	// Iterator tags

	struct InputIteratorTag
	{
	};
	struct OutputIteratorTag
	{
	};
	struct ForwardIteratorTag : public InputIteratorTag
	{
	};
	struct BidirectionalIteratorTag : public ForwardIteratorTag
	{
	};
	struct RandomAccessIteratorTag : public BidirectionalIteratorTag
	{
	};

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
	struct IteratorTraits<T *> // specialize IteratorTraits for arrays
	{
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T *pointer;
		typedef T &reference;
		typedef RandomAccessIteratorTag iterator_category;
	};

	template <typename T>
	struct IteratorTraits<const T *> // specialize IteratorTraits for const arrays
	{
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef const T *pointer;
		typedef const T &reference;
		typedef RandomAccessIteratorTag iterator_category;
	};

	// Iterator distance

	// random access iterator optimization
	template <typename RAIt>
	typename IteratorTraits<RAIt>::difference_type distance(RAIt first, RAIt last, RandomAccessIteratorTag)
	{
		return last - first;
	}

	// non random access iterator implementation
	template <typename It>
	typename IteratorTraits<It>::difference_type distance(It first, It last, InputIteratorTag)
	{
		typename IteratorTraits<It>::difference_type dist = 0;
		for (; first != last; ++first)
			dist++;
		return dist;
	}

	template <typename InputIt>
	typename IteratorTraits<InputIt>::difference_type distance(InputIt first, InputIt last)
	{
		return distance(first, last, typename IteratorTraits<InputIt>::iterator_category());
	}

	// Iterator advance

	// random access iterator optimization
	template <typename RAIt, typename Distance>
	void advance(RAIt &ite, Distance distance, RandomAccessIteratorTag)
	{
		ite += distance;
	}

	// non random access iterator implementation
	template <typename It, typename Distance>
	void advance(It &ite, Distance distance, InputIteratorTag)
	{
		for (ptrdiff_t i = 0; i < distance; ++i)
			++ite;
	}

	template <typename InputIt, typename Distance>
	void advance(InputIt &ite, Distance distance)
	{
		return advance(ite, distance, typename IteratorTraits<InputIt>::iterator_category());
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

		ReverseIterator(Iter base) : _base(base)
		{
		}

		ReverseIterator(const ReverseIterator<Iter> &other) : _base(other._base)
		{
		}

		~ReverseIterator()
		{
		}

		Iter base() const
		{
			return _base;
		}

		ReverseIterator<Iter> &operator=(const ReverseIterator<Iter> &other)
		{
			_base = other._base;
			return *this;
		}

		ReverseIterator<Iter> &operator++()
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

		ReverseIterator<Iter> &operator--()
		{
			++_base;
			return *this;
		}

		ReverseIterator<Iter> operator--(int)
		{
			ReverseIterator<Iter> ite(_base++);
			return ite;
		}

		ReverseIterator<Iter> &operator+=(difference_type offset)
		{
			_base -= offset;
			return *this;
		}

		ReverseIterator<Iter> &operator-=(difference_type offset)
		{
			_base += offset;
			return *this;
		}
	};

	template <typename Iter>
	bool operator==(const ReverseIterator<Iter> &lhs, const ReverseIterator<Iter> &rhs)
	{
		return lhs.base() == rhs.base();
	}

	template <typename Iter>
	bool operator!=(const ReverseIterator<Iter> &lhs, const ReverseIterator<Iter> &rhs)
	{
		return lhs.base() != rhs.base();
	}

	template <typename Iter>
	bool operator<(const ReverseIterator<Iter> &lhs, const ReverseIterator<Iter> &rhs)
	{
		return lhs.base() > rhs.base();
	}

	template <typename Iter>
	bool operator>(const ReverseIterator<Iter> &lhs, const ReverseIterator<Iter> &rhs)
	{
		return lhs.base() < rhs.base();
	}

	template <typename Iter>
	bool operator<=(const ReverseIterator<Iter> &lhs, const ReverseIterator<Iter> &rhs)
	{
		return lhs.base() >= rhs.base();
	}

	template <typename Iter>
	bool operator>=(const ReverseIterator<Iter> &lhs, const ReverseIterator<Iter> &rhs)
	{
		return lhs.base() <= rhs.base();
	}

	template <typename Iter>
	ReverseIterator<Iter> operator+(const ReverseIterator<Iter> &ite, size_t offset)
	{
		ReverseIterator<Iter> r(ite.base() - offset);
		return r;
	}

	template <typename Iter>
	ReverseIterator<Iter> operator+(typename ReverseIterator<Iter>::difference_type offset, const ReverseIterator<Iter> &ite)
	{
		ReverseIterator<Iter> r(ite.base() - offset);
		return r;
	}

	template <typename Iter>
	ReverseIterator<Iter> operator-(const ReverseIterator<Iter> &ite, typename ReverseIterator<Iter>::difference_type offset)
	{
		ReverseIterator<Iter> r(ite.base() + offset);
		return r;
	}

	template <typename Iter>
	ptrdiff_t operator-(const ReverseIterator<Iter> &lhs, const ReverseIterator<Iter> &rhs)
	{
		return rhs.base() - lhs.base();
	}

	// Operators

	template <typename T>
	struct Less
	{
		bool operator()(const T &lhs, const T &rhs) const
		{
			return lhs < rhs;
		}
	};

	template <typename T>
	void swap(Less<T> const &x, Less<T> const &y)
	{
		(void)x;
		(void)y;
	}

	template <typename T>
	struct Equal
	{
		bool operator()(const T &lhs, const T &rhs) const
		{
			return lhs == rhs;
		}
	};

	template <typename T>
	void swap(Equal<T> const &x, Equal<T> const &y)
	{
		(void)x;
		(void)y;
	}

	// lexicographical compare

	template <
		typename InputIt1,
		typename InputIt2,
		typename Compare = Less<typename IteratorTraits<InputIt1>::value_type>>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
								 InputIt2 first2, InputIt2 last2,
								 Compare comp = Compare())
	{
		for (; first1 != last1 && first2 != last2; ++first1, ++first2)
		{
			if (comp(*first1, *first2))
				return true;
			if (comp(*first2, *first1))
				return false;
		}
		return (first1 == last1) && (first2 != last2);
	}

	// equal

	template <typename InputIt1, typename InputIt2>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
	{
		for (; first1 != last1; ++first1, ++first2)
			if (*first1 != *first2)
				return false;
		return true;
	}

	// min / max

	template <typename T>
	const T &min(const T &a, const T &b)
	{
		return a < b ? a : b;
	}

	template <typename T>
	const T &max(const T &a, const T &b)
	{
		return a < b ? b : a;
	}

	// copy / move / fill

	template <typename InputIt1, typename InputIt2>
	InputIt2 copy(InputIt1 first, InputIt1 last, InputIt2 dest_first)
	{
		while (first != last)
			*dest_first++ = *first++;
		return dest_first;
	}

	template <typename InputIt1, typename InputIt2>
	InputIt2 move(InputIt1 first, InputIt1 last, InputIt2 dest_first)
	{
		return copy(first, last, dest_first);
	}

	template <typename InputIt1, typename InputIt2>
	InputIt2 copy_backward(InputIt1 first, InputIt1 last, InputIt2 dest_last)
	{
		while (first != last)
			*(--dest_last) = *(--last);
		return dest_last;
	}

	template <typename InputIt1, typename InputIt2>
	InputIt2 move_backward(InputIt1 first, InputIt1 last, InputIt2 dest_last)
	{
		return copy_backward(first, last, dest_last);
	}

	template <typename InputIt, typename T>
	void fill(InputIt first, InputIt last, const T &val)
	{
		for (; first != last; ++first)
		{
			*first = val;
		}
	}

	template <typename InputIt1, typename InputIt2>
	InputIt2 uninitialized_copy(InputIt1 first, InputIt1 last, InputIt2 dest_first)
	{
		typedef typename IteratorTraits<InputIt2>::value_type Value;
		for (; first != last; ++first, ++dest_first)
		{
			::new (static_cast<void *>(&*dest_first)) Value(*first);
		}
		return dest_first;
	}

	template <typename InputIt1, typename InputIt2>
	InputIt2 uninitialized_move(InputIt1 first, InputIt1 last, InputIt2 dest_first)
	{
		return uninitialized_copy(first, last, dest_first);
	}

	template <typename InputIt, typename T>
	void uninitialized_fill(InputIt first, InputIt last, const T &val)
	{
		typedef typename IteratorTraits<InputIt>::value_type Value;
		for (; first != last; ++first)
		{
			::new (static_cast<void *>(&*first)) Value(val);
		}
	}

} // namespace ft

#endif
