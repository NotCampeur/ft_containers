// A classic implementation of a red-black tree.

#ifndef CONTAINERS_RED_BLACK_TREE_NODE_HPP
# define CONTAINERS_RED_BLACK_TREE_NODE_HPP

typedef enum e_node_color
{
	red,
	black
}				node_color;

template <typename T>
class RedBlackTreeNode
{
	public:

		typedef RedBlackTreeNode<T>*	node_pointer;

		node_pointer				_parent;
		node_pointer				_left;
		node_pointer				_right;
		T							_value;
		node_color					_color;

		RedBlackTreeNode()
		: _parent(NULL), _left(NULL), _right(NULL)
		, _value(), _color(black) {}

		RedBlackTreeNode(const T& value, node_color color = black)
		: _parent(NULL), _left(NULL), _right(NULL)
		, _value(value), _color(color) {}
		RedBlackTreeNode(const RedBlackTreeNode& other)
		: _parent(other._parent), _left(other._left), _right(other._right)
		, _value(other._value), _color(other._color) {}

		~RedBlackTreeNode()
		{
			if (_left)
				delete _left;
			if (_right)
				delete _right;
		}

		RedBlackTreeNode&				operator=(const RedBlackTreeNode& other)
		{
			if (this != &other)
			{
				_parent = other._parent;
				_left = other._left;
				_right = other._right;
				_value = other._value;
				_color = other._color;
			}
			return (*this);
		}

		// This function will insert a new node in the tree in a sorting order.
		// And resolve the red-black tree properties.
		// return the new root of the tree.
		RedBlackTreeNode*	insert(const T& value)
		{
			RedBlackTreeNode*			node(this);
			while (node)
			{
				if (value < node->_value)
				{
					if (node->_left == NULL)
					{
						node->_left = new RedBlackTreeNode(value, red);
						node->_left->_parent = node;
						// Resolve the red-black tree properties.
						_resolve_insertion(node->_left);
						break ;
					}
					node = node->_left;
				}
				else if (value > node->_value)
				{
					if (node->_right == NULL)
					{
						node->_right = new RedBlackTreeNode(value, red);
						node->_right->_parent = node;
						// Resolve the red-black tree properties.
						_resolve_insertion(node->_right);
						break ;
					}
					node = node->_right;
				}
				else
					throw std::runtime_error("RedBlackTreeNode::insert: value already exists.");
			}
			return (get_root());
		}

		// This function will return the root of the tree.
		RedBlackTreeNode*			get_root() const
		{
			RedBlackTreeNode*			node(const_cast<RedBlackTreeNode*>(this));

			while (node->_parent)
				node = node->_parent;
			return (node);
		}

	private:

		// This function function will rotate the tree to the left from the given node.
		// The node must be the right child of its parent.
		// behavior: The parent of the given node will become the left child of the node.
		// If the node already has a left child, it will become the right child of the parent.
		// Thus the sorted order of the tree will be preserved.
		void	_rotate_left(RedBlackTreeNode* node)
		{
			RedBlackTreeNode*			parent(node->_parent);
			RedBlackTreeNode*			left(node->_left);

			if (parent == NULL || parent->_right != node)
				throw std::runtime_error("_rotate_left: node is not the right child of its parent.");
			parent->_right = left;
			node->_left = parent;
			node->_parent = parent->_parent;
			parent->_parent = node;
			if (left)
				left->_parent = parent;
			if (node->_parent)
			{
				if (node->_parent->_left == parent)
					node->_parent->_left = node;
				else
					node->_parent->_right = node;
			}
		}

		// This function function will rotate the tree to the right from the given node.
		// The node must be the left child of its parent.
		// behavior: The parent of the given node will become the right child of the node.
		// If the node already has a right child, it will become the left child of the parent.
		// Thus the sorted order of the tree will be preserved.
		void	_rotate_right(RedBlackTreeNode* node)
		{
			RedBlackTreeNode*			parent(node->_parent);
			RedBlackTreeNode*			right(node->_right);

			if (parent == NULL || parent->_left != node)
				throw std::runtime_error("_rotate_right: node is not the left child of its parent.");
			parent->_left = right;
			node->_right = parent;
			node->_parent = parent->_parent;
			parent->_parent = node;
			if (right)
				right->_parent = parent;
			if (node->_parent)
			{
				if (node->_parent->_left == parent)
					node->_parent->_left = node;
				else
					node->_parent->_right = node;
			}
		}

		// This function will create family relation based on the node.
		void	_make_relation(RedBlackTreeNode* current_node,
			RedBlackTreeNode** parent_node,
			RedBlackTreeNode** grand_parent_node,
			RedBlackTreeNode** uncle_node)
		{
			if (current_node == NULL || current_node->_parent == NULL)
			{
				*parent_node = NULL;
				*grand_parent_node = NULL;
				*uncle_node = NULL;
				return ;
			}
			else if (current_node->_parent->_parent == NULL)
			{
				*parent_node = current_node->_parent;
				*grand_parent_node = NULL;
				*uncle_node = NULL;
				return ;
			}
			else
			{
				*parent_node = current_node->_parent;
				*grand_parent_node = current_node->_parent->_parent;
				if (current_node->_parent == (*grand_parent_node)->_left)
					*uncle_node = (*grand_parent_node)->_right;
				else
					*uncle_node = (*grand_parent_node)->_left;
			}
		}

		// If the uncle is red, recolor the parent and uncle to black and grandparent to red.
		// Then call _resolve_insertion on the grandparent.
		void	_uncle_is_red(RedBlackTreeNode* current_node,
							RedBlackTreeNode* parent_node,
							RedBlackTreeNode* grand_parent_node,
							RedBlackTreeNode* uncle_node)
		{
			if (uncle_node != NULL && uncle_node->_color == red)
			{
				parent_node->_color = black;
				uncle_node->_color = black;
				grand_parent_node->_color = red;
				_resolve_insertion(grand_parent_node);
				return ;
			}
		}

		// If the parent is a left child:
		//	If the node is a right child,
		//	rotate the node to the left then to the right.
		//	Then recolor node to black and grandparent to red.
		//
		//	If the node is a left child,
		//	rotate the parent to the right.
		//	Then recolor the parent and grandparent to black and red.
		void	_left_parent(RedBlackTreeNode* current_node,
										RedBlackTreeNode* parent_node,
										RedBlackTreeNode* grand_parent_node)
		{
			if (grand_parent_node->_left == parent_node)
			{
				if (parent_node->_right == node)
				{
					_rotate_left(node);
					_rotate_right(node);
					node->_color = black;
					grand_parent_node->_color = red;
				}
				else if (parent_node->_left == node)
				{
					_rotate_right(parent_node);
					parent_node->_color = black;
					grand_parent_node->_color = red;
				}
				return;
			}
		}

		// If the parent is a right child:
		//	If the node is a right child,
		//	rotate the parent to the left.
		//	Then recolor the parent and grandparent to black and red.
		//
		//	If the node is a left child,
		//	rotate the node to the right then to the left.
		//	Then recolor node to black and grandparent to red.
		void	_right_parent(RedBlackTreeNode* current_node,
								RedBlackTreeNode* parent_node,
								RedBlackTreeNode* grand_parent_node)
		{
			if (grand_parent_node->_right == parent_node)
			{
				if (parent_node->_right == node)
				{
					_rotate_left(parent_node);
					parent_node->_color = black;
					grand_parent_node->_color = red;
				}
				else if (parent_node->_left == node)
				{
					_rotate_right(node);
					_rotate_left(node);
					node->_color = black;
					grand_parent_node->_color = red;
				}
				return;
			}
		}

		// This function will resolve the red-black tree properties after insertion.
		// It will either rotate the tree to the left or to the right. Or just recolor the nodes.
		// The node->_parent, node->_parent->_parent and node->_parent->_parent->[_left, _right] will be used.
		void	_resolve_insertion(RedBlackTreeNode* node)
		{
			RedBlackTreeNode*				parent_node;
			RedBlackTreeNode*				grand_parent_node;
			RedBlackTreeNode*				uncle_node;

			if (node == NULL)
				return ;

			_make_relation(node, &parent_node, &grand_parent_node, &uncle_node);

			// If the node is the root, just recolor it.
			if (parent_node == NULL)
			{
				node->_color = black;
				return ;
			}

			// If the parent is black, the tree is already correct.
			if (parent_node->_color == black)
				return ;
			_uncle_is_red(node, parent_node, grand_parent_node, uncle_node);
			_left_parent(node, parent_node, grand_parent_node);
			_right_parent(node, parent_node, grand_parent_node);
		}
};

#endif