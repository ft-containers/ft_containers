#include <vector>
#include <iostream>
#include "../vector.hpp"

template <typename Tp>
void	print_vector(std::vector<Tp>& myvector)
{
	std::cout << "--print_vector--" << '\n';
	typename std::vector<Tp>::iterator it;
	for (it = myvector.begin(); it < myvector.end(); it++)
		std::cout << ' ' << *it;
	std::cout << '\n';
    std::cout << "size : " << myvector.size() << '\n';
	std::cout << "capa : " << myvector.capacity() << '\n';
	std::cout << "----------------" << '\n'; 
}

template <typename Tp>
void	ft_print_vector(ft::vector<Tp>& myvector)
{
	std::cout << "--print_vector--" << '\n';
	typename ft::vector<Tp>::iterator it;
	for (it = myvector.begin(); it < myvector.end(); it++)
		std::cout << ' ' << *it;
	std::cout << '\n';
    std::cout << "size : " << myvector.size() << '\n';
	std::cout << "capa : " << myvector.capacity() << '\n';
	std::cout << "----------------" << '\n'; 
}

int main(void) {

{
    std::cout << "------------std--------------" << std::endl;
	std::vector<int> test1(10, 42);
	std::vector<int> test2(5, 11);

	test2.reserve(15);
	test2.resize(3);
	
	test2.push_back(1);

	print_vector(test1);
	print_vector(test2);
	test2 = test1;
    test1.clear();
    std::cout << "----after clear-----" << std::endl;

	print_vector(test1);
	print_vector(test2);
}


{
    std::cout << "------------ft--------------" << std::endl;
	ft::vector<int> test1(10, 42);
    ft::vector<int> test2(5, 11);

	test2.reserve(15);
	test2.resize(3);
	
	test2.push_back(1);

	ft_print_vector(test1);
	ft_print_vector(test2);
	test2 = test1;
	test2.push_back(4);
	test2.push_back(4);
	test2.push_back(4);
	ft_print_vector(test1);
	ft_print_vector(test2);
}

	return 0;
}