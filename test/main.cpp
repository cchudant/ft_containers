/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skybt <skybt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 15:31:12 by skybt             #+#    #+#             */
/*   Updated: 2020/08/08 12:37:33 by skybt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Test.hpp"

int main()
{
	std::cout << ":: Vector ::" << std::endl;
	test_vector();
	std::cout << ":: List ::" << std::endl;
	test_list();
	std::cout << ":: Stack ::" << std::endl;
	test_stack();
	std::cout << ":: Queue ::" << std::endl;
	test_queue();
	std::cout << ":: Map ::" << std::endl;
	test_map();
	std::cout << ":: Set ::" << std::endl;
	test_set();
	std::cout << ":: MultiMap ::" << std::endl;
	test_multimap();
	std::cout << ":: MultiSet ::" << std::endl;
	test_multiset();
	std::cout << ":: Deque ::" << std::endl;
	test_deque();
	std::cout << ":: Everything is ok! ::" << std::endl;
	return 0;
}