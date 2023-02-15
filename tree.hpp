#ifndef TREE_HPP
#define TREE_HPP

#include <memory>
#include "map_iterator.hpp"

namespace ft
{
	template <typename Val>
	struct tree_node 
	{
		Val			pair_data_;
		tree_node*	parent_;
		tree_node*	left_;
		tree_node*	right_;
		size_t		height;

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
		// typedef member Types of Nodes 
		typedef typename allocator_type::template rebind<tree_node<Val> >::other	allocator_node;
		typedef typename allocator_node::reference									node_reference;
		typedef typename allocator_node::const_reference							node_const_reference;
		typedef typename allocator_node::difference_type							node_difference_type;
		typedef typename allocator_node::pointer									node_pointer;
		typedef typename allocator_node::const_pointer								node_const_pointer;
		typedef typename allocator_node::size_type									node_size_type;
		typedef tree_node<value_type>												node_type;
		typedef node_type*															node_type_pointer;

	public:
		// typedef member Types of Tree iterator
		typedef typename allocator_type::reference						reference;
		typedef typename allocator_type::const_reference				const_reference;
		typedef typename allocator_type::difference_type				difference_type;
		typedef typename allocator_type::pointer						pointer;
		typedef typename allocator_type::const_pointer					const_pointer;
		typedef typename allocator_type::size_type						size_type;
		typedef typename value_type::first_type							key_type;
		typedef typename value_type::second_type						mapped_type;
		typedef ft::map_iterator<pointer, node_type_pointer>			iterator;
		typedef ft::map_iterator<const_pointer, node_type_pointer>		const_iterator;
		typedef ft::reverse_iterator<iterator>							reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;

	private:
		// Declare all attributes needed in Tree
		allocator_node		alloc_;
		Compare				comp_;
		node_type_pointer	root_;
		node_type_pointer	end_;
		int					size_;

	public:
		tree(const Compare &compare = Compare(), const allocator_type& alloc = allocator_type())
			: size_(0), comp_(compare)
		{
			this->alloc_ = alloc;
			this->end_ = this->_make_node(value_type());
			this->root_ = this->end_;
		};
		~tree() {};

	private:
		node_type_pointer _make_node(value_type key)
		{
			node_type_pointer newnode = this->alloc_.allocate(1);
			this->alloc_.construct(newnode, key);
			newnode->height = 1;
			newnode->parent = NULL;
			newnode->left = NULL;
			newnode->right = NULL;
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
				_destroy(node->left);
				_destroy(node->right);
				this->alloc_.destroy(node);
				this->alloc_.deallocate(node, 1);
			}
		};

		int	_height(node_type_pointer temp)
		{
			if (temp == NULL)
				return (0);
			return (temp->height);
		};

		int _get_balance_factor(node_type_pointer n)
		{
			if (n == NULL)
				return 0;
			return (_height(n->left) - _height(n->right));
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
			x->left = T2;
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
				T2->parent = x;
			x->height_ = std::max(_height(x->left_), _height(x->right_)) + 1;
			y->height_ = std::max(_height(y->left_), _height(y->right_)) + 1;
			return y;
		};

		node_type_pointer _right_left_rotate(node_type_pointer node)
		{
			node->right_ = _rightRotate(node->right_);
			return (_leftRotate(node));
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
				temp->height = 1;
			else if (temp->left_ == NULL)
				temp->height = 1 + temp->right_->height;
			else if (temp->right_ == NULL /* || temp->right_ == this->end_ */)
				temp->height = 1 + temp->left_->height;
			else
				temp->height = 1 + std::max(temp->right_->height, temp->left_->height);
		};

		node_type_pointer _insert(node_type_pointer temp, node_type_pointer new_node)
		{
			if (temp == NULL || temp == this->end_)
				return (new_node);
			if (!this->comp_(temp->key.first, new_node->key.first))
			{
				temp->left_ = _insert(temp->left_, new_node);
				if (temp->left_ == new_node)
					new_node->parent_ = temp;
			}
			else if (this->comp_(temp->key.first, new_node->key.first))
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
			else if (this->comp_(key.first, root->key.first))
				root->left_ = _remove(root->left_, key);
			else if (this->comp_(root->key.first, key.first))
				root->right_ = _remove(root->right_, key);
			else
			{
				if (root->left == NULL && root->right == NULL)
				{
					this->alloc_.destroy(root);
					this->alloc_.deallocate(root, 1);
					root = NULL;
					return (root);
				}
				else if (root->left == NULL)
				{
					node_type_pointer	temp = root;
					root = root->right_;
					root->parent_ = temp->parent_;
					this->alloc_.destroy(temp);
					this->alloc_.deallocate(temp, 1);
					temp = NULL;
					return (root);
				}
				else if (root->right_ == NULL)
				{
					node_type_pointer	temp = root;
					root = root->left_;
					root->parent_ = temp->parent_;
					this->alloc_.destroy(temp);
					this->alloc_.deallocate(temp, 1);
					temp = NULL;
					return (root);
				}
				else
				{
					node_type_pointer temp = _tree_min(root->right_);
					value_type p = temp->key;
					root->right_ = _remove(root->right_ , temp->key);
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
			if (temp->key.first == key)
				return (temp);
			else if (this->comp_(key, temp->key.first))
				return (_search(temp->left_, key));
			else if (this->comp_(temp->key.first, key))
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
			}
			return (newnode);
		};

		// why 필요? -> 원하는 위치에 원소 삽입을 위해?
		// 그리면서 내일(2월 16일) 다시 해보기
		node_type_pointer	insert_in_position(node_type_pointer position, Val key)
		{
			node_type_pointer newnode = _make_node(key);
			if (position == this->end_)
			{
				position = newnode;
				position->parent_ = this->end_;
				this->end_->left_ = position;
				++this->size_;
			}
			else
			{
				++this->size_;
				position = _insert(position, newnode);
			}
			return (newnode);
		};

		void	remove(Val key)
		{
			this->root_ = _remove(this->root_, key);
		};
		
		void	clear()
		{
			if (this->root_ != this->end_)
			{
				_destroy(this->root_);
				this->sie_ = 0;
				this->root_ = this->end_;
				this->end_->left_ = this->roozt_;
			}
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
			temp = temp->right_;
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
}
#endif
