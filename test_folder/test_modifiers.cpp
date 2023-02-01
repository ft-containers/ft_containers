#include "../vector.hpp"
#include <iostream>
#include <vector>
#include <memory>

/*
assign
push_back
pop_back
insert
erase
swap
clear
*/

template <typename Tp>
void	print_vector(ft::vector<Tp> myvector)
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

int	main()
{
	// done
	// modifiers
	// element access
	{
		ft::vector<int> vec_test1;
		std::cout << "-----push x 4-----" << std::endl;
		vec_test1.push_back(1);
		vec_test1.push_back(-23);
		vec_test1.push_back(42);
		vec_test1.push_back(100);
		std::cout << std::endl;
		print_vector(vec_test1);
		std::cout << std::endl;

		std::cout << "-----pop x 5------" << std::endl;
		vec_test1.pop_back();
		vec_test1.pop_back();
		vec_test1.pop_back();
		vec_test1.pop_back();
		vec_test1.pop_back();
		std::cout << std::endl;
		print_vector(vec_test1);
		std::cout << std::endl;

		std::cout << "-----assign-------" << std::endl;
		vec_test1.assign(5, 42);
		std::cout << std::endl;
		print_vector(vec_test1);
		std::cout << std::endl;
		
		std::cout << "-----assign it----" << std::endl;
		ft::vector<int>::iterator it_begin = vec_test1.begin();
		ft::vector<int>::iterator it_end = vec_test1.end();
		ft::vector<int> vec_test2;
		vec_test2.assign(it_begin, it_end);
		std::cout << std::endl;
		print_vector(vec_test2);
		std::cout << std::endl;
		
		std::cout << "-----clear--------" << std::endl;
		vec_test1.clear();
		std::cout << std::endl;
		print_vector(vec_test1);
		std::cout << std::endl;
		
		std::cout << "-----insert-------" << std::endl;
		vec_test1.assign(5, 0);
		print_vector(vec_test1);
		it_end = vec_test1.end();
		vec_test1.insert(it_end - 2, 444222);
		vec_test1.insert(it_end - 2, 2, 11111);	
		std::cout << std::endl;
		std::cout << "after insert : ";
		print_vector(vec_test1);
		std::cout << std::endl;


		std::cout << "-----erase-------" << std::endl;
		std::cout << "size : " << vec_test1.size() << std::endl;
		vec_test1.erase(it_end - 1);
		ft::vector<int> vec_test3;
		vec_test3.assign(5, 42);
		ft::vector<int>::iterator it_begin3 = vec_test3.begin();
		ft::vector<int>::iterator it_end3 = vec_test3.end();
		std::cout << "after erase v1: "<< '\n';
		print_vector(vec_test1);
		std::cout << "size : " << vec_test1.size() << std::endl;
		vec_test3.erase(it_begin3, it_end3);
		std::cout << "after erase v3:  "<< '\n';
		print_vector(vec_test3);
		std::cout << "size : " << vec_test1.size() << std::endl;
		

		std::cout << "-----swap-------" << std::endl;
		vec_test1.swap(vec_test2);
		std::cout << "after swap : "<< std::endl;
		std::cout << "vec_test1 : ";
		print_vector(vec_test1);
		std::cout << "vec_test2 : ";
		print_vector(vec_test2);
		
		std::cout << "------ [] ------" << std::endl;
		std::cout << vec_test2[1] << std::endl;
		std::cout << vec_test2.at(1) << std::endl;

 
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;

		ft::vector<char>	cv1(4);
		ft::vector<char>	cv2(5, 'c');
		ft::vector<int>		cv3(5, 42, std::allocator<int>());
		ft::vector<int>		cv4(cv3.begin(), cv3.end());
		ft::vector<int>		cv5(cv3.begin(), cv3.end(), std::allocator<int>());

		std::cout << "cv1" << std::endl; 
		print_vector(cv1);
		std::cout << "cv2" << std::endl; 
		print_vector(cv2);
		std::cout << "cv3" << std::endl; 
		print_vector(cv3);
		std::cout << "cv4" << std::endl; 
		print_vector(cv4);
		std::cout << "cv5" << std::endl; 
		print_vector(cv5);
	}

	return 0;
}