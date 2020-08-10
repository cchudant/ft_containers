/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVLTree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skybt <skybt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 01:15:42 by cchudant          #+#    #+#             */
/*   Updated: 2020/08/10 19:38:54 by skybt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include "Utility.hpp"

/*
 * AVL Tree.
 * Automatically balanced using the AVL algorithm.
 * 
 * The end of the tree is marked by a sentinel node, which is
 * the node pointed by the end() iterator.
 */

namespace ft
{
	template <typename E, typename Compare, bool AllowDuplicate>
	class AVLTree;

	template <typename E, typename Compare, bool AllowDuplicate, typename Node>
	class AVLTreeIterator
	{

	public:
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef E value_type;
		typedef E *pointer;
		typedef E &reference;
		typedef BidirectionalIteratorTag iterator_category;

	private:
		typedef AVLTree<E, Compare, AllowDuplicate> _tree;
		typedef Node _node;
		typedef AVLTreeIterator<E, Compare, AllowDuplicate, Node> _Self;

		_node *_n;

		AVLTreeIterator(_node *n)
			: _n(n) {}

	public:
		AVLTreeIterator(const _Self &other)
			: _n(other._n) {}

		AVLTreeIterator() {}

		~AVLTreeIterator() {}

		_Self &operator=(const _Self &other)
		{
			_n = other._n;
			return *this;
		}

		_Self &operator++()
		{
			if (_n->right)
			{
				_n = _n->right;
				while (_n->left)
					_n = _n->left;
			}
			else
			{
				_node *tmp;
				do
				{
					tmp = _n;
					_n = _n->parent;
				} while (_n && tmp == _n->right);
			}
			return *this;
		}

		_Self operator++(int)
		{
			_Self cpy = *this;
			operator++();
			return cpy;
		}

		_Self &operator--()
		{
			if (_n->left)
			{
				_n = _n->left;
				while (_n && _n->right)
					_n = _n->right;
			}
			else
			{
				_node *tmp;
				do
				{
					tmp = _n;
					_n = _n->parent;
				} while (_n && tmp == _n->left);
			}
			return *this;
		}

		_Self operator--(int)
		{
			_Self cpy = *this;
			operator--();
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

		template <typename _E, typename _Compare, bool _AllowDuplicate, typename _Node>
		friend bool operator==(
			const AVLTreeIterator<_E, _Compare, _AllowDuplicate, _Node> &lhs,
			const AVLTreeIterator<_E, _Compare, _AllowDuplicate, _Node> &rhs);

		template <typename _E, typename _Compare, bool _AllowDuplicate>
		friend class AVLTree;
	};

	template <typename E, typename Compare, bool AllowDuplicate, typename Node>
	bool operator==(
		const AVLTreeIterator<E, Compare, AllowDuplicate, Node> &lhs,
		const AVLTreeIterator<E, Compare, AllowDuplicate, Node> &rhs)
	{
		return lhs._n == rhs._n;
	}

	template <typename E, typename Compare, bool AllowDuplicate, typename Node>
	bool operator!=(
		const AVLTreeIterator<E, Compare, AllowDuplicate, Node> &lhs,
		const AVLTreeIterator<E, Compare, AllowDuplicate, Node> &rhs)
	{
		return !(lhs == rhs);
	}

	template <typename E, typename Compare, bool AllowDuplicate>
	class AVLTree
	{
	private:
		struct _node;

	public:
		typedef E value_type;
		typedef Compare compare;
		typedef AVLTreeIterator<E, compare, AllowDuplicate, _node> iterator;
		typedef AVLTreeIterator<const E, compare, AllowDuplicate, const _node> const_iterator;
		typedef ReverseIterator<iterator> reverse_iterator;
		typedef ReverseIterator<const_iterator> const_reverse_iterator;
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;

	private:
		struct _node
		{
			E el;
			_node *parent;
			_node *left;
			_node *right;
			difference_type height;

			_node(const E &el_, _node *parent_, _node *left_, _node *right_, difference_type height_)
				: el(el_), parent(parent_), left(left_), right(right_), height(height_) {}
		};

		typedef AVLTree<E, Compare, AllowDuplicate> _Self;

		compare _cmp;
		_node *_root;
		_node *_sentinel;
		size_type _len;

		bool _compare_node(E const &val, _node *n) const
		{
			if (n == _sentinel) // _sentinel compares superior to everything else
				return false;
			return _cmp(n->el, val);
		}

		static difference_type _balance_factor(_node *n)
		{
			if (!n)
				return 0;
			return (n->left ? n->left->height : -1) -
				   (n->right ? n->right->height : -1);
		}

		static void _rotate_left(_node **target)
		{
			_node *y = (*target)->right;
			_node *parent = (*target)->parent;
			(*target)->parent = y;
			y->parent = parent;
			(*target)->right = y->left;
			y->left = *target;
			(*target)->height = max(
									(*target)->left ? (*target)->left->height : -1,
									(*target)->right ? (*target)->right->height : -1) +
								1;
			*target = y;
			y->height = max(
							y->left ? y->left->height : -1,
							y->right ? y->right->height : -1) +
						1;
		}

		static void _rotate_right(_node **target)
		{
			_node *y = (*target)->left;
			_node *parent = (*target)->parent;
			(*target)->parent = y;
			y->parent = parent;
			(*target)->left = y->right;
			y->right = *target;
			(*target)->height = max(
									(*target)->left ? (*target)->left->height : -1,
									(*target)->right ? (*target)->right->height : -1) +
								1;
			*target = y;
			y->height = max(
							y->left ? y->left->height : -1,
							y->right ? y->right->height : -1) +
						1;
		}

		void _rec_clear(_node *n)
		{
			if (n->left)
				_rec_clear(n->left);
			if (n->right)
				_rec_clear(n->right);
			if (n != _sentinel)
				delete n;
		}

		void _erase_rebalance(_node *parent)
		{
			for (_node *p = parent; p; p = p->parent)
			{
				p->height = max(
								p->left ? p->left->height : -1,
								p->right ? p->right->height : -1) +
							1;

				if (_balance_factor(p) <= -2 || _balance_factor(p) >= 2)
				{
					_node *x = p;
					_node *y = x->left->height > x->right->height ? x->left : x->right;
					_node *z;
					if (y->left->height == y->right->height)
						z = y == x->left ? y->left : y->right;
					else
						z = y->left->height > y->right->height ? y->left : y->right;

					if (y == x->left)
					{
						if (z == x->left->right)
							_rotate_left(y);
						_rotate_right(x);
					}
					else if (y == x->right)
					{
						if (z == x->right->left)
							_rotate_left(y);
						_rotate_right(x);
					}
				}
			}
		}

		void _insert_rebalance(_node *inserted)
		{
			// go back to the root and update heights
			for (_node *n = inserted; n; n = n->parent)
			{
				n->height = max(
								n->left ? n->left->height : -1,
								n->right ? n->right->height : -1) +
							1;
				_node **x;
				if (!n->parent)
					x = &_root;
				else
					x = n == n->parent->left ? &n->parent->left : &n->parent->right;

				if (_balance_factor(n) < -1)
				{
					if (_balance_factor(n->right) > 0)
						_rotate_right(&(*x)->right);
					_rotate_left(x);
					break;
				}
				else if (_balance_factor(n) > 1)
				{
					if (_balance_factor(n->left) < 0)
						_rotate_left(&(*x)->left);
					_rotate_right(x);
					break;
				}
			}
		}

	public:
		AVLTree(const compare &cmp = compare()) : _cmp(cmp), _len(0)
		{
			_root = new _node(E(), NULL, NULL, NULL, 0);
			_sentinel = _root;
		}

		template <typename InputIt>
		AVLTree(InputIt first, InputIt last, const compare &cmp = compare()) : _cmp(cmp), _len(0)
		{
			_root = new _node(E(), NULL, NULL, NULL, 0);
			_sentinel = _root;
			insert(first, last);
		}

		AVLTree(const _Self &o) : _cmp(o._cmp), _len(0)
		{
			_root = new _node(E(), NULL, NULL, NULL, 0);
			_sentinel = _root;

			insert(o.begin(), o.end());
		}

		compare const &comparator() const
		{
			return _cmp;
		}

		~AVLTree()
		{
			clear();
			delete _sentinel;
		}

		_Self &operator=(const _Self &o)
		{
			clear();
			insert(o.begin(), o.end());
			return *this;
		}

		// void debug() const
		// {
		// 	debug(_root);
		// }

		// void debug(_node *n, int indent = 1) const
		// {
		// 	std::stringstream ss;
		// 	for (int i = 0; i < indent; i++)
		// 		ss << ">>";
		// 	if (!n)
		// 	{
		// 		printf("%s NULL\n", ss.str().c_str());
		// 		return;
		// 	}

		// 	if (_sentinel == n)
		// 		printf("%s SENTINEL\n", ss.str().c_str());
		// 	else
		// 		printf("%s El is (%d,%d) (h = %td, balance = %td)\n", ss.str().c_str(), n->el.first, n->el.second, n->height, _balance_factor(n));

		// 	assert(!n->left || n->left->parent == n);
		// 	assert(!n->right || n->right->parent == n);

		// 	printf("%s Left\n", ss.str().c_str());
		// 	debug(n->left, indent + 1);
		// 	printf("%s Right\n", ss.str().c_str());
		// 	debug(n->right, indent + 1);
		// }

		iterator begin()
		{
			_node *n = _root;
			while (n && n->left)
				n = n->left;
			return iterator(n);
		}

		const_iterator begin() const
		{
			_node *n = _root;
			while (n && n->left)
				n = n->left;
			return const_iterator(n);
		}

		iterator end()
		{
			return iterator(_sentinel);
		}

		const_iterator end() const
		{
			return const_iterator(_sentinel);
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
			return std::numeric_limits<difference_type>::max() / sizeof(value_type);
		}

		Pair<iterator, bool> insert(const value_type &val)
		{
			return insert(iterator(_root), val);
		}

		Pair<iterator, bool> insert(iterator hint, const value_type &val)
		{
			(void)hint;
			_node *part = _root;
			_node *newNode;

			while (true)
			{
				if (part == _sentinel)
				{
					_node *parent = _sentinel->parent;
					_node *&place = parent ? parent->right : _root;

					newNode = new _node(val, parent, NULL, _sentinel, 0);
					place = newNode;
					_sentinel->parent = newNode;
					break;
				}

				bool res = _cmp(val, part->el);

				if (!AllowDuplicate && !res && !_cmp(part->el, val))
					return make_pair(iterator(part), false);

				if (res)
				{
					if (part->left)
						part = part->left;
					else
					{
						newNode = new _node(val, part, NULL, NULL, 0);
						part->left = newNode;
						break;
					}
				}
				else
				{
					if (part->right)
						part = part->right;
					else
					{
						newNode = new _node(val, part, NULL, NULL, 0);
						part->right = newNode;
						break;
					}
				}
			}

			// _insert_rebalance(newNode);

			_len++;
			return make_pair(iterator(newNode), true);
		}

		template <typename InputIt>
		void insert(InputIt first, InputIt last)
		{
			for (; first != last; ++first)
				insert(*first);
		}

		void erase(iterator position)
		{
			_node *n = position._n;

			_node **x;
			if (!n->parent)
				x = &_root;
			else
				x = n == n->parent->left ? &n->parent->left : &n->parent->right;

			if (!n->left && !n->right) // _node is a leaf
				*x = NULL;
			else if ((n->left || n->right) && !(n->left && n->right)) // _node has one child
				*x = n->left ? n->left : n->right;
			else // _node has two children
			{
				_node *succ = n->right;
				while (succ->left)
					succ = succ->left;
				succ->parent->left = NULL;
				succ->left = n->left;
				succ->right = n->right;
				*x = succ;
			}

			// _erase_rebalance(n->parent);

			delete n;
			_len--;
		}

		void erase(iterator first, iterator last)
		{
			for (; first != last; ++first)
				erase(*first);
		}

		void swap(AVLTree<E, Compare, AllowDuplicate> &x)
		{
			std::swap(x._root, _root);
			std::swap(x._sentinel, _sentinel);
			// ft::swap(x._cmp, _cmp);
			std::swap(x._len, _len);
		}

		void clear()
		{
			_rec_clear(_root);
			_sentinel->right = NULL;
			_sentinel->left = NULL;
			_sentinel->parent = NULL;
			_sentinel->height = 0;
			_root = _sentinel;
			_len = 0;
		}

		iterator find(const value_type &v)
		{
			_node *n = _root;
			while (n && n != _sentinel)
			{
				bool ret = _cmp(n->el, v);
				if (!ret && !_cmp(v, n->el))
					return iterator(n);
				if (!ret)
					n = n->left;
				else
					n = n->right;
			}
			return end();
		}

		const_iterator find(const value_type &v) const
		{
			_node *n = _root;
			while (n && n != _sentinel)
			{
				bool ret = _cmp(n->el, v);
				if (!ret && !_cmp(v, n->el))
					return const_iterator(n);
				if (!ret)
					n = n->left;
				else
					n = n->right;
			}
			return end();
		}

		size_type count(const value_type &v) const
		{
			size_type count = 0;
			_node *n = _root;
			while (n && n != _sentinel)
			{
				bool ret = _cmp(n->el, v);
				if (!ret && !_cmp(v, n->el))
				{
					if (AllowDuplicate)
						count++;
					else
						return 1;
					n = n->right;
				}
				else if (!ret)
					n = n->left;
				else
					n = n->right;
			}
			return count;
		}

		iterator lower_bound(const value_type &v)
		{
			for (iterator ite = begin(); ite != end(); ++ite)
				if (!_cmp(*ite, v))
					return ite;
			return end();
		}

		const_iterator lower_bound(const value_type &v) const
		{
			for (const_iterator ite = begin(); ite != end(); ++ite)
				if (!_cmp(*ite, v))
					return ite;
			return end();
		}

		iterator upper_bound(const value_type &v)
		{
			for (iterator ite = begin(); ite != end(); ++ite)
				if (_cmp(v, *ite))
					return ite;
			return end();
		}

		const_iterator upper_bound(const value_type &v) const
		{
			for (const_iterator ite = begin(); ite != end(); ++ite)
				if (_cmp(v, *ite))
					return ite;
			return end();
		}

		Pair<iterator, iterator> equal_range(const value_type &v)
		{
			return make_pair(lower_bound(v), upper_bound(v));
		}

		const_iterator equal_range(const value_type &v) const
		{
			return make_pair(lower_bound(v), upper_bound(v));
		}

		template <typename _E, typename _Compare, bool _AllowDuplicate, typename _Node>
		friend class AVLTreeIterator;
	};

	template <typename E, typename Compare, bool AllowDuplicate>
	void swap(AVLTree<E, Compare, AllowDuplicate> &x, AVLTree<E, Compare, AllowDuplicate> &y)
	{
		x.swap(y);
	}
} // namespace ft

#endif
