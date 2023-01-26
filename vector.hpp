#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include "iterator_traits.hpp"
#include "vector_iterator.hpp" // 나중에 vector_iterator 옮기고 지우기

namespace ft
{
	// vector_base_common class
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

	// vector_base class
	template <class Tp, class Allocator = std::allocator<Tp>()>
	class vector_base
		: protected vector_base_common<true>
	{
	public:
		typedef Allocator									allocator_type;
	protected:
		typedef Tp											value_type;
		typedef typename allocator_type::reference 			reference;
		typedef typename allocator_type::const_reference 	const_reference;
		typedef typename allocator_type::size_type 			size_type;
		typedef typename allocator_type::difference_type	difference_type;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef pointer										iterator;
		typedef const_pointer								const_iterator;

		iterator		_begin;
		iterator		_end;
		iterator		_end_cap;
		allocator_type	_a;

		// constructor
		vector_base() throw()
			: _begin(NULL), _end(NULL), _end_cap(NULL) {}

		vector_base(const allocator_type& a)
			: _begin(NULL), _end(NULL), _end_cap(NULL, a) {}

		// destructor
		// ~vector_base()
		// {
		// 	if (_begin != NULL)
		// 	{
		// 		clear();
		// 		_a.deallocate(_begin, _capacity());
		// 	}
		// }

		allocator_type& __alloc() throw()
			{return _end_cap.second();}
		const allocator_type& __alloc() const throw()
			{return _end_cap.second();}
		pointer& __end_cap() throw()
			{return _end_cap.first();}
		const pointer& __end_cap() const throw()
			{return _end_cap.first();}
	};

	// vector class
	template <typename Tp, typename Allocator = std::allocator<Tp> >
	class vector
		: private vector_base<Tp, Allocator>
	{
	private:
		typedef vector_base<Tp, Allocator>				base;
	public:
		typedef vector									self;
		typedef Tp										value_type;
		typedef Allocator								allocator_type;
		typedef typename base::reference				reference;
		typedef typename base::const_reference			const_reference;
		typedef typename base::size_type				size_type;
		typedef typename base::difference_type			difference_type;
		typedef typename base::pointer					pointer;
		typedef typename base::const_pointer			const_pointer;
		typedef vector_iterator<pointer>				iterator;
		typedef vector_iterator<const_pointer>			const_iterator;
		//typedef ft::reverse_iterator<iterator>		reverse_iterator;
		//typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		// constructor
		vector() throw() {}
		explicit vector(const allocator_type& a) throw() : base(a) {} //explicit

			//explicit 98버전이 맞는지? 형 안 맞는것 넣었을 때 오류 발생하는 키워드
		explicit vector(size_type n);
		vector(size_type n, const value_type& x);
		vector(size_type n, const value_type& x, const allocator_type& a);

		template <class InputIterator> // vector 403줄
		vector(InputIterator first,
				typename enable_if<(ft::is_input_iterator<InputIterator>::value &&
									!(ft::is_forward_iterator<InputIterator>::value)), InputIterator
									>::type last); // is_constructible ?
		template <class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type& a,
				typename enable_if<(ft::is_input_iterator<InputIterator>::value &&
									!ft::is_forward_iterator<InputIterator>::value)
									>::type* = 0);
		template <class ForwardIterator>
		vector(ForwardIterator first,
				typename enable_if<(ft::is_forward_iterator<ForwardIterator>::value), ForwardIterator
									>::type last);
		template <class ForwardIterator>
		vector(ForwardIterator first, ForwardIterator last, const allocator_type& a,
				typename enable_if<(ft::is_forward_iterator<ForwardIterator>::value)>::type* = 0);

		// vector(const vector& x) {}
		// vector(const vector& x, const allocator_type& a) {}
		// vector& operator=(const vector& x);
			// clear, assign, size 등 이런 친구들 만들고 하기?

		// Iterators
		iterator begin() throw()
		{ return this->begin; }
		const_iterator begin() const
		{ return this->begin; }
		iterator end()
		{ return this->end; }
		const_iterator end() const
		{ return this->end; }
		// reverse_iterator rbegin()
		// { return reverse_iterator(end()); }
		// const_reverse_iterator rbegin() const 
		// { return const_reverse_iterator(end()); }
		// reverse_iterator rend() 
		// { return reverse_iterator(begin()); }
		// const_reverse_iterator rend() const 
		// { return const_reverse_iterator(begin()); }
		void	vallocate(size_type __n);
	};

	// constructor
	template <class Tp, class Allocator>
	vector<Tp, Allocator>::vector(size_type n)
	{
		if (n > 0)
		{
			vallocate(n);
			__construct_at_end(n);
		}
	}

	template <class _Tp, class _Allocator>
	void
	vector<_Tp, _Allocator>::vallocate(size_type n)
	{
		if (n > max_size())
			this->throw_length_error();
		this->__begin_ = this->__end_ = allocator_type::allocate(this->__alloc(), n);
		this->__end_cap() = this->__begin_ + n;
		__annotate_new(0);
	}
};

#endif
