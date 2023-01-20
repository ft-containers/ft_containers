#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

namespace ft
{
	// iterator_tag
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : input_iterator_tag {};
	struct bidirectional_iterator_tag : forward_iterator_tag {};
	struct random_access_iterator_tag : bidirectional_iterator_tag {};

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

	// pointer를 위한 iterator_traits
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
};

#endif
