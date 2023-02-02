#include <vector>
#include <iostream>
#include "../vector.hpp"

bool mypre (int i, int j) {
  return (i==j);
}

int main(void) {
	{	
		std::cout << "=================ft===================" << std::endl;

		ft::vector<int>	vec_test1(5, 42);
		ft::vector<int>	vec_test2(5, 42);
		ft::vector<int> vec_test3(5, 44);
		ft::vector<int> vec_test4(6, 44);

		std::cout << "equal(same) : " << ft::equal(vec_test1.begin(), vec_test1.end(), vec_test2.begin()) << std::endl;
		std::cout << "equal() : " << ft::equal(vec_test1.begin(), vec_test1.end(), vec_test3.begin()) << std::endl;
		std::cout << "== : " << (vec_test1 == vec_test2) << std::endl;
		std::cout << "!= : " << (vec_test1 != vec_test2) << std::endl;
		std::cout << "< : " << (vec_test1 < vec_test2) << std::endl;
		std::cout << "<= : " << (vec_test1 <= vec_test2) << std::endl;
		std::cout << "> : " << (vec_test1 > vec_test2) << std::endl;
		std::cout << ">= : " << (vec_test1 >= vec_test2) << std::endl;

		std::cout << "======================================" << std::endl;
	}

	{
		std::cout << "=================std==================" << std::endl;
		
        std::vector<int>	vec_test1(5, 42);
		std::vector<int>	vec_test2(5, 42);
		std::vector<int>	vec_test3(5, 44);
		std::vector<int>	vec_test4(6, 44);

		std::cout << "equal(same) : " << std::equal(vec_test1.begin(), vec_test1.end(), vec_test2.begin()) << std::endl;
		std::cout << "equal() : " << std::equal(vec_test1.begin(), vec_test1.end(), vec_test3.begin()) << std::endl;
		std::cout << "== : " << (vec_test1 == vec_test2) << std::endl;
		std::cout << "!= : " << (vec_test1 != vec_test2) << std::endl;
		std::cout << "< : " << (vec_test1 < vec_test2) << std::endl;
		std::cout << "<= : " << (vec_test1 <= vec_test2) << std::endl;
		std::cout << "> : " << (vec_test1 > vec_test2) << std::endl;
		std::cout << ">= : " << (vec_test1 >= vec_test2) << std::endl;

		std::cout << "======================================" << std::endl;
	}
    
    return 0;
}
