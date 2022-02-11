// A classic implementation of a red-black tree.

template <typename T>
class RedBlackTree
{
public:
	typedef enum e_node_color
	{
		red,
		black
	}				node_color;

	typedef RedBlackTree<T>*	node_pointer;

	node_pointer				_parent;
	node_pointer				_left;
	node_pointer				_right;
	T							_value;
	node_color					_color;

	RedBlackTree()
	: _parent(NULL), _left(NULL), _right(NULL)
	, _value(), _color(black) {}

	RedBlackTree(const T& value, node_color color = black)
	: _parent(NULL), _left(NULL), _right(NULL)
	, _value(value), _color(color) {}
	RedBlackTree(const RedBlackTree& other)
	: _parent(other._parent), _left(other._left), _right(other._right)
	, _value(other._value), _color(other._color) {}

	~RedBlackTree()
	{
		if (_left)
			delete _left;
		if (_right)
			delete _right;
	}

	RedBlackTree&				operator=(const RedBlackTree& other)
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

	// This function will insert a new node in the tree.
	// And resolve the red-black tree properties.
	void						insert(const T& value)
	{
		RedBlackTree*				node = this;
		while (node)
		{
			if (value < node->_value)
			{
				if (node->_left == NULL)
				{
					node->_left = new RedBlackTree(value);
					node->_left->_parent = node;
					break ;
				}
				node = node->_left;
			}
			else if (value > node->_value)
			{
				if (node->_right == NULL)
				{
					node->_right = new RedBlackTree(value);
					node->_right->_parent = node;
					break ;
				}
				node = node->_right;
			}
			else
				throw std::runtime_error("RedBlackTree::insert: value already exists.");
		}

		// Resolve the red-black tree properties.
		resolve_insertion(node);
	}

	// This function will create family relation based on the node.
	void	make_relation(RedBlackTree* current_node,
		RedBlackTree** parent_node,
		RedBlackTree** grand_parent_node,
		RedBlackTree** uncle_node)
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

	// This function will resolve the red-black tree properties after insertion.
	// It will either rotate the tree to the left or to the right. Or just recolor the nodes.
	// The node->_parent, node->_parent->_parent and node->_parent->_parent->[_left, _right] will be used.
	void	resolve_insertion(RedBlackTree* node)
	{
		RedBlackTree*				parent_node;
		RedBlackTree*				grand_parent_node;
		RedBlackTree*				uncle_node;

		make_relation(node, &parent_node, &grand_parent_node, &uncle_node);

		// If the node is the root, just recolor it.
		if (parent_node == NULL)
		{
			node->_color = black;
			return ;
		}

		// If the parent is black, the tree is already correct.
		if (parent_node->_color == black)
			return ;

		// If the uncle is red, recolor the parent and uncle to black and grandparent to red.
		// Then rotate the grandparent.
		if (uncle_node != NULL && uncle_node->_color == red)
		{
			parent_node->_color = black;
			uncle_node->_color = black;
			grand_parent_node->_color = red;
			resolve_insertion(grand_parent_node);
			return ;
		}

		// If the parent is a left child and the node is a right child,
		// rotate the node to the left and recolor the parent and node to black.
		if (parent_node->_left == node && node->_right != NULL)
		{
			rotate_left(node);
			parent_node->_color = black;
			node->_color = black;
			return ;
		}

		// If the parent is a right child and the node is a left child,
		// rotate the node to the right and recolor the parent and node to black.
		if (parent_node->_right == node && node->_left != NULL)
		{
			rotate_right(node);
			parent_node->_color = black;
			node->_color = black;
			return ;
		}

		// If the parent is a left child and the node is a left child,
		// rotate the grandparent to the right and recolor the parent, grandparent and node to black.
		if (parent_node->_left == node && node->_left != NULL)
		{
			rotate_right(grand_parent_node);
			parent_node->_color = black;
			grand_parent_node->_color = black;
			node->_color = black;
			return ;
		}

		// If the parent is a right child and the node is a right child,
		// rotate the grandparent to the left and recolor the parent, grandparent and node to black.
		if (parent_node->_right == node && node->_right != NULL)
		{
			rotate_left(grand_parent_node);
			parent_node->_color = black;
			grand_parent_node->_color = black;
			node->_color = black;
		}
	}
};