/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree_node.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 03:45:41 by ldutriez          #+#    #+#             */
/*   Updated: 2022/03/05 02:22:32 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// A classic implementation of a red-black tree.

#ifndef CONTAINERS_RED_BLACK_TREE_NODE_HPP
# define CONTAINERS_RED_BLACK_TREE_NODE_HPP

# include <memory>
# include <exception>
# include "../../tools/comparison/rbtree_node_compare.hpp"

namespace ft
{
	typedef enum e_node_color
	{
		red,
		black
	}				node_color;

	template <typename T, typename Compare = std::less<T>, typename Alloc = std::allocator<T> >
	class RedBlackTreeNode
	{
		public:

			typedef T 											value_type;
			typedef Alloc										allocator_type;
			typedef RedBlackTreeNode<T, Compare, Alloc>			node_type;
			typedef RedBlackTreeNode<T, Compare, Alloc>*		node_pointer;
			
			node_pointer				_parent;
			node_pointer				_left;
			node_pointer				_right;
			T*							_value;
			node_color					_color;

		private:

			node_pointer				_limit;

		public:

			RedBlackTreeNode()
			: _parent(NULL), _left(NULL), _right(NULL)
			, _value(NULL), _color(black), _limit(NULL)
			{
				allocator_type alloc;
				
				_value = alloc.allocate(1);
				alloc.construct(_value, T());
			}

			RedBlackTreeNode(const T& value, node_color color = black)
			: _parent(NULL), _left(NULL), _right(NULL)
			, _value(NULL), _color(color), _limit(NULL)
			{
				allocator_type alloc;
				
				_value = alloc.allocate(1);
				alloc.construct(_value, value);
			}

			RedBlackTreeNode(const RedBlackTreeNode& other)
			: _parent(other._parent), _left(other._left), _right(other._right)
			, _value(NULL), _color(other._color), _limit(NULL)
			{
				allocator_type alloc;
				
				_value = alloc.allocate(1);
				alloc.construct(_value, *other._value);
			}

			~RedBlackTreeNode()
			{
				allocator_type alloc;

				alloc.destroy(_value);
				alloc.deallocate(_value, 1);
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

			// Set the limit of the tree.
			void	set_limit(node_pointer limit)
			{
				_limit = limit;
			}

			// This function will insert a new node in the tree after a given node.
			// And resolve the red-black tree properties.
			// return the new root of the tree.
			RedBlackTreeNode*	insert(RedBlackTreeNode* node, char side, const T& value, node_pointer limit, std::allocator<RedBlackTreeNode>& alloc)
			{
				if (side == 0)
				{
					node->_right = alloc.allocate(1);
					alloc.construct(node->_right, value);
					node->_right->_color = red;
					node->_right->_parent = node;
					node->_right->_limit = limit;
					_resolve_insertion(node->_right);
				}
				else if (side == 1)
				{
					node->_left = alloc.allocate(1);
					alloc.construct(node->_left, value);
					node->_left->_color = red;
					node->_left->_parent = node;
					node->_left->_limit = limit;
					// Resolve the red-black tree properties.
					_resolve_insertion(node->_left);
				}
				return (root());
			}

			// This function will insert a new node in the tree in a sorting order.
			// And resolve the red-black tree properties.
			// return the new root of the tree.
			RedBlackTreeNode*	insert(const T& value, node_pointer limit, std::allocator<RedBlackTreeNode>& alloc)
			{
				RedBlackTreeNode*			node(this);
				
				// std::cout << "limit int insert : " << limit << std::endl;
				while (node)
				{
					if (is_superior_in_key(node, value) == true)
					{
						if (node->_left == NULL)
						{
							node->_left = alloc.allocate(1);
							alloc.construct(node->_left, value);
							node->_left->_color = red;
							node->_left->_parent = node;
							node->_left->_limit = limit;
							// Resolve the red-black tree properties.
							_resolve_insertion(node->_left);
							break ;
						}
						node = node->_left;
					}
					else if (is_inferior_in_key(node, value) == true)
					{
						if (node->_right == NULL)
						{
							node->_right = alloc.allocate(1);
							alloc.construct(node->_right, value);
							node->_right->_color = red;
							node->_right->_parent = node;
							node->_right->_limit = limit;
							// Resolve the red-black tree properties.
							_resolve_insertion(node->_right);
							break ;
						}
						node = node->_right;
					}
					else
						throw std::runtime_error("RedBlackTreeNode::insert: value already exists.");
				}
				return (root());
			}

			// This function will return the root of the tree.
			RedBlackTreeNode*			root() const
			{
				RedBlackTreeNode*			node(const_cast<RedBlackTreeNode*>(this));

				while (node->_parent != NULL)
					node = node->_parent;
				return (node);
			}

			// This function will return the node with the given value.
			// If the node doesn't exist, it will return the limit.
			RedBlackTreeNode*			node(const T& value) const
			{
				RedBlackTreeNode*			current_node(const_cast<RedBlackTreeNode*>(this));
				
				while (current_node)
				{
					if (is_superior_in_key(current_node, value) == true)
					{
						if (current_node->_left == NULL)
							return (_limit);
						current_node = current_node->_left;
					}
					else if (is_inferior_in_key(current_node, value) == true)
					{
						if (current_node->_right == NULL)
							return (_limit);
						current_node = current_node->_right;
					}
					else
						return (current_node);
				}
				return (_limit);
			}

			// This function will remove the node with the given value.
			// If the node doesn't exist, it do nothing.
			// return the new root of the tree.
			RedBlackTreeNode * remove(const T& value, std::allocator<RedBlackTreeNode>& alloc)
			{
				RedBlackTreeNode *v = node(value);
			
				if (v == _limit)
					throw std::runtime_error("RedBlackTreeNode::remove: node doesn't exist.");
				_delete_node(v, alloc);
				return (root());
			}

			// This function return the limit of the tree.
			node_pointer				limit() const
			{
				return _limit;
			}

		private:

			void _resolve_double_black(RedBlackTreeNode *node)
			{
				if (node == NULL || node->_parent == NULL)
					return;
			
				RedBlackTreeNode *sibling = node->_sibling();
				RedBlackTreeNode *parent = node->_parent;

				if (sibling == NULL)
				{
					_resolve_double_black(parent);
				}
				else
				{
					if (sibling->_color == red)
					{
						parent->_color = red;
						sibling->_color = black;
						if (sibling->_parent->_left == sibling)
						{
							_rotate_right(sibling);
						}
						else
						{
							_rotate_left(sibling);
						}
						_resolve_double_black(node);
					}
					else
					{
						if ((sibling->_left != NULL && sibling->_left->_color == red)
						|| (sibling->_right != NULL && sibling->_right->_color == red))
						{
							// at least 1 red children
							if (sibling->_right == NULL)
							{
								if (sibling->_parent->_left == sibling)
								{
									// left left
									sibling->_left->_color = sibling->_color;
									sibling->_color = parent->_color;
									_rotate_right(sibling);
								}
								else
								{
									// right left
									sibling->_left->_color = parent->_color;
									RedBlackTreeNode *tmp = sibling->_left;
									_rotate_right(tmp);
									_rotate_left(tmp);
								}
							}
							else
							{
								if (sibling->_parent->_left == sibling)
								{
									// left right
									sibling->_right->_color = parent->_color;
									RedBlackTreeNode *tmp = sibling->_right;
									_rotate_left(tmp);
									_rotate_right(tmp);
								}
								else
								{
									// right right
									sibling->_right->_color = sibling->_color;
									sibling->_color = parent->_color;
									_rotate_left(sibling);
								}
							}
							parent->_color = black;
						}
						else
						{
							// 2 black children
							sibling->_color = red;
							if (parent->_color == black)
								_resolve_double_black(parent);
							else
								parent->_color = black;
						}
					}
				}
			}

			// find node that do not have a left child
			// in the subtree of the given node
			RedBlackTreeNode *_successor(RedBlackTreeNode *node)
			{
				RedBlackTreeNode *temp = node;
			
				while (temp->_left != NULL)
					temp = temp->_left;
				return temp;
			}

			// find node that replaces a deleted node in BST
			RedBlackTreeNode *_find_replacement(RedBlackTreeNode *node)
			{
				// when node have 2 children
				if (node->_left != NULL && node->_right != NULL)
					return _successor(node->_right);
			
				// when leaf
				if (node->_left == NULL && node->_right == NULL)
					return NULL;
			
				// when single child
				if (node->_left != NULL)
					return node->_left;
				else
					return node->_right;
			}

			// return true if both given nodes are black
			bool _are_both_black(RedBlackTreeNode *node1, RedBlackTreeNode *node2)
			{
				if (node1 == NULL && node2 == NULL)
					return true;
				else if (node1 == NULL && node2 != NULL && node2->_color == black)
					return true;
				else if (node1 != NULL && node1->_color == black && node2 == NULL)
					return true;
				else
					return (node1 != NULL && node2 != NULL
					&& node1->_color == black && node2->_color == black);
			}

			// returns pointer to sibling
			RedBlackTreeNode *_sibling(void)
			{
				// sibling null if no parent
				if (this->_parent == NULL)
					return NULL;
			
				if (this->_parent->_left == this)
					return this->_parent->_right;
			
				return this->_parent->_left;
			}

			// Deletes the given node from the tree
			// After deletion, the node will be replaced by its successor
			// or NULL if the node is a leaf.
			// Will then resolve any double black nodes.
			void _delete_node(RedBlackTreeNode *node_to_del, std::allocator<RedBlackTreeNode>& alloc)
			{
				if (node_to_del == NULL)
					return;
				RedBlackTreeNode*	replacement = _find_replacement(node_to_del);
				bool				is_r_n_black = _are_both_black(replacement, node_to_del);
				// RedBlackTreeNode*	parent = node_to_del->_parent;
			
				if (replacement == NULL)
				{
					// replacement is NULL therefore node_to_del is leaf
					if (node_to_del->_parent != NULL)
					{
						if (is_r_n_black)
						{
							// replacement and node_to_del both black
							// node_to_del is leaf, fix double black at node_to_del
							_resolve_double_black(node_to_del);
						}
						else
						{
							// Node_to_del is red
							if (node_to_del->_sibling() != NULL)
								// sibling is not null, make it red"
								node_to_del->_sibling()->_color = red;
						}
			
						// delete node_to_del from the tree
						if (node_to_del->_parent->_left == node_to_del)
						{
							node_to_del->_parent->_left = NULL;
						}
						else
						{
							node_to_del->_parent->_right = NULL;
						}
					}
					alloc.destroy(node_to_del);
					alloc.deallocate(node_to_del, 1);
					return;
				}
			
				if (node_to_del->_left == NULL || node_to_del->_right == NULL)
				{
					// node_to_del has 1 child
					if (node_to_del->_parent == NULL)
					{
						// node_to_del is root, assign the value of replacement to node_to_del, and delete replacement
						std::swap(node_to_del->_value, replacement->_value);
						node_to_del->_left = node_to_del->_right = NULL;
						alloc.destroy(replacement);
						alloc.deallocate(replacement, 1);
						// delete replacement;
					}
					else
					{
						// Detach node_to_del from tree and move replacement up
						if (node_to_del->_parent->_left == node_to_del)
							node_to_del->_parent->_left = replacement;
						else
							node_to_del->_parent->_right = replacement;
						replacement->_parent = node_to_del->_parent;
						alloc.destroy(node_to_del);
						alloc.deallocate(node_to_del, 1);
						// delete node_to_del;
						if (is_r_n_black)
							// replacement and node_to_del both black, fix double black at replacement
							_resolve_double_black(replacement);
						else
							// replacement or node_to_del red, color replacement black
							replacement->_color = black;
					}
					return;
				}
				// node_to_del has 2 children, swap values with _successor and recurse
				std::swap(node_to_del->_value, replacement->_value);
				_delete_node(replacement, alloc);
			}
	
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
			void	_uncle_is_red(RedBlackTreeNode* node)
			{
				RedBlackTreeNode*	parent_node;
				RedBlackTreeNode*	grand_parent_node;
				RedBlackTreeNode*	uncle_node;

				_make_relation(node, &parent_node, &grand_parent_node, &uncle_node);
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
			void	_left_parent(RedBlackTreeNode* current_node)
			{
				RedBlackTreeNode*	parent_node;
				RedBlackTreeNode*	grand_parent_node;
				RedBlackTreeNode*	uncle_node;

				_make_relation(current_node, &parent_node, &grand_parent_node, &uncle_node);
				if (grand_parent_node->_left == parent_node)
				{
					if (parent_node->_right == current_node)
					{
						_rotate_left(current_node);
						_rotate_right(current_node);
						current_node->_color = black;
						grand_parent_node->_color = red;
					}
					else if (parent_node->_left == current_node)
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
			void	_right_parent(RedBlackTreeNode* current_node)
			{
				RedBlackTreeNode*	parent_node;
				RedBlackTreeNode*	grand_parent_node;
				RedBlackTreeNode*	uncle_node;

				_make_relation(current_node, &parent_node, &grand_parent_node, &uncle_node);
				if (grand_parent_node->_right == parent_node)
				{
					if (parent_node->_right == current_node)
					{
						_rotate_left(parent_node);
						parent_node->_color = black;
						grand_parent_node->_color = red;
					}
					else if (parent_node->_left == current_node)
					{
						_rotate_right(current_node);
						_rotate_left(current_node);
						current_node->_color = black;
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

				// If the parent is black, the node is already correct.
				if (parent_node->_color == black)
				{
					return;
				}
				if (uncle_node != NULL && uncle_node->_color == red)
					_uncle_is_red(node);
				else if (grand_parent_node->_left == parent_node)
					_left_parent(node);
				else if (grand_parent_node->_right == parent_node)
					_right_parent(node);
				if (node->_color == red)
					_resolve_insertion(node);
			}
	};

	// Get the root node of the tree.
	// Starting from the given node.
	template <typename T, typename Compare, typename Alloc>
	RedBlackTreeNode<T, Compare, Alloc>*	root(const RedBlackTreeNode<T, Compare, Alloc>* node)
	{
		if (node == NULL)
			return NULL;
		while (node->_parent != NULL)
			node = node->_parent;
		return const_cast<RedBlackTreeNode<T, Compare, Alloc> *>(node);
	}

	// This function will get the node with the next inorder value.
	// If the node is the last, it will return the node.
	template <typename T, typename Compare, typename Alloc>
	RedBlackTreeNode<T, Compare, Alloc> * next_inorder(const RedBlackTreeNode<T, Compare, Alloc> * node)
	{
		if (node == NULL)
			throw std::runtime_error("next_inorder: node is NULL");
		if (node->_left == NULL && node->_right == NULL
		&& node->_parent != NULL && node->_parent->_left != node && node->_parent->_right != node)
			return last(node);
		if (node == last(node))
			return node->limit();
		if (node->_right != NULL)
			return leftmost(node->_right);
		else
		{
			RedBlackTreeNode<T, Compare, Alloc> * parent = node->_parent;
			while (parent != NULL && parent->_right == node)
			{
				node = parent;
				parent = node->_parent;
			}
			if (parent == NULL)
				return const_cast<RedBlackTreeNode<T, Compare, Alloc> *>(node);
			return parent;
		}
	}

	// This function will get the node with the previous inorder value.
	// If the node is the first, it will return the node.
	template <typename T, typename Compare, typename Alloc>
	RedBlackTreeNode<T, Compare, Alloc> * prev_inorder(const RedBlackTreeNode<T, Compare, Alloc> * node)
	{
		if (node == NULL)
			throw std::runtime_error("prev_inorder: node is NULL");
		if (node->_left == NULL && node->_right == NULL
		&& node->_parent != NULL && node->_parent->_left != node && node->_parent->_right != node)
			return last(node);
		// if (node == begin(node))
		if (node == begin(node))
			return node->limit();
		if (node->_left != NULL)
			return rightmost(node->_left);
		else
		{
			RedBlackTreeNode<T, Compare, Alloc> * parent = node->_parent;
			while (parent != NULL && parent->_left == node)
			{
				node = parent;
				parent = node->_parent;
			}
			if (parent == NULL)
				return const_cast<RedBlackTreeNode<T, Compare, Alloc> *>(node);
			return parent;
		}
	}

	// This function will get the node with the leftmost value.
	// Start from the node and go to the leftmost node.
	template <typename T, typename Compare, typename Alloc>
	RedBlackTreeNode<T, Compare, Alloc> * leftmost(const RedBlackTreeNode<T, Compare, Alloc> * node)
	{
		if (node == NULL)
			throw std::runtime_error("leftmost: node is NULL");
		while (node->_left != NULL)
			node = node->_left;
		return const_cast<RedBlackTreeNode<T, Compare, Alloc> *>(node);
	}

	// This function will get the node with the rightmost value.
	// Start from the node and go to the rightmost node.
	template <typename T, typename Compare, typename Alloc>
	RedBlackTreeNode<T, Compare, Alloc> * rightmost(const RedBlackTreeNode<T, Compare, Alloc> * node)
	{
		if (node == NULL)
			throw std::runtime_error("rightmost: node is NULL");
		while (node->_right != NULL)
			node = node->_right;
		return const_cast<RedBlackTreeNode<T, Compare, Alloc> *>(node);
	}

	// This function will get the first node of the tree. (Leftmost node)
	template <typename T, typename Compare, typename Alloc>
	RedBlackTreeNode<T, Compare, Alloc> * begin(const RedBlackTreeNode<T, Compare, Alloc> * node)
	{
		if (node == NULL)
			throw std::runtime_error("begin: node is NULL");
		node = root(node);
		node = leftmost(node);
		return const_cast<RedBlackTreeNode<T, Compare, Alloc> *>(node);
	}

	// This function will get the last node of the tree. (Rightmost node)
	template <typename T, typename Compare, typename Alloc>
	RedBlackTreeNode<T, Compare, Alloc> * last(const RedBlackTreeNode<T, Compare, Alloc> * node)
	{
		if (node == NULL)
			throw std::runtime_error("last: node is NULL");
		node = root(node);
		node = rightmost(node);
		return const_cast<RedBlackTreeNode<T, Compare, Alloc> *>(node);
	}

	// This function return the end of the tree (address of last + 1).
	// The closing pointer, mainly used by iterator.
	// If you don't give the root, it will manually come back to the root to make sure the end is correct.
	template <typename T, typename Compare, typename Alloc>
	RedBlackTreeNode<T, Compare, Alloc> * end(RedBlackTreeNode<T, Compare, Alloc> * node)
	{
		if (node == NULL)
			throw std::runtime_error("end: node is NULL");
		node = last(node);
		return node->_limit;
	}
}

#endif