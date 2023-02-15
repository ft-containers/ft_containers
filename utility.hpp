#ifndef UTILITY_HPP
#define UTILITY_HPP

#include "iterator_traits.hpp"
#include "type_traits.hpp"

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

	template <class T1, class T2>
	bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
	return lhs.first == rhs.first && lhs.second == rhs.second;
	}

	template <class T1, class T2>
	bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
	return !(lhs == rhs);
	}

	template <class T1, class T2>
	bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
	return lhs.first < rhs.first ||
			(!(rhs.first < lhs.first) && lhs.second < rhs.second);
	}

	template <class T1, class T2>
	bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
	return rhs < lhs;
	}

	template <class T1, class T2>
	bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
	return !(lhs < rhs);
	}

	template <class T1, class T2>
	bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
	return !(rhs < lhs);
	}

	template <typename T1, typename T2>
	inline pair<T1, T2> make_pair(T1 x, T2 y) {
	return pair<T1, T2>(x, y);
	}

	template <typename T>
	void swap(T &x, T &y) {
	T tmp(x);
	x = y;
	y = tmp;
	}

	template <typename pair>
	struct select_first {
	typename pair::first_type &operator()(pair &x) const { return x.first; }
	const typename pair::first_type &operator()(const pair &x) const {
		return x.first;
	}
	};

	// template <typename T>
	// struct identity {
	// T &operator()(T &x) const { return x; }
	// const T &operator()(const T &x) const { return x; }
	// };
	
	// clang
	template <typename InputIter>
	typename iterator_traits<InputIter>::difference_type
	__distance(InputIter first, InputIter last, input_iterator_tag)
	{
		typename iterator_traits<InputIter>::difference_type i(0);
		for (; first != last; ++first)
			++i;
		return i;
	}

	template <typename RandIter>
	typename iterator_traits<RandIter>::difference_type
	__distance(RandIter first, RandIter last, random_access_iterator_tag)
	{ return last - first; }

	// 템플릿으로 하지않고 오버로딩으로 구현한 이유는, 랜덤엑세스이터레이터태그가 인풋이터레이터태그도 갖고있기때문에?인듯하다
	template <typename InputIter>
	typename iterator_traits<InputIter>::difference_type
	distance(InputIter first, InputIter last)
	{ return ft::__distance(first, last, typename iterator_traits<InputIter>::iterator_category()); }

};

#endif
