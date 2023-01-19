#include <type_traits>

#include <iostream>
#include <string>

template <typename U, typename T, typename S = void>
struct test {
	static const int v = 3;
	U b;
	// S a;
};

template <typename T, typename S>
struct test <T, S> {
	static const int v = 2;
	// U b;
	S a;
};

template <typename T, typename U>
struct test <T, T, U> {
	static const int v = 1;
	// T a;
	// U b;
};

int main(void) {
	test<int, char, char> a;
	test<int, int, double> b;
	// test<int, char, int> c;
	// test<int> d;

	std::cout << "a: " << a.v << std::endl;
	std::cout << "b: " << b.v << std::endl;
	//std::cout << "c: " << c.v << std::endl;

	return 0;
}
