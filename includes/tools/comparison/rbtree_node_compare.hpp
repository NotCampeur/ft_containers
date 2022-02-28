/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree_node_compare.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 05:52:48 by ldutriez          #+#    #+#             */
/*   Updated: 2022/02/28 04:45:26 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINERS_RBTREE_NODE_COMPARE_HPP
# define CONTAINERS_RBTREE_NODE_COMPARE_HPP

# include "../../containers/binary_tree/red_black_tree.hpp"
# include "../../containers/pair.hpp"

namespace ft
{
	template <typename T, typename Compare, typename Alloc>
	class RedBlackTreeNode;

	// Templated function which take a Compare to tell if the argument node is less than the given value.
	template <typename T, typename Compare, typename Alloc>
	bool	is_inferior_in_key(const ft::RedBlackTreeNode<T, Compare, Alloc> * node, const T & value)
	{
		Compare comp;
		
		if (node == NULL)
			throw std::runtime_error("is_inferior_in_key: node is NULL");
		return comp(*node->_value, value);
	}

	// A specialisation of the above function, if the type is a pair but compare a pair.
	template <typename U, typename V, typename Compare, typename Alloc>
	bool	is_inferior_in_key(const ft::RedBlackTreeNode<ft::pair<U, V>, Compare, Alloc> * node1, const ft::RedBlackTreeNode<ft::pair<U, V>, Compare, Alloc> * node2)
	{
		Compare comp;
		
		if (node1 == NULL || node2 == NULL)
			throw std::runtime_error("is_inferior_in_key: node is NULL");
		return comp(node1->_value->first, node2->_value->first);
	}

	// A specialisation of the above function, if the type is a pair but compare a key.
	template <typename U, typename V, typename Compare, typename Alloc>
	bool	is_inferior_in_key(const ft::RedBlackTreeNode<ft::pair<U, V>, Compare, Alloc> * node, const ft::pair<U, V> & value)
	{
		Compare comp;
		
		if (node == NULL)
			throw std::runtime_error("is_inferior_in_key: node is NULL");
		return comp(node->_value->first, value.first);
	}

	// A specialisation of the above function, if the type is a pair but compare a key.
	template <typename U, typename V, typename Compare, typename Alloc>
	bool	is_inferior_in_key(const ft::RedBlackTreeNode<ft::pair<U, V>, Compare, Alloc> * node, const U & value)
	{
		Compare comp;
		
		if (node == NULL)
			throw std::runtime_error("is_inferior_in_key: node is NULL");
		return comp(node->_value->first, value);
	}

	// Templated function which take a Compare to tell if the argument node is greter than the given value.
	template <typename T, typename Compare, typename Alloc>
	bool	is_superior_in_key(const ft::RedBlackTreeNode<T, Compare, Alloc> * node, const T & value)
	{
		Compare comp;
		
		if (node == NULL)
			throw std::runtime_error("is_superior_in_key: node is NULL");
		return comp(value, *node->_value);
	}

	template <typename U, typename V, typename Compare, typename Alloc>
	bool	is_superior_in_key(const ft::RedBlackTreeNode<ft::pair<U, V>, Compare, Alloc> * node, const ft::pair<U, V> & value)
	{
		Compare comp;
		
		if (node == NULL)
			throw std::runtime_error("is_superior_in_key: node is NULL");
		return comp(value.first, node->_value->first);
	}

	template <typename U, typename V, typename Compare, typename Alloc>
	bool	is_superior_in_key(const ft::RedBlackTreeNode<ft::pair<U, V>, Compare, Alloc> * node, const U & value)
	{
		Compare comp;
		
		if (node == NULL)
			throw std::runtime_error("is_superior_in_key: node is NULL");
		return comp(value, node->_value->first);
	}

	// Templated function which take a Compare to tell if the argument node is less than the given value.
	template <typename T, typename Compare, typename Alloc>
	bool	is_inferior(const ft::RedBlackTreeNode<T, Compare, Alloc> * node, const T & value)
	{
		Compare comp;
		
		if (node == NULL)
			throw std::runtime_error("is_inferior: node is NULL");
		return comp(*node->_value, value);
	}

	// A specialisation of the above function, if the type is a pair but compare a pair. And not only the key.
	template <typename U, typename V, typename Compare, typename Alloc>
	bool	is_inferior(const ft::RedBlackTreeNode<ft::pair<U, V>, Compare, Alloc> * node1, const ft::RedBlackTreeNode<ft::pair<U, V>, Compare, Alloc> * node2)
	{
		Compare comp;
		
		if (node1 == NULL || node2 == NULL)
			throw std::runtime_error("is_inferior: node is NULL");
		if (comp(node1->_value->first, node2->_value->first) == true)
			return true;
		else if (comp(node2->_value->first, node1->_value->first) == true)
			return false;
		else
			return comp(node1->_value->second, node2->_value->second);
	}

	// A specialisation of the above function, if the type is a pair but compare a key.
	template <typename U, typename V, typename Compare, typename Alloc>
	bool	is_inferior(const ft::RedBlackTreeNode<ft::pair<U, V>, Compare, Alloc> * node, const ft::pair<U, V> & value)
	{
		Compare comp;
		
		if (node == NULL)
			throw std::runtime_error("is_inferior: node is NULL");
		if (comp(node->_value->first, value.first) == true)
			return true;
		else if (comp(value.first, node->_value->first) == true)
			return false;
		else
			return comp(node->_value->second, value.second);
	}

	// Templated function which take a Compare to tell if the argument node is greter than the given value.
	template <typename T, typename Compare, typename Alloc>
	bool	is_superior(const ft::RedBlackTreeNode<T, Compare, Alloc> * node, const T & value)
	{
		Compare comp;
		
		if (node == NULL)
			throw std::runtime_error("is_superior: node is NULL");
		return comp(value, *node->_value);
	}

	template <typename U, typename V, typename Compare, typename Alloc>
	bool	is_superior(const ft::RedBlackTreeNode<ft::pair<U, V>, Compare, Alloc> * node, const ft::pair<U, V> & value)
	{
		Compare comp;
		
		if (node == NULL)
			throw std::runtime_error("is_superior: node is NULL");
		if (comp(value.first, node->_value->first) == true)
			return true;
		else if (comp(node->_value->first, value.first) == true)
			return false;
		else
			return comp(value.second, node->_value->second);
	}
}

#endif