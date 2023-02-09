#include "../stack.hpp"
#include <deque>
#include <stack>
#include <vector>
#include <iostream>

int	main()
{
	ft::stack<int>						s1;
	ft::stack<int, std::deque<int> >	s2;

	ft::stack<int>	v1;
	std::stack<int> v2;

	v1.top();
	v2.top();

	std::cout << v1.back() << std::endl;
	std::cout << v2.back() << std::endl;
 	s1.top();
	std::cout << "size : " << s1.size() << std::endl;
	std::cout << "size : " << s2.size() << std::endl;
	std::cout << "empty : " << s1.empty() << std::endl;
	std::cout << "empty : " << s2.empty() << std::endl;
	std::cout << "top : s1" << '"' << s1.top()  << '"' << std::endl;
	// std::cout << "top : s2" << '"' << s2.top()  << '"' << std::endl;

	s1.push(4);
	s1.push(44);
	s2.push(4);
	s2.push(44);
	
	std::cout << "size : " << s1.size() << std::endl;
	std::cout << "size : " << s2.size() << std::endl;
	std::cout << "empty : " << s1.empty() << std::endl;
	std::cout << "empty : " << s2.empty() << std::endl;
	std::cout << "top : " << '"' << s1.top()  << '"' << std::endl;
	std::cout << "top : " << '"' << s2.top()  << '"' << std::endl;
	
	
	return (0);
}