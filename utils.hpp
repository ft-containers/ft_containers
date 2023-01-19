#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstddef>

namespace ft
{
	// enable_if
	template <bool, typename Tp = void>
	struct enable_if {};
	template <typename Tp>
	struct enable_if<true, Tp>
	{ typedef Tp type; };
	
	// is_integral
	template <typename Tp, Tp v>
	struct integral_constant
	{
		static const Tp	value = v;
		typedef Tp	value_type;
		typedef integral_constant	type;

		operator value_type() const throw() { return value; }
	};

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
	template <>
	struct is_integral_type<long long int> : public true_type {};	
	template <>
	struct is_integral_type<unsigned char> : public true_type {};	
	template <>
	struct is_integral_type<unsigned short int> : public true_type {};
	template <>
	struct is_integral_type<unsigned int> : public true_type {};
	template <>
	struct is_integral_type<unsigned long int> : public true_type {};
	template <>
	struct is_integral_type<unsigned long long int> : public true_type {};
	
	template <typename Tp>
	struct is_integral : public is_integral_type<Tp> { };
};

#endif
