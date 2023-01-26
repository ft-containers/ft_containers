#ifndef UTILITY_HPP
#define UTILITY_HPP

namespace ft
{
	template <typename T1, typename T2>
	struct pair
	{
		// typedef
		typedef T1 first_type;
		typedef T2 second_type;

		// member variable
		T1 first;
		T2 second;

		// constructor
		pair() : first(), second() {}
		template <typename U1, typename U2>
		pair(const pair<U1, U2> &other)
			: first(other.first), second(other.second) {}
		pair(const T1 &t1, const T2 &t2) : first(t1), second(t2) {}

		// assign operator
		pair &operator=(pair const &other)
		{
			first = other.first;
			second = other.second;
			return *this;
		}
	};
};

#endif
