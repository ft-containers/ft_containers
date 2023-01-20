// #include "../type_traits.hpp"
// #include "../iterator_traits.hpp"
// #include "../vector.hpp"
#include <vector>
#include <iostream>

namespace ft {
	template <typename>
	struct void_t 
	{ typedef void type; };


	template <typename T>
	struct has_iterator_typedefs
	{
		private:
		struct two
		{
			char x;
			char y;
		};

		template <typename U>
		static two is_qualified(...){ std::cout << "!!!!!!" << '\n';};
		template <typename U>
		// void_t 유무, 변수 유무(임시객체), 0 과 NULL
		static char is_qualified(
			typename ft::void_t<typename U::iterator_category>::type*,
			typename ft::void_t<typename U::difference_type>::type*,
			typename ft::void_t<typename U::value_type>::type*,
			typename ft::void_t<typename U::reference>::type*,
			typename ft::void_t<typename U::pointer>::type*){};
		public:
			static const bool value = 
				sizeof(is_qualified<T>(NULL, NULL, NULL, NULL, NULL)) == 1;
	};
};

template <typename T>
struct ic
{
	typedef typename T::iterator_category	iterator_category;
	
};

int	main(void)
{
	// ft::vector<int>::iterator i;
	// std::cout  << ft::is_iterator< ft::vector<int>::iterator>::value << '\n';
	
	std::cout << ft::has_iterator_typedefs<int>::value << '\n';
	// std::cout << ft::has_iterator_typedefs<ft::iterator_traits<ft::vector<int>::iterator> >::value << '\n';
	std::cout << ft::has_iterator_typedefs<std::vector<int>::iterator>::value << '\n';
	std::cout << ft::has_iterator_typedefs<ic<std::vector<int>::iterator> >::value << '\n';
	return (0);
}

//ft::has_iterator_typedefs<iterator_traits<Iter> >::value>
