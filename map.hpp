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
#include "tree.hpp"
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
		typedef Key																key_type;
		typedef Tp																mapped_type;
		typedef pair<const key_type, mapped_type>								value_type;
		typedef typename identity<Compare>::type								key_compare;
		//value_compare is a class below
		typedef typename identity<Allocator>::type								allocator_type;
		typedef value_type&														reference;
		typedef const value_type& 												const_reference;
		typedef typename allocator_type::pointer								pointer;
		typedef typename allocator_type::const_pointer							const_pointer;
		typedef ft::__map_iterator<typename tree_type::iterator>				iterator;
		typedef ft::__map_const_iterator<typename tree_type::const_iterator>	const_iterator;
		typedef ft::reverse_iterator<iterator>									reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>							const_reverse_iterator;
		typedef typename allocator_type::difference_type						difference_type;
		typedef typename allocator_type::size_type								size_type;

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
					{ return comp(x.first, y.first); }
		};

	private:
		typedef tree_node<value_type>							node_type;
		typedef node_type*										node_type_pointer;
		typedef tree<value_type, key_compare, allocator_type>	tree_type;
		typedef tree_type*										tree_type_pointer;

		tree_type		tree_;
		allocator_type	alloc_;
		key_compare		comp_;

	/*
	public:
		typedef typename Tree_type::iterator				iterator;
			typedef typename Tree_type::const_iterator			const_iterator;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
	*/

	//why?
	template <class _Key2, class _Value2, class _Comp2, class _Alloc2>
	friend class  map;
	
//todo list 


	// constructor
	public:
		explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
			_tree(comp, alloc), _alloc(alloc), _comp(comp) {};
		template <class InputIterator>
		map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
			_tree(comp, alloc), _alloc(alloc), _comp(comp) { insert(first, last); };
		map (const map& x) { *this = x; };

	// destructor

	// Iterators: begin end rbegin rend 

	// Capacity: empty size max_size

	// Element access: operator[] at

	// Modifiers: insert erase swap clear
	
	// Observers: key_comp value_comp

	// Operations: find count lower_bound upper_bound equal_range

	// Allocator: get_allocator
	};
};

#endif
