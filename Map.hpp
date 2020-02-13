/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchudant <cchudant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 23:30:02 by cchudant          #+#    #+#             */
/*   Updated: 2020/02/13 17:44:56 by cchudant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include "Utility.hpp"

namespace ft
{

	template <typename Key, typename T, typename Compare>
	class Map
	{
		private:
			key_compare& _cmp;

		public:

			typedef Key key_type;
			typedef T mapped_type;
			typedef std::pair<const key_type, mapped_type>;
			typedef Compare key_compare;
			class value_compare;
			typedef T& reference;
			typedef const T& const_reference;
			typedef T* pointer;
			typedef const T* const_pointer;
			typedef int iterator; //todo
			typedef int const_iterator; //todo
			typedef std::reverse_iterator<iterator> reverse_iterator;
			typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
			typedef std::ptrdiff_t difference_type;
			typedef size_t size_type;

			class value_compare: public binary_function<value_type, value_type, bool>
			{
				private:
					value_compare _cmp;

					value_compare(Compare c):
						_cmp(c)
					{
					}

					~value_compare()
					{
					}

					value_compare(const value_compare& o);
					value_compare& operator=(const value_compare& o);
				
				public:

					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;

					bool operator()(const value_type& x, const value_type& y) const
					{
						return cmp(x.first, y.first);
					}
			}

			explicit Map(const key_compare& cmp = key_compare()):
				_cmp(cmp)
			{
			}

			template <typename InputIt>
			Map(InputIt first, InputIt last, const key_compare& cmp = key_compare());
			Map(const Map& o);
			~Map();
			Map<Key, T, Compare> operator=(const Map<Key, T, Compare>& o);

			iterator begin();
			const_iterator begin() const;
			iterator end();
			const_iterator end() const;
			reverse_iterator rbegin();
			const_reverse_iterator rbegin() const;
			reverse_iterator rend();
			const_reverse_iterator rend() const;

			bool empty() const;
			size_type size() const;
			size_type max_size() const;

			mapped_type& operator[](const key_type& k);

			std::pair<iterator, bool> insert(const value_type& val);
			iterator insert(iterator position, const value_type& val);
			template <typename InputIt>
			void insert(InputIt first, InputIt last);
			void erase(iterator position);
			size_type erase(const key_type& k);
			void erase(iterator first, iterator last);
			void swap(Map<Key, T, Compare>& x);
			void clear();

			key_compare key_comp() const;
			value_compare value_comp() const
			{
				return _cmp;
			}

			iterator find(const key_type& k);
			const_iterator find(const key_type& k) const;
			size_type count(const key_type& k) const;
			iterator lowest_bound(const key_type& k);
			const_iterator lowest_bound(const key_type& k) const;
			iterator upper_bound(const key_type& k);
			const_iterator upper_bound(const key_type& k) const;

			std::pair<iterator, iterator> equal_range(const key_type& k);
			std::pair<const_iterator, const_iterator> equal_range(const key_type& k) const;
	};
}

#endif
