#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <limits>
#include <algorithm>
#include <string>
#include "utility.hpp"
#include "iterator_traits.hpp"
#include "vector_iterator.hpp"
#include "vector_reverse_iterator.hpp"
#include "algorithm.hpp"
#include <iterator>
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
	template <typename Tp, typename Allocator = std::allocator<Tp>()>
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
		~vector_base()
		{
			if (begin_ != NULL)
			{
				clear();
				this->alloc().deallocate(begin_, capacity());
			}
		}

		void	__swap_data(vector_base& other) throw();
	
		void 	__destroy_from_end(pointer new_end);

		void clear() throw()
		{ __destroy_from_end(begin_); }
		size_type capacity() const throw()
		{ return static_cast<size_type>(end_cap() - begin_); }
		allocator_type&			alloc() throw()
		{ return end_cap_.second; }
		const allocator_type&	alloc() const throw()
		{ return end_cap_.second; }
		pointer&				end_cap() throw()
		{ return end_cap_.first; }
		const pointer&			end_cap() const throw()
		{ return end_cap_.first; }

		size_type check_length(size_type n)
		{
			if (n > alloc().max_size())
				throw_length_error();
			return n;
		}

		void	__copy_data(vector_base const& other) throw();

		void	__copy_data(
			iterator const& new_begin_, iterator const& new_end,
			pair<iterator, Allocator> const& new_end_cap_) throw();
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
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;


		// constructor
			// //clang
			// vector() _NOEXCEPT_(is_nothrow_default_constructible<allocator_type>::value)
			// {
			// #if _LIBCPP_DEBUG_LEVEL >= 2
			// 			__get_db()->__insert_c(this);
			// #endif
			// 		}
			// 	_LIBCPP_INLINE_VISIBILITY explicit vector(const allocator_type& __a)
			// #if _LIBCPP_STD_VER <= 14
			// 		_NOEXCEPT_(is_nothrow_copy_constructible<allocator_type>::value)
			// #else
			// 		_NOEXCEPT
			// #endif
			// : __base(__a)

		vector() throw() {}
		explicit vector(const allocator_type& a) throw() : base(a) {} //explicit

		explicit vector(size_type n);
		vector(size_type n, const value_type& x);
		vector(size_type n, const value_type& x, const allocator_type& a);

		template <typename InputIterator> // vector 403줄
		vector(InputIterator first,
				typename enable_if<(is_input_iterator<InputIterator>::value &&
									!(is_forward_iterator<InputIterator>::value)), InputIterator
									>::type last);

		template <typename InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type& a,
				typename enable_if<(is_input_iterator<InputIterator>::value &&
									!is_forward_iterator<InputIterator>::value)
									>::type* = 0);
		
		template <typename ForwardIterator>
		vector(ForwardIterator first,
				typename enable_if<(is_forward_iterator<ForwardIterator>::value), ForwardIterator
									>::type last);

		template <typename ForwardIterator>
		vector(ForwardIterator first, ForwardIterator last, const allocator_type& a,
				typename enable_if<(is_forward_iterator<ForwardIterator>::value)>::type* = 0);
		
		// = operator
		vector(const vector& other);
		vector& operator=(const vector& other); 

		// Iterators
		iterator begin() throw()
		{ return this->begin_; }
		const_iterator begin() const
		{ return this->begin_; }
		iterator end()
		{ return this->end_; }
		const_iterator end() const
		{ return this->end_; }
		reverse_iterator rbegin()
		{ return reverse_iterator(end()); }
		const_reverse_iterator rbegin() const 
		{ return const_reverse_iterator(end()); }
		reverse_iterator rend() 
		{ return reverse_iterator(begin()); }
		const_reverse_iterator rend() const 
		{ return const_reverse_iterator(begin()); }
		
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

		//	Modifiers
		template <typename InputIterator>
			typename enable_if<is_input_iterator <InputIterator>::value && !is_forward_iterator<InputIterator>::value, void>::type
			assign(InputIterator first, InputIterator last);
		template <typename ForwardIterator>
			typename enable_if<is_forward_iterator<ForwardIterator>::value, void>::type
			assign(ForwardIterator first, ForwardIterator last);
		void assign(size_type n, const value_type& val);
		
		void	push_back(const value_type& val);
		void	pop_back();

		iterator	insert(iterator position, const value_type& val);
		void		insert(iterator position, size_type n, const value_type& val);
		template <typename InputIterator>
			typename enable_if <is_input_iterator <InputIterator>::value 
				&& !is_forward_iterator<InputIterator>::value , void>::type
			insert(iterator position, InputIterator first, InputIterator last);
		template <typename ForwardIterator>
			typename enable_if <is_forward_iterator<ForwardIterator>::value, void>::type
			insert(iterator position, ForwardIterator first, ForwardIterator last);

		iterator erase(iterator position);
		iterator erase(iterator first, iterator last);

		void swap(vector& x) { this->__swap_data(x); }
		void clear()
		{
			if (this->begin_) 
				this->__destroy_from_end(this->begin_);
		}

		allocator_type get_allocator() const
		{ return (this->alloc()); }
		
	//서브젝트 요구사항! (public에 있을 이유 없음)
	private : 
		void	__vallocate(size_type __n);

		void	__construct_at_end(size_type n);
		void	__construct_at_end(size_type n, const_reference x);
		// 리턴타입 잘보셈
		template <typename ForwardIterator>
		typename enable_if <is_forward_iterator<ForwardIterator>::value, void >::type
				__construct_at_end(ForwardIterator first, ForwardIterator last, size_type n);

		// Modifiers_private
		void	__reallocate(size_type n);
		void	__reconstruct_push_back(const value_type& val);

		

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
			__vallocate(n);
			__construct_at_end(n);
		}
	}

	template <class Tp, class Allocator>
	vector<Tp, Allocator>::vector(size_type n, const value_type& x)
	{
		if (n > 0)
		{
			__vallocate(n);
			__construct_at_end(n, x);
		}
	}

	template <class Tp, class Allocator>
	vector<Tp, Allocator>::vector(size_type n, const value_type& x, const allocator_type& a)
		: base(a)
	{
		if (n > 0)
		{
			__vallocate(n);
			__construct_at_end(n, x);
		}
	}

	template <class Tp, class Allocator>
	template <class InputIterator>
	vector<Tp, Allocator>::vector(InputIterator first,
									typename enable_if<(is_input_iterator<InputIterator>::value &&
									!(is_forward_iterator<InputIterator>::value)), InputIterator
									>::type last)
	{
		for (; first != last; ++first)
			push_back(first);
	}

	template <class Tp, class Allocator>
	template <class InputIterator>
	vector<Tp, Allocator>::vector(InputIterator first, InputIterator last, const allocator_type& a,
									typename enable_if<(is_input_iterator<InputIterator>::value &&
									!is_forward_iterator<InputIterator>::value)
									>::type*)
		: base(a)
	{
		for (; first != last; ++first)
			push_back(*first);
	}
	
	template <class Tp, class Allocator>
	template <class ForwardIterator>

	vector<Tp, Allocator>::vector(ForwardIterator first,
									typename enable_if<(is_forward_iterator<ForwardIterator>::value), ForwardIterator
									>::type last)
	{
		size_type n = static_cast<size_type>(ft::distance(first, last));
		if (n > 0)
		{
			__vallocate(n);
			__construct_at_end(first, last, n);
		}
	}

	template <class Tp, class Allocator>
	template <class ForwardIterator>
	vector<Tp, Allocator>::vector(ForwardIterator first, ForwardIterator last, const allocator_type& a,
									typename enable_if<(is_forward_iterator<ForwardIterator>::value)>::type*)
		: base(a)
	{
		size_type n = static_cast<size_type>(ft::distance(first, last));
		if (n > 0)
		{
			__vallocate(n);
			__construct_at_end(first, last, n);
		}
	}

	// Copy Constructor
	template <typename Tp, typename Allocator>
	vector<Tp, Allocator>::vector(const vector<Tp, Allocator>& other)
		: base(other.alloc())
	{
		this->__vallocate(other.size());
		this->end_ = std::uninitialized_copy(other.begin_, other.end_, this->begin_);
	}

	// operator=
	template <typename Tp, typename Allocator>
	vector<Tp, Allocator>& vector<Tp, Allocator>::operator=(
		const vector<Tp, Allocator>& other)
	{
		if (this != &other)
		{
			if (this->alloc() != other.alloc())
			{
				clear();
				this->alloc().deallocate(this->begin_, capacity());
				this->begin_ = this->end_ = NULL;
				// this->begin_ = this->end_ = this->end_cap() = NULL;
				this->alloc() = other.alloc();
			}
			assign(other.begin(), other.end());
		}
		return *this;
	}

	/* max_size */
	template <class Tp, class Allocator>
	typename vector<Tp, Allocator>::size_type
		vector<Tp, Allocator>::max_size() const
	{
		return std::min<size_type>(this->alloc().max_size(),
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
	void vector<Tp, Allocator>::__vallocate(size_type n)
	{
		if (n > max_size())
			this->throw_length_error();
		this->begin_ = this->end_ = this->alloc().allocate(n);
		this->end_cap() = this->begin_ + n;
	}

	template <typename Tp, typename Allocator>
	void vector_base<Tp, Allocator>::__destroy_from_end(pointer new_end)
	{
		pointer current_end = this->end_;
		while(new_end != current_end)
		{
			--current_end;
			this->alloc().destroy(current_end);
		}
		this->end_ = new_end;
	}

	template <typename Tp, typename Allocator>
	void vector<Tp, Allocator>::resize(size_type n, value_type val) 
	{
		size_type prev_size = size();
		if (n < prev_size)
		{
			this->__destroy_from_end(this->begin_ + n);
			return ;
		}
		else if (n > capacity())
			this->__reallocate(2 * capacity());
		insert(end(), n - prev_size, val);
	}

	template <typename Tp, typename Allocator>
	void vector<Tp, Allocator>::__construct_at_end(size_type n)
	{
		ConstructTransaction tx(*this, n);
		for (; tx.pos_ != tx.new_end_; ++tx.pos_)
			this->alloc().construct(tx.pos_);
			//alloc().construct(this->alloc(), std::__to_raw_pointer(tx.pos_));
	}
	template <typename Tp, typename Allocator>
	void vector<Tp, Allocator>::__construct_at_end(size_type n, const_reference x)
	{
		ConstructTransaction tx(*this, n);
		for (; tx.pos_ != tx.new_end_; ++tx.pos_)
			this->alloc().construct(tx.pos_, x);
			// alloc().construct( std::__to_raw_pointer(tx.pos_), x);
	}

	template <typename Tp, typename Allocator>
	template <typename ForwardIterator>
	typename enable_if<is_forward_iterator<ForwardIterator>::value, void>::type
		vector<Tp, Allocator>::__construct_at_end(ForwardIterator first, ForwardIterator last, size_type n)
	{
		ConstructTransaction tx(*this, n);
		std::__construct_range_forward(this->alloc(), first, last, tx.pos_);
	}

	// push_back
	template <typename Tp, typename Allocator>
	void vector_base<Tp, Allocator>::__copy_data(vector_base const& other) throw() 
	{
		begin_ = other.begin_;
		end_ = other.end_;
		end_cap_ = other.end_cap_;
	}

	template <typename Tp, typename Allocator>
	void vector_base<Tp, Allocator>::__copy_data(
		iterator const& new_begin_, iterator const& new_end,
		pair<iterator, Allocator> const& new_end_cap_) throw()
	{
		begin_ = new_begin_;
		end_ = new_end;
		end_cap_ = new_end_cap_;
	}

	// assign
	template <typename Tp, typename Allocator>
	template <typename InputIterator>
	typename enable_if<is_input_iterator <InputIterator>::value && !is_forward_iterator<InputIterator>::value, void>::type
		vector<Tp, Allocator>::assign(InputIterator first, InputIterator last)
	{
		clear();
		for (; first != last; ++first)
			push_back(*first);
	}

	template <typename Tp, typename Allocator>
	template <typename ForwardIterator>
	typename enable_if<is_forward_iterator<ForwardIterator>::value, void>::type
		vector<Tp, Allocator>::assign(ForwardIterator first, ForwardIterator last) 
	{
		size_type	new_n = ft::distance(first, last);
		if (new_n < capacity())
		{
			clear();
			this->end_ = std::uninitialized_copy(first, last, this->begin_);
		}
		else
		{
			vector<Tp, Allocator> tmp(first, last);
			this->__swap_data(tmp);
		}
	}

	template <typename Tp, typename Allocator>
	void vector<Tp, Allocator>::assign(size_type n, const value_type& val)
	{
		if (n < capacity())
		{
			clear();
			std::uninitialized_fill(this->begin_, this->begin_ + n, val);
			this->end_ += n;
		}
		else
		{
			vector<Tp, Allocator> tmp(n, val);
			this->__swap_data(tmp);
		}
	}

	template <typename Tp, typename Allocator>
	void vector<Tp, Allocator>::pop_back()
	{
		if (this->empty())
			return ;
		this->__destroy_from_end(this->end_ - 1);
	}

	template <typename Tp, typename Allocator>
	typename vector<Tp, Allocator>::iterator
		vector<Tp, Allocator>::insert(iterator position, const value_type& val) 
	{
		difference_type diff = position - begin();
		if (this->end_ == this->end_cap())
		{
			if (empty())
				reserve(size_type(1));
			else
				reserve(size_type(capacity() * 2));
		}
		pointer p = this->begin_ + diff;
		pointer old_end = this->end_;
		while (old_end != p)
		{
			--old_end;
			this->alloc().construct(old_end + 1, *(old_end));
			this->alloc().destroy(old_end);
		}
		this->alloc().construct(p, val);
		++(this->end_);
		return iterator(this->begin_ + diff);
	}

	template <typename Tp, typename Allocator>
	void vector<Tp, Allocator>::insert(iterator position, size_type n,
										const value_type& val)
	{
		difference_type diff = position - begin();
		if (size() + n > capacity())
		{
			if (empty())
				reserve(size_type(n));
			else if	(size() + n < capacity() * 2)
				reserve(capacity() * 2);
			else
				reserve(size() + n);
		}
		pointer p = this->begin_ + diff;
		pointer old_end = this->end_;
		while (old_end != p)
		{
			--old_end;
			this->alloc().construct(old_end + n, *(old_end));
			this->alloc().destroy(old_end);
		}
		std::uninitialized_fill(p, p + n, val);
		this->end_ += n;
	}

	template <typename Tp, typename Allocator>
	template <typename InputIterator>
	typename enable_if <is_input_iterator <InputIterator>::value 
		&& !is_forward_iterator<InputIterator>::value, void>::type
	vector<Tp, Allocator>::insert(iterator position, InputIterator first, InputIterator last)
	{
		difference_type diff = position - begin();
		pointer p = this->begin_ + diff;
		pointer prev_end_ = this->end_;
		for (int i = 0; first != last; ++first, ++i) 
			insert(position + i, *first);
	}

	template <typename Tp, typename Allocator>
	template <typename ForwardIterator>
	typename enable_if <is_forward_iterator<ForwardIterator>::value, void>::type
	vector<Tp, Allocator>::insert(iterator position, ForwardIterator first, ForwardIterator last)
	{
		difference_type in_size = ft::distance(first, last);
		difference_type diff = position - begin();
		if (in_size <= 0) 
			return ;
		if (in_size + size() > capacity())
		{
			if (empty())
				reserve(size_type(in_size));
			else if	(size() + in_size < capacity() * 2)
				reserve(capacity() * 2);
			else
				reserve(size() + in_size);
		}
		pointer p = this->begin_ + diff;
		pointer old_end = this->end_;
		while (old_end != p) 
		{
			--old_end;
			this->alloc().construct(old_end + in_size, *(old_end));
			this->alloc().destroy(old_end);
		}
		std::uninitialized_copy(first, last, p);
		this->end_ += in_size;
	}

	// erase
	template <typename Tp, typename Allocator>
	typename vector<Tp, Allocator>::iterator
	vector<Tp, Allocator>::erase(iterator position)
	{
		difference_type diff = position - begin();
		pointer p = this->begin_ + diff;
		this->alloc().destroy(p);
		this->alloc().destroy(std::uninitialized_copy(p + 1, (this->end_)--, p));
		return (iterator(this->begin_ + diff));
	}

	template <typename Tp, typename Allocator>
	typename vector<Tp, Allocator>::iterator
	vector<Tp, Allocator>::erase(iterator first, iterator last)
	{
		difference_type diff = first - begin();
		pointer p = this->begin_ + diff;

		if (last == end())
		{
			this->__destroy_from_end(p);
			return iterator(this->begin_ + diff);
		}

		difference_type range = last - first;
		pointer p_last = p + range;
		pointer new_end = this->end_ - range;

		for (difference_type i = 0; i <= range; ++i)
		{
			this->alloc().destroy(p + i);
			if (i <= this->end_ - p_last)
				this->alloc().construct(p + i, *(p_last + i));
		}
		this->__destroy_from_end(new_end);
		return (iterator(this->begin_ + diff));
	}


	// 5.temp의 소멸자와 함께 기존 벡터가 사라지게 하기 위해 temp와 기존 벡터 내의 원소 및 반복자 교환?
	template <typename Tp, typename Allocator>
	void vector_base<Tp, Allocator>::__swap_data(vector_base& other) throw()
	{
		iterator					tmp_begin_(begin_);
		iterator					tmp_end_(end_);
		pair<iterator, Allocator>	tmp_end_cap_(end_cap(), alloc());

		this->__copy_data(other);
		other.__copy_data(tmp_begin_, tmp_end_, tmp_end_cap_);
	}

	// 4. 이미 있던 벡터의 원소(데이터)를 새 벡터에 복사
	template <typename Tp, typename Allocator>
	void vector<Tp, Allocator>::__reallocate(size_type n)
	{
		vector<Tp, Allocator> tmp(n);
		std::uninitialized_copy(this->begin_, this->end_, tmp.begin_);
		tmp.end_ = tmp.begin_ + size();
		this->__swap_data(tmp);
	}
	// 3. 적절한 크기인지 체크 후 재할당
	// 새로 넣을 카파시티가 더 클 경우에만 작동함.
	template <typename Tp, typename Allocator>
	void vector<Tp, Allocator>::reserve(size_type n) 
	{
		size_type new_size = base::check_length(n);
		if (new_size > capacity())
			__reallocate(new_size);
	}
	// 2. 캐패서티를 넘어가는데 원소를 추가한 경우 -> 캐퍼서티를 늘리고 재할당
	template <typename Tp, typename Allocator>
	void vector<Tp, Allocator>::__reconstruct_push_back(const value_type& val)
	{
		size_type cap = this->capacity();
		size_type max_size = this->max_size();
		size_type new_size = cap > (max_size >> 1) ? max_size : cap << 1;
		if (new_size == 0)
			new_size = 1;
		reserve(new_size);
		this->alloc().construct(this->end_++, val);
	}
	// 1. iterator를 이용한 생성자를 만들다가 push_back이 필요했음.
	template <typename Tp, typename Allocator>
	void vector<Tp, Allocator>::push_back(const value_type& val) 
	{
		if (this->end_ != this->end_cap())
			this->alloc().construct(this->end_++, val);
		else
			__reconstruct_push_back(val);
	}

	//swap
	template <class Tp, class Allocator>
	void swap (vector<Tp, Allocator>& x, vector<Tp, Allocator>& y)
	{ x.swap(y); }

};

// non_member func 
template <class Tp, class Allocator>
bool operator== (const ft::vector<Tp, Allocator>& x, const ft::vector<Tp, Allocator>& y)
{
	const typename ft::vector<Tp, Allocator>::size_type sz = x.size();
	return (sz == y.size() && ft::equal(x.begin(), x.end(), y.begin()));
}
template <class Tp, class Allocator>
bool operator!= (const ft::vector<Tp, Allocator>& x, const ft::vector<Tp, Allocator>& y)
{ return !(x == y); }

template <class Tp, class Allocator>
bool operator<  (const ft::vector<Tp, Allocator>& x, const ft::vector<Tp, Allocator>& y)
{ return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()); }

template <class Tp, class Allocator>
bool operator<= (const ft::vector<Tp, Allocator>& x, const ft::vector<Tp, Allocator>& y)
{ return !(y < x); }

template <class Tp, class Allocator>
bool operator>  (const ft::vector<Tp, Allocator>& x, const ft::vector<Tp, Allocator>& y)
{ return (y < x); }

template <class Tp, class Allocator>
bool operator>= (const ft::vector<Tp, Allocator>& x, const ft::vector<Tp, Allocator>& y)
{ return !(x < y); }

#endif
