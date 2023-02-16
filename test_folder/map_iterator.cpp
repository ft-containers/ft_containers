#include <map>
#include <iostream>
#include "../map.hpp"
#include "../map_iterator.hpp"


using namespace std;

int main()
{
	std::map<char, int> test;
	std::map<char, int>::iterator it;
	std::map<char, int>::reverse_iterator re_it;

	test.insert(std::make_pair('a', 1));
	test.insert(std::make_pair('b', 2));
	test.insert(std::make_pair('c', 3));
	test.insert(std::make_pair('d', 4));

	it = test.begin();
	re_it = test.rbegin();
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
	std::cout << "re_it : " << re_it->second << std::endl;

	// while (re_it != test.rend())
	// {
	// 	std::cout << "re_it : " << re_it->second << std::endl;
	// 	--re_it;
	// }

	// std::cout << "========================" << std::endl;
	// 	std::cout << "re_it[] : " << re_it['b'].second << std::endl;
	// 	std::cout << "re_it[] : " << re_it['e'].second << std::endl;

}
