#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"
#include <memory>
#include <iostream>

namespace ft
{
	template <typename Tp, typename Container = ft::vector<Tp> >
	class stack
	{
	public:
		typedef Container									container_type;
		typedef typename container_type::value_type			value_type;
		typedef typename container_type::size_type			size_type;

	protected:
		container_type c_;

	public:
		//constructor
		explicit stack(const container_type& c = container_type()) : c_(c) {}

		//member functions
		bool empty() const { return c_.empty(); }
		size_type size() const { return c_.size(); }
		value_type& top() { return c_.back(); }
		const value_type& top() const { std::cout << "const called!"<< std::endl; return c_.back(); }
		void push(const value_type& v) { c_.push_back(v); }
		void pop() { c_.pop_back(); }
		
	};
	template <class Tp, class Container>
	bool operator==(const stack<Tp, Container>& x, const stack<Tp, Container>& y)
	{ return x.c_ == y.c_; }

	template <class Tp, class Container>
	bool operator< (const stack<Tp, Container>& x, const stack<Tp, Container>& y)
	{ return x.c_ < y.c_; }

	template <class Tp, class Container>
	bool
	operator!=(const stack<Tp, Container>& x, const stack<Tp, Container>& y)
	{ return !(x == y); }

	template <class Tp, class Container>
	bool operator> (const stack<Tp, Container>& x, const stack<Tp, Container>& y)
	{ return y < x; }

	template <class Tp, class Container>
	bool operator>=(const stack<Tp, Container>& x, const stack<Tp, Container>& y)
	{ return !(x < y); }

	template <class Tp, class Container>
	bool operator<=(const stack<Tp, Container>& x, const stack<Tp, Container>& y)
	{ return !(y < x); }
}

#endif
