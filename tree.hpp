#ifndef TREE_HPP
#define TREE_HPP

#include <memory>
#include "map_iterator.hpp"

#include <iostream>

namespace ft
{
	template <typename Val>
	struct tree_node 
	{
		Val			pair_data_;
		tree_node*	parent_;
		tree_node*	left_;
		tree_node*	right_;
		size_t		height_;

	public:
		tree_node(): pair_data_() {};
		tree_node(Val p): pair_data_(p) {};
	};

	template <typename Val, typename Compare, typename Allocator>
	class tree
	{
	public:
		// typedef all template parameters
		typedef Val					value_type;
		typedef Compare				key_compare;
		typedef Allocator			allocator_type;

	private:
		// typedef member Types of Nodes / typedef of tree_node
		typedef typename allocator_type::template rebind<tree_node<Val> >::other	allocator_node;
		typedef typename allocator_node::reference									node_reference;
		typedef typename allocator_node::const_reference							node_const_reference;
		typedef typename allocator_node::difference_type							node_difference_type;
		typedef typename allocator_node::pointer									node_pointer;
		typedef typename allocator_node::const_pointer								node_const_pointer;
		typedef typename allocator_node::size_type									node_size_type;
		// 테스터로 다 완성 해보고 잘 되면 node_type_pointer->node_type으로 바꿔버리기
		// 위의 node_pointer와 동일
		typedef tree_node<value_type>												node_type;
		typedef node_type*															node_type_pointer;

	public:
		// typedef member Types of Tree iterator / typedef of Allocator = pair<>
		typedef typename allocator_type::reference					reference;
		typedef typename allocator_type::const_reference			const_reference;
		typedef typename allocator_type::difference_type			difference_type;
		typedef typename allocator_type::pointer					pointer;
		typedef typename allocator_type::const_pointer				const_pointer;
		typedef typename allocator_type::size_type					size_type;
		typedef typename value_type::first_type						key_type;
		typedef typename value_type::second_type					mapped_type;
		typedef ft::map_iterator<pointer, node_type_pointer>		iterator;
		typedef ft::map_iterator<const_pointer, node_type_pointer>	const_iterator;
		typedef ft::reverse_iterator<iterator>						reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;

	private:
		////
		template <typename Com>
		bool set_comp_factor()
		{
			typedef typename Com::first_argument_type	first_argument_type;
			typedef typename Com::second_argument_type	second_argument_type;
			typedef typename Com::result_type			result_type;
			if (typeid(result_type) == typeid(bool))
				return (true);
			else
				return (false);
		}

		// Declare all attributes needed in Tree
		allocator_node		alloc_;
		Compare				comp_;
		node_type_pointer	root_;
		node_type_pointer	end_;
		int					size_;
		bool				comp_factor;

	public:
		tree(const Compare &compare = Compare(), const allocator_type& alloc = allocator_type())
			: comp_(compare), size_(0)
		{
			comp_factor = set_comp_factor<Compare>();
			this->alloc_ = alloc;
			this->end_ = this->_make_node(value_type());
			this->root_ = this->end_;
		};
		//
		~tree()
		{
			this->clear();
			this->alloc_.destroy(end_);
			this->alloc_.deallocate(end_, 1);
		};

		// Iterators
		iterator		begin()					{ return (iterator(get_min())); };
		const_iterator	begin() const			{ return (const_iterator(get_min())); };
		iterator		end()					{ return (iterator(this->end_)); };
		const_iterator	end() const				{ return (const_iterator(this->end_)); };
		reverse_iterator rbegin()				{ return (reverse_iterator(end())); };
		const_reverse_iterator rbegin() const	{ return (const_reverse_iterator(end())); };
		reverse_iterator rend()					{ return (reverse_iterator(begin())); };
		const_reverse_iterator rend() const		{ return (const_reverse_iterator(begin())); };
	
		// Capacity
		bool		empty() const 		{ return (this->size_ == 0); };
		size_type 	size() const		{ return (this->size_); };
		size_type 	max_size() const	//min's parameter 어떤 의미인지 알기!
		{ return (std::min<size_type>(std::numeric_limits<size_type>::max() / sizeof(node_type_pointer), \
										std::numeric_limits<difference_type>::max())); };

	private:
		// private func
		node_type_pointer _make_node(value_type key)
		{
			node_type_pointer newnode = this->alloc_.allocate(1);
			this->alloc_.construct(newnode, key);
			newnode->height_ = 1;
			newnode->parent_ = NULL;
			newnode->left_ = NULL;
			newnode->right_ = NULL;
			return (newnode);
		};

		void _delete_node(node_type_pointer* node)
		{
			this->alloc_.destroy(*node);
			this->alloc_.deallocate(*node, 1);
			*node = NULL;
		};

		// exterminate subtree under the node
		void	_destroy(node_type_pointer node)
		{
			if (node != NULL)
			{
				_destroy(node->left_);
				_destroy(node->right_);
				_delete_node(&node);
			}
		};

		int	_height(node_type_pointer temp)
		{
			if (temp == NULL)
				return (0);
			return (temp->height_);
		};

		int _get_balance_factor(node_type_pointer n)
		{
			if (n == NULL)
				return 0;
			return (_height(n->left_) - _height(n->right_));
		}

		// rebalance
		node_type_pointer _left_rotate(node_type_pointer x)
		{
			node_type_pointer y = x->right_;
			node_type_pointer T2 = y->left_;
			node_type_pointer p = x->parent_;
			y->left_ = x;
			x->right_ = T2;
			if (p != this->end_)
			{
				if (p->left_ == x)
					p->left_ = y;
				else
					p->right_ = y;
			}
			y->parent_ = x->parent_;
			x->parent_ = y;
			if (T2 != NULL)
				T2->parent_ = x;
			x->height_ = std::max(_height(x->left_), _height(x->right_)) + 1;
			y->height_ = std::max(_height(y->left_), _height(y->right_)) + 1;
			return y;
		};

		node_type_pointer _right_rotate(node_type_pointer x)
		{
			node_type_pointer y = x->left_;
			node_type_pointer T2 = y->right_;
			node_type_pointer p = x->parent_;
			y->right_ = x;
			x->left_ = T2;
			if (p != this->end_)
			{
				if (p->right_ == x)
					p->right_ = y;
				else
					p->left_ = y;
			}
			y->parent_ = x->parent_;
			x->parent_ = y;
			if (T2 != NULL)
				T2->parent_ = x;
			x->height_ = std::max(_height(x->left_), _height(x->right_)) + 1;
			y->height_ = std::max(_height(y->left_), _height(y->right_)) + 1;
			return y;
		};

		node_type_pointer _right_left_rotate(node_type_pointer node)
		{
			node->right_ = _right_rotate(node->right_);
			return (_left_rotate(node));
		};

		node_type_pointer _left_right_rotate(node_type_pointer node)
		{
			node->left_ = _left_rotate(node->left_);
			return (_right_rotate(node));
		};

		node_type_pointer	_re_balance(node_type_pointer node)
		{
			int	balance_factor = _get_balance_factor(node);
			if (balance_factor > 1)
			{
				if (_get_balance_factor(node->left_) >= 0)
					return (_right_rotate(node));
				else
					return (_left_right_rotate(node));
			}
			else if (balance_factor < -1)
			{
				if (_get_balance_factor(node->right_) <= 0)
					return (_left_rotate(node));
				else
					return (_right_left_rotate(node));
			}
			return (node);
		};
		
		void _reset_height(node_type_pointer temp)
		{
			if (!temp->left_ && !temp->right_)
				temp->height_ = 1;
			else if (temp->left_ == NULL)
				temp->height_ = 1 + temp->right_->height_;
			else if (temp->right_ == NULL /* || temp->right_ == this->end_ */)
				temp->height_ = 1 + temp->left_->height_;
			else
				temp->height_ = 1 + std::max(temp->right_->height_, temp->left_->height_);
		};

		node_type_pointer _insert(node_type_pointer temp, node_type_pointer new_node)
		{
			if (temp == NULL || temp == this->end_)
				return (new_node);
			if (!this->comp_(temp->pair_data_.first, new_node->pair_data_.first)
				|| comp_factor == false)
			{
				temp->left_ = _insert(temp->left_, new_node);
				if (temp->left_ == new_node)
					new_node->parent_ = temp;
			}
			else if (this->comp_(temp->pair_data_.first, new_node->pair_data_.first))
			{
				temp->right_ = _insert(temp->right_, new_node);
				if (temp->right_ == new_node)
					new_node->parent_ = temp;
			}
			else
				return (temp);
			_reset_height(temp);
			temp = _re_balance(temp);
			return (temp);
		};

		node_type_pointer	_remove(node_type_pointer root, Val key)
		{
			if (root == NULL)
				return (NULL);
			else if (this->comp_(key.first, root->pair_data_.first))
				root->left_ = _remove(root->left_, key);
			else if (this->comp_(root->pair_data_.first, key.first))
				root->right_ = _remove(root->right_, key);
			else
			{
				if (root->left_ == NULL && root->right_ == NULL)
				{
					_delete_node(&root);
					--size_;
					return (root);
				}
				else if (root->left_ == NULL)
				{
					node_type_pointer	old_root = root;
					root = old_root->right_;
					root->parent_ = old_root->parent_;
					if (old_root == old_root->parent_->left_)
						old_root->parent_->left_ = root;
					else
						old_root->parent_->right_ = root;
					_delete_node(&old_root);
					--size_;
					return (root);
				}
				else if (root->right_ == NULL)
				{
					node_type_pointer	old_root = root;
					root = old_root->left_;
					root->parent_ = old_root->parent_;
					if (old_root == old_root->parent_->left_)
						old_root->parent_->left_ = root;
					else
						old_root->parent_->right_ = root;
					_delete_node(&old_root);
					--size_;
					return (root);
				}
				else
				{
					node_type_pointer temp = _tree_min(root->right_);
					value_type p = temp->pair_data_;
					root->right_ = _remove(root->right_ , temp->pair_data_);
					this->alloc_.construct(root, p);
				}
			}
			_reset_height(root);
			root = _re_balance(root);
			return (root);
		};

		node_type_pointer _search(node_type_pointer temp, key_type key) const
		{
			if (temp == NULL)
				return (this->end_);
			if (temp->pair_data_.first == key)
				return (temp);
			else if (this->comp_(key, temp->pair_data_.first))
				return (_search(temp->left_, key));
			else if (this->comp_(temp->pair_data_.first, key))
				return (_search(temp->right_, key));

			return (this->end_);
		};

	public:
		node_type_pointer	insert(value_type key)
		{
			node_type_pointer newnode = _make_node(key);
			if (this->root_ == this->end_)
			{
				this->root_ = newnode;
				this->root_->parent_ = this->end_;
				this->end_->left_ = this->root_;
				++this->size_;
			}
			else
			{
				++this->size_;
				this->root_ = _insert(this->root_, newnode);
				this->end_->left_ = this->root_; // end_ 추가
			}
			return (newnode);
		};

		void	remove(Val key)
		{
			this->root_ = _remove(this->root_, key);
			this->end_->left_ = root_; // end_ 추가
			if (this->size() == 0)
				this->root_ = this->end_;
		};

		void	swap(tree &x)
		{
			size_type tmp_size = x.size_;
			allocator_type tmp_alloc = x.alloc_;
			node_type_pointer tmp_root = x.root_;
			node_type_pointer tmp_end = x.end_;

			x.size_ = this->size_;
			this->size_ = tmp_size;

			x.alloc_ = this->alloc_;
			this->alloc_ = tmp_alloc;

			x.end_ = this->end_;
			this->end_ = tmp_end;

			x.root_ = this->root_;
			this->root_ = tmp_root;
		};

		node_type_pointer lower_bound(key_type val) const
		{
			node_type_pointer node = get_min();

			while (!this->comp_(val, node->pair_data_.first))
			{
				if (val == node->pair_data_.first)
					break;
				node = successor(node);
				if (node == NULL || node == this->end_)
					return (this->end_);
			}
			return (node);
		};

		node_type_pointer upper_bound(key_type val) const
		{
			node_type_pointer node = get_min();

			while (!this->comp_(val, node->pair_data_.first))
			{
				node = successor(node);
				if (node == NULL || node == this->end_)
					return (this->end_);
			}
			return (node);
		};

		void	clear()
		{
			if (this->root_ != this->end_)
			{
				_destroy(this->root_);
				this->size_ = 0;
				this->root_ = this->end_;
				this->end_->left_ = this->root_;
			}
		};

		node_type_pointer	get_min() const
		{
			node_type_pointer tmp = this->root_;

			while (tmp != this->end_ && tmp->left_)
				tmp = tmp->left_;
			return (tmp);
		};
		
		node_type_pointer	get_max() const
		{
			node_type_pointer tmp = this->root_;

			while (tmp->right_ && tmp->right_ != this->end_)
				tmp = tmp->right_;
			return (tmp);
		};

		node_type_pointer search(key_type key) const
		{
			if (this->root_ == this->end_)
				return (this->end_);
			else
				return (_search(this->root_, key));
		};
	};

	template<typename node_type_pointer>
	node_type_pointer _tree_min(node_type_pointer temp)
	{
		while (temp->left_ != NULL)
			temp = temp->left_;
		return (temp);
	};

	template<typename node_type_pointer>
	node_type_pointer _tree_max(node_type_pointer temp)
	{
		while (temp->right_ != NULL)
		{
			temp = temp->right_;
		}
		return (temp);
	};

	template<class node_type_pointer>
	node_type_pointer successor(node_type_pointer node)
	{
		if (node->right_)
			return (_tree_min(node->right_));

		node_type_pointer temp = node->parent_;
		while (temp && temp->right_ == node)
		{
			node = temp;
			temp = temp->parent_;
		}
		return (temp);
	};

//cchu ver for us
	// template<class node_type_pointer>
	// node_type_pointer predecessor(node_type_pointer node)
	// {
	// 	if (node->left_)
	// 		return (_tree_max(node->left_));
	// 	node_type_pointer temp;
	// 	// do
	// 	// {
	// 	// 	temp = node;
	// 	// 	node = node->parent_;
	// 	// } while (node && temp == node->left_);
	// 	// return (node);
	// 	while (temp && temp->left_ == node)
	// 	{
	// 		node = temp;
	// 		temp = temp->parent_;
	// 	}
	// 	if (temp == NULL)
	// 		return (node);
	// 	return (temp);
	// };

	template<class node_type_pointer>
	node_type_pointer predecessor(node_type_pointer node)
	{
		if (node->left_)
			return (_tree_max(node->left_));

		node_type_pointer temp = node->parent_;
		while (temp && temp->left_ == node)
		{
			node = temp;
			temp = temp->parent_;
		}
		if (temp == NULL)
			return (node);
		return (temp);
	};

//cchu
		// _Self &operator--()
		// {
		// 	if (_n->left)
		// 	{
		// 		_n = _n->left;
		// 		while (_n && _n->right)
		// 			_n = _n->right;
		// 	}
		// 	else
		// 	{
		// 		_node *tmp;
		// 		do
		// 		{
		// 			tmp = _n;
		// 			_n = _n->parent;
		// 		} while (_n && tmp == _n->left);
		// 	}
		// 	return *this;
		// }

}
#endif
