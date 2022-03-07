/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_red_black_tree.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:55:25 by ldutriez          #+#    #+#             */
/*   Updated: 2022/03/07 14:52:03 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINERS_RED_BLACK_TREE_HPP
# define CONTAINERS_RED_BLACK_TREE_HPP

# include <memory>
# include <exception>
# include "new_red_black_tree_node.hpp"
// # include "../../tools/iterators/red_black_tree_iterator.hpp"
# include "../../tools/iterators/new_red_black_tree_iterator.hpp"
# include "../../tools/iterators/reverse_iterator.hpp"
# include "../../tools/comparison/lexicographical_compare.hpp"
# include "../../tools/comparison/rbtree_node_compare.hpp"

namespace ft
{
	// Will assign a std::size_t to a template value.
	// Used to assign the size of the tree to the limit.
	// If the first value is a pair, the value will be assigned to the key.
	template <typename T, typename U>
	void	assign_size(ft::pair<const T, U> &value, std::size_t size)
	{
		T *p;
		
		p = const_cast<T *>(&value.first);
		*p = size;
	}

	template <typename T, typename U>
	void	assign_size(std::pair<const T, U> &value, std::size_t size)
	{
		T *p;
		
		p = const_cast<T *>(&value.first);
		*p = size;
	}

	template <typename T>
	void	assign_size(const T &value, std::size_t size)
	{
		T *p;
		
		p = const_cast<T *>(&value);
		*p = size;
	}

	template< typename T, typename Compare = std::less<T>, typename Alloc = std::allocator<T> >
	class rbtree
	{
		public:

			typedef T 												value_type;
			typedef ft::RedBlackTreeNode<T, Compare>				node_type;
			typedef Compare 										compare;
			typedef Alloc											allocator_type;
			typedef std::allocator<node_type>						node_allocator_type;

			typedef typename node_allocator_type::reference			reference;
			typedef typename node_allocator_type::const_reference	const_reference;

			typedef typename node_allocator_type::pointer			node_pointer;
			typedef typename node_allocator_type::const_pointer		const_pointer;

			typedef ft::red_black_tree_iterator< node_type >		iterator;
			typedef ft::const_red_black_tree_iterator< node_type >	const_iterator;

			typedef ft::rb_reverse_iterator< iterator >				reverse_iterator;
			typedef ft::rb_reverse_iterator< const_iterator >		const_reverse_iterator;

			typedef std::ptrdiff_t									difference_type;

			typedef std::size_t										size_type;

		private:
		
			node_allocator_type		_alloc;
			node_pointer			_limit;

			iterator				_root;
			iterator				_begin;
			
			size_type				_size;
			
			void	_destroy_tree(node_pointer node)
			{
				if (node == NULL)
					return ;
				if (node->_left)
					_destroy_tree(node->_left);
				if (node->_right)
					_destroy_tree(node->_right);
				_alloc.destroy(node);
				_alloc.deallocate(node, 1);
			}

		public:
			rbtree()
			: _alloc(), _limit(_alloc.allocate(1)), _root(NULL, _limit)
			, _begin(NULL, _limit)
			, _size(0)
			{
				// _limit = _alloc.allocate(1);// TESTING THE USE OF ALLOC IN INITIALIZATION LIST
				_alloc.construct(_limit, ft::RedBlackTreeNode<T, Compare>());
				_root = iterator(NULL, _limit);
			}
			
			rbtree(const rbtree &other)
			: _alloc(), _limit(_alloc.allocate(1)), _root(NULL, _limit)
			, _begin(NULL, _limit)
			, _size(0)
			{
				// _limit = _alloc.allocate(1);// TESTING THE USE OF ALLOC IN INITIALIZATION LIST
				_alloc.construct(_limit, ft::RedBlackTreeNode<T, Compare>());
				const_iterator it = other.begin();
				while (it != other.end())
				{
					insert(*it);
					++it;
				}
			}

			// While destroy and deallocate every node using iterators.
			~rbtree()
			{
				_destroy_tree(_root.base());
				_alloc.destroy(_limit);
				_alloc.deallocate(_limit, 1);
			}

			rbtree &operator=(const rbtree &other)
			{
				if (this != &other)
				{
					_destroy_tree(_root.base());
					_root._ptr = NULL;
					const_iterator it = other.begin();
					while (it != other.end())
					{
						insert(*it);
						++it;
					}
				}
				return *this;
			}

			void	clear()
			{
				_destroy_tree(_root.base());
				_root._ptr = NULL;
				_begin._ptr = NULL;
				_size = 0;
				assign_size(_limit->_value, _size);
			}
			
			// Iterators

			iterator		root() {return (_root.base() == NULL) ? iterator(_limit, _limit) : _root;}
			const_iterator	root() const {return (_root.base() == NULL) ? const_iterator(_limit, _limit) : const_iterator(_root);}
			
			iterator		begin() {return (_begin.base() == NULL) ? iterator(_limit, _limit) : _begin;}
			const_iterator	begin() const {return (_begin.base() == NULL) ? const_iterator(_limit, _limit) : const_iterator(_begin);}
			
			iterator		end() {return iterator(_limit, _limit);}
			const_iterator	end() const {return const_iterator(_limit, _limit);}

			reverse_iterator		rbegin() {return reverse_iterator(end());}
			const_reverse_iterator	rbegin() const {return const_reverse_iterator(end());}

			reverse_iterator		rend() {return reverse_iterator(begin());}
			const_reverse_iterator	rend() const {return const_reverse_iterator(begin());}

			// Return the number of nodes in the tree. (Leaves doesn't count)
			size_type		size() const {return _size;}

			// Return the limit of the tree.
			node_pointer	limit() const {return _limit;}
			
			// Insert a new node in the tree by calling the insert function of the root.
			// Will return hte pointer of the inserted node.
			ft::RedBlackTreeNode<T, Compare>*	insert(const T& value)
			{
				node_pointer	result;
				
				if (_root.base() == NULL)
				{
					_root._ptr = _alloc.allocate(1);
					_alloc.construct(_root.base(), ft::RedBlackTreeNode<T, Compare>(value));
					_begin = _root;
					_size = 1;
					assign_size(_limit->_value, _size);
					_limit->_parent = _root.base();
					result =  _root.base();
				}
				else
				{
					result = _insert(value, _alloc);
					_begin._ptr = leftmost(_root.base());
					++_size;
					assign_size(_limit->_value, _size);
					_limit->_parent = _root.base();
				}
				return result;
			}

			
			// Insert a new node in the tree skipping the search thanks to an iterator.
			// This function take a char to indicate if the value need to be left or right.
			// If the iterator is null, a classic insert a done.
			// If side is '1', the value will be inserted in the left of the iterator.
			void	insert(const_iterator it, const T& value, char side)
			{
				iterator	tmp(const_cast<node_type *>(it.base()), _limit);
				
				if (tmp.base() == NULL)
					insert(value);
				else
				{
					_root._ptr = _insert(tmp.base(), side, value, _alloc);
					_begin._ptr = leftmost(_root.base());
					++_size;
					assign_size(_limit->_value, _size);
					_limit->_parent = _root.base();
				}
			}

			// Insert a new node in the tree via a node_type reference.
			ft::RedBlackTreeNode<T, Compare>*	insert(const node_type &node)
			{
				node_pointer	result;
				
				if (_root.base() == NULL)
				{
					_root._ptr = _alloc.allocate(1);
					_alloc.construct(_root.base(), node._value);
					_begin = _root;
					_size = 1;
					assign_size(_limit->_value, _size);
					_limit->_parent = _root.base();
					result =  _root.base();
				}
				else
				{
					result = _insert(node._value, _alloc);
					_begin._ptr = leftmost(_root.base());
					++_size;
					assign_size(_limit->_value, _size);
					_limit->_parent = _root.base();
				}
				return result;
			}

			// Remove a node from the tree by calling the remove function of the root.
			void	remove(const T& value)
			{
				if (_root.base() != NULL)
				{
					try
					{
						if (_root._ptr != _limit && _root._ptr->_left == NULL &&
							_root._ptr->_right == NULL && _root._ptr->_right == NULL &&
							is_superior_in_key(_root.base(), value) == false &&
							is_inferior_in_key(_root.base(), value) == false)
						{
							_alloc.destroy(_root.base());
							_alloc.deallocate(_root.base(), 1);
							_root._ptr = NULL;
							_begin._ptr = NULL;
						}
						else
						{
							_root._ptr = _remove(value, _alloc);
							_begin._ptr = leftmost(_root.base());
						}
						--_size;
						assign_size(_limit->_value, _size);
						_limit->_parent = _root.base();
					}
					catch(...)
					{
						throw;
					}
				}
			}

			// This function will return the node with the given value.
			// If the node doesn't exist, it will return the limit.
			ft::RedBlackTreeNode<T, Compare>*	get(const T& value) const // ======= CAN BE CHANGED TO BE CLEVER.
			{
				node_pointer			current_node(_root.base());
				
				while (current_node)
				{
					// Logger() << "Searching for the node";
					if (is_superior_in_key(current_node, value) == true)
						current_node = current_node->_left;
					else if (is_inferior_in_key(current_node, value) == true)
						current_node = current_node->_right;
					else
					{
						// Logger() << "Node found";
						return (current_node);
					}
				}
				// Logger() << "Node not found";
				return (_limit);
			}

			// Operator to get the node with the value.
			ft::RedBlackTreeNode<T, Compare>*	operator[](const T& value) const
			{
				return get(value);
			}

			// Swap the tree with another tree.
			void	swap(rbtree &other)
			{
				std::swap(_root, other._root);
				std::swap(_begin, other._begin);
				std::swap(_limit, other._limit);
				std::swap(_size, other._size);
			}

			// Return the first node not less than the value.
			// Will not use the iterators increment to allow a log(n) complexity.
			const_iterator	lower_bound(const T& value) const
			{
				if (_root.base() == NULL)
					return end();
				iterator	it = _root;
				iterator	previous(NULL, _limit);
				while (it.base() != NULL)
				{
					if (is_superior_in_key(it.base(), value))
					{
						previous = it;
						it._ptr = it.base()->_left;
						if (it.base() == NULL)
							return previous;
					}
					else if (is_inferior_in_key(it.base(), value))
					{
						if (it.base()->_right == NULL)
							return (previous.base() == NULL) ? end() : previous;
						it._ptr = it.base()->_right;
					}
					else
						return it;
				}
				return end();
			}

			// Return the first node not less or equal than the value.
			// Will not use the iterators increment to allow a log(n) complexity.
			const_iterator	upper_bound(const T& value) const
			{
				if (_root.base() == NULL)
					return end();
				iterator	it = _root;
				iterator	previous(NULL, _limit);
				while (it.base() != NULL)
				{
					if (is_superior_in_key(it.base(), value))
					{
						previous = it;
						it._ptr = it.base()->_left;
						if (it.base() == NULL)
							return previous;
					}
					else if (is_inferior_in_key(it.base(), value))
					{
						if (it.base()->_right == NULL)
							return previous.base() == NULL ? end() : previous;
						it._ptr = it.base()->_right;
					}
					else if (previous.base() == NULL)
						return (it.base()->_right == NULL) ? end() : iterator(it.base()->_right, _limit);
					else
						return previous;
				}
				return end();
			}
			
			// Operators
			friend bool	operator==(const rbtree &lhs, const rbtree &rhs)
			{
				if (lhs.size() != rhs.size())
					return false;
				const_iterator 	lit = lhs.begin();
				const_iterator 	rit = rhs.begin();
				while (lit != lhs.end() && rit != rhs.end())
				{
					if (is_inferior(lit.base(), rit.base()) == true || is_inferior(rit.base(), lit.base()) == true)
						return false;
					++lit;
					++rit;
				}
				if (lit != lhs.end() || rit != rhs.end())
					return false;
				return true;
			}

			friend bool operator<(const rbtree &lhs, const rbtree &rhs)
			{
				const_iterator 	lit = lhs.begin();
				const_iterator 	rit = rhs.begin();

				while (lit != lhs.end())
				{
					if (rit == rhs.end() || is_inferior(rit.base(), lit.base()) == true)
						return false;
					else if (is_inferior(lit.base(), rit.base()) == true)
						return true;
					++lit;
					++rit;
				}
				if (rit == rhs.end())
					return false;
				return true;
			}
			private:

				// This function will actualyze the root of the tree.
				node_pointer			_update_root() const
				{
					node_pointer			current_node(_root.base());

					while (current_node != NULL && current_node->_parent != NULL)
						current_node = current_node->_parent;
					return (current_node);
				}
				
				// This function will insert a new node in the tree in a sorting order.
				// And resolve the red-black tree properties.
				// return the new root of the tree.
				node_pointer	_insert(const T& value, std::allocator<node_type>& alloc)
				{
					node_pointer			node(_root.base());
					node_pointer			result(node);
					
					while (node)
					{
						if (is_superior_in_key(node, value) == true)
						{
							if (node->_left == NULL)
							{
								node->_left = alloc.allocate(1);
								alloc.construct(node->_left, value); //=============== CAN BE CHANGED TO BE SOOOOO MUCH MORE EFFICIENT AND CLEVER.
								node->_left->_color = RED;
								node->_left->_parent = node;
								result = node->_left;
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
								alloc.construct(node->_right, value); //=============== CAN BE CHANGED TO BE SOOOOO MUCH MORE EFFICIENT AND CLEVER.
								node->_right->_color = RED;
								node->_right->_parent = node;
								result = node->_right;
								// Resolve the red-black tree properties.
								_resolve_insertion(node->_right);
								break ;
							}
							node = node->_right;
						}
						else
							throw std::runtime_error("RedBlackTreeNode::insert: value already exists.");
					}
					_root._ptr = _update_root();
					return (result);
				}
				
				// This function will insert a new node in the tree after a given node.
				// And resolve the red-black tree properties.
				// return the new root of the tree.
				node_pointer	_insert(node_pointer node, char side, const T& value, std::allocator<node_type>& alloc)
				{
					if (side == 0)
					{
						node->_right = alloc.allocate(1);
						alloc.construct(node->_right, value);
						node->_right->_color = RED;
						node->_right->_parent = node;
						_resolve_insertion(node->_right);
					}
					else if (side == 1)
					{
						node->_left = alloc.allocate(1);
						alloc.construct(node->_left, value);
						node->_left->_color = RED;
						node->_left->_parent = node;
						// Resolve the red-black tree properties.
						_resolve_insertion(node->_left);
					}
					return (_update_root());
				}
				
				// This function will remove the node with the given value.
				// If the node doesn't exist, a runtime_error is thrown.
				// return the new root of the tree.
				node_pointer  _remove(const T& value, std::allocator<node_type>& alloc)
				{
					node_pointer v = get(value);
				
					if (v == _limit)
						throw std::runtime_error("rbtree::_remove: node doesn't exist.");
					_delete_node(v, alloc);
					return (_update_root());
				}

				// TOOLS METHODS USED BY THE INTERN ALGORITHMS.

				// This function will resolve the red-black tree properties after a black node deletion.
				void _resolve_double_black(node_pointer node)
				{
					if (node == NULL || node->_parent == NULL)
						return;
				
					node_pointer sibling = _sibling(node);
					node_pointer parent = node->_parent;

					if (sibling == NULL)
					{
						_resolve_double_black(parent);
					}
					else
					{
						if (sibling->_color == RED)
						{
							parent->_color = RED;
							sibling->_color = BLACK;
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
							if ((sibling->_left != NULL && sibling->_left->_color == RED)
							|| (sibling->_right != NULL && sibling->_right->_color == RED))
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
										node_pointer tmp = sibling->_left;
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
										node_pointer tmp = sibling->_right;
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
								parent->_color = BLACK;
							}
							else
							{
								// 2 black children
								sibling->_color = RED;
								if (parent->_color == BLACK)
									_resolve_double_black(parent);
								else
									parent->_color = BLACK;
							}
						}
					}
				}

				// find node that do not have a left child
				// in the subtree of the given node
				node_pointer _successor(node_pointer node)
				{
					node_pointer temp = node;
				
					while (temp->_left != NULL)
						temp = temp->_left;
					return temp;
				}

				// find node that replaces a deleted node in BST
				node_pointer _find_replacement(node_pointer node)
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
				bool _are_both_black(node_pointer node1, node_pointer node2)
				{
					if (node1 == NULL && node2 == NULL)
						return true;
					else if (node1 == NULL && node2 != NULL && node2->_color == BLACK)
						return true;
					else if (node1 != NULL && node1->_color == BLACK && node2 == NULL)
						return true;
					else
						return (node1 != NULL && node2 != NULL
						&& node1->_color == BLACK && node2->_color == BLACK);
				}
				
				// returns pointer to sibling
				node_pointer _sibling(node_pointer current_node)
				{
					// sibling null if no parent
					if (current_node->_parent == NULL)
						return NULL;
				
					if (current_node->_parent->_left == current_node)
						return current_node->_parent->_right;
				
					return current_node->_parent->_left;
				}

				// Swap every links between 2 nodes.
				// Also redo links of nodes that have links on swaped nodes.
				void _swap_links(node_pointer node1, node_pointer node2)
				{
					std::swap(node1->_color, node2->_color);
					if (node2->_parent == node1)
					{
						node2->_parent = node1->_parent;
						node1->_parent = node2;
						if (node2->_parent != NULL)
						{
							if (node2->_parent->_left == node1)
								node2->_parent->_left = node2;
							else
								node2->_parent->_right = node2;
						}
						if (node1->_right == node2)
						{
							node1->_right = node2->_right;
							node2->_right = node1;
							if (node1->_right != NULL)
								node1->_right->_parent = node1;
							std::swap(node1->_left, node2->_left);
							if (node1->_left != NULL)
								node1->_left->_parent = node1;
							if (node2->_left != NULL)
								node2->_left->_parent = node2;
						}
						else if (node1->_left == node2)
						{
							node1->_left = node2->_left;
							node2->_left = node1;
							if (node1->_left != NULL)
								node1->_left->_parent = node1;
							std::swap(node1->_right, node2->_right);
							if (node1->_right != NULL)
								node1->_right->_parent = node1;
							if (node2->_right != NULL)
								node2->_right->_parent = node2;
						}
					}
					else
					{
						if (node1->_parent != NULL)
						{
							if (node1->_parent->_left == node1)
								node1->_parent->_left = node2;
							else
								node1->_parent->_right = node2;
						}
						if (node2->_parent != NULL)
						{
							if (node2->_parent->_left == node2)
								node2->_parent->_left = node1;
							else
								node2->_parent->_right = node1;
						}
						std::swap(node1->_parent, node2->_parent);
						std::swap(node1->_left, node2->_left);
						std::swap(node1->_right, node2->_right);
						if (node1->_left != NULL)
							node1->_left->_parent = node1;
						if (node1->_right != NULL)
							node1->_right->_parent = node1;
						if (node2->_left != NULL)
							node2->_left->_parent = node2;
						if (node2->_right != NULL)
							node2->_right->_parent = node2;
					}
					// Set the root and the parent of limit accordingly if a change as been done.
					if (node1->_parent == NULL)
						_root._ptr = node1;
					else if (node2->_parent == NULL)
						_root._ptr = node2;
					_limit->_parent = _root.base();
				}

				// Deletes the given node from the tree
				// After deletion, the node will be replaced by its successor
				// or NULL if the node is a leaf.
				// Will then resolve any double black nodes.
				void _delete_node(node_pointer node_to_del, std::allocator<node_type>& alloc)
				{
					if (node_to_del == NULL)
						return;
					node_pointer	replacement = _find_replacement(node_to_del);
					bool			is_r_n_black = _are_both_black(replacement, node_to_del);
					// node_pointer	parent = node_to_del->_parent;
				
					if (replacement == NULL)
					{
						// replacement is NULL therefore node_to_del is leaf
						if (node_to_del->_parent != NULL)
						{
							// Logger() << "replacement is NULL therefore node_to_del is leaf";
							if (is_r_n_black)
							{
								// replacement and node_to_del both black
								// node_to_del is leaf, fix double black at node_to_del
								_resolve_double_black(node_to_del);
							}
							else
							{
								// Node_to_del is red
								if (_sibling(node_to_del) != NULL)
									// sibling is not null, make it red"
									_sibling(node_to_del)->_color = RED;
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
							// std::swap(node_to_del->_value, replacement->_value); // NEED TO SWAP POINTERS AND NOT ONLY VALUES.
							// std::swap(node_to_del->_left, replacement->_left);
							// std::swap(node_to_del->_right, replacement->_right);
							// std::swap(node_to_del->_parent, replacement->_parent);
							// std::swap(node_to_del->_color, replacement->_color);
							_swap_links(node_to_del, replacement);
							replacement->_left = replacement->_right = NULL;
							// node_to_del->_left = node_to_del->_right = NULL;
							// alloc.destroy(replacement);
							// alloc.deallocate(replacement, 1);
							alloc.destroy(node_to_del);
							alloc.deallocate(node_to_del, 1);
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
								replacement->_color = BLACK;
						}
						return;
					}
					// Logger() << "node_to_del has 2 children";
					// node_to_del has 2 children, swap values with _successor and recurse
					// std::swap(node_to_del->_value, replacement->_value); // NEED TO SWAP POINTERS AND NOT ONLY VALUES.
					// _delete_node(replacement, alloc);
					// std::swap(node_to_del->_left, replacement->_left);
					// std::swap(node_to_del->_right, replacement->_right);
					// std::swap(node_to_del->_parent, replacement->_parent);
					// std::swap(node_to_del->_color, replacement->_color);
					_swap_links(node_to_del, replacement);
					_delete_node(node_to_del, alloc);
				}
					
				// This function function will rotate the tree to the left from the given node.
				// The node must be the right child of its parent.
				// behavior: The parent of the given node will become the left child of the node.
				// If the node already has a left child, it will become the right child of the parent.
				// Thus the sorted order of the tree will be preserved.
				void	_rotate_left(node_pointer node)
				{
					node_pointer			parent(node->_parent);
					node_pointer			left(node->_left);

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
				void	_rotate_right(node_pointer node)
				{
					node_pointer			parent(node->_parent);
					node_pointer			right(node->_right);

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
				void	_make_relation(node_pointer current_node,
					node_pointer* parent_node,
					node_pointer* grand_parent_node,
					node_pointer* uncle_node)
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
				void	_uncle_is_red(node_pointer node)
				{
					node_pointer	parent_node;
					node_pointer	grand_parent_node;
					node_pointer	uncle_node;

					_make_relation(node, &parent_node, &grand_parent_node, &uncle_node);
					if (uncle_node != NULL && uncle_node->_color == RED)
					{
						parent_node->_color = BLACK;
						uncle_node->_color = BLACK;
						grand_parent_node->_color = RED;
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
				void	_left_parent(node_pointer current_node)
				{
					node_pointer	parent_node;
					node_pointer	grand_parent_node;
					node_pointer	uncle_node;

					_make_relation(current_node, &parent_node, &grand_parent_node, &uncle_node);
					if (grand_parent_node->_left == parent_node)
					{
						if (parent_node->_right == current_node)
						{
							_rotate_left(current_node);
							_rotate_right(current_node);
							current_node->_color = BLACK;
							grand_parent_node->_color = RED;
						}
						else if (parent_node->_left == current_node)
						{
							_rotate_right(parent_node);
							parent_node->_color = BLACK;
							grand_parent_node->_color = RED;
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
				void	_right_parent(node_pointer current_node)
				{
					node_pointer	parent_node;
					node_pointer	grand_parent_node;
					node_pointer	uncle_node;

					_make_relation(current_node, &parent_node, &grand_parent_node, &uncle_node);
					if (grand_parent_node->_right == parent_node)
					{
						if (parent_node->_right == current_node)
						{
							_rotate_left(parent_node);
							parent_node->_color = BLACK;
							grand_parent_node->_color = RED;
						}
						else if (parent_node->_left == current_node)
						{
							_rotate_right(current_node);
							_rotate_left(current_node);
							current_node->_color = BLACK;
							grand_parent_node->_color = RED;
						}
						return;
					}
				}

				// This function will resolve the red-black tree properties after insertion.
				// It will either rotate the tree to the left or to the right. Or just recolor the nodes.
				// The node->_parent, node->_parent->_parent and node->_parent->_parent->[_left, _right] will be used.
				void	_resolve_insertion(node_pointer node)
				{
					node_pointer				parent_node;
					node_pointer				grand_parent_node;
					node_pointer				uncle_node;

					if (node == NULL)
						return ;

					_make_relation(node, &parent_node, &grand_parent_node, &uncle_node);

					// If the node is the root, just recolor it.
					if (parent_node == NULL)
					{
						node->_color = BLACK;
						return ;
					}

					// If the parent is black, the node is already correct.
					if (parent_node->_color == BLACK)
					{
						return;
					}
					if (uncle_node != NULL && uncle_node->_color == RED)
						_uncle_is_red(node);
					else if (grand_parent_node->_left == parent_node)
						_left_parent(node);
					else if (grand_parent_node->_right == parent_node)
						_right_parent(node);
					if (node->_color == RED)
						_resolve_insertion(node);
				}
	};

	template <typename T, typename Compare>
	bool	operator!=(const rbtree<T, Compare> &lhs, const rbtree<T, Compare> &rhs)
	{
		return !(lhs == rhs);
	}

	template <typename T, typename Compare>
	bool	operator>(const rbtree<T, Compare> &lhs, const rbtree<T, Compare> &rhs)
	{
		return rhs < lhs;
	}

	template <typename T, typename Compare>
	bool	operator<=(const rbtree<T, Compare> &lhs, const rbtree<T, Compare> &rhs)
	{
		return !(lhs > rhs);
	}

	template <typename T, typename Compare>
	bool	operator>=(const rbtree<T, Compare> &lhs, const rbtree<T, Compare> &rhs)
	{
		return !(lhs < rhs);
	}

	template <typename T, typename Compare>
	void	swap(rbtree<T, Compare> &lhs, rbtree<T, Compare> &rhs)
	{
		lhs.swap(rhs);
	}
}

#endif