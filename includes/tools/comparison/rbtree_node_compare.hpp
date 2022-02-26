/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree_node_compare.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 05:52:48 by ldutriez          #+#    #+#             */
/*   Updated: 2022/02/26 06:40:59 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINERS_RBTREE_NODE_COMPARE_HPP
# define CONTAINERS_RBTREE_NODE_COMPARE_HPP

# include "../../containers/binary_tree/red_black_tree.hpp"
# include "../../containers/pair.hpp"

template <typename T, typename Compare>
class RedBlackTreeNode;

// Templated function which take a Compare to tell if the argument node is less than the given value.
template <typename T, typename Compare>
bool	is_inferior(const RedBlackTreeNode<T, Compare> * node, const T & value)
{
	Compare comp;
	
	if (node == NULL)
		throw std::runtime_error("is_inferior: node is NULL");
	return comp(node->_value, value);
}

// A specialisation of the above function, if the type is a pair but compare a pair.
template <typename U, typename V, typename Compare>
bool	is_inferior(const RedBlackTreeNode<ft::pair<U, V>, Compare> * node1, const RedBlackTreeNode<ft::pair<U, V>, Compare> * node2)
{
	Compare comp;
	
	if (node1 == NULL || node2 == NULL)
		throw std::runtime_error("is_inferior: node is NULL");
	return comp(node1->_value.first, node2->_value.first);
}

// A specialisation of the above function, if the type is a pair but compare a key.
template <typename U, typename V, typename Compare>
bool	is_inferior(const RedBlackTreeNode<ft::pair<U, V>, Compare> * node, const ft::pair<U, V> & value)
{
	Compare comp;
	
	if (node == NULL)
		throw std::runtime_error("is_inferior: node is NULL");
	return comp(node->_value.first, value.first);
}

// A specialisation of the above function, if the type is a pair but compare a key.
template <typename U, typename V, typename Compare>
bool	is_inferior(const RedBlackTreeNode<ft::pair<U, V>, Compare> * node, const U & value)
{
	Compare comp;
	
	if (node == NULL)
		throw std::runtime_error("is_inferior: node is NULL");
	return comp(node->_value.first, value);
}

// Templated function which take a Compare to tell if the argument node is greter than the given value.
template <typename T, typename Compare>
bool	is_superior(const RedBlackTreeNode<T, Compare> * node, const T & value)
{
	Compare comp;
	
	if (node == NULL)
		throw std::runtime_error("is_superior: node is NULL");
	return comp(value, node->_value);
}

template <typename U, typename V, typename Compare>
bool	is_superior(const RedBlackTreeNode<ft::pair<U, V>, Compare> * node, const ft::pair<U, V> & value)
{
	Compare comp;
	
	if (node == NULL)
		throw std::runtime_error("is_superior: node is NULL");
	return comp(value.first, node->_value.first);
}

template <typename U, typename V, typename Compare>
bool	is_superior(const RedBlackTreeNode<ft::pair<U, V>, Compare> * node, const U & value)
{
	Compare comp;
	
	if (node == NULL)
		throw std::runtime_error("is_superior: node is NULL");
	return comp(value, node->_value.first);
}

#endif