// is_integral example
#include <iostream>
#include <type_traits>

#include "../utils.hpp"

int main() {
	std::cout << std::boolalpha;
	std::cout << "is_integral:" << std::endl;
	std::cout << "char: " << ft::is_integral<char>::value << std::endl;
	std::cout << "int: " << ft::is_integral<int>::value << std::endl;
	std::cout << "float: " << ft::is_integral<float>::value << std::endl;
	std::cout << "char: " << ft::is_integral<char>() << std::endl;
	std::cout << "int: " << ft::is_integral<int>() << std::endl;
	std::cout << "float: " << ft::is_integral<float>() << std::endl;

	std::cout << "------------std----------------"<< std::endl;
	std::cout << "char: " << std::is_integral<char>::value << std::endl;
	std::cout << "int: " << std::is_integral<int>::value << std::endl;
	std::cout << "float: " << std::is_integral<float>::value << std::endl;
	std::cout << "char: " << std::is_integral<char>() << std::endl;
	std::cout << "int: " << std::is_integral<int>() << std::endl;
	std::cout << "float: " << std::is_integral<float>() << std::endl;

	return 0;
}
// 참고: https://cplusplus.com/reference/type_traits/is_integral/


/*
** All the next part is an adaptation of is_integral.
** "is_integral" for this project in C++98 is a structure 
** that contain if the type given to it is a type from this list :
**  - bool
**  - char
**  - signed char
**  - int
**  - long int
**  - long long int
**  - unsigned char
**  - unsigned short int
**  - unsigned int
**  - unsigned long int
**  - unsigned long long int
*/
