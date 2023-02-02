#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include "type_traits.hpp"

namespace ft
{
	template <class Iter>
	class vector_iterator
	{
	public:
		typedef Iter														iterator_type;
		typedef typename iterator_traits<iterator_type>::iterator_category	iterator_category;
		typedef typename iterator_traits<iterator_type>::value_type			value_type;
		typedef typename iterator_traits<iterator_type>::difference_type	difference_type;
		typedef typename iterator_traits<iterator_type>::pointer			pointer;
		typedef typename iterator_traits<iterator_type>::reference			reference;
	private:
		iterator_type i;
	public:
		vector_iterator() throw() {}
		template <class Up>
		vector_iterator(const vector_iterator<Up>& u,
			typename ft::enable_if<ft::is_random_access_iterator<Up>::value>::type* = 0) throw()
			: i(u.base()) {}
		vector_iterator(iterator_type x) : i(x) {}

		iterator_type		 base() const { return i; }

		reference			operator* () const { return *i; }
		pointer				operator->() const { return i; }
		vector_iterator&	operator++() { ++i; return *this; }
		vector_iterator		operator++(int) { vector_iterator tmp(*this); ++(*this); return tmp; }
		vector_iterator&	operator--() { --i; return *this; }
		vector_iterator		operator--(int) { vector_iterator tmp(*this); --(*this); return tmp; }
		vector_iterator		operator+ (difference_type n) const { vector_iterator w(*this); w += n; return w; }
		vector_iterator&	operator+=(difference_type n) { i += n; return *this; }
		vector_iterator		operator- (difference_type n) const { return (*this + (-n)); }
		vector_iterator&	operator-=(difference_type n) { *this += -n; return *this; }
		reference			operator[](difference_type n) const { return i[n]; }
	};

	template <class Iter1, class Iter2>
	inline bool operator==(const vector_iterator<Iter1>& x, const vector_iterator<Iter2>& y) throw()
	{ return x.base() == y.base(); }

	template <class Iter1, class Iter2>
	inline bool operator<(const vector_iterator<Iter1>& x, const vector_iterator<Iter2>& y) throw()
	{ return x.base() < y.base(); }

	template <class Iter1, class Iter2>
	inline bool operator!=(const vector_iterator<Iter1>& x, const vector_iterator<Iter2>& y) throw()
	{ return !(x == y); }

	template <class Iter1, class Iter2>
	inline bool operator>(const vector_iterator<Iter1>& x, const vector_iterator<Iter2>& y) throw()
	{ return y < x; }

	template <class Iter1, class Iter2>
	inline bool operator>=(const vector_iterator<Iter1>& x, const vector_iterator<Iter2>& y) throw()
	{ return !(x < y); }

	template <class Iter1, class Iter2>
	inline bool operator<=(const vector_iterator<Iter1>& x, const vector_iterator<Iter2>& y) throw()
	{ return !(y < x); }

	template <class Iter1>
	inline bool operator!=(const vector_iterator<Iter1>& x, const vector_iterator<Iter1>& y) throw()
	{ return !(x == y); }

	template <class Iter1>
	inline bool operator>(const vector_iterator<Iter1>& x, const vector_iterator<Iter1>& y) throw()
	{ return y < x; }

	template <class Iter1>
	inline bool operator>=(const vector_iterator<Iter1>& x, const vector_iterator<Iter1>& y) throw()
	{ return !(x < y); }

	template <class Iter1>
	inline bool operator<=(const vector_iterator<Iter1>& x, const vector_iterator<Iter1>& y) throw()
	{ return !(y < x); }

	template <class Iter1, class Iter2>
	inline typename vector_iterator<Iter1>::difference_type
	operator-(const vector_iterator<Iter1>& x, const vector_iterator<Iter2>& y) throw()
	{ return x.base() - y.base(); }

	template <class Iter>
	inline 
	vector_iterator<Iter>
	operator+(typename vector_iterator<Iter>::difference_type n,
			vector_iterator<Iter> x) throw()
	{ x += n; return x; }
};

#endif
