/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:55:25 by ldutriez          #+#    #+#             */
/*   Updated: 2022/02/23 04:06:23 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINERS_RED_BLACK_TREE_HPP
# define CONTAINERS_RED_BLACK_TREE_HPP

# include <memory>
# include <exception>
# include "red_black_tree_node.hpp"
# include "../../tools/iterators/red_black_tree_iterator.hpp"
# include "../../tools/iterators/reverse_iterator.hpp"

template< typename T, typename Compare = std::less<T>, typename Alloc = std::allocator<RedBlackTreeNode<T> > >
class rbtree
{
	public:

		typedef T 											value_type;
		typedef RedBlackTreeNode<T, Compare>				node_type;
		typedef Alloc										allocator_type;
		
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;

		typedef typename allocator_type::pointer			node_pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		
		typedef red_black_tree_iterator< node_type >		iterator;
		typedef const_red_black_tree_iterator< node_type >	const_iterator;

		typedef ft::reverse_iterator< iterator >			reverse_iterator;
		typedef ft::reverse_iterator< const_iterator >		const_reverse_iterator;

		typedef std::ptrdiff_t								difference_type;

		typedef std::size_t									size_type;

	private:
	
		Alloc					_alloc;
		node_pointer			_limit;

		iterator				_root;
		iterator				_begin;
		iterator				_last;
		
		size_type				_size;
		
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
		rbtree()
		: _alloc(), _limit(NULL), _root(NULL)
		, _begin(NULL), _last(NULL)
		, _size(0) {}
		
		// While destroy and deallocate every node using iterators.
		~rbtree()
		{
			_destroy_tree(&*_root);
			_alloc.destroy(_limit);
			_alloc.deallocate(_limit, 1);
		}

		// Iterators

		iterator		root() {return _root;};
		const_iterator	root() const {return const_iterator(_root);};
		
		iterator		begin() {return _begin;};
		const_iterator	begin() const {return const_iterator(_begin);};
		
		iterator		last() {return _last;};
		const_iterator	last() const {return const_iteraotr(_last);};
		
		iterator		end() {return iterator(_limit);};
		const_iterator	end() const {return const_iterator(_limit);};

		reverse_iterator		rbegin() {return reverse_iterator(end());};
		const_reverse_iterator	rbegin() const {return const_reverse_iterator(end());};

		reverse_iterator		rend() {return reverse_iterator(begin());};
		const_reverse_iterator	rend() const {return const_reverse_iterator(begin());};

		// Return the number of nodes in the tree. (Leaves doesn't count)
		size_type		size() const {return _size;};

		// Return the limit of the tree.
		node_pointer	limit() const {return _limit;};

		// Insert a new node in the tree by calling the insert function of the root.
		void	insert(const T& value)
		{
			if (_root == iterator(NULL))
			{
				_limit = _alloc.allocate(1);
				_alloc.construct(_limit, RedBlackTreeNode<T, Compare>());
				_limit->set_limit(_limit);
				_root = _alloc.allocate(1);
				_alloc.construct(&*_root, RedBlackTreeNode<T, Compare>(value));
				_root->set_limit(_limit);
				_begin = _root;
				_last = _root;
				_size = 1;
				_limit->_parent = &*_root;
			}
			else
			{
				// std::cout << "limit : " << _limit << std::endl;
				_root = _root->insert(value, _limit, _alloc);
				_begin = leftmost(&*_root);
				_last = rightmost(&*_root);
				++_size;
				_limit->_parent = &*_root;
			}
		};

		// Remove a node from the tree by calling the remove function of the root.
		void	remove(const T& value)
		{
			if (_root != iterator(NULL))
			{
				try
				{
					_root = _root->remove(value, _alloc);
					_begin = leftmost(&*_root);
					_last = rightmost(&*_root);
					--_size;
					_limit->_parent = &*_root;
				}
				catch(...)
				{
					throw;
				}
			}
		};

		// Get the node with the value.
		RedBlackTreeNode<T>*	get(const T& value)
		{
			if (_root == iterator(NULL))
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