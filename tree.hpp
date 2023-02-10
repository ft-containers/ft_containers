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
		typedef _Key					key_type;
		typedef _Val					value_type;
		typedef value_type				*pointer;
		typedef const value_type		*const_pointer;
		typedef value_type				&reference;
		typedef const value_type		&const_reference;
		typedef size_t					size_type;
		typedef ptrdiff_t				difference_type;
		typedef _Alloc					allocator_type;

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

		node_type_pointer _right_rotate(node_type_pointer parent)
		{
			node_type_pointer child = parent->left;
			node_type_pointer T2 = child->right;
			node_type_pointer p = parent->parent;
			child->right = parent;
			parent->left = T2;
			if (p != this->_end)
			{
				if (p->right == parent)
					p->right = child;
				else
					p->left = child;
			}
			child->parent = parent->parent;
			parent->parent = child;
			if (T2 != NULL)
				T2->parent = parent;
			parent->height = std::max(_height(parent->left), _height(parent->right)) + 1;
			child->height = std::max(_height(child->left), _height(child->right)) + 1;
			return child;
		};


	};
}
#endif
