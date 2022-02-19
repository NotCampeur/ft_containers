/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:55:25 by ldutriez          #+#    #+#             */
/*   Updated: 2022/02/19 05:58:30 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINERS_RED_BLACK_TREE_HPP
# define CONTAINERS_RED_BLACK_TREE_HPP

# include <memory>
# include <exception>
# include "red_black_tree_node.hpp"

template< typename T, typename Alloc = std::allocator<RedBlackTreeNode<T> > >
class rbtree
{
	private:
		Alloc		_alloc;

	public:

		typedef T 											value_type;
		typedef Alloc										allocator_type;
		
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;

		typedef typename allocator_type::pointer			node_pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		
	private:
		node_pointer			_root;
		void	_destroy_tree(node_pointer node)
		{
			if (node && node->_left)
				_destroy_tree(node->_left);
			if (node && node->_right)
				_destroy_tree(node->_right);
			_alloc.destroy(node);
			_alloc.deallocate(node, 1);
		}

	public:
		rbtree() : _root(NULL) {}
		~rbtree()
		{
			_destroy_tree(_root);
		}

		node_pointer	root() const {return _root;};

		// Insert a new node in the tree by calling the insert function of the root.
		void	insert(const T& value)
		{
			if (_root == NULL)
			{
				_root = _alloc.allocate(1);
				_alloc.construct(_root, RedBlackTreeNode<T>(value));
				// _root = new RedBlackTreeNode<T>(value);
			}
			else
				_root = _root->insert(value, _alloc);
		};

		// Remove a node from the tree by calling the remove function of the root.
		void	remove(const T& value)
		{
			if (_root != NULL)
				_root = _root->remove(value, _alloc);
		};

		// Get the node with the value.
		RedBlackTreeNode<T>*	get(const T& value)
		{
			if (_root == NULL)
				return NULL;
			return _root->node(value);
		};

		// Operator to get the node with the value.
		RedBlackTreeNode<T>*	operator[](const T& value)
		{
			return get(value);
		};
};

#endif