/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skybt <skybt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 11:26:16 by skybt             #+#    #+#             */
/*   Updated: 2020/08/08 12:39:12 by skybt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Test.hpp"

static void test_simple_insert()
{
    ft::Map<int, int> map;

    map.insert(ft::make_pair(0, 2));
    assert(map.size() == 1);
    map.insert(ft::make_pair(1, 5));
    assert(map.size() == 2);
    map.insert(ft::make_pair(1, 8));
    assert(map.size() == 2);

    for (size_t l = 0; l < 50; l++)
        map.insert(ft::make_pair(l, 2 * l));

    assert(map.size() == 50);
}

static void test_accessors()
{
    ft::Map<int, int> map;

    assert(map.empty());
    assert(map.size() == 0);
    map.insert(ft::make_pair(0, 2));
    assert(!map.empty());
    assert(map.size() == 1);
    map.insert(ft::make_pair(1, 5));
    assert(map.size() == 2);
    map.insert(ft::make_pair(1, 8));
    assert(map.size() == 2);

    for (size_t l = 0; l < 50; l++)
        map.insert(ft::make_pair(l, 2 * l));

    assert(map[0] == 2);
    assert(map[1] == 5);
    assert(map[2] == 4);
    assert(map[3] == 6);
    assert(map[4] == 8);
    assert(map[49] == 49 * 2);
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
    assert(map.size() == 2);

    assert(!map.empty());
}

static void test_index()
{
    ft::Map<int, int> map;

    assert(map.empty());
    assert(map.size() == 0);
    map[0] = 2;
    assert(map[0] == 2);
    assert(!map.empty());
    assert(map.size() == 1);
    map[1] = 5;
    assert(map[1] == 5);
    assert(map.size() == 2);
    map[1] = 8;
    assert(map[1] == 8);
    assert(map.size() == 2);

    for (size_t l = 0; l < 50; l++)
        map.insert(ft::make_pair(l, 2 * l));

    assert(map[0] == 2);
    assert(map[1] == 8);
    assert(map[2] == 4);
    assert(map[3] == 6);
    assert(map[4] == 8);
    assert(map[49] == 49 * 2);
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
    assert(map.size() == 2);

    assert(!map.empty());
}

static void test_constructors()
{
    ft::Map<int, int> map;
    map[0] = 50;
    map[90] = 5;
    map[2] = 80;

    assert(map.size() == 3);

    ft::Map<int, int> cpy;
    assert(cpy.size() == 0);

    cpy = map;
    assert(cpy.size() == 3);
    assert(cpy[0] == 50);
    assert(cpy[90] == 5);
    assert(cpy[2] == 80);

    cpy[5] = 8;
    map[5] = 80;
    map[9] = 80;
    assert(cpy[5] == 8);
    assert(map[5] == 80);

    ft::swap(cpy, map);
    assert(map[5] == 8);
    assert(cpy[5] == 80);

    assert(map.size() == 4);
    assert(cpy.size() == 5);

    ft::Map<int, int> cpy2(cpy);

    assert(cpy2.size() == 5);
    assert(cpy[5] == 80);
    assert(cpy2[5] == 80);
}

static void test_iterators()
{
    ft::Map<int, int> map;
    map[0] = 50;
    map[90] = 5;
    map[2] = 80;

    ft::Map<int, int>::iterator ite = map.begin();
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

    const ft::Map<int, int> &map2 = map;

    ft::Map<int, int>::const_iterator ite2 = map2.end();
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
    ft::Map<int, int> map;
    map[0] = 50;
    map[90] = 5;
    map[2] = 80;

    ft::Map<int, int>::reverse_iterator ite = map.rbegin();
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

    const ft::Map<int, int> &map2 = map;

    ft::Map<int, int>::const_reverse_iterator ite2 = map2.rend();
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
    ft::Map<int, int> map;
    map[0] = 50;
    map[90] = 5;
    map[2] = 80;

    ft::Pair<int, int> tab[6] = {
        ft::make_pair(0, 1),
        ft::make_pair(50, 2),
        ft::make_pair(6, 4),
        ft::make_pair(-45, -5),
        ft::make_pair(4, 98),
        ft::make_pair(6, 9),
    };

    map.insert(tab, tab + 6);
    assert(map.size() == 7);
    assert(map[0] == 50);
    assert(map[90] == 5);
    assert(map[6] == 4);
    assert(map[-45] == -5);
    assert(map[4] == 98);

    map.clear();
    map.insert(tab, tab + 6);
    assert(map.size() == 5);
    assert(map[0] == 1);
    assert(map[6] == 4);
    assert(map[-45] == -5);
    assert(map[4] == 98);
}

static void test_cmp()
{
    ft::Map<int, int> map;
    map[0] = 50;
    map[90] = 5;

    ft::Map<int, int> map2;
    map2[0] = 50;
    map2[90] = 5;
    map2[2] = 80;

    assert(map != map2);
    assert(map2 < map);
    assert(map2 <= map);
    assert(!(map2 > map));
    assert(!(map2 >= map));

    map[2] = 80;
    assert(map == map2);
    assert(!(map2 < map));
    assert(map2 <= map);
    assert(!(map2 > map));
    assert(map2 >= map);

    map[1] = 4;
    assert(map != map2);
    assert(map2 > map);
    assert(map2 >= map);
    assert(!(map2 < map));
    assert(!(map2 <= map));
}

static void test_swap()
{
    ft::Map<int, int> map;
    map[10] = 96;
    map[36] = 9;
    map[8] = 8;

    ft::Map<int, int> map2;
    map2[0] = 50;
    map2[90] = 5;

    assert(map.size() == 3);
    assert(map[10] == 96);
    assert(map[36] == 9);
    assert(map[8] == 8);
    assert(map2.size() == 2);
    assert(map2[0] == 50);
    assert(map2[90] == 5);

    ft::swap(map, map2);

    assert(map2.size() == 3);
    assert(map2[10] == 96);
    assert(map2[36] == 9);
    assert(map2[8] == 8);
    assert(map.size() == 2);
    assert(map[0] == 50);
    assert(map[90] == 5);

    map2.swap(map);

    assert(map.size() == 3);
    assert(map[10] == 96);
    assert(map[36] == 9);
    assert(map[8] == 8);
    assert(map2.size() == 2);
    assert(map2[0] == 50);
    assert(map2[90] == 5);
}

static void test_count_find()
{
    ft::Map<int, int> map;
    map[10] = 96;
    map[36] = 9;
    map[8] = 8;

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
    ft::Map<int, int> map;
    map[10] = 96;
    map[36] = 9;
    map[8] = 8;

    ft::Map<int, int>::iterator ite = map.begin();
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
    assert(map.upper_bound(8) == ite);
    assert(map.upper_bound(9) == ite);
    assert(map.upper_bound(10) != ite);
    ++ite;
    assert(map.upper_bound(10) == ite);
    assert(map.upper_bound(30) == ite);

    typedef typename ft::Map<int, int>::iterator iter;
    ft::Pair<iter, iter> range;

    range = map.equal_range(8);
    ite = map.begin();
    assert(range.first == map.begin() && range.second == ++ite);

    range = map.equal_range(36);
    ite = map.begin();
    ++ite;
    assert(range.first == ++ite && range.second == ++ite);

    range = map.equal_range(50);
    assert(range.first == map.end());
    assert(range.second == map.end());

    range = map.equal_range(0);
    assert(range.first == map.begin());
    assert(range.second == map.begin());
}

void test_map()
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
