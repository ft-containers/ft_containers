#ifndef MAP_HPP
#define MAP_HPP

// #include <__config>
// #include <__tree>
// #include <__node_handle>
// #include <iterator>
#include <memory>
// #include <utility>
#include <functional> //less
#include "algorithm.hpp"
#include "utility.hpp"
#include "tree.hpp"
#include "reverse_iterator.hpp"
// #include <initializer_list>
// #include <type_traits>
// #include <version>

namespace ft
{
	template <typename Key, typename Tp, typename Compare = std::less<Key>,
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
		typedef typename tree_type::iterator					iterator;
		typedef typename tree_type::const_iterator				const_iterator;
		typedef ft::reverse_iterator<iterator>					reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
	

	//why? //because of relational operators or swap ?
	// template <class _Key2, class _Value2, class _Comp2, class _Alloc2>
	// friend class  map;
	
	public:
		// constructor
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
		
		// Iterators
		iterator				begin()			{ return (this->tree_.begin()); };
		const_iterator			begin() const	{ return (this->tree_.begin()); };
		iterator				end()			{ return (this->tree_.end()); };
		const_iterator			end() const		{ return (this->tree_.end()); };
		reverse_iterator		rbegin()		{ return (this->tree_.rbegin()); };
		const_reverse_iterator	rbegin() const	{ return (this->tree_.rbegin()); };
		reverse_iterator		rend()			{ return (this->tree_.rend()); };
		const_reverse_iterator	rend() const	{ return (this->tree_.rend()); };

		// Capacity
		bool		empty() const		{ return (this->tree_.empty()); };
		size_type	size() const		{ return (this->tree_.size()); };
		size_type	max_size() const	{ return (this->tree_.max_size()); };

		// Element access
		mapped_type& operator[] (const key_type& k)
		{ return ((*(insert(ft::make_pair(k, mapped_type())).first)).second); };

		// Modifiers
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

		template <typename InputIterator>
		void insert (InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				this->tree_.insert(*first);
				first++;
			};
		};

		void erase (iterator position)
		{ this->tree_.remove(*position); };
		
		size_type erase (const key_type& k)
		{
			size_type s = size();
			this->tree_.remove(*find(k));
			return (s - size());
		};
		
		void erase (iterator first, iterator last)
		{
			iterator position;
			while(first != last)
			{
				position = first;
				first++;
				erase(position);
			}
		};

		void swap (map& x) { this->tree_.swap(x.tree_); };
		
		void clear() { this->tree_.clear(); };
	
		// Observers
		key_compare		key_comp() const	{ return (this->comp_); };
		value_compare	value_comp() const	{ return (value_compare(this->comp_)); };

		// Opeations
		iterator find (const key_type& k)
		{ return (iterator(this->tree_.search(k))); };
		
		const_iterator find (const key_type& k) const
		{ return (const_iterator(this->tree_.search(k))); };

		size_type count (const key_type& k) const
		{ return (this->find(k) != this->end() ? 1 : 0); };
		
		iterator lower_bound (const key_type& k)
		{ return (iterator(this->tree_.lower_bound(k))); };
		
		const_iterator lower_bound (const key_type& k) const
		{ return (const_iterator(this->tree_.lower_bound(k))); };
		
		iterator upper_bound (const key_type& k)
		{ return (iterator(this->tree_.upper_bound(k))); };
		
		const_iterator upper_bound (const key_type& k) const
		{ return (const_iterator(this->tree_.upper_bound(k))); };
		
		pair<const_iterator, const_iterator> equal_range (const key_type &k) const
		{ return (ft::make_pair(this->lower_bound(k), this->upper_bound(k))); };
		
		pair<iterator, iterator> equal_range (const key_type &k)
		{ return (ft::make_pair(this->lower_bound(k), this->upper_bound(k))); };

		// Allocator: get_allocator
		allocator_type get_allocator() const 
		{ return (allocator_type()); };
	
	};
	//non-member functions
	
	// relational operators
	template <typename Key, typename T, typename Compare, typename Alloc>
	bool operator== (const map<Key,T,Compare,Alloc>& x, const map<Key,T,Compare,Alloc>& y)
	{ return ((x.size() == y.size()) && ft::equal(x.begin(), x.end(), y.begin()));};
	
	template <typename Key, typename T, typename Compare, typename Alloc>
	bool operator!= (const map<Key,T,Compare,Alloc>& x, const map<Key,T,Compare,Alloc>& y)
	{ return (!(x == y));};
	
	template <typename Key, typename T, typename Compare, typename Alloc>
	bool operator<  (const map<Key,T,Compare,Alloc>& x, const map<Key,T,Compare,Alloc>& y)
	{ return (ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()));};
	
	template <typename Key, typename T, typename Compare, typename Alloc>
	bool operator<= (const map<Key,T,Compare,Alloc>& x, const map<Key,T,Compare,Alloc>& y)
	{ return (!(y < x));};
	
	template <typename Key, typename T, typename Compare, typename Alloc>
	bool operator>  (const map<Key,T,Compare,Alloc>& x, const map<Key,T,Compare,Alloc>& y)
	{ return (ft::lexicographical_compare(y.begin(), y.end(), x.begin(), x.end()));};
	
	template <typename Key, typename T, typename Compare, typename Alloc>
	bool operator>= (const map<Key,T,Compare,Alloc>& x, const map<Key,T,Compare,Alloc>& y)
	{ return (!(x < y));};

	// swap
	template <typename Key, typename T, typename Compare, typename Alloc>
	void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y) { x.swap(y); };

};

#endif
