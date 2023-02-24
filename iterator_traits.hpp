#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

#include <cstddef>
#include <iterator>

namespace ft
{
	// tags for iterator_traits
	#if defined(_LIBCPP_ITERATOR) || defined(_STL_ITERATOR_H)

	typedef std::input_iterator_tag input_iterator_tag;
	typedef std::output_iterator_tag output_iterator_tag;
	typedef std::forward_iterator_tag forward_iterator_tag;
	typedef std::bidirectional_iterator_tag bidirectional_iterator_tag;
	typedef std::random_access_iterator_tag random_access_iterator_tag;

	#else  // !defined(_LIBCPP_ITERATOR) && !defined(_STL_ITERATOR_H)
	// iterator_tag
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};
	#endif  // defined(_LIBCPP_ITERATOR) || defined(_STL_ITERATOR_H)

	// iterator를 위한 iterator_traits
	template <typename Iter>
	struct iterator_traits
	{
		typedef typename Iter::iterator_category iterator_category;
		typedef typename Iter::value_type value_type;
		typedef typename Iter::difference_type difference_type;
		typedef difference_type distance_type;
		typedef typename Iter::pointer pointer;
		typedef typename Iter::reference reference;
	};

	// vector_iterator를 위한 iterator_traits
	// random_access_iterator의 경우 표준 라이브러리에 반복기 유형이 지정되어 있지않아,
	// 일반적으로 특수화를 진행한다
	template <typename Ty>
	struct iterator_traits<Ty*>
	{
		typedef random_access_iterator_tag iterator_category;
		typedef Ty value_type;
		typedef ptrdiff_t difference_type;
		typedef ptrdiff_t distance_type;
		typedef Ty* pointer;
		typedef Ty& reference;
	};

}

#endif
