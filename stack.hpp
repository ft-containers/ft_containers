#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"
#include <memory>
#include <vector>
#include <iostream>


namespace ft
{
	template <typename _Tp, typename _Container = ft::vector<_Tp> >
	class stack
	{
	public:
		typedef _Container									container_type;
		typedef typename container_type::value_type			value_type;
		typedef typename container_type::size_type			size_type;

	protected:
		container_type c;

	public:
		//constructor
		explicit stack(const container_type& c = container_type()) : c(c) {}

		//member functions
		bool empty() const { return c.empty(); }
		size_type size() const { return c.size(); }
		value_type& top() { return c.back(); }
		const value_type& top() const { std::cout << "const called!"<< std::endl; return c.back(); }
		void push(const value_type& v) { c.push_back(v); }
		void pop() { c.pop_back(); }


		template <class T, class C>
		friend bool operator==(const stack<T, C>& x, const stack<T, C>& y);

		template <class T, class C>
		friend bool operator< (const stack<T, C>& x, const stack<T, C>& y);
	};

	template <class Tp, class Container>
	bool operator==(const stack<Tp, Container>& x, const stack<Tp, Container>& y)
	{ return x.c == y.c; }

	template <class Tp, class Container>
	bool operator< (const stack<Tp, Container>& x, const stack<Tp, Container>& y)
	{ return x.c < y.c; }

	template <class Tp, class Container>
	bool operator!=(const stack<Tp, Container>& x, const stack<Tp, Container>& y)
	{ return !(x == y); }

	template <class Tp, class Container>
	bool operator>(const stack<Tp, Container>& x, const stack<Tp, Container>& y)
	{ return y < x; }

	template <class Tp, class Container>
	bool operator>=(const stack<Tp, Container>& x, const stack<Tp, Container>& y)
	{ return !(x < y); }

	template <class Tp, class Container>
	bool operator<=(const stack<Tp, Container>& x, const stack<Tp, Container>& y)
	{ return !(y < x); }
}

#endif
