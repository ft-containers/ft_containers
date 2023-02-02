#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP


namespace ft
{
	template <class T1, class T2 = T1>
	struct __equal_to
	{
		bool operator()(const T1& x, const T1& y) const 
		{return x == y;}

		bool operator()(const T1& x, const T2& y) const 
		{return x == y;}

		bool operator()(const T2& x, const T1& y) const 
		{return x == y;}
		
		bool operator()(const T2& x, const T2& y) const
		{return x == y;}
	};

	template <class T1>
	struct __equal_to<T1, T1>
	{
		bool operator()(const T1& x, const T1& y) const {return x == y;}
	};

	template <class T1>
	struct __equal_to<const T1, T1>
	{
		bool operator()(const T1& x, const T1& y) const {return x == y;}
	};

	template <class T1>
	struct __equal_to<T1, const T1>
	{
		bool operator()(const T1& x, const T1& y) const {return x == y;}
	};

	template <class InputIterator1, class InputIterator2>
	bool
	equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		typedef typename ft::iterator_traits<InputIterator1>::value_type v1;
		typedef typename ft::iterator_traits<InputIterator2>::value_type v2;
		return equal(first1, last1, first2, __equal_to<v1, v2>());
	}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool
	equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
	{
		for (; first1 != last1; ++first1, (void) ++first2)
			if (!pred(*first1, *first2))
				return false;
		return true;
	}
};

#endif
