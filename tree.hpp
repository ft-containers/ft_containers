#ifndef TREE_HPP
#define TREE_HPP

#include <memory>

namespace ft
{
	template <typename _Val>
	struct tree_node 
	{
		_Val		pair_data_;
		tree_node*	parent_;
		tree_node*	left_;
		tree_node*	right_;
		size_type	height;
		
		public:
			tree_node(): pair_data_() {};
			tree_node(_Val p): pair_data_(p) {};
	};

	template <typename _Val, typename _Compare, typename _Alloc>
	class tree
	{
	public:
		typedef _Key				key_type;
		typedef _Val				value_type;
		typedef value_type			*pointer;
		typedef const value_type	*const_pointer;
		typedef value_type			&reference;
		typedef const value_type	&const_reference;
		typedef size_t				size_type;
		typedef ptrdiff_t			difference_type;
		typedef _Alloc				allocator_type;

		typedef ft::__tree_iterator<value_type>			iterator;
		typedef ft::__tree_const_iterator<value_type>	const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

	// typedef member Types of Nodes 
	private:
		typedef typename allocator_type::template rebind<tree_node<_Val> >::other	allocator_node;
		typedef typename allocator_node::reference									node_reference;
		typedef typename allocator_node::const_reference							node_const_reference;
		typedef typename allocator_node::difference_type							node_difference_type;
		typedef typename allocator_node::pointer									node_pointer;
		typedef typename allocator_node::const_pointer								node_const_pointer;
		typedef typename allocator_node::size_type									node_size_type;
		typedef tree_node<value_type>												node_type;
		typedef node_type*															node_type_pointer;

	// Declare all attributes needed in Tree
	private:
		allocator_node								_alloc;
		_Compare									_comp;
		node_type_pointer							_root;
		node_type_pointer							_end;
		int											_size;

	public:
		Tree(const _Compare &compare = _Compare(), const allocator_type& alloc = allocator_type())
			: _size(0), _comp(compare)
		{
			this->_alloc = alloc; // Y are u here? not in initializer?
			this->_end = this->_make_node(value_type());
			this->_root = this->_end;
		};
		~Tree() {};

	private:
		node_type_pointer _make_node(value_type key)
		{
			node_type_pointer newnode = this->_alloc.allocate(1);
			this->_alloc.construct(newnode, key);
			newnode->height = 1;
			newnode->parent = NULL;
			newnode->left = NULL;
			newnode->right = NULL;
			return (newnode);
		};

		void _delete_node(node_type_pointer* node)
		{
			this->_alloc.destroy(*node);
			this->_alloc.deallocate(*node, 1);
			*node = NULL;
		};
		
		// exterminate subtree under the node
		void	_destroy(node_type_pointer node)
		{
			if (node != NULL)
			{
				_destroy(node->left);
				_destroy(node->right);
				this->_alloc.destroy(node);
				this->_alloc.deallocate(node, 1);
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
			node_type_pointer y = x->right;
			node_type_pointer T2 = y->left;
			node_type_pointer p = x->parent;
			y->left = x;
			x->right = T2;
			if (p != this->_end)
			{
				if (p->left == x)
					p->left = y;
				else
					p->right = y;
			}
			y->parent = x->parent;
			x->parent = y;
			if (T2 != NULL)
				T2->parent = x;
			x->height = std::max(_height(x->left), _height(x->right)) + 1;
			y->height = std::max(_height(y->left), _height(y->right)) + 1;
			return y;
		};

		node_type_pointer _right_rotate(node_type_pointer x)
		{
			node_type_pointer y = x->left;
			node_type_pointer T2 = y->right;
			node_type_pointer p = x->parent;
			y->right = x;
			x->left = T2;
			if (p != this->_end)
			{
				if (p->right == x)
					p->right = y;
				else
					p->left = y;
			}
			y->parent = x->parent;
			x->parent = y;
			if (T2 != NULL)
				T2->parent = x;
			x->height = std::max(_height(x->left), _height(x->right)) + 1;
			y->height = std::max(_height(y->left), _height(y->right)) + 1;
			return y;
		};

		node_type_pointer _right_left_rotate(node_type_pointer node)
		{
			node->right = _rightRotate(node->right);
			return (_leftRotate(node));
		};

		node_type_pointer _left_right_rotate(node_type_pointer node)
		{
			node->left = _left_rotate(node->left);
			return (_right_rotate(node));
		};

		node_type_pointer	_re_balance(node_type_pointer node)
		{
			int	balance_factor = _get_balance_factor(node);
			if (balance_factor > 1)
			{
				if (_get_balance_factor(node->left) >= 0)
					return (_right_rotate(node));
				else
					return (_left_right_rotate(node));
			}
			else if (balance_factor < -1)
			{
				if (_get_balance_factor(node->right) <= 0)
					return (_left_rotate(node));
				else
					return (_right_left_rotate(node));
			}
			return (node);
		};
		
		void _reset_height(node_type_pointer temp)
		{
			if (!temp->left && !temp->right)
				temp->height = 1;
			else if (temp->left == NULL)
				temp->height = 1 + temp->right->height;
			else if (temp->right == NULL /* || temp->right == this->_end */)
				temp->height = 1 + temp->left->height;
			else
				temp->height = 1 + std::max(temp->right->height, temp->left->height);
		};

		node_type_pointer _insert(node_type_pointer temp, node_type_pointer new_node)
		{
			if (temp == NULL || temp == this->_end)
				return (new_node);
			if (!this->_comp(temp->key.first, new_node->key.first))
			{
				temp->left = _insert(temp->left, new_node);
				if (temp->left == new_node)
					new_node->parent = temp;
			}
			else if (this->_comp(temp->key.first, new_node->key.first))
			{
				temp->right = _insert(temp->right, new_node);
				if (temp->right == new_node)
					new_node->parent = temp;
			}
			else
				return (temp);
			_reset_height(temp);
			temp = _re_balance(temp);
			return (temp);
		};

		node_type_pointer	_remove(node_type_pointer root, T key)
		{
			if (root == NULL)
				return (NULL);
			else if (this->_comp(key.first, root->key.first))
				root->left = _remove(root->left, key);
			else if (this->_comp(root->key.first, key.first))
				root->right = _remove(root->right, key);
			else
			{
				if (root->left == NULL && root->right == NULL)
				{
					this->_alloc.destroy(root);
					this->_alloc.deallocate(root, 1);
					root = NULL;
					return (root);
				}
				else if (root->left == NULL)
				{
					node_type_pointer	temp = root;
					root = root->right;
					root->parent = temp->parent;
					this->_alloc.destroy(temp);
					this->_alloc.deallocate(temp, 1);
					temp = NULL;
					return (root);
				}
				else if (root->right == NULL)
				{
					node_type_pointer	temp = root;
					root = root->left;
					root->parent = temp->parent;
					this->_alloc.destroy(temp);
					this->_alloc.deallocate(temp, 1);
					temp = NULL;
					return (root);
				}
				else
				{
					node_type_pointer temp = _tree_min(root->right);
					value_type p = temp->key;
					root->right = _remove(root->right , temp->key);
					this->_alloc.construct(root, p);
				}
			}
			_reset_height(root);
			root = _re_balance(root);
			return (root);
		};

		node_type_pointer _search(node_type_pointer temp, key_type key) const
		{
			if (temp == NULL)
				return (this->_end);
			if (temp->key.first == key)
				return (temp);
			else if (this->_comp(key, temp->key.first))
				return (_search(temp->left, key));
			else if (this->_comp(temp->key.first, key))
				return (_search(temp->right, key));

			return (this->_end);
		};

	public:
		node_type_pointer	insert(value_type key)
		{
			node_type_pointer newnode = _makeNode(key);
			if (this->_root == this->_end)
			{
				this->_root = newnode;
				this->_root->parent = this->_end;
				this->_end->left = this->_root;
				++this->_size;
			}
			else
			{
				++this->_size;
				this->_root = _insert(this->_root, newnode);
			}
			return (newnode);
		};

		// why 필요? -> 원하는 위치에 원소 삽입을 위해?
		// Node_ptr	insertInPossition(Node_ptr position, T key)
		// {
		// 	Node_ptr newnode = _makeNode(key);
		// 	if (position == this->_end)
		// 	{
		// 		position = newnode;
		// 		position->parent = this->_end;
		// 		this->_end->left = position;
		// 		++this->_size;
		// 	}
		// 	else
		// 	{
		// 		++this->_size;
		// 		position = _insert(position, newnode);
		// 	}
		// 	return (newnode);
		// };

		void	remove(T key)
		{
			this->_root =  _remove(this->_root, key);
		};
		
		void	clear()
		{
			if (this->_root != this->_end)
			{
				_destroy(this->_root);
				this->_size = 0;
				this->_root = this->_end;
				this->_end->left = this->_root;
			}
		};
	};

	template<typename node_type_pointer>
	node_type_pointer _tree_min(node_type_pointer temp)
	{
		while (temp->left != NULL)
			temp = temp->left;
		return (temp);
	};

	template<typename node_type_pointer>
	node_type_pointer _tree_max(node_type_pointer temp)
	{
		while (temp->right != NULL)
			temp = temp->right;
		return (temp);
	};
}
#endif
