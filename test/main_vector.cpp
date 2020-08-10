/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skybt <skybt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 06:28:20 by cchudant          #+#    #+#             */
/*   Updated: 2020/08/08 12:39:32 by skybt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Test.hpp"

static void test_pushback()
{
	ft::Vector<ConstrCounter> vec;
	assert(vec.size() == 0);

	vec.push_back(ConstrCounter(0));
	assert(vec.size() == 1);
	assert(vec[0].val == 0);

	vec.push_back(ConstrCounter(1));
	assert(vec.size() == 2);
	assert(vec[1].val == 1);

	vec.push_back(ConstrCounter(8000));
	assert(vec.size() == 3);
	assert(vec[2].val == 8000);

	vec.push_back(ConstrCounter(33));
	assert(vec.size() == 4);
	assert(vec[3].val == 33);
}

static void test_assign()
{
	ft::Vector<ConstrCounter> vec;
	assert(vec.size() == 0);

	vec.assign(0, ConstrCounter(66));
	assert(vec.size() == 0);

	vec.assign(10, ConstrCounter(5));
	assert(vec.size() == 10);
	assert(vec[2].val == 5);
	assert(vec[9].val == 5);

	vec.assign(15, ConstrCounter(120));
	assert(vec.size() == 15);
	assert(vec[0].val == 120);
	assert(vec[6].val == 120);

	vec.assign(5, ConstrCounter(6));
	assert(vec.size() == 5);
	assert(vec[2].val == 6);
	assert(vec[3].val == 6);

	vec.assign(50, ConstrCounter(9000));
	assert(vec.size() == 50);
	assert(vec[26].val == 9000);
	assert(vec[49].val == 9000);
}

static void test_assign_iter()
{
	ft::Vector<ConstrCounter> vec;
	assert(vec.size() == 0);

	{
		ConstrCounter array[0] = {};

		vec.assign(array, array);
		assert(vec.size() == 0);
	}
	{
		ConstrCounter array[5] = {0, 1, 2, 3, 4};

		vec.assign(array, array + 5);
		assert(vec.size() == 5);
		assert(vec[0].val == 0);
		assert(vec[1].val == 1);
		assert(vec[2].val == 2);
		assert(vec[3].val == 3);
		assert(vec[4].val == 4);
	}
	{
		ConstrCounter array[2] = {42, 43};

		vec.assign(array, array + 2);
		assert(vec.size() == 2);
		assert(vec[0].val == 42);
		assert(vec[1].val == 43);
	}
}

static void test_constr()
{
	{
		ft::Vector<ConstrCounter> vec(0, ConstrCounter(5));
		assert(vec.size() == 0);
	}
	{
		ft::Vector<ConstrCounter> vec(10, ConstrCounter(5));
		assert(vec.size() == 10);
		assert(vec[2].val == 5);
		assert(vec[9].val == 5);
	}
	{
		ft::Vector<ConstrCounter> vec(15, ConstrCounter(120));
		assert(vec.size() == 15);
		assert(vec[0].val == 120);
		assert(vec[6].val == 120);
	}
	{
		ft::Vector<ConstrCounter> vec(5, ConstrCounter(6));
		assert(vec.size() == 5);
		assert(vec[2].val == 6);
		assert(vec[3].val == 6);
	}
	{
		ft::Vector<ConstrCounter> vec(50, ConstrCounter(9000));
		assert(vec.size() == 50);
		assert(vec[26].val == 9000);
		assert(vec[49].val == 9000);
	}
}

static void test_constr_iter()
{
	{
		ConstrCounter array[0] = {};

		ft::Vector<ConstrCounter> vec(array, array);
		assert(vec.size() == 0);
	}
	{
		ConstrCounter array[5] = {0, 1, 2, 3, 4};

		ft::Vector<ConstrCounter> vec(array, array + 5);
		assert(vec.size() == 5);
		assert(vec[0].val == 0);
		assert(vec[1].val == 1);
		assert(vec[2].val == 2);
		assert(vec[3].val == 3);
		assert(vec[4].val == 4);
	}
	{
		ConstrCounter array[2] = {42, 43};

		ft::Vector<ConstrCounter> vec(array, array + 2);
		assert(vec.size() == 2);
		assert(vec[0].val == 42);
		assert(vec[1].val == 43);
	}
}

static void test_assign_copy()
{
	ft::Vector<ConstrCounter> vec;
	vec.push_back(ConstrCounter(0));
	vec.push_back(ConstrCounter(1));
	vec.push_back(ConstrCounter(2));

	ft::Vector<ConstrCounter> vec2(vec);
	assert(vec2.size() == 3);
	assert(vec2[0].val == 0);
	assert(vec2[1].val == 1);
	assert(vec2[2].val == 2);

	vec2.push_back(ConstrCounter(3));
	assert(vec.size() == 3);
	assert(vec2.size() == 4);

	ft::Vector<ConstrCounter> vec3;
	assert(vec3.size() == 0);

	vec3 = vec2;
	assert(vec.size() == 3);
	assert(vec2.size() == 4);
	assert(vec3.size() == 4);

	vec = vec3;
	assert(vec.size() == 4);
	assert(vec2.size() == 4);
	assert(vec3.size() == 4);

	assert(vec[0].val == 0);
	assert(vec[1].val == 1);
	assert(vec[2].val == 2);
	assert(vec[3].val == 3);
	assert(vec2[0].val == 0);
	assert(vec2[1].val == 1);
	assert(vec2[2].val == 2);
	assert(vec2[3].val == 3);
	assert(vec3[0].val == 0);
	assert(vec3[1].val == 1);
	assert(vec3[2].val == 2);
	assert(vec3[3].val == 3);
}

static void test_accessors()
{
	ft::Vector<ConstrCounter> vec;
	vec.push_back(ConstrCounter(0));
	vec.push_back(ConstrCounter(1));
	vec.push_back(ConstrCounter(2));

	assert(vec[0].val == 0);
	assert(vec[1].val == 1);
	assert(vec[2].val == 2);

	assert(vec.at(0).val == 0);
	assert(vec.at(1).val == 1);
	assert(vec.at(2).val == 2);

	bool exception = false;
	try
	{
		vec.at(3);
	}
	catch (const std::out_of_range &e)
	{
		exception = true;
	}
	assert(exception);

	assert(vec.front().val == 0);
	assert(vec.back().val == 2);
}

static void test_capacity()
{
	ft::Vector<ConstrCounter> vec;
	assert(vec.empty());
	assert(vec.size() == 0);

	vec.push_back(ConstrCounter(0));
	vec.push_back(ConstrCounter(1));
	vec.push_back(ConstrCounter(2));

	assert(!vec.empty());
	assert(vec.size() == 3);

	vec.reserve(50);
	assert(vec.capacity() >= 50);
	vec.reserve(50);
	assert(vec.capacity() >= 50);
	vec.reserve(20);
	assert(vec.capacity() >= 50);
	vec.reserve(10);
	assert(vec.capacity() >= 50);
	vec.reserve(0);
	assert(vec.capacity() >= 50);
	vec.reserve(60);
	assert(vec.capacity() >= 60);
	vec.reserve(10);
	assert(vec.capacity() >= 60);
	vec.reserve(0);
	assert(vec.capacity() >= 60);

	vec.clear();
	assert(vec.size() == 0);
	assert(vec.empty());
	assert(vec.capacity() >= 60);
}

static void test_iterator()
{
	ft::Vector<ConstrCounter> vec;
	assert(vec.size() == 0);
	assert(vec.begin() == vec.end());

	vec.push_back(ConstrCounter(0));
	assert(vec.size() == 1);
	assert(vec.begin() + 1 == vec.end());

	vec.push_back(ConstrCounter(1));
	assert(vec.size() == 2);
	assert(vec.begin() + 2 == vec.end());

	vec.push_back(ConstrCounter(2));
	assert(vec.size() == 3);
	assert(vec.begin() + 3 == vec.end());
	assert(vec.begin() == vec.end() - 3);

	const ft::Vector<ConstrCounter> &vec2 = vec;

	ft::Vector<ConstrCounter>::const_iterator ite = vec2.begin();
	assert((*ite).val == 0);
	assert(ite->val == 0);
	assert(++ite == vec2.begin() + 1);
	assert((*ite).val == 1);
	assert(ite->val == 1);
	assert(ite++ == vec2.begin() + 1);
	assert(ite == vec2.begin() + 2);
	assert((*ite).val == 2);
	assert(ite->val == 2);
	assert(++ite == vec2.end());
	assert(--ite == vec2.end() - 1);
	assert(ite->val == 2);
	assert(ite-- == vec2.end() - 1);
	assert(ite == vec2.end() - 2);
	assert(ite->val == 1);
	assert(--ite == vec2.begin());
	assert(ite->val == 0);
}

static void test_reverse_iterator()
{
	ft::Vector<ConstrCounter> vec;
	vec.push_back(ConstrCounter(0));
	vec.push_back(ConstrCounter(1));
	vec.push_back(ConstrCounter(2));

	ft::Vector<ConstrCounter>::reverse_iterator ite =
		vec.rbegin();
	assert(ite->val == 2);
	++ite;
	assert(ite->val == 1);
	++ite;
	assert(ite->val == 0);
	++ite;
	assert(ite == vec.rend());
}

static void test_insert_one()
{
	ft::Vector<ConstrCounter> vec;

	vec.reserve(2);
	assert(vec.insert(vec.begin(), ConstrCounter(5)) == vec.begin());
	assert(vec.size() == 1);
	assert(vec[0].val == 5);

	assert(vec.insert(vec.begin() + 1, ConstrCounter(5)) == vec.begin() + 1);
	assert(vec.size() == 2);
	assert(vec[1].val == 5);
}

static void test_insert()
{
	ft::Vector<ConstrCounter> vec;
	vec.reserve(12);
	assert(vec.size() == 0);

	vec.insert(vec.begin(), 0, ConstrCounter(66));
	assert(vec.size() == 0);

	vec.insert(vec.begin(), 10, ConstrCounter(120));
	assert(vec.size() == 10);
	assert(vec[2].val == 120);
	assert(vec[9].val == 120);

	vec.insert(vec.begin() + 3, 2, ConstrCounter(33));
	assert(vec.size() == 12);
	assert(vec[3].val == 33);
	assert(vec[6].val == 120);
}

static void test_insert_iter()
{
	ft::Vector<ConstrCounter> vec;
	vec.reserve(7);
	assert(vec.size() == 0);

	{
		ConstrCounter array[5] = {0, 1, 2, 3, 4};

		vec.insert(vec.begin(), array, array + 5);
		assert(vec.size() == 5);
		assert(vec[0].val == 0);
		assert(vec[1].val == 1);
		assert(vec[2].val == 2);
		assert(vec[3].val == 3);
		assert(vec[4].val == 4);
	}
	{
		ConstrCounter array[0] = {};

		vec.insert(vec.begin() + 2, array, array);
		assert(vec.size() == 5);
	}
	{
		ConstrCounter array[2] = {42, 43};

		vec.insert(vec.begin() + 2, array, array + 2);
		assert(vec.size() == 7);
		assert(vec[0].val == 0);
		assert(vec[1].val == 1);
		assert(vec[2].val == 42);
		assert(vec[3].val == 43);
		assert(vec[4].val == 2);
		assert(vec[5].val == 3);
		assert(vec[6].val == 4);
	}
}

static void test_erase()
{
	ft::Vector<ConstrCounter> vec;
	ConstrCounter array[5] = {0, 1, 2, 3, 4};
	vec.insert(vec.begin(), array, array + 5);

	assert(vec.erase(vec.begin()) == vec.begin());
	assert(vec.size() == 4);
	assert(vec[0].val == 1);

	assert(vec.erase(vec.begin() + 2) == vec.begin() + 2);
	assert(vec.size() == 3);
	assert(vec[2].val == 4);
}

static void test_erase_range()
{
	ft::Vector<ConstrCounter> vec;
	ConstrCounter array[5] = {0, 1, 2, 3, 4};
	vec.insert(vec.begin(), array, array + 5);

	vec.erase(vec.begin() + 1, vec.end() - 1);
	assert(vec.size() == 2);
	assert(vec[0].val == 0);
	assert(vec[1].val == 4);

	vec.erase(vec.begin(), vec.begin());
	assert(vec.size() == 2);
	assert(vec[0].val == 0);
	assert(vec[1].val == 4);
}

static void test_pop_back()
{
	ft::Vector<ConstrCounter> vec;
	ConstrCounter array[5] = {0, 1, 2, 3, 4};
	vec.insert(vec.begin(), array, array + 5);

	assert(vec.size() == 5);
	vec.pop_back();
	assert(vec.size() == 4);
	vec.pop_back();
	assert(vec.size() == 3);
	vec.pop_back();
	assert(vec.size() == 2);
	vec.pop_back();
	assert(vec.size() == 1);
	vec.pop_back();
	assert(vec.size() == 0);
}

static void test_resize()
{
	ft::Vector<ConstrCounter> vec;

	vec.resize(3, ConstrCounter(0));
	assert(vec.size() == 3);
	assert(vec[0].val == 0);
	assert(vec[1].val == 0);
	assert(vec[2].val == 0);

	vec.resize(2, ConstrCounter(5));
	assert(vec.size() == 2);
	assert(vec[0].val == 0);
	assert(vec[1].val == 0);

	vec.resize(5, ConstrCounter(99));
	assert(vec.size() == 5);
	assert(vec[0].val == 0);
	assert(vec[1].val == 0);
	assert(vec[2].val == 99);
	assert(vec[3].val == 99);
	assert(vec[4].val == 99);
}

static void test_swap()
{
	ConstrCounter array[5] = {0, 1, 2, 3, 4};
	ft::Vector<ConstrCounter> vec(array, array + 5);

	ConstrCounter array2[3] = {2, 3, 1};
	ft::Vector<ConstrCounter> vec2(array2, array2 + 3);

	vec.swap(vec2);
	assert(vec.size() == 3);
	assert(vec2.size() == 5);
	assert(vec[0].val == 2);
	assert(vec2[0].val == 0);

	ft::swap(vec2, vec);
	assert(vec.size() == 5);
	assert(vec2.size() == 3);
	assert(vec[0].val == 0);
	assert(vec2[0].val == 2);
}

static void test_cmp_eq()
{
	ConstrCounter array[5] = {0, 1, 2, 3, 4};
	ft::Vector<ConstrCounter> vec(array, array + 5);
	ft::Vector<ConstrCounter> vec2(vec);

	assert(vec == vec2);
	assert(vec >= vec2);
	assert(vec <= vec2);

	vec2.push_back(50);
	assert(vec != vec2);
	assert(vec < vec2);
	assert(vec <= vec2);
	assert(vec2 > vec);
	assert(vec2 >= vec);

	vec.push_back(200);
	assert(vec != vec2);
	assert(vec > vec2);
	assert(vec >= vec2);
	assert(vec2 < vec);
	assert(vec2 <= vec);
}

void test_vector()
{
	test_one("push_back", test_pushback);
	test_one("assign", test_assign);
	test_one("assign_iter", test_assign_iter);
	test_one("constr", test_constr);
	test_one("constr_iter", test_constr_iter);
	test_one("assign_copy", test_assign_copy);
	test_one("accessors", test_accessors);
	test_one("capacity", test_capacity);
	test_one("iterator", test_iterator);
	test_one("reverse_iterator", test_reverse_iterator);
	test_one("insert_one", test_insert_one);
	test_one("insert", test_insert);
	test_one("insert_iter", test_insert_iter);
	test_one("erase", test_erase);
	test_one("erase_range", test_erase_range);
	test_one("pop_back", test_pop_back);
	test_one("resize", test_resize);
	test_one("swap", test_swap);
	test_one("cmp_eq", test_cmp_eq);
}
