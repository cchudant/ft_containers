/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_deque.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skybt <skybt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 06:28:20 by cchudant          #+#    #+#             */
/*   Updated: 2020/08/08 19:31:35 by skybt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Test.hpp"

static void test_pushback()
{
    ft::Deque<ConstrCounter> deque;
    assert(deque.size() == 0);
    assert(deque.empty());

    deque.push_back(ConstrCounter(0));
    assert(deque.size() == 1);
    assert(!deque.empty());
    assert(deque[0].val == 0);

    assert(deque.front() == 0);
    assert(deque.back() == 0);

    deque.push_back(ConstrCounter(1));
    assert(deque.size() == 2);
    assert(!deque.empty());
    assert(deque[0].val == 0);
    assert(deque[1].val == 1);

    assert(deque.front() == 0);
    assert(deque.back() == 1);

    deque.push_back(ConstrCounter(8000));
    assert(deque.size() == 3);
    assert(!deque.empty());
    assert(deque[0].val == 0);
    assert(deque[1].val == 1);
    assert(deque[2].val == 8000);

    assert(deque.front() == 0);
    assert(deque.back() == 8000);

    deque.push_back(ConstrCounter(33));
    assert(deque.size() == 4);
    assert(!deque.empty());
    assert(deque[0].val == 0);
    assert(deque[1].val == 1);
    assert(deque[2].val == 8000);
    assert(deque[3].val == 33);

    assert(deque.front() == 0);
    assert(deque.back() == 33);
}

static void test_pushfront()
{
    ft::Deque<ConstrCounter> deque;
    assert(deque.size() == 0);
    assert(deque.empty());

    deque.push_front(ConstrCounter(0));
    assert(deque.size() == 1);
    assert(!deque.empty());
    assert(deque[0].val == 0);

    assert(deque.front() == 0);
    assert(deque.back() == 0);

    deque.push_front(ConstrCounter(1));
    assert(deque.size() == 2);
    assert(!deque.empty());
    assert(deque[0].val == 1);
    assert(deque[1].val == 0);

    assert(deque.front() == 1);
    assert(deque.back() == 0);

    deque.push_front(ConstrCounter(8000));
    assert(deque.size() == 3);
    assert(!deque.empty());
    assert(deque[0].val == 8000);
    assert(deque[1].val == 1);
    assert(deque[2].val == 0);

    assert(deque.front() == 8000);
    assert(deque.back() == 0);

    deque.push_front(ConstrCounter(33));
    assert(deque.size() == 4);
    assert(!deque.empty());
    assert(deque[0].val == 33);
    assert(deque[1].val == 8000);
    assert(deque[2].val == 1);
    assert(deque[3].val == 0);

    assert(deque.front() == 33);
    assert(deque.back() == 0);
}

static void test_assign()
{
    ft::Deque<ConstrCounter> deque;
    assert(deque.size() == 0);

    deque.assign(0, ConstrCounter(66));
    assert(deque.size() == 0);

    deque.assign(10, ConstrCounter(5));
    assert(deque.size() == 10);
    assert(deque[2].val == 5);
    assert(deque[9].val == 5);

    deque.assign(15, ConstrCounter(120));
    assert(deque.size() == 15);
    assert(deque[0].val == 120);
    assert(deque[6].val == 120);

    deque.assign(5, ConstrCounter(6));
    assert(deque.size() == 5);
    assert(deque[2].val == 6);
    assert(deque[3].val == 6);

    deque.assign(50, ConstrCounter(9000));
    assert(deque.size() == 50);
    assert(deque[26].val == 9000);
    assert(deque[49].val == 9000);
}

static void test_assign_iter()
{
    ft::Deque<ConstrCounter> deque;
    assert(deque.size() == 0);

    {
        ConstrCounter array[0] = {};

        deque.assign(array, array);
        assert(deque.size() == 0);
    }
    {
        ConstrCounter array[5] = {0, 1, 2, 3, 4};

        deque.assign(array, array + 5);
        assert(deque.size() == 5);
        assert(deque[0].val == 0);
        assert(deque[1].val == 1);
        assert(deque[2].val == 2);
        assert(deque[3].val == 3);
        assert(deque[4].val == 4);
    }
    {
        ConstrCounter array[2] = {42, 43};

        deque.assign(array, array + 2);
        assert(deque.size() == 2);
        assert(deque[0].val == 42);
        assert(deque[1].val == 43);
    }
}

static void test_constr()
{
    {
        ft::Deque<ConstrCounter> deque(0, ConstrCounter(5));
        assert(deque.size() == 0);
    }
    {
        ft::Deque<ConstrCounter> deque(10, ConstrCounter(5));
        assert(deque.size() == 10);
        assert(deque[2].val == 5);
        assert(deque[9].val == 5);
    }
    {
        ft::Deque<ConstrCounter> deque(15, ConstrCounter(120));
        assert(deque.size() == 15);
        assert(deque[0].val == 120);
        assert(deque[6].val == 120);
    }
    {
        ft::Deque<ConstrCounter> deque(5, ConstrCounter(6));
        assert(deque.size() == 5);
        assert(deque[2].val == 6);
        assert(deque[3].val == 6);
    }
    {
        ft::Deque<ConstrCounter> deque(50, ConstrCounter(9000));
        assert(deque.size() == 50);
        assert(deque[26].val == 9000);
        assert(deque[49].val == 9000);
    }
}

static void test_constr_iter()
{
    {
        ConstrCounter array[0] = {};

        ft::Deque<ConstrCounter> deque(array, array);
        assert(deque.size() == 0);
    }
    {
        ConstrCounter array[5] = {0, 1, 2, 3, 4};

        ft::Deque<ConstrCounter> deque(array, array + 5);
        assert(deque.size() == 5);
        assert(deque[0].val == 0);
        assert(deque[1].val == 1);
        assert(deque[2].val == 2);
        assert(deque[3].val == 3);
        assert(deque[4].val == 4);
    }
    {
        ConstrCounter array[2] = {42, 43};

        ft::Deque<ConstrCounter> deque(array, array + 2);
        assert(deque.size() == 2);
        assert(deque[0].val == 42);
        assert(deque[1].val == 43);
    }
}

static void test_assign_copy()
{
    ft::Deque<ConstrCounter> deque;
    deque.push_back(ConstrCounter(0));
    deque.push_back(ConstrCounter(1));
    deque.push_back(ConstrCounter(2));

    ft::Deque<ConstrCounter> deque2(deque);
    assert(deque2.size() == 3);
    assert(deque2[0].val == 0);
    assert(deque2[1].val == 1);
    assert(deque2[2].val == 2);

    deque2.push_back(ConstrCounter(3));
    assert(deque.size() == 3);
    assert(deque2.size() == 4);

    ft::Deque<ConstrCounter> deque3;
    assert(deque3.size() == 0);

    deque3 = deque2;
    assert(deque.size() == 3);
    assert(deque2.size() == 4);
    assert(deque3.size() == 4);

    deque = deque3;
    assert(deque.size() == 4);
    assert(deque2.size() == 4);
    assert(deque3.size() == 4);

    assert(deque[0].val == 0);
    assert(deque[1].val == 1);
    assert(deque[2].val == 2);
    assert(deque[3].val == 3);
    assert(deque2[0].val == 0);
    assert(deque2[1].val == 1);
    assert(deque2[2].val == 2);
    assert(deque2[3].val == 3);
    assert(deque3[0].val == 0);
    assert(deque3[1].val == 1);
    assert(deque3[2].val == 2);
    assert(deque3[3].val == 3);
}

static void test_accessors()
{
    ft::Deque<ConstrCounter> deque;
    deque.push_back(ConstrCounter(0));
    deque.push_back(ConstrCounter(1));
    deque.push_back(ConstrCounter(2));

    assert(deque[0].val == 0);
    assert(deque[1].val == 1);
    assert(deque[2].val == 2);

    assert(deque.at(0).val == 0);
    assert(deque.at(1).val == 1);
    assert(deque.at(2).val == 2);

    bool exception = false;
    try
    {
        deque.at(3);
    }
    catch (const std::out_of_range &e)
    {
        exception = true;
    }
    assert(exception);

    assert(deque.front().val == 0);
    assert(deque.back().val == 2);
}

static void test_iterator()
{
    ft::Deque<ConstrCounter> deque;
    assert(deque.size() == 0);
    assert(deque.begin() == deque.end());

    deque.push_back(ConstrCounter(0));
    assert(deque.size() == 1);
    assert(deque.begin() + 1 == deque.end());

    deque.push_back(ConstrCounter(1));
    assert(deque.size() == 2);
    assert(deque.begin() + 2 == deque.end());

    deque.push_back(ConstrCounter(2));
    assert(deque.size() == 3);
    assert(deque.begin() + 3 == deque.end());
    assert(deque.begin() == deque.end() - 3);

    const ft::Deque<ConstrCounter> &deque2 = deque;

    ft::Deque<ConstrCounter>::const_iterator ite = deque2.begin();
    assert((*ite).val == 0);
    assert(ite->val == 0);
    assert(++ite == deque2.begin() + 1);
    assert((*ite).val == 1);
    assert(ite->val == 1);
    assert(ite++ == deque2.begin() + 1);
    assert(ite == deque2.begin() + 2);
    assert((*ite).val == 2);
    assert(ite->val == 2);
    assert(++ite == deque2.end());
    assert(--ite == deque2.end() - 1);
    assert(ite->val == 2);
    assert(ite-- == deque2.end() - 1);
    assert(ite == deque2.end() - 2);
    assert(ite->val == 1);
    assert(--ite == deque2.begin());
    assert(ite->val == 0);
}

static void test_reverse_iterator()
{
    ft::Deque<ConstrCounter> deque;
    deque.push_back(ConstrCounter(0));
    deque.push_back(ConstrCounter(1));
    deque.push_back(ConstrCounter(2));

    ft::Deque<ConstrCounter>::reverse_iterator ite =
        deque.rbegin();
    assert(ite->val == 2);
    ++ite;
    assert(ite->val == 1);
    ++ite;
    assert(ite->val == 0);
    ++ite;
    assert(ite == deque.rend());
}

static void test_insert_one()
{
    ft::Deque<ConstrCounter> deque;

    assert(deque.insert(deque.begin(), ConstrCounter(5)) == deque.begin());
    assert(deque.size() == 1);
    assert(deque[0].val == 5);

    assert(deque.insert(deque.begin() + 1, ConstrCounter(5)) == deque.begin() + 1);
    assert(deque.size() == 2);
    assert(deque[1].val == 5);
}

static void test_insert()
{
    ft::Deque<ConstrCounter> deque;
    assert(deque.size() == 0);

    deque.insert(deque.begin(), 0, ConstrCounter(66));
    assert(deque.size() == 0);

    deque.insert(deque.begin(), 10, ConstrCounter(120));
    assert(deque.size() == 10);
    assert(deque[2].val == 120);
    assert(deque[9].val == 120);

    deque.insert(deque.begin() + 3, 2, ConstrCounter(33));
    assert(deque.size() == 12);
    assert(deque[3].val == 33);
    assert(deque[6].val == 120);
}

static void test_insert_iter()
{
    ft::Deque<ConstrCounter> deque;
    assert(deque.size() == 0);

    {
        ConstrCounter array[5] = {0, 1, 2, 3, 4};

        deque.insert(deque.begin(), array, array + 5);
        assert(deque.size() == 5);
        assert(deque[0].val == 0);
        assert(deque[1].val == 1);
        assert(deque[2].val == 2);
        assert(deque[3].val == 3);
        assert(deque[4].val == 4);
    }
    {
        ConstrCounter array[0] = {};

        deque.insert(deque.begin() + 2, array, array);
        assert(deque.size() == 5);
    }
    {
        ConstrCounter array[2] = {42, 43};

        deque.insert(deque.begin() + 2, array, array + 2);
        assert(deque.size() == 7);
        assert(deque[0].val == 0);
        assert(deque[1].val == 1);
        assert(deque[2].val == 42);
        assert(deque[3].val == 43);
        assert(deque[4].val == 2);
        assert(deque[5].val == 3);
        assert(deque[6].val == 4);
    }
    {
        ConstrCounter array[2] = {52, 42};

        deque.insert(deque.begin() + 1, array, array + 2);
        assert(deque.size() == 9);
        assert(deque[0].val == 0);
        assert(deque[1].val == 52);
        assert(deque[2].val == 42);
        assert(deque[3].val == 1);
        assert(deque[4].val == 42);
        assert(deque[5].val == 43);
        assert(deque[6].val == 2);
        assert(deque[7].val == 3);
        assert(deque[8].val == 4);
    }
    {
        ConstrCounter array[6] = {99, 98};

        deque.insert(deque.begin() + 3, array, array + 2);
        assert(deque.size() == 11);
        assert(deque[0].val == 0);
        assert(deque[1].val == 52);
        assert(deque[2].val == 42);
        assert(deque[3].val == 99);
        assert(deque[4].val == 98);
        assert(deque[5].val == 1);
        assert(deque[6].val == 42);
        assert(deque[7].val == 43);
        assert(deque[8].val == 2);
        assert(deque[9].val == 3);
        assert(deque[10].val == 4);
    }

    {
        ConstrCounter array[5] = {0, 1, 2, 3, 4};

        deque.clear();
        deque.insert(deque.begin(), array, array + 5);
        assert(deque.size() == 5);
        assert(deque[0].val == 0);
        assert(deque[1].val == 1);
        assert(deque[2].val == 2);
        assert(deque[3].val == 3);
        assert(deque[4].val == 4);
    }
}

static void test_erase()
{
    ft::Deque<ConstrCounter> deque;
    ConstrCounter array[5] = {0, 1, 2, 3, 4};
    assert(deque.empty());
    deque.insert(deque.begin(), array, array + 5);
    assert(!deque.empty());

    assert(deque.erase(deque.begin()) == deque.begin());
    assert(deque.size() == 4);
    assert(deque[0].val == 1);

    assert(deque.erase(deque.begin() + 2) == deque.begin() + 2);
    assert(deque.size() == 3);
    assert(deque[2].val == 4);
}

static void test_erase_range()
{
    ft::Deque<ConstrCounter> deque;
    ConstrCounter array[5] = {0, 1, 2, 3, 4};
    assert(deque.empty());
    deque.insert(deque.begin(), array, array + 5);
    assert(!deque.empty());

    deque.erase(deque.begin() + 1, deque.end() - 1);
    assert(deque.size() == 2);
    assert(deque[0].val == 0);
    assert(deque[1].val == 4);

    deque.erase(deque.begin(), deque.begin());
    assert(deque.size() == 2);
    assert(deque[0].val == 0);
    assert(deque[1].val == 4);

    deque.clear();
    assert(deque.empty());

    deque.insert(deque.begin(), array, array + 5);
    assert(!deque.empty());

    deque.erase(deque.begin(), deque.begin() + 2);
    deque.erase(deque.begin(), deque.begin() + 3);
    assert(deque.empty());
}

static void test_pop_back()
{
    ft::Deque<ConstrCounter> deque;
    ConstrCounter array[5] = {0, 1, 2, 3, 4};
    deque.insert(deque.begin(), array, array + 5);

    assert(deque.size() == 5);
    assert(deque.back() == 4);
    deque.pop_back();
    assert(deque.size() == 4);
    assert(deque.back() == 3);
    deque.pop_back();
    assert(deque.size() == 3);
    assert(deque.back() == 2);
    deque.pop_back();
    assert(deque.size() == 2);
    assert(deque.back() == 1);
    deque.pop_back();
    assert(deque.size() == 1);
    assert(deque.back() == 0);
    deque.pop_back();
    assert(deque.size() == 0);
    assert(deque.empty());
}

static void test_pop_front()
{
    ft::Deque<ConstrCounter> deque;
    ConstrCounter array[5] = {0, 1, 2, 3, 4};
    deque.insert(deque.begin(), array, array + 5);

    assert(deque.size() == 5);
    assert(deque.front() == 0);
    deque.pop_front();
    assert(deque.size() == 4);
    assert(deque.front() == 1);
    deque.pop_front();
    assert(deque.size() == 3);
    assert(deque.front() == 2);
    deque.pop_front();
    assert(deque.size() == 2);
    assert(deque.front() == 3);
    deque.pop_front();
    assert(deque.size() == 1);
    assert(deque.front() == 4);
    deque.pop_front();
    assert(deque.size() == 0);
    assert(deque.empty());
}

static void test_resize()
{
    ft::Deque<ConstrCounter> deque;

    deque.resize(3, ConstrCounter(0));
    assert(deque.size() == 3);
    assert(deque[0].val == 0);
    assert(deque[1].val == 0);
    assert(deque[2].val == 0);

    deque.resize(2, ConstrCounter(5));
    assert(deque.size() == 2);
    assert(deque[0].val == 0);
    assert(deque[1].val == 0);

    deque.resize(5, ConstrCounter(99));
    assert(deque.size() == 5);
    assert(deque[0].val == 0);
    assert(deque[1].val == 0);
    assert(deque[2].val == 99);
    assert(deque[3].val == 99);
    assert(deque[4].val == 99);
}

static void test_swap()
{
    ConstrCounter array[5] = {0, 1, 2, 3, 4};
    ft::Deque<ConstrCounter> deque(array, array + 5);

    ConstrCounter array2[3] = {2, 3, 1};
    ft::Deque<ConstrCounter> deque2(array2, array2 + 3);

    deque.swap(deque2);
    assert(deque.size() == 3);
    assert(deque2.size() == 5);
    assert(deque[0].val == 2);
    assert(deque2[0].val == 0);

    ft::swap(deque2, deque);
    assert(deque.size() == 5);
    assert(deque2.size() == 3);
    assert(deque[0].val == 0);
    assert(deque2[0].val == 2);
}

static void test_cmp_eq()
{
    ConstrCounter array[5] = {0, 1, 2, 3, 4};
    ft::Deque<ConstrCounter> deque(array, array + 5);
    ft::Deque<ConstrCounter> deque2(deque);

    assert(deque == deque2);
    assert(deque >= deque2);
    assert(deque <= deque2);

    deque2.push_back(50);
    assert(deque != deque2);
    assert(deque < deque2);
    assert(deque <= deque2);
    assert(deque2 > deque);
    assert(deque2 >= deque);

    deque.push_back(200);
    assert(deque != deque2);
    assert(deque > deque2);
    assert(deque >= deque2);
    assert(deque2 < deque);
    assert(deque2 <= deque);
}

void test_deque()
{
    test_one("push_back", test_pushback);
    test_one("push_front", test_pushfront);
    test_one("assign", test_assign);
    test_one("assign_iter", test_assign_iter);
    test_one("constr", test_constr);
    test_one("constr_iter", test_constr_iter);
    test_one("assign_copy", test_assign_copy);
    test_one("accessors", test_accessors);
    test_one("iterator", test_iterator);
    test_one("reverse_iterator", test_reverse_iterator);
    test_one("insert_one", test_insert_one);
    test_one("insert", test_insert);
    test_one("insert_iter", test_insert_iter);
    test_one("erase", test_erase);
    test_one("erase_range", test_erase_range);
    test_one("pop_back", test_pop_back);
    test_one("pop_front", test_pop_front);
    test_one("resize", test_resize);
    test_one("swap", test_swap);
    test_one("cmp_eq", test_cmp_eq);
}
