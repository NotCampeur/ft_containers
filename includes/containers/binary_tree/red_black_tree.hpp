/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:55:25 by ldutriez          #+#    #+#             */
/*   Updated: 2022/02/28 04:44:47 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINERS_RED_BLACK_TREE_HPP
# define CONTAINERS_RED_BLACK_TREE_HPP

# include <memory>
# include <exception>
# include "red_black_tree_node.hpp"
# include "../../tools/iterators/red_black_tree_iterator.hpp"
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
			typedef ft::RedBlackTreeNode<T, Compare, Alloc>			node_type;
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
			iterator				_last;
			
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
			: _alloc(), _limit(NULL), _root(NULL)
			, _begin(NULL), _last(NULL)
			, _size(0)
			{
				_limit = _alloc.allocate(1);
				_alloc.construct(_limit, ft::RedBlackTreeNode<T, Compare, Alloc>());
				_limit->set_limit(_limit);
			}
			
			rbtree(const rbtree &other)
			: _alloc(), _limit(NULL), _root(NULL)
			, _begin(NULL), _last(NULL)
			, _size(0)
			{
				_limit = _alloc.allocate(1);
				_alloc.construct(_limit, ft::RedBlackTreeNode<T, Compare, Alloc>());
				_limit->set_limit(_limit);
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
					_root = NULL;
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
				_root = NULL;
				_begin = NULL;
				_last = NULL;
				_size = 0;
				assign_size(*_limit->_value, _size);
			}
			
			// Iterators

			iterator		root() {return (_root.base() == NULL) ? iterator(_limit) : _root;}
			const_iterator	root() const {return (_root.base() == NULL) ? const_iterator(_limit) : const_iterator(_root);}
			
			iterator		begin() {return (_begin.base() == NULL) ? iterator(_limit) : _begin;}
			const_iterator	begin() const {return (_begin.base() == NULL) ? const_iterator(_limit) : const_iterator(_begin);}
			
			iterator		last() {return (_last.base() == NULL) ? iterator(_limit) : _last;}
			const_iterator	last() const {return (_last.base() == NULL) ? const_iterator(_limit) : const_iterator(_last);}
			
			iterator		end() {return iterator(_limit);}
			const_iterator	end() const {return const_iterator(_limit);}

			reverse_iterator		rbegin() {return reverse_iterator(end());}
			const_reverse_iterator	rbegin() const {return const_reverse_iterator(end());}

			reverse_iterator		rend() {return reverse_iterator(begin());}
			const_reverse_iterator	rend() const {return const_reverse_iterator(begin());}

			// Return the number of nodes in the tree. (Leaves doesn't count)
			size_type		size() const {return _size;}

			// Return the limit of the tree.
			node_pointer	limit() const {return _limit;}

			// Insert a new node in the tree by calling the insert function of the root.
			void	insert(const T& value)
			{
				if (_root == iterator(NULL))
				{
					_root = _alloc.allocate(1);
					_alloc.construct(_root.base(), ft::RedBlackTreeNode<T, Compare, Alloc>(value));
					_root.base()->set_limit(_limit);
					_begin = _root;
					_last = _root;
					_size = 1;
					assign_size(*_limit->_value, _size);
					_limit->_parent = _root.base();
				}
				else
				{
					_root = _root.base()->insert(value, _limit, _alloc);
					_begin = static_cast<iterator>(leftmost(_root.base()));
					_last = static_cast<iterator>(rightmost(_root.base()));
					++_size;
					assign_size(*_limit->_value, _size);
					_limit->_parent = _root.base();
				}
			}

			// Insert a new node in the tree via a node_type reference.
			void	insert(const node_type &node)
			{
				if (_root == iterator(NULL))
				{
					_limit = _alloc.allocate(1);
					_alloc.construct(_limit, ft::RedBlackTreeNode<T, Compare, Alloc>());
					_limit->set_limit(_limit);
					_root = _alloc.allocate(1);
					_alloc.construct(_root.base(), node._value);
					_root.base()->set_limit(_limit);
					_begin = _root;
					_last = _root;
					_size = 1;
					assign_size(*_limit->_value, _size);
					_limit->_parent = _root.base();
				}
				else
				{
					_root = _root.base()->insert(node._value, _limit, _alloc);
					_begin = static_cast<iterator>(leftmost(_root.base()));
					_last = static_cast<iterator>(rightmost(_root.base()));
					++_size;
					assign_size(*_limit->_value, _size);
					_limit->_parent = _root.base();
				}
			}

			// Remove a node from the tree by calling the remove function of the root.
			void	remove(const T& value)
			{
				if (_root != iterator(NULL))
				{
					try
					{
						_root = _root.base()->remove(value, _alloc);
						_begin = static_cast<iterator>(leftmost(_root.base()));
						_last = static_cast<iterator>(rightmost(_root.base()));
						--_size;
						assign_size(*_limit->_value, _size);
						_limit->_parent = _root.base();
					}
					catch(...)
					{
						throw;
					}
				}
			}

			// Get the node with the value.
			ft::RedBlackTreeNode<T, Compare>*	get(const T& value) const
			{
				if (_root.base() == NULL)
					return _limit;
				return _root.base()->node(value);
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
				std::swap(_last, other._last);
				std::swap(_limit, other._limit);
				std::swap(_size, other._size);
			}

			// Return the first node not less than the value.
			iterator	lower_bound(const T& value)
			{
				iterator	it = begin();
				while (it != end() && is_inferior_in_key(it.base(), value) == true)
					++it;
				return it;
			}

			// Return the first node not less or equal than the value.
			iterator	upper_bound(const T& value)
			{
				iterator	it = lower_bound(value);
				if (it != end() &&
					is_inferior_in_key(it.base(), value) == false &&
					is_superior_in_key(it.base(), value) == false)
					++it;
				return it;
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