#include <map>
#include <vector>
#include "containers/map/map.hpp"
#include "containers/vector/vector.hpp"
#include <iostream>

using namespace ft;

int main()
{
	ft::map<char, int> test;
	ft::map<char, int>::iterator it;
	ft::map<char, int>::reverse_iterator re_it;

	test.insert(ft::make_pair('a', 1));
	test.insert(ft::make_pair('b', 2));
	test.insert(ft::make_pair('c', 3));
	test.insert(ft::make_pair('d', 4));

	it = test.begin();
	re_it = test.rbegin();

	while (it != test.end())
	{
		std::cout << "it : " << it->second << std::endl;
		++it;
	}
	std::cout << "========================" << std::endl;
	while (re_it != test.rend())
	{
		std::cout << "re_it : " << re_it->second << std::endl;
		++re_it;
	}
	std::cout << "========================" << std::endl;
	// std::cout << "re_it[] : " << re_it[1].second << std::endl;

	ft::vector<int> v;
	ft::vector<int>::reverse_iterator re_it2;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);

	re_it2 = v.rbegin();
	std::cout << "re_it2[] : " << re_it2[1] << std::endl;

}
