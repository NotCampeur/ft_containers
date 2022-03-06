/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_red_black_tree_node.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 03:45:41 by ldutriez          #+#    #+#             */
/*   Updated: 2022/03/06 13:57:27 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// A classic implementation of a red-black tree.

#ifndef CONTAINERS_RED_BLACK_TREE_NODE_HPP
# define CONTAINERS_RED_BLACK_TREE_NODE_HPP

# include <memory>
# include <exception>
# include "../../tools/comparison/rbtree_node_compare.hpp"

# define RED true
# define BLACK false

namespace ft
{
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
			bool						_color;

			RedBlackTreeNode()
			: _parent(NULL), _left(NULL), _right(NULL)
			, _value(NULL), _color(BLACK)
			{
				allocator_type alloc;
				
				_value = alloc.allocate(1);
				alloc.construct(_value, T());
			}

			RedBlackTreeNode(const T& value, bool color = BLACK)
			: _parent(NULL), _left(NULL), _right(NULL)
			, _value(NULL), _color(color)
			{
				allocator_type alloc;
				
				_value = alloc.allocate(1);
				alloc.construct(_value, value);
			}

			RedBlackTreeNode(const RedBlackTreeNode& other)
			: _parent(other._parent), _left(other._left), _right(other._right)
			, _value(NULL), _color(other._color)
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
	RedBlackTreeNode<T, Compare, Alloc> * next_inorder(const RedBlackTreeNode<T, Compare, Alloc> * node
													, const RedBlackTreeNode<T, Compare, Alloc> * limit)
	{
		if (node == NULL)
			throw std::runtime_error("next_inorder: node is NULL");
		if (node->_left == NULL && node->_right == NULL
		&& node->_parent != NULL && node->_parent->_left != node && node->_parent->_right != node)
			return last(node);
		if (node == last(node))
			return const_cast<RedBlackTreeNode<T, Compare, Alloc> *>(limit);
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
	RedBlackTreeNode<T, Compare, Alloc> * prev_inorder(const RedBlackTreeNode<T, Compare, Alloc> * node
													, const RedBlackTreeNode<T, Compare, Alloc> * limit)
	{
		if (node == NULL)
			throw std::runtime_error("prev_inorder: node is NULL");
		if (node->_left == NULL && node->_right == NULL
		&& node->_parent != NULL && node->_parent->_left != node && node->_parent->_right != node)
			return last(node);
		if (node == begin(node))
			return const_cast<RedBlackTreeNode<T, Compare, Alloc> *>(limit);
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

	// // This function return the end of the tree (address of last + 1).
	// // The closing pointer, mainly used by iterator.
	// // If you don't give the root, it will manually come back to the root to make sure the end is correct.
	// template <typename T, typename Compare, typename Alloc>
	// RedBlackTreeNode<T, Compare, Alloc> * end(RedBlackTreeNode<T, Compare, Alloc> * node)
	// {
	// 	if (node == NULL)
	// 		throw std::runtime_error("end: node is NULL");
	// 	node = last(node);
	// 	return node->_limit;
	// }
}

#endif