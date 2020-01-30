/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchudant <cchudant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 15:31:12 by skybt             #+#    #+#             */
/*   Updated: 2020/01/30 18:13:09 by cchudant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Test.hpp"

int main()
{
	std::cout << ":: Vector ::" << std::endl;
	test_vector();
	std::cout << ":: List ::" << std::endl;
	test_list();
	std::cout << ":: Everything is ok! ::" << std::endl;
	return 0;
}