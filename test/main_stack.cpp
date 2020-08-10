/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_stack.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skybt <skybt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 21:47:45 by cchudant          #+#    #+#             */
/*   Updated: 2020/08/08 12:39:29 by skybt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Test.hpp"

static void test_push_pop()
{
	ft::Stack<ConstrCounter> stack;
	assert(stack.size() == 0);
	assert(stack.empty());

	stack.push(ConstrCounter(0));
	assert(stack.size() == 1);
	assert(!stack.empty());
	assert(stack.top() == 0);

	stack.push(ConstrCounter(1));
	assert(stack.size() == 2);
	assert(!stack.empty());
	assert(stack.top() == 1);

	stack.push(ConstrCounter(2));
	assert(stack.size() == 3);
	assert(!stack.empty());
	assert(stack.top() == 2);

	stack.push(ConstrCounter(3));
	assert(stack.size() == 4);
	assert(!stack.empty());
	assert(stack.top() == 3);

	stack.push(ConstrCounter(4));
	assert(stack.size() == 5);
	assert(!stack.empty());
	assert(stack.top() == 4);

	stack.pop();
	assert(stack.size() == 4);
	assert(!stack.empty());
	assert(stack.top() == 3);

	stack.pop();
	assert(stack.size() == 3);
	assert(!stack.empty());
	assert(stack.top() == 2);

	stack.pop();
	assert(stack.size() == 2);
	assert(!stack.empty());
	assert(stack.top() == 1);

	stack.pop();
	assert(stack.size() == 1);
	assert(!stack.empty());
	assert(stack.top() == 0);

	stack.pop();
	assert(stack.size() == 0);
	assert(stack.empty());
}

static void test_assign_copy()
{
	ft::Stack<ConstrCounter> stack;
	stack.push(ConstrCounter(0));
	stack.push(ConstrCounter(1));
	stack.push(ConstrCounter(2));

	ft::Stack<ConstrCounter> stack2(stack);
	assert(stack2.size() == 3);
	assert(stack2.top() == 2);
	stack2.pop();
	assert(stack2.size() == 2);
	assert(stack2.top() == 1);
	stack2.pop();
	assert(stack2.size() == 1);
	assert(stack2.top() == 0);
	stack2.pop();
	assert(stack2.size() == 0);

	stack2.push(ConstrCounter(0));
	assert(stack2.size() == 1);
	stack2.push(ConstrCounter(1));
	assert(stack2.size() == 2);
	stack2.push(ConstrCounter(2));
	assert(stack2.size() == 3);

	stack2.push(ConstrCounter(3));
	assert(stack.size() == 3);
	assert(stack2.size() == 4);

	ft::Stack<ConstrCounter> stack3;
	assert(stack3.size() == 0);

	stack3 = stack2;
	assert(stack.size() == 3);
	assert(stack2.size() == 4);
	assert(stack3.size() == 4);

	stack = stack3;
	assert(stack.size() == 4);
	assert(stack2.size() == 4);
	assert(stack3.size() == 4);

	assert(stack.size() == 4);
	assert(stack.top() == 3);
	stack.pop();
	assert(stack.size() == 3);
	assert(stack.top() == 2);
	stack.pop();
	assert(stack.size() == 2);
	assert(stack.top() == 1);
	stack.pop();
	assert(stack.size() == 1);
	assert(stack.top() == 0);
	stack.pop();
	assert(stack.size() == 0);

	assert(stack2.size() == 4);
	assert(stack2.top() == 3);
	stack2.pop();
	assert(stack2.size() == 3);
	assert(stack2.top() == 2);
	stack2.pop();
	assert(stack2.size() == 2);
	assert(stack2.top() == 1);
	stack2.pop();
	assert(stack2.size() == 1);
	assert(stack2.top() == 0);
	stack2.pop();
	assert(stack2.size() == 0);

	assert(stack3.size() == 4);
	assert(stack3.top() == 3);
	stack3.pop();
	assert(stack3.size() == 3);
	assert(stack3.top() == 2);
	stack3.pop();
	assert(stack3.size() == 2);
	assert(stack3.top() == 1);
	stack3.pop();
	assert(stack3.size() == 1);
	assert(stack3.top() == 0);
	stack3.pop();
	assert(stack3.size() == 0);
}

static void test_swap()
{
	ConstrCounter array[5] = {0, 1, 2, 3, 4};
	ft::Stack<ConstrCounter> stack(ft::Vector<ConstrCounter>(array, array + 5));

	ConstrCounter array2[3] = {2, 3, 1};
	ft::Stack<ConstrCounter> stack2(ft::Vector<ConstrCounter>(array2, array2 + 3));

	ft::swap(stack, stack2);
	assert(stack.size() == 3);
	assert(stack2.size() == 5);
	assert(stack.top() == 1);
	assert(stack2.top() == 4);

	ft::swap(stack2, stack);
	assert(stack.size() == 5);
	assert(stack2.size() == 3);
	assert(stack.top() == 4);
	assert(stack2.top() == 1);
}

static void test_cmp_eq()
{
	ConstrCounter array[5] = {0, 1, 2, 3, 4};
	ft::Stack<ConstrCounter> stack(ft::Vector<ConstrCounter>(array, array + 5));
	ft::Stack<ConstrCounter> stack2(stack);

	assert(stack == stack2);
	assert(stack >= stack2);
	assert(stack <= stack2);

	stack2.push(50);
	assert(stack != stack2);
	assert(stack < stack2);
	assert(stack <= stack2);
	assert(stack2 > stack);
	assert(stack2 >= stack);

	stack.push(200);
	assert(stack != stack2);
	assert(stack > stack2);
	assert(stack >= stack2);
	assert(stack2 < stack);
	assert(stack2 <= stack);
}

void test_stack()
{
	test_one("push_pop", test_push_pop);
	test_one("assign_copy", test_assign_copy);
	test_one("swap", test_swap);
	test_one("cmp_eq", test_cmp_eq);
}
