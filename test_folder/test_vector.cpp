#include "../vector.hpp"
#include <iostream>
#include <vector>

template <typename Tp>
void	print_vector(ft::vector<Tp> myvector)
{
	std::cout << "--print_vector--" << '\n';
	typename ft::vector<Tp>::reverse_iterator it;
	for (it = myvector.rbegin(); it < myvector.rend(); it++)
		std::cout << ' ' << *it;
	std::cout << '\n';
    std::cout << "size : " << myvector.size() << '\n';
	std::cout << "capa : " << myvector.capacity() << '\n';
	std::cout << "----------------" << '\n'; 
}

int	main() {
	// // default constructor
	// {
	// 	ft::vector<int> vec_test;
	// 	std::vector<int> vec_test2;
	// }
	// // size_type constructor
	// {
	// 	ft::vector<int> vec_test(1);
	// 	std::vector<int> vec_test2(2);
	// }
	// {
	// 	ft::vector<int> vec_test(0);
	// 	std::vector<int> vec_test2(0);
	// }
	// // constructor (input forward)
	// {
	// 	ft::vector<int> vec_test1;
	// 	vec_test1.push_back(5);
	// 	std::cout << vec_test1.front() << std::endl;
	// 	std::cout << vec_test1.back() << std::endl;
		
	// 	ft::vector<int>::iterator begin = vec_test1.begin();
	// 	ft::vector<int>::iterator end = vec_test1.end();

	// 	ft::vector<int> vec_test2(begin, end);
	// 	std::cout << vec_test2.front() << std::endl;
	// 	std::cout << vec_test2.back() << std::endl;
	// }
	// // capacity
	// {
	// 	ft::vector<int> vec_test;
	// 	vec_test.push_back(4);
	// 	vec_test.push_back(44);
	// 	std::cout << "size : " << vec_test.size() << std::endl;
	// 	std::cout << "max_size : " << vec_test.max_size() << std::endl;
	// 	vec_test.resize(1);
	// 	std::cout << "capacity : " << vec_test.capacity() << std::endl;
	// 	std::cout << "empty : " << vec_test.empty() << std::endl;
	// 	vec_test.reserve(10);
	// 	std::cout << "after 10 reserve : " << vec_test.capacity() << std::endl;
	// 	vec_test.reserve(8);
	// 	std::cout << "after 8 reserve : " << vec_test.capacity() << std::endl;
	// }
	//reverse_iterator
	{
		ft::vector<int>						v1;

		v1.push_back(5);
		v1.push_back(51);
		v1.push_back(58);
		v1.push_back(35);
		v1.push_back(26);

		print_vector(v1);
	}
	return 0;
}
