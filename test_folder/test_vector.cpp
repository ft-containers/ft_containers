#include "../vector.hpp"
#include <iostream>
#include <vector>


int	main() {
	// default constructor
	{
		ft::vector<int> vec_test;
		std::vector<int> vec_test2;\
	}

	// size_type constructor
	{
		ft::vector<int> vec_test(1);
		std::vector<int> vec_test2(2);

	}

	{
		ft::vector<int> vec_test(0);
		std::vector<int> vec_test2(0);
	}

	// constructor (input forward)
	{
		ft::vector<int> vec_test1;
		vec_test1.push_back(5);
		std::cout << vec_test1.front() << std::endl;
		std::cout << vec_test1.back() << std::endl;
		
		ft::vector<int>::iterator begin = vec_test1.begin();
		ft::vector<int>::iterator end = vec_test1.end();

		ft::vector<int> vec_test2(begin, end);
		std::cout << vec_test2.front() << std::endl;
		std::cout << vec_test2.back() << std::endl;

	}
	return 0;
}
