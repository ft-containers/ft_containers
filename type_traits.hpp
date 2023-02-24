#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

#include <cstddef>
#include "iterator_traits.hpp"

namespace ft
{
	// enable_if
	template <bool, typename Tp = void>
	struct enable_if {};
	template <typename Tp>
	struct enable_if<true, Tp>
	{ typedef Tp type; };
	
	// integral_constant
	template <typename Tp, Tp v>
	struct integral_constant
	{
		// typedef integral_constant<Tp, v>	type;
		static const Tp	value = v;
		typedef Tp	value_type;
		typedef integral_constant	type;

		operator value_type() const throw() { return value; }
	};

	template <typename From, typename To>
	struct is_convertible
	{
		private:
		static char test(To);
		static char (&test(...))[2];

		public:
		enum { value = sizeof(test(From())) == sizeof(char) };
	};

//----------------------------------
	//is_constructible
	// template <typename T, typename Arg>
	// struct is_constructible_helper {
	// private:
	// 	template <typename U>
	// 	static char check(U(*)[1]);
	// 	static char check(...);
	// 	static T makeT();
	// public:
	// 	enum { value = sizeof(check(makeT())) == sizeof(char) };
	// };

	// template <typename T, typename Arg>
	// struct is_constructible : public std::integral_constant<bool, is_constructible_helper<T, Arg>::value> {};

	//integral_constant
	typedef integral_constant<bool, true> true_type;
	typedef integral_constant<bool, false> false_type;

	template <typename>
	struct is_integral_type : public false_type {};
	template <>
	struct is_integral_type<bool> : public true_type {};
	template <>
	struct is_integral_type<char> : public true_type {};
	template <>
	struct is_integral_type<signed char> : public true_type {};
	template <>
	struct is_integral_type<short int> : public true_type {};
	template <>
	struct is_integral_type<int> : public true_type {};	
	template <>
	struct is_integral_type<long int> : public true_type {};	
	// template <>
	// struct is_integral_type<long long int> : public true_type {};	
	template <>
	struct is_integral_type<unsigned char> : public true_type {};	
	template <>
	struct is_integral_type<unsigned short int> : public true_type {};
	template <>
	struct is_integral_type<unsigned int> : public true_type {};
	template <>
	struct is_integral_type<unsigned long int> : public true_type {};
	// template <>
	// struct is_integral_type<unsigned long long int> : public true_type {};
	
	// is_integral
	template <typename Tp>
	struct is_integral : public is_integral_type<Tp> {};

	// is_same
	template <typename T, typename U>
	struct is_same : public false_type {};

	template <typename T>
	struct is_same<T, T> : public true_type {};

	// void_t : template인 이유는 인자를 받을수 있는지만 보기위하여 template클래스로 정의됨. //좋아요수 3
	// 			1. 88번 줄의 템플릿 특수화된 함수를 검사한다.
	//			2. void_t<typename ...>을 검사하는데 typename이 존재한다면 한줄씩 넘어간다.
	//			3. 그런데 존재하지않는다면 88번의 함수를 호출한다.
	//			* 2.에서 typename을 검사하기위해서 void_t가 template클래스로 정의된다? 인듯
	template <typename>
	struct void_t 
	{ typedef void type; };

	// has_iterator_typedefs
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
		static two is_qualified(...){};
		template <typename U>
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

	// is_iterator
	template <typename Iter, bool = has_iterator_typedefs<Iter>::value>
	struct is_iterator : public false_type
	{ typedef void category; };

	template <typename Iter>
	struct is_iterator<Iter, true> : public true_type
	{ typedef typename Iter::iterator_category category; };

	template <typename T>
	struct is_iterator<T *, true> : public true_type
	{ typedef typename iterator_traits<T *>::iterator_category category; };

	// is_input_iterator
	template <typename Iter>
	struct is_input_iterator
		: public integral_constant<bool,
								is_same<typename is_iterator<Iter>::category,
											input_iterator_tag>::value ||
								is_same<typename is_iterator<Iter>::category,
											forward_iterator_tag>::value ||
								is_same<typename is_iterator<Iter>::category,
											bidirectional_iterator_tag>::value ||
								is_same<typename is_iterator<Iter>::category,
											random_access_iterator_tag>::value> {};

	// is_output_iterator
	template <typename Iter>
	struct is_output_iterator
		: public integral_constant<bool,
								is_same<typename is_iterator<Iter>::category,
											output_iterator_tag>::value> {};

	// is_forward_iterator
	template <typename Iter>
	struct is_forward_iterator
		: public integral_constant<bool, 
								is_same<typename is_iterator<Iter>::category,
									forward_iterator_tag>::value ||
								is_same<typename is_iterator<Iter>::category,
									bidirectional_iterator_tag>::value ||
								is_same<typename is_iterator<Iter>::category,
									random_access_iterator_tag>::value> {};

	// is_bidirectional_iterator
	template <typename Iter>
	struct is_bidirectional_iterator
		: public integral_constant<bool, 
								is_same<typename is_iterator<Iter>::category,
									bidirectional_iterator_tag>::value ||
								is_same<typename is_iterator<Iter>::category,
									random_access_iterator_tag>::value> {};

	// is_random_access_iterator
	template <typename Iter>
	struct is_random_access_iterator
		: public integral_constant<bool,
								is_same<typename is_iterator<Iter>::category,
									random_access_iterator_tag>::value> {};
}

#endif
