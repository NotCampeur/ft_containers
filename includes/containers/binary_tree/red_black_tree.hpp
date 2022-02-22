/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:55:25 by ldutriez          #+#    #+#             */
/*   Updated: 2022/02/22 14:24:18 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINERS_RED_BLACK_TREE_HPP
# define CONTAINERS_RED_BLACK_TREE_HPP

# include <memory>
# include <exception>
# include "red_black_tree_node.hpp"

template< typename T, typename Compare = std::less<T>, typename Alloc = std::allocator<RedBlackTreeNode<T> > >
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
		node_pointer			_begin;
		node_pointer			_last;
		node_pointer			_end;
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
		rbtree() : _root(NULL), _begin(NULL), _last(NULL), _end(NULL) {}
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
				_alloc.construct(_root, RedBlackTreeNode<T, Compare>(value));
				_begin = _root;
				_last = _root;
				_end = _root + 1;
			}
			else
			{
				_root = _root->insert(value, _alloc);
				_begin = leftmost(_root);
				_last = rightmost(_root);
				_end = _last + 1;
			}
		};

		// Remove a node from the tree by calling the remove function of the root.
		void	remove(const T& value)
		{
			if (_root != NULL)
			{
				_root = _root->remove(value, _alloc);
				_begin = leftmost(_root);
				_last = rightmost(_root);
				_end = _last + 1;
			}
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