#include "../vector.hpp"

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
	return 0;
}
