#include <map>
#include <iostream>

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
		std::cout << "re_it[] : " << re_it[1].second << std::endl;

}
