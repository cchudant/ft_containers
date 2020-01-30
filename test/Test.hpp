/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Test.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchudant <cchudant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 06:27:31 by cchudant          #+#    #+#             */
/*   Updated: 2020/01/30 23:15:43 by cchudant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_HPP
# define TEST_HPP

# include "../Vector.hpp"
# include "../List.hpp"
# include "../Stack.hpp"
# include "../Queue.hpp"
# include <iostream>
# include <assert.h>

class ConstrCounter
{
    public:
        static int g_constr;
        static int g_destr;

        int val;

        ConstrCounter(int val);
        ConstrCounter(const ConstrCounter &o);
        ~ConstrCounter();

        static void reset_counters();
};

bool operator==(const ConstrCounter& lhs, const ConstrCounter& rhs);
bool operator!=(const ConstrCounter& lhs, const ConstrCounter& rhs);
bool operator<(const ConstrCounter& lhs, const ConstrCounter& rhs);
bool operator<=(const ConstrCounter& lhs, const ConstrCounter& rhs);
bool operator>(const ConstrCounter& lhs, const ConstrCounter& rhs);
bool operator>=(const ConstrCounter& lhs, const ConstrCounter& rhs);

void test_one(std::string name, void (&fn)());

void test_vector();
void test_list();
void test_stack();
void test_queue();

#endif
