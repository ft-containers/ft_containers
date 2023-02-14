#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include "tree.hpp"
#include "vector_reverse_iterator.hpp"

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
		TreeIter(): it_(NULL) {};
		explicit	TreeIter( node_pointer x ): it_(x) {};
		template <class Iter>
		TreeIter ( const TreeIter<Iter, Node_ptr>& node_it ): it_(node_it.base()) {};

		node_pointer	base() const							{ return (this->_it); };
		reference		operator*() const						{ return (this->_it->key); };
		TreeIter&		operator++()							{this->_it = successor(this->_it); return (*this); };		// pre-increment
		TreeIter		operator++(int)							{ TreeIter temp(*this); ++(*this); return (temp); };		// post-increment
		TreeIter&		operator--()							{this->_it = predecessor(this->_it); return (*this); };		// pre-decrement
		TreeIter		operator--(int)							{ TreeIter temp(*this); --(*this); return (temp); };		// post-decrement
		pointer			operator->()							{ return (&(operator*())); };
		reference		operator[]( difference_type n ) const	{ return (*(this->_it + n)); };
	};
	
	template <class Tp, class node_pointer>
	bool operator== (const TreeIter<Tp, node_pointer>& lhs, const TreeIter<Tp, node_pointer>& rhs) { return (lhs.base() == rhs.base()); };
	template <class Tp, class node_pointer>
	bool operator!= (const TreeIter<Tp, node_pointer>& lhs, const TreeIter<Tp, node_pointer>& rhs) { return (lhs.base() != rhs.base()); };
	template <class Tp, class node_pointer>
	bool operator<  (const TreeIter<Tp, node_pointer>& lhs, const TreeIter<Tp, node_pointer>& rhs) { return (lhs.base() < rhs.base()); };
	template <class Tp, class node_pointer>
	bool operator<= (const TreeIter<Tp, node_pointer>& lhs, const TreeIter<Tp, node_pointer>& rhs) { return (lhs.base() <= rhs.base()); };
	template <class Tp, class node_pointer>
	bool operator>  (const TreeIter<Tp, node_pointer>& lhs, const TreeIter<Tp, node_pointer>& rhs) { return (lhs.base() > rhs.base()); };
	template <class Tp, class node_pointer>
	bool operator>=  (const TreeIter<Tp, node_pointer>& lhs, const TreeIter<Tp, node_pointer>& rhs) { return (lhs.base() >= rhs.base()); };



}; //ft _end;

#endif