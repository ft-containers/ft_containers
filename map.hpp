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
#include "reverse_iterator.hpp"
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
		typedef Key															key_type;
		typedef Tp															mapped_type;
		typedef ft::pair<const key_type, mapped_type>						value_type;
		typedef Compare														key_compare;
		//value_compare is a class below
		typedef Allocator													allocator_type;
		typedef typename allocator_type::reference							reference;
		typedef typename allocator_type::const_reference 					const_reference;
		typedef typename allocator_type::pointer							pointer;
		typedef typename allocator_type::const_pointer						const_pointer;
		typedef typename allocator_type::difference_type					difference_type;
		typedef typename allocator_type::size_type							size_type;

		// value_compare class
		class value_compare
			: public std::binary_function<value_type, value_type, bool>
		{
			// friend class map; //need?

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

	public:
		typedef typename tree_type::iterator									iterator;
		// typedef typename tree_type::const_iterator								const_iterator;
		typedef ft::reverse_iterator<iterator>									reverse_iterator;
		// typedef ft::reverse_iterator<const_iterator>							const_reverse_iterator;
	

	//why? //because of relational operators or swap ?
	// template <class _Key2, class _Value2, class _Comp2, class _Alloc2>
	// friend class  map;
	
	
//todo list
	// constructor
	public:
		explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
			tree_(comp, alloc), alloc_(alloc), comp_(comp) {};
		template <class InputIterator>
		map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
			tree_(comp, alloc), alloc_(alloc), comp_(comp) { insert(first, last); };
		map (const map& x) { *this = x; };

	// destructor
		~map() { this->tree_.clear(); };
	// operator=
		map& operator= (const map& x)
		{
			if (this != &x)
			{
				this->tree_.clear();
				this->comp_ = x.comp_;
				this->alloc_ = x.alloc_;
				insert(x.begin(), x.end());
			}
			return (*this);
		};
		
	// Iterators: begin end rbegin rend 

	// Capacity: empty size max_size

	// Element access: operator[]

	// Modifiers: insert erase swap clear
		
		ft::pair<iterator,bool> insert (const value_type& val)
		{
			iterator node = iterator(this->tree_.search(val.first));
			if (node != end())
				return (ft::pair<iterator, bool>(node, false));

			node_type_pointer inserted_node = this->tree_.insert(val);
			return (ft::pair<iterator,bool>(iterator(inserted_node), true));
		};

		iterator insert (iterator position, const value_type& val)
		{
			node_type_pointer node = position.base();
			if (val.first > predecessor(node)->pair_data_.first && val.first < successor(node)->pair_data_.first)
				position = iterator(this->tree_.insert_in_position(node, val));
			else
				position = insert(val).first;
			return (position);
		};

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				this->tree_.insert(*first);
				first++;
			};
		};
	
	// Observers: key_comp value_comp

	// Operations: find count lower_bound upper_bound equal_range

	// Allocator: get_allocator
	};
};

#endif
