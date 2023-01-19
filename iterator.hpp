#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "utils.hpp"

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
//------------------------------------------------------------------------

template <typename T, typename U>
struct is_same : public false_type {};

template <typename T>
struct is_same<T, T> : public true_type {};
//////////////////////

template <typename>
struct void_t {
  typedef void type;
};
//////////////////////

template <typename _T>
struct __has_iterator_typedefs {
 private:
  struct __two {
    char __x;
    char __y;
  };
};

/////////////////////////

template <typename _Iter,
          bool = __has_iterator_typedefs<iterator_traits<_Iter> >::value>
struct __is_iterator : public false_type {
  typedef void category;
};

template <typename _Iter>
struct __is_iterator<_Iter, true> : public true_type {
  typedef typename _Iter::iterator_category category;
};

template <typename _T>
struct __is_iterator<_T *, true> : public true_type {
  typedef typename iterator_traits<_T *>::iterator_category category;
};

template <typename _Iter>
struct __is_input_iterator
    : public integral_constant<bool,
                               (is_same<typename __is_iterator<_Iter>::category,
                                        input_iterator_tag>::value ||
                                is_same<typename __is_iterator<_Iter>::category,
                                        forward_iterator_tag>::value ||
                                is_same<typename __is_iterator<_Iter>::category,
                                        bidirectional_iterator_tag>::value ||
                                is_same<typename __is_iterator<_Iter>::category,
                                        random_access_iterator_tag>::value)> {};

template <typename _Iter>
struct __is_output_iterator
    : public integral_constant<bool,
                               is_same<typename __is_iterator<_Iter>::category,
                                       output_iterator_tag>::value> {};

template <typename _Iter>
struct __is_forward_iterator
    : public integral_constant<
          bool, is_same<typename __is_iterator<_Iter>::category,
                        forward_iterator_tag>::value ||
                    is_same<typename __is_iterator<_Iter>::category,
                            bidirectional_iterator_tag>::value ||
                    is_same<typename __is_iterator<_Iter>::category,
                            random_access_iterator_tag>::value> {};

template <typename _Iter>
struct __is_bidirectional_iterator
    : public integral_constant<
          bool, is_same<typename __is_iterator<_Iter>::category,
                        bidirectional_iterator_tag>::value ||
                    is_same<typename __is_iterator<_Iter>::category,
                            random_access_iterator_tag>::value> {};

template <typename _Iter>
struct __is_random_access_iterator
    : public integral_constant<bool,
                               is_same<typename __is_iterator<_Iter>::category,
                                       random_access_iterator_tag>::value> {};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class Up> 
		vector_iterator(const vector_iterator<Up>& u,
			typename enable_if<is_convertible<Up, iterator_type>::value>::type* = 0) throw()
			: i(u.base()){}
	reference operator*() const throw(){ return *i; }
	pointer  operator->() const throw()
	{ return (pointer)std::addressof(*i); }
	vector_iterator& operator++() throw()
	{
		++i;
		return *this;
	}
	vector_iterator operator++(int) throw()
		{ vector_iterator tmp(*this); ++(*this); return tmp; }
	vector_iterator& operator--() throw()
	{
		--i;
		return *this;
	}
	vector_iterator operator--(int) throw()
		{ vector_iterator tmp(*this); --(*this); return tmp; }
	wrap_ite  operator+ (difference_type n) const throw()
		{ vector_iterator w(*this); w += n; return w; }
	vector_iterator& operator+=(difference_type n) throw()
	{
		i += n;
		return *this;
	}
	vector_iterator operator- (difference_type n) const throw()
	{ return (*this + (-n)); }
	vector_iterator& operator-=(difference_type n) throw()
	{
		*this += -n;
		return *this;
	}
	reference operator[](difference_type n) const throw()
	{
		return i[n];
	}
	iterator_type base() const throw() { return i; }

	vector_iterator(iterator_type x) throw() : i(x) {}
};

template <class Iter1, class Iter2>
inline bool operator==(const vector_iterator<Iter1>& x, const vector_iterator<Iter2>& y) throw()
{
	return x.base() == y.base();
}

template <class Iter1, class Iter2>
inline bool operator<(const vector_iterator<Iter1>& x, const vector_iterator<Iter2>& y) throw()
{
	return x.base() < y.base();
}

template <class Iter1, class Iter2>
inline bool operator!=(const vector_iterator<Iter1>& x, const vector_iterator<Iter2>& y) throw()
{
	return !(x == y);
}

template <class Iter1, class Iter2>
inline bool operator>(const vector_iterator<Iter1>& x, const vector_iterator<Iter2>& y) throw()
{
	return y < x;
}

template <class Iter1, class Iter2>
inline bool operator>=(const vector_iterator<Iter1>& x, const vector_iterator<Iter2>& y) throw()
{
	return !(x < y);
}

template <class Iter1, class Iter2>
inline bool operator<=(const vector_iterator<Iter1>& x, const vector_iterator<Iter2>& y) throw()
{
	return !(y < x);
}

template <class Iter1>
inline bool operator!=(const vector_iterator<Iter1>& x, const vector_iterator<Iter1>& y) throw()
{
	return !(x == y);
}

template <class Iter1>
inline bool operator>(const vector_iterator<Iter1>& x, const vector_iterator<_ter1>& y) throw()
{
	return y < x;
}

template <class Iter1>
inline bool operator>=(const vector_iterator<_Iter1>& x, const vector_iterator<_Iter1>& y) throw()
{
	return !(x < y);
}

template <class Iter1>
inline bool operator<=(const vector_iterator<_Iter1>& x, const __vector_iterator<_Iter1>& y) throw()
{
	return !(y < x);
}

template <class Iter1, class Iter2>
inline typename vector_iterator<Iter1>::difference_type
operator-(const vector_iterator<Iter1>& x, const vector_iterator<Iter2>& y) throw()
{
	return x.base() - y.base();
}

template <class Iter>
inline 
vector_iterator<_Iter>
operator+(typename vector_iterator<Iter>::difference_type n,
		vector_iterator<Iter> x) throw()
{
	x += n;
	return x;
}


/*           backup           */

//	   - 종류
//     - 입력 반복자 : *iter , → , ++ , == , != , 복사생성자 연산 제공
//     - 출력 반복자 : *iter = x(쓰기) , ++ , 복사생성자 연산 제공
//     - 순방향 반복자 : *iter , → , ++ , == , != , = , 기본생성자, 복사생성자 연산 제공
//     - 양방향 반복자 : 순방향 , --
//     - 임의 접근 반복자 : 양방향 , [ ] , += , -= , + , - , < , > , ≤ , ≥ 연산 제공

	// template <typename Iter>
	// class wrap_iter
	// {
	// public:
	// 	typedef Iter															iterator_type;
	// 	typedef typename ft::iterator_traits<iterator_type>::value_type			value_type;
	// 	typedef typename ft::iterator_traits<iterator_type>::difference_type	difference_type;
	// 	typedef typename ft::iterator_traits<iterator_type>::pointer			pointer;
	// 	typedef typename ft::iterator_traits<iterator_type>::reference			reference;
	// 	typedef typename ft::iterator_traits<iterator_type>::iterator_category	iterator_category;

	// private:
	// 	iterator_type	i;
	// 	wrap_iter(iterator_type x) throw() : i(x) {}

	// public:
	// 	wrap_iter() throw();

	// 	reference operator*() const throw()
	// 	{ return *i; }
	// 	pointer operator->() const throw()
	// 	{ return std::__to_address(i); }
	// 	wrap_iter& operator++() throw()
	// 	{
	// 		++i;
	// 		return *this;
	// 	}
	// 	wrap_iter  operator++(int) throw()
	// 	{
	// 		wrap_iter tmp(*this);
	// 		++(*this);
	// 		return tmp;
	// 	}
	// 	wrap_iter& operator--() throw()
	// 	{
	// 		--i;
	// 		return *this;
	// 	}
	// 	wrap_iter operator--(int) throw()
	// 	{
	// 		wrap_iter tmp(*this)
	// 		--(*this);
	// 		return tmp;
	// 	}
	// 	wrap_iter operator+(difference_type n) const throw()
	// 	{
	// 		wrap_iter w(*this);
	// 		w += n;
	// 		return w;
	// 	}
	// 	wrap_iter& operator+=(difference_type n) throw()
	// 	{
	// 		i += n;
	// 		return *this;
	// 	}
	// 	wrap_iter operator-(difference_type n) const throw()
	// 	{ return (*this + (-n)); }
	// 	wrap_iter& operator-=(difference_type n) throw()
	// 	{
	// 		*this += -n;
	// 		return *this;
	// 	}
	// 	reference operator[](difference_type n) const throw()
	// 	{ return i[n]; }

	// 	iterator_type base() const throw()
	// 	{ return i; }
	// };

#endif
