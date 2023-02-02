#include <vector>
#include <iostream>
#include "../vector.hpp"

bool mypre (int i, int j) {
  return (i==j);
}


int main(void) {
	ft::vector<int>	vec_test1(5, 42);
	ft::vector<int>	vec_test2(5, 42);
    ft::vector<int> vec_test3(5, 44);
    ft::vector<int> vec_test4(6, 44);

	std::cout << "== : " << (vec_test1 == vec_test2) << std::endl;
	std::cout << "!= : " << (vec_test1 != vec_test2) << std::endl;
	std::cout << "<= : " << (vec_test1 <= vec_test2) << std::endl;
	std::cout << "< : " << (vec_test1 < vec_test2) << std::endl;
	std::cout << ">= : " << (vec_test1 >= vec_test2) << std::endl;
	std::cout << "> : " << (vec_test1 > vec_test2) << std::endl;

    std::cout << "======================================" << std::endl;
    
    return 0;
}
