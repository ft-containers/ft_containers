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

	// capacity
	{
		ft::vector<int> vec_test;
		vec_test.push_back(4);
		vec_test.push_back(44);
		std::cout << "size : " << vec_test.size() << std::endl;
		std::cout << "max_size : " << vec_test.max_size() << std::endl;
		vec_test.resize(1);
		std::cout << "capacity : " << vec_test.capacity() << std::endl;
		std::cout << "empty : " << vec_test.empty() << std::endl;
		vec_test.reserve(10);
		std::cout << "after 10 reserve : " << vec_test.capacity() << std::endl;
		vec_test.reserve(8);
		std::cout << "after 8 reserve : " << vec_test.capacity() << std::endl;
	}
	
	return 0;
}
