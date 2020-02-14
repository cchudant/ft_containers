#include "Map.hpp"
#include <iostream>

struct Test
{
	bool operator()(int a, int b) const
	{
		return a < b;
	}
};

void add(ft::Map<int, int, Test> &map, int k)
{
	for (ft::Map<int, int, Test>::iterator ite = map.begin(); ite != map.end(); ++ite)
		std::cout << ite->first << std::endl;

	std::cout << "--" << std::endl;

	map.insert(ft::make_pair(k, 0));
}

int main()
{
	ft::Map<int, int, Test> map;
	int array[] = { 8, 12, 22, 19, 11, 14, 23, 10, 16, 3, 4, 7, 15, 17, 0, 24, 20, 2, 21, 6, 9, 13, 1, 18, 5 };
	for (int i = 0; i < 25; i++)
		add(map, array[i]);
}
