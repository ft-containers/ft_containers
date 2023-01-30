#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <limits>
#include <algorithm>
#include "utility.hpp"
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

		// 함수와 변수를 구분하기 위하여 맨 뒤에 는더바맨.
		iterator											begin_;
		iterator											end_;
		// end_cap_.first는 iterator, end_cap_.second는 allocator
		pair<iterator, allocator_type>						end_cap_;

		// constructor 
		vector_base() throw()
			: begin_(NULL), end_(NULL), end_cap_(NULL, std::allocator<Tp>()) {}

		vector_base(const allocator_type& a)
			: begin_(NULL), end_(NULL), end_cap_(NULL, a) {}

		// destructor
		// ~vector_base()
		// {
		// 	if (_begin != NULL)
		// 	{
		// 		clear();
		// 		_a.deallocate(_begin, _capacity());
		// 	}
		// }

		void	swap_data(vector_base& other) throw();

		void clear() throw()
		{ destruct_at_end(begin_); }
		size_type capacity() const throw()
		{ return static_cast<size_type>(end_cap() - begin_); }
		void destruct_at_end(pointer new_last) throw(); // 나중에 필요할 때 

		allocator_type&			alloc() throw()
		{return end_cap_.second();}
		const allocator_type&	alloc() const throw()
		{return end_cap_.second();}
		pointer&				end_cap() throw()
		{return end_cap_.first();}
		const pointer&			end_cap() const throw()
		{return end_cap_.first();}

		size_type check_length(size_type n)
		{
			if (n > a_.max_size())
				throw_length_error();
			return n;
		}

		void copy_data(vector_base const& other) throw();

		void copy_data(
			pointer const& new_begin_, pointer const& new_end,
			pointer const& new_end_cap_) throw();
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

		// func
		

		// Iterators
		iterator begin() throw()
		{ return this->begin_; }
		const_iterator begin() const
		{ return this->begin_; }
		iterator end()
		{ return this->end_; }
		const_iterator end() const
		{ return this->end_; }
		// reverse_iterator rbegin()
		// { return reverse_iterator(end()); }
		// const_reverse_iterator rbegin() const 
		// { return const_reverse_iterator(end()); }
		// reverse_iterator rend() 
		// { return reverse_iterator(begin()); }
		// const_reverse_iterator rend() const 
		// { return const_reverse_iterator(begin()); }
		
		// Capacity -> 서브젝트 요구사항 다 만듬
		size_type	size() const
		{ return static_cast<size_type>(this->end_ - this->begin_); }
		size_type	max_size() const;
		void		resize (size_type n, value_type val = value_type());
		size_type	capacity() const 
		{ return base::capacity(); }
		bool		empty() const 
		{ return this->begin_ == this->end_; }
		void		reserve(size_type n);

		// Element access
		reference operator[](size_type n)
		{ return this->begin_[n]; }
		const_reference operator[](size_type n) const 
		{ return this->begin_[n]; }
		reference at(size_type n)
		{
			if (n >= size())
				this->throw_out_of_range();
			return this->begin_[n];
		}
		const_reference at(size_type n) const
		{
			if (n >= size())
				this->throw_out_of_range();
			return this->begin_[n];
		}
		reference front()
		{ return *this->begin_; }
		const_reference front() const
		{ return *this->begin_; }
		reference back()
		{ return *(this->end_ - 1); }
		const_reference back() const
		{ return *(this->end_ - 1); }

		// Modifiers
		void	push_back(const value_type& val);

	//서브젝트 요구사항! (public에 있을 이유 없음)
	private : 
		void	vallocate(size_type __n);

		void	construct_at_end(size_type n);
		void	construct_at_end(size_type n, const_reference x);
		// 리턴타입 잘보셈
		template <class ForwardIterator>
		typename enable_if < is_forward_iterator<ForwardIterator>::value, void >::type
				construct_at_end(ForwardIterator first, ForwardIterator last, size_type n);

		// Modifiers_private
		void	reallocate(size_type n);
		void	reconstruct_push_back(const value_type& val);

		// vector객체와 size_type n을 받아서 생성
		// 크기를 늘릴 준비를 해준다
		struct ConstructTransaction
		{
			vector				&v_;
			pointer				pos_;
			const_pointer const	new_end_;

			// constructor
			explicit ConstructTransaction(vector &v, size_type n)
				: v_(v),  pos_(v.end_), new_end_(v.end_ + n) {}
			// destructor
			~ConstructTransaction() { v_.end_ = pos_; }

			// private:
			// 	ConstructTransaction(ConstructTransaction const&) = delete; //아예 사용도 못하게
			// 	ConstructTransaction& operator=(ConstructTransaction const&) = delete;
		};
	};

	// constructor
	template <class Tp, class Allocator>
	vector<Tp, Allocator>::vector(size_type n)
	{
		if (n > 0)
		{
			vallocate(n);
			construct_at_end(n);
		}
	}

	template <class Tp, class Allocator>
	vector<Tp, Allocator>::vector(size_type n, const value_type& x)
	{
		if (n > 0)
		{
			vallocate(n);
			construct_at_end(n, x);
		}
	}

	template <class Tp, class Allocator>
	vector<Tp, Allocator>::vector(size_type n, const value_type& x, const allocator_type& a)
		: base(a)
	{
		if (n > 0)
		{
			vallocate(n);
			construct_at_end(n, x);
		}
	}

	template <class Tp, class Allocator>
	template <class InputIterator>
	vector<Tp, Allocator>::vector(InputIterator first,
									typename enable_if<(ft::is_input_iterator<InputIterator>::value &&
									!(ft::is_forward_iterator<InputIterator>::value)), InputIterator
									>::type last)
	{
		for (; first != last; ++first)
			push_back(first);
	}

	template <class Tp, class Allocator>
	template <class InputIterator>
	vector<Tp, Allocator>::vector(InputIterator first, InputIterator last, const allocator_type& a,
									typename enable_if<(ft::is_input_iterator<InputIterator>::value &&
									!ft::is_forward_iterator<InputIterator>::value)
									>::type* = 0)
		: base(a)
	{
		for (; first != last; ++first)
			push_back(*first);
	}

	template <class Tp, class Allocator>
	template <class ForwardIterator>
	vector<Tp, Allocator>::vector(ForwardIterator first,
									typename enable_if<(ft::is_forward_iterator<ForwardIterator>::value), ForwardIterator
									>::type last)
	{
		size_type n = static_cast<size_type>(std::distance(first, last));
		if (n > 0)
		{
			vallocate(n);
			construct_at_end(first, last, n);
		}
	}

	template <class Tp, class Allocator>
	template <class ForwardIterator>
	vector<Tp, Allocator>::vector(ForwardIterator first, ForwardIterator last, const allocator_type& a,
									typename enable_if<(ft::is_forward_iterator<ForwardIterator>::value)>::type* = 0)
		: base(a)
	{
		size_type n = static_cast<size_type>(std::distance(first, last));
		if (n > 0)
		{
			vallocate(n);
			construct_at_end(first, last, n);
		}
	}

	/* max_size */
	template <class Tp, class Allocator>
	typename vector<Tp, Allocator>::size_type
	vector<Tp, Allocator>::max_size() const throw()
	{
		return std::min<size_type>(allocator_type::max_size(this->alloc()),
									std::numeric_limits<difference_type>::max());
	}

		//  Allocate space for __n objects
		//  throws length_error if __n > max_size()
		//  throws (probably bad_alloc) if memory run out
		//  Precondition:  __begin_ == __end_ == __end_cap() == 0
		//  Precondition:  __n > 0
		//  Postcondition:  capacity() == __n
		//  Postcondition:  size() == 0
	template <class Tp, class Allocator>
	void
	vector<Tp, Allocator>::vallocate(size_type n)
	{
		if (n > max_size())
			this->throw_length_error();
		this->begin_ = this->end_ = allocator_type::allocate(this->alloc(), n);
		this->end_cap() = this->begin_ + n;
	}

		//  Default constructs __n objects starting at __end_
		//  throws if construction throws
		//  Precondition:  __n > 0
		//  Precondition:  size() + __n <= capacity() //캐퍼서티 범위내에서만 동작하는 함수
		//  Postcondition:  size() == size() + __n
	template <class Tp, class Allocator>
	void
	vector<Tp, Allocator>::construct_at_end(size_type n)
	{
		ConstructTransaction tx(*this, n);
		for (; tx.pos_ != tx.new_end_; ++tx.pos_)
			allocator_type::construct(this->alloc(), std::__to_raw_pointer(tx.pos_));
	}

	template <class Tp, class Allocator>
	void
	vector<Tp, Allocator>::construct_at_end(size_type n, const_reference x)
	{
		ConstructTransaction tx(*this, n);
		for (; tx.pos_ != tx.new_end_; ++tx.pos_)
			allocator_type::construct(this->alloc(), std::__to_raw_pointer(tx.pos_), x);
	}

	template <class Tp, class Allocator>
	template <class ForwardIterator>
	typename enable_if<is_forward_iterator<ForwardIterator>::value, void>::type
	vector<Tp, Allocator>::construct_at_end(ForwardIterator first, ForwardIterator last, size_type n)
	{
		ConstructTransaction tx(*this, n);
		allocator_type::construct_range_forward(this->alloc(), first, last, tx.pos_);
	}

	// push_back
	template <typename T, typename Allocator>
	void vector_base<T, Allocator>::copy_data(vector_base const& other) throw() 
	{
		begin_ = other.begin_;
		end_ = other.end_;
		end_cap_ = other.end_cap_;
	}

	template <typename T, typename Allocator>
	void vector_base<T, Allocator>::copy_data(
		pointer const& new_begin_, pointer const& new_end,
		pointer const& new_end_cap_) throw()
	{
		begin_ = new_begin_;
		end_ = new_end;
		end_cap_ = new_end_cap_;
	}

	// 5.temp의 소멸자와 함께 기존 벡터가 사라지게 하기 위해 temp와 기존 벡터 내의 원소 및 반복자 교환?
	template <typename T, typename Allocator>
	void vector_base<T, Allocator>::swap_data(vector_base& other) throw()
	{
		iterator					tmp_begin_(begin_);
		iterator					tmp_end_(end_);
		pair<iterator, Allocator>	tmp_end_cap_(end_cap(), alloc());

		this->copy_data(other);
		other.copy_data(tmp_begin_, tmp_end_, tmp_end_cap_);
	}

	// 4. 이미 있던 벡터의 원소(데이터)를 새 벡터에 복사
	template <typename T, typename Allocator>
	void vector<T, Allocator>::reallocate(size_type n)
	{
		vector<T, Allocator> tmp(n);
		std::uninitialized_copy(this->begin_, this->end_, tmp.begin_);
		tmp.end_ = tmp.begin_ + size();
		this->swap_data(tmp);
	}
	
	// 3. 적절한 크기인지 체크 후 재할당
	// 새로 넣을 카파시티가 더 클 경우에만 작동함.
	template <typename T, typename Allocator>
	void vector<T, Allocator>::reserve(size_type n) 
	{
		size_type new_size = base::check_length(n);
		if (new_size > capacity())
			reallocate(new_size);
	}

	// 2. 캐패서티를 넘어가는데 원소를 추가한 경우 -> 캐퍼서티를 늘리고 재할당
	template <typename T, typename Allocator>
	void vector<T, Allocator>::reconstruct_push_back(const value_type& val)
	{
		size_type cap = this->capacity();
		size_type max_size = max_size();
		size_type new_size = cap > (max_size >> 1) ? max_size : cap << 1;
		if (new_size == 0)
			new_size = 1;
		reserve(new_size);
		this->alloc().construct(this->end_++, val);
	}

	// 1. iterator를 이용한 생성자를 만들다가 push_back이 필요했음.
	template <typename T, typename Allocator>
	void vector<T, Allocator>::push_back(const value_type& val) 
	{
		if (this->end_ != this->end_cap_)
			this->alloc().construct(this->end_++, val);
		else
			reconstruct_push_back(val);
	}
};

#endif
