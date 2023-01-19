#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include "iterator_traits.hpp"

namespace ft
{
	/*---------------------vector_base_common class---------------------*/
	template <bool>
	class vector_base_common
	{
	protected:
		vector_base_common() {}
		void throw_length_error() const;
		void throw_out_of_range() const;
	};

	template <bool b>
	void vector_base_common<b>::throw_length_error() const
	{ std::__throw_length_error("vector"); }

	template <bool b>
	void vector_base_common<b>::throw_out_of_range() const
	{ std::__throw_out_of_range("vector"); }

	/*---------------------vector_base class--------------------------*/
	template <class Tp, class Allocator>
	class vector_base
		: protected vector_base_common<true>
	{
	public:
		typedef Allocator								allocator_type;
		typedef std::allocator_traits<allocator_type>	alloc_traits;
		typedef typename std::alloc_traits::size_type	size_type;
	protected:
		typedef Tp										value_type;
		typedef value_type&								reference;
		typedef const value_type&						const_reference;
		typedef typename alloc_traits::difference_type	difference_type;
		typedef typename alloc_traits::pointer			pointer;
		typedef typename alloc_traits::const_pointer	const_pointer;
		typedef pointer									iterator;
		typedef const_pointer							const_iterator;

		// 나중에 다시 확인
		// __vector_base() _NOEXCEPT_(is_nothrow_default_constructible<allocator_type>::value);
		// __vector_base(const allocator_type& __a);
	};

	template <typename Iter>
	class wrap_iter
	{
	public:
		typedef Iter															iterator_type;
		typedef typename ft::iterator_traits<iterator_type>::value_type			value_type;
		typedef typename ft::iterator_traits<iterator_type>::difference_type	difference_type;
		typedef typename ft::iterator_traits<iterator_type>::pointer			pointer;
		typedef typename ft::iterator_traits<iterator_type>::reference			reference;
		typedef typename ft::iterator_traits<iterator_type>::iterator_category	iterator_category;

	private:
		iterator_type	i;
		wrap_iter(iterator_type x) throw() : i(x) {}

	public:
		wrap_iter() throw();

		reference operator*() const throw()
		{ return *i; }
		pointer operator->() const throw()
		{ return std::__to_address(i); }
		wrap_iter& operator++() throw()
		{
			++i;
			return *this;
		}
		wrap_iter  operator++(int) throw()
		{
			wrap_iter tmp(*this);
			++(*this);
			return tmp;
		}
		wrap_iter& operator--() throw()
		{
			--i;
			return *this;
		}
		wrap_iter operator--(int) throw()
		{
			wrap_iter tmp(*this)
			--(*this);
			return tmp;
		}
		wrap_iter operator+(difference_type n) const throw()
		{
			wrap_iter w(*this);
			w += n;
			return w;
		}
		wrap_iter& operator+=(difference_type n) throw()
		{
			i += n;
			return *this;
		}
		wrap_iter operator- (difference_type n) const throw()
		{ return (*this + (-n)); }
		wrap_iter& operator-=(difference_type n) throw()
		{
			*this += -n;
			return *this;
		}
		reference operator[](difference_type n) const throw()
		{ return i[n]; }

		iterator_type base() const throw()
		{ return i; }
	};

	/*-------------------------vector class----------------------------*/
	template <typename Tp, typename Allocator /* = allocator<_Tp> */>
	class vector
		: private vector_base<Tp, Allocator>
	{
	private:
		typedef vector_base<Tp, Allocator>				base;
		typedef allocator<Tp>							default_allocator_type;
	public:
		typedef vector									self;
		typedef Tp										value_type;
		typedef Allocator								allocator_type;
		typedef typename base::alloc_traits				alloc_traits;
		typedef typename base::reference				reference;
		typedef typename base::const_reference			const_reference;
		typedef typename base::size_type				size_type;
		typedef typename base::difference_type			difference_type;
		typedef typename base::pointer					pointer;
		typedef typename base::const_pointer			const_pointer;
		typedef wrap_iter<pointer>						iterator;
		typedef wrap_iter<const_pointer>				const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
	};
}

#endif
