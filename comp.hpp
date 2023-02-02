#ifndef COMP_HPP
#define COMP_HPP

namespace ft 
{
	// __equal_to
	template <class T1, class T2 = T1>
	struct __equal_to
	{
		bool operator()(const T1& x, const T1& y) const { return x == y; }
		bool operator()(const T1& x, const T2& y) const { return x == y; }
		bool operator()(const T2& x, const T1& y) const { return x == y; }		
		bool operator()(const T2& x, const T2& y) const { return x == y; }
	};

	template <class T1>
	struct __equal_to<T1, T1>
	{ bool operator()(const T1& x, const T1& y) const { return x == y; } };

	template <class T1>
	struct __equal_to<const T1, T1>
	{ bool operator()(const T1& x, const T1& y) const { return x == y; } };

	template <class T1>
	struct __equal_to<T1, const T1>
	{ bool operator()(const T1& x, const T1& y) const { return x == y; } };

	// __less
	template <class T1, class T2 = T1>
	struct __less
	{
		bool operator()(const T1& x, const T1& y) const { return x < y; }
		bool operator()(const T1& x, const T2& y) const { return x < y; }
		bool operator()(const T2& x, const T1& y) const { return x < y; }
		bool operator()(const T2& x, const T2& y) const { return x < y; }
	};

	template <class T1>
	struct __less<T1, T1>
	{ bool operator()(const T1& x, const T1& y) const { return x < y; } };

	template <class T1>
	struct __less<const T1, T1>
	{ bool operator()(const T1& x, const T1& y) const { return x < y; } };

	template <class T1>
	struct __less<T1, const T1>
	{ bool operator()(const T1& x, const T1& y) const { return x < y; } };
}

#endif
