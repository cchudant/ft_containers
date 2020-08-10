/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_multimap.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skybt <skybt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 11:26:16 by skybt             #+#    #+#             */
/*   Updated: 2020/08/08 12:39:15 by skybt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Test.hpp"

static void test_simple_insert()
{
    ft::MultiMap<int, int> map;

    map.insert(ft::make_pair(0, 2));
    assert(map.size() == 1);
    map.insert(ft::make_pair(1, 5));
    assert(map.size() == 2);
    map.insert(ft::make_pair(1, 8));
    assert(map.size() == 3);

    for (size_t l = 0; l < 50; l++)
        map.insert(ft::make_pair(l, 2 * l));

    assert(map.size() == 53);
}

static void test_accessors()
{
    ft::MultiMap<int, int> map;

    assert(map.empty());
    assert(map.size() == 0);
    map.insert(ft::make_pair(0, 2));
    assert(!map.empty());
    assert(map.size() == 1);
    map.insert(ft::make_pair(1, 5));
    assert(map.size() == 2);
    map.insert(ft::make_pair(1, 8));
    assert(map.size() == 3);

    for (size_t l = 0; l < 50; l++)
        map.insert(ft::make_pair(l, 2 * l));

    assert(map.count(0) == 2);
    assert(map.count(1) == 3);
    assert(map.count(2) == 1);
    assert(map.count(3) == 1);
    assert(map.count(4) == 1);
    assert(map.count(49) == 1);
    assert(!map.empty());

    map.clear();
    assert(map.empty());
    assert(map.size() == 0);
    map.insert(ft::make_pair(0, 2));
    assert(!map.empty());
    assert(map.size() == 1);
    map.insert(ft::make_pair(1, 5));
    assert(map.size() == 2);
    map.insert(ft::make_pair(1, 8));
    assert(map.size() == 3);

    assert(!map.empty());
}

static void test_index()
{
    ft::MultiMap<int, int> map;

    assert(map.empty());
    assert(map.size() == 0);
    map.insert(ft::make_pair(0, 2));
    assert(map.count(0) == 1);
    assert(!map.empty());
    assert(map.size() == 1);
    map.insert(ft::make_pair(1, 5));
    assert(map.count(1) == 1);
    assert(map.size() == 2);
    map.insert(ft::make_pair(1, 8));
    assert(map.count(1) == 2);
    assert(map.size() == 3);

    for (size_t l = 0; l < 50; l++)
        map.insert(ft::make_pair(l, 2 * l));

    assert(map.count(0) == 2);
    assert(map.count(1) == 3);
    assert(map.count(2) == 1);
    assert(map.count(3) == 1);
    assert(map.count(4) == 1);
    assert(map.count(49) == 1);
    assert(!map.empty());

    map.clear();
    assert(map.empty());
    assert(map.size() == 0);
    map.insert(ft::make_pair(0, 2));
    assert(!map.empty());
    assert(map.size() == 1);
    map.insert(ft::make_pair(1, 5));
    assert(map.size() == 2);
    map.insert(ft::make_pair(1, 8));
    assert(map.size() == 3);

    assert(!map.empty());
}

static void test_constructors()
{
    ft::MultiMap<int, int> map;
    map.insert(ft::make_pair(0, 50));
    map.insert(ft::make_pair(90, 5));
    map.insert(ft::make_pair(2, 80));

    assert(map.size() == 3);

    ft::MultiMap<int, int> cpy;
    assert(cpy.size() == 0);

    cpy = map;
    assert(cpy.size() == 3);
    assert(cpy.count(0) == 1);
    assert(cpy.count(90) == 1);
    assert(cpy.count(2) == 1);

    cpy.insert(ft::make_pair(5, 8));
    map.insert(ft::make_pair(5, 80));
    map.insert(ft::make_pair(9, 80));
    assert(cpy.count(5) == 1);
    assert(map.count(5) == 1);

    ft::swap(cpy, map);
    assert(map.count(5) == 1);
    assert(cpy.count(5) == 1);

    assert(map.size() == 4);
    assert(cpy.size() == 5);

    ft::MultiMap<int, int> cpy2(cpy);

    assert(cpy2.size() == 5);
    assert(cpy.count(5) == 1);
    assert(cpy2.count(5) == 1);
}

static void test_iterators()
{
    ft::MultiMap<int, int> map;
    map.insert(ft::make_pair(0, 50));
    map.insert(ft::make_pair(90, 5));
    map.insert(ft::make_pair(2, 80));

    ft::MultiMap<int, int>::iterator ite = map.begin();
    assert(ite->first == 0);
    assert(ite->second == 50);
    assert((++ite)->first == 2);
    assert((ite++)->second == 80);
    assert(ite->first == 90);
    assert(ite->second == 5);

    ft::Pair<int, int> pair = *ite;
    assert(pair.first == 90);
    assert(pair.second == 5);

    assert(++ite == map.end());
    assert(--ite != map.end());

    const ft::MultiMap<int, int> &map2 = map;

    ft::MultiMap<int, int>::const_iterator ite2 = map2.end();
    --ite2;

    assert(ite2->first == 90);
    assert(ite2->second == 5);
    assert((--ite2)->first == 2);
    assert((ite2--)->second == 80);
    assert(ite2->first == 0);
    assert(ite2->second == 50);

    assert(ite2 == map2.begin());
}

static void test_reverse_iterators()
{
    ft::MultiMap<int, int> map;
    map.insert(ft::make_pair(0, 50));
    map.insert(ft::make_pair(90, 5));
    map.insert(ft::make_pair(2, 80));

    ft::MultiMap<int, int>::reverse_iterator ite = map.rbegin();
    assert(ite->first == 90);
    assert(ite->second == 5);
    assert((++ite)->first == 2);
    assert((ite++)->second == 80);
    assert(ite->first == 0);
    assert(ite->second == 50);

    ft::Pair<int, int> pair = *ite;
    assert(pair.first == 0);
    assert(pair.second == 50);

    assert(++ite == map.rend());
    assert(--ite != map.rend());

    const ft::MultiMap<int, int> &map2 = map;

    ft::MultiMap<int, int>::const_reverse_iterator ite2 = map2.rend();
    --ite2;

    assert(ite2->first == 0);
    assert(ite2->second == 50);
    assert((--ite2)->first == 2);
    assert((ite2--)->second == 80);
    assert(ite2->first == 90);
    assert(ite2->second == 5);

    assert(ite2 == map2.rbegin());
}

static void test_insert()
{
    ft::MultiMap<int, int> map;
    map.insert(ft::make_pair(0, 50));
    map.insert(ft::make_pair(90, 5));
    map.insert(ft::make_pair(2, 80));

    ft::Pair<int, int> tab[6] = {
        ft::make_pair(0, 1),
        ft::make_pair(50, 2),
        ft::make_pair(6, 4),
        ft::make_pair(-45, -5),
        ft::make_pair(4, 98),
        ft::make_pair(6, 9),
    };

    map.insert(tab, tab + 6);
    assert(map.size() == 9);
    assert(map.count(0) == 2);
    assert(map.count(90) == 1);
    assert(map.count(6) == 2);
    assert(map.count(-45) == 1);
    assert(map.count(4) == 1);

    map.clear();
    map.insert(tab, tab + 6);
    assert(map.size() == 6);
    assert(map.count(0) == 1);
    assert(map.count(6) == 2);
    assert(map.count(-45) == 1);
    assert(map.count(4) == 1);
}

static void test_cmp()
{
    ft::MultiMap<int, int> map;
    map.insert(ft::make_pair(0, 50));
    map.insert(ft::make_pair(90, 5));

    ft::MultiMap<int, int> map2;
    map2.insert(ft::make_pair(0, 50));
    map2.insert(ft::make_pair(90, 5));
    map2.insert(ft::make_pair(2, 80));

    assert(map != map2);
    assert(map2 < map);
    assert(map2 <= map);
    assert(!(map2 > map));
    assert(!(map2 >= map));

    map.insert(ft::make_pair(2, 80));
    assert(map == map2);
    assert(!(map2 < map));
    assert(map2 <= map);
    assert(!(map2 > map));
    assert(map2 >= map);

    map.insert(ft::make_pair(1, 4));
    assert(map != map2);
    assert(map2 > map);
    assert(map2 >= map);
    assert(!(map2 < map));
    assert(!(map2 <= map));
}

static void test_swap()
{
    ft::MultiMap<int, int> map;
    map.insert(ft::make_pair(10, 96));
    map.insert(ft::make_pair(36, 9));
    map.insert(ft::make_pair(8, 8));

    ft::MultiMap<int, int> map2;
    map2.insert(ft::make_pair(0, 50));
    map2.insert(ft::make_pair(90, 5));

    assert(map.size() == 3);
    assert(map.count(10) == 1);
    assert(map.count(36) == 1);
    assert(map.count(8) == 1);
    assert(map2.size() == 2);
    assert(map2.count(0) == 1);
    assert(map2.count(90) == 1);

    ft::swap(map, map2);

    assert(map2.size() == 3);
    assert(map2.count(10) == 1);
    assert(map2.count(36) == 1);
    assert(map2.count(8) == 1);
    assert(map.size() == 2);
    assert(map.count(0) == 1);
    assert(map.count(90) == 1);

    map2.swap(map);

    assert(map.size() == 3);
    assert(map.count(10) == 1);
    assert(map.count(36) == 1);
    assert(map.count(8) == 1);
    assert(map2.size() == 2);
    assert(map2.count(0) == 1);
    assert(map2.count(90) == 1);
}

static void test_count_find()
{
    ft::MultiMap<int, int> map;
    map.insert(ft::make_pair(10, 96));
    map.insert(ft::make_pair(36, 9));
    map.insert(ft::make_pair(8, 8));

    assert(map.find(10)->second == 96);
    assert(map.find(36)->second == 9);
    assert(map.find(99) == map.end());
    assert(map.find(0) == map.end());
    assert(map.find(8) == map.begin());

    assert(map.count(10) == 1);
    assert(map.count(9) == 0);
    assert(map.count(36) == 1);
    assert(map.count(55) == 0);
}

static void test_range()
{
    ft::MultiMap<int, int> map;
    map.insert(ft::make_pair(10, 96));
    map.insert(ft::make_pair(36, 9));
    map.insert(ft::make_pair(8, 8));
    map.insert(ft::make_pair(8, 10));

    ft::MultiMap<int, int>::iterator ite = map.begin();
    ++ite;
    ++ite;

    assert(map.lower_bound(5) == map.begin());
    assert(map.lower_bound(9) != map.begin());
    assert(map.lower_bound(9) == ite);
    assert(map.lower_bound(60) == map.end());
    ++ite;

    assert(map.lower_bound(35) == ite);
    assert(map.lower_bound(36) == ite);
    assert(map.lower_bound(37) != ite);
    ++ite;
    assert(map.lower_bound(37) == ite);
    assert(map.lower_bound(37) == map.end());

    ite = map.begin();

    assert(map.upper_bound(5) == ite);
    assert(map.upper_bound(6) == ite);
    assert(map.upper_bound(8) != ite);
    ++ite;
    ++ite;
    assert(map.upper_bound(8) == ite);
    assert(map.upper_bound(9) == ite);
    assert(map.upper_bound(10) != ite);
    ++ite;
    assert(map.upper_bound(10) == ite);
    assert(map.upper_bound(30) == ite);

    typedef typename ft::MultiMap<int, int>::iterator iter;
    ft::Pair<iter, iter> range;

    range = map.equal_range(8);
    ite = map.begin();
    ++ite;
    assert(range.first == map.begin() && range.second == ++ite);

    range = map.equal_range(36);
    ite = map.begin();
    ++ite;
    ++ite;
    assert(range.first == ++ite && range.second == ++ite);

    range = map.equal_range(50);
    assert(range.first == map.end());
    assert(range.second == map.end());

    range = map.equal_range(0);
    assert(range.first == map.begin());
    assert(range.second == map.begin());
}

void test_multimap()
{
    test_one("simple_insert", test_simple_insert);
    test_one("accessors", test_accessors);
    test_one("index", test_index);
    test_one("constructors", test_constructors);
    test_one("iterators", test_iterators);
    test_one("reverse_iterators", test_reverse_iterators);
    test_one("insert", test_insert);
    test_one("cmp", test_cmp);
    test_one("swap", test_swap);
    test_one("count_find", test_count_find);
    test_one("range", test_range);
}
