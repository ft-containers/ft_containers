#include <map>
#include <iostream>
#include "Map.hpp"
#include "AVLTree.hpp"
#include "Utility.hpp"

using namespace std;

int main()
{
	ft::map<char, int> test;
	ft::map<char, int>::iterator it;
	// ft::map<char, int>::reverse_iterator re_it;

	test.insert(ft::make_pair('a', 1));
	test.insert(ft::make_pair('b', 2));
	test.insert(ft::make_pair('c', 3));
	test.insert(ft::make_pair('d', 4));

	it = test.begin();
	// re_it = test.rbegin();
	// 터져야하는데 안터짐
	// re_it = test.rend();
	// std::cout << "re_it : " << re_it->second << std::endl;

	while (it != test.end())
	{
		std::cout << "it : " << it->second << std::endl;
		++it;
	}
	--it;
	std::cout << "it : " << it->second << std::endl;
	--it;
	std::cout << "it : " << it->second << std::endl;


	std::cout << "========================" << std::endl;
	// re_it = test.rend();
	// re_it++;
	// std::cout << "re_it : " << re_it->second << std::endl;

	// while (re_it != test.rend())
	// {
	// 	std::cout << "re_it : " << re_it->second << std::endl;
	// 	--re_it;
	// }

	// std::cout << "========================" << std::endl;
	// 	std::cout << "re_it[] : " << re_it['b'].second << std::endl;
	// 	std::cout << "re_it[] : " << re_it['e'].second << std::endl;

}
