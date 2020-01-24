/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Test.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchudant <cchudant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 06:27:31 by cchudant          #+#    #+#             */
/*   Updated: 2020/01/24 10:44:36 by cchudant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_HPP
# define TEST_HPP

# include "Vector.hpp"
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

        static void resetCounters();
};

bool operator==(const ConstrCounter& lhs, const ConstrCounter& rhs);
bool operator!=(const ConstrCounter& lhs, const ConstrCounter& rhs);
bool operator<(const ConstrCounter& lhs, const ConstrCounter& rhs);
bool operator<=(const ConstrCounter& lhs, const ConstrCounter& rhs);
bool operator>(const ConstrCounter& lhs, const ConstrCounter& rhs);
bool operator>=(const ConstrCounter& lhs, const ConstrCounter& rhs);

void testOne(std::string name, void (&fn)());

void test_vector();

#endif
