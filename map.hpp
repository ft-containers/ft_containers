#ifndef MAP_HPP
#define MAP_HPP

// #include <__config>
// #include <__tree>
// #include <__node_handle>
// #include <iterator>
#include <memory>
// #include <utility>
#include <functional> //less
#include "utility.hpp"
// #include <initializer_list>
// #include <type_traits>
// #include <version>

namespace ft
{
	template <class Key, class Tp, class Compare = std::less<Key>,
		class Allocator = std::allocator<ft::pair<const Key, Tp> > >
	class map
	{
	public:
		typedef Key										key_type;
		typedef Tp										mapped_type;
		typedef pair<const key_type, mapped_type>		value_type;
		typedef typename identity<Compare>::type		key_compare;
		typedef typename identity<Allocator>::type		allocator_type;
		typedef value_type&								reference;
		typedef const value_type& 						const_reference;

	// value_compare class
	class value_compare
		: public binary_function<value_type, value_type, bool>
	{
		friend class map;
		protected:
			key_compare comp;
			value_compare(key_compare c) : comp(c) {}
		public:
			bool operator()(const value_type& x, const value_type& y) const
				{return comp(x.first, y.first);}
	};

	// 아직 뭔지 몰라서 손 안댐. 필요하면 주석맨 풀기
	// private:
	// 	typedef std::__value_type<key_type, mapped_type>			__value_type;
	// 	typedef __map_value_compare<key_type, __value_type, key_compare>	__vc;
	// 	typedef typename __rebind_alloc_helper<allocator_traits<allocator_type>,
	// 												__value_type>::type __allocator_type;
		typedef __tree<__value_type, __vc, __allocator_type>	__base;
	// 	typedef typename __base::__node_traits					__node_traits;
	// 	// typedef allocator_traits<allocator_type>				__alloc_traits;

	__base __tree_;

	// yongju
// 	 private:
//   typedef __tree<key_type, value_type, ft::select_first<value_type>,
//                  key_compare, allocator_type>
//       __base;

	public:
		typedef typename allocator_type::pointer						pointer;
		typedef typename allocator_type::const_pointer					const_pointer;
		typedef typename allocator_type::size_type						size_type;
		typedef typename allocator_type::difference_type				difference_type;
		typedef ft::__map_iterator<typename __base::iterator>				iterator;
		typedef ft::__map_const_iterator<typename __base::const_iterator>	const_iterator;
		typedef ft::reverse_iterator<iterator>							reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;

	//why?
	template <class _Key2, class _Value2, class _Comp2, class _Alloc2>
	friend class  map;

	};
};
#endif
