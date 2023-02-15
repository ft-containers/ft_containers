#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include "tree.hpp"
#include "reverse_iterator.hpp"
#include "iterator_traits.hpp"

namespace ft
{
	template<class Tp, class node_pointer>
	class map_iterator
	{
	public:
		typedef Tp													iterator_type;
		typedef ft::bidirectional_iterator_tag						iterator_category;
		typedef typename iterator_traits<Tp>::value_type			value_type;
		typedef	typename iterator_traits<Tp>::difference_type		difference_type;
		typedef typename iterator_traits<Tp>::pointer				pointer;
		typedef typename iterator_traits<Tp>::reference				reference;
	
	private:
		node_pointer	it_;

	public:
		map_iterator(): it_(NULL) {};
		explicit	map_iterator( node_pointer x ): it_(x) {};
		template <class Iter>
		map_iterator ( const map_iterator<Iter, node_pointer>& node_it ): it_(node_it.base()) {};

		node_pointer	base() const							{ return (this->it_); };
		reference		operator* () const						{ return (this->it_->pair_data_); };
		map_iterator&	operator++()							{ this->it_ = successor(this->it_); return (*this); };			// pre-increment
		map_iterator	operator++(int)							{ map_iterator temp(*this); ++(*this); return (temp); };		// post-increment
		map_iterator&	operator--()							{ this->it_ = predecessor(this->it_); return (*this); };		// pre-decrement
		map_iterator	operator--(int)							{ map_iterator temp(*this); --(*this); return (temp); };		// post-decrement
		pointer			operator->()							{ return (&(operator*())); };
		// reference		operator[]( difference_type n ) const	{ return (*(this->it_ + n)); };
	};
	
	template <class Tp, class node_pointer>
	bool operator== (const map_iterator<Tp, node_pointer>& x, const map_iterator<Tp, node_pointer>& y)
		{ return (x.base() == y.base()); };
	template <class Tp, class node_pointer>
	bool operator!= (const map_iterator<Tp, node_pointer>& x, const map_iterator<Tp, node_pointer>& y)
		{ return (x.base() != y.base()); };
	template <class Tp, class node_pointer>
	bool operator<  (const map_iterator<Tp, node_pointer>& x, const map_iterator<Tp, node_pointer>& y)
		{ return (x.base() < y.base()); };
	template <class Tp, class node_pointer>
	bool operator<= (const map_iterator<Tp, node_pointer>& x, const map_iterator<Tp, node_pointer>& y)
		{ return (x.base() <= y.base()); };
	template <class Tp, class node_pointer>
	bool operator>  (const map_iterator<Tp, node_pointer>& x, const map_iterator<Tp, node_pointer>& y)
		{ return (x.base() > y.base()); };
	template <class Tp, class node_pointer>
	bool operator>=  (const map_iterator<Tp, node_pointer>& x, const map_iterator<Tp, node_pointer>& y)
		{ return (x.base() >= y.base()); };

};

#endif
