/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 17:23:00 by notcampeur        #+#    #+#             */
/*   Updated: 2022/02/24 03:17:28 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINERS_MAP_HPP
# define CONTAINERS_MAP_HPP

# include <memory>
# include "pair.hpp"
# include "../tools/iterators/bidirectional_iterator.hpp"
# include "../binary_tree/red_black_tree.hpp"

namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>,
		class Alloc = std::allocator<std::pair<const Key,T> > >
	class map
	{
		public:
			typedef Key 											key_type;
			typedef T												mapped_type;
			typedef std::pair<const Key,T> 							value_type;
			typedef Compare 										key_compare;
			typedef Alloc											allocator_type;
			
			typedef std::size_t										size_type;
			typedef std::ptrdiff_t									difference_type;

			typedef value_type&										reference;
			typedef const value_type& 								const_reference;

			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;

			typedef rbtree<value_type, key_compare>					rbtree_type;
			typedef typename rbtree_type::node_type					node_type;
			
			typedef red_black_tree_iterator< node_type >			iterator;
			typedef const_red_black_tree_iterator< node_type >		const_iterator;

			typedef ft::reverse_iterator< iterator >				reverse_iterator;
			typedef ft::reverse_iterator< const_iterator >			const_reverse_iterator;

		private:

			rbtree_type												_tree;
			key_compare												_comp;
			allocator_type											_alloc;
			
		public:

			class value_compare : public std::binary_function<value_type, value_type, bool>
			{
				friend class map;
				protected:
					Compare comp;
					value_compare(Compare c) : comp(c) {}
				public:
					bool operator()(const value_type& x, const value_type& y) const { return comp(x.first, y.first); }
			};

			explicit map(const Compare& comp = Compare(), const allocator_type& alloc = allocator_type())
			: _tree(), _comp(comp), _alloc(alloc) {}

			template <class InputIterator>
			map(InputIterator first, InputIterator last,
			const Compare& comp = Compare(), const allocator_type& alloc = allocator_type())
			: _tree(), _comp(comp), _alloc(alloc)
			{
				for (; first != last; ++first)
				{
					try
					{
						_tree.insert(*first);
					}
					catch(...)
					{
					}
				}
			}

			// The copy constructor will call the copy constructor of the rbtree.
			// Which will do a deep copy of the tree.
			map(const map& other)
			: _tree(other._tree) {}

			~map() {}

			map& operator=(const map& other)
			{
				if (this != &other)
					_tree = other._tree;
				return *this;
			}

			// Iterators
			iterator begin() { return _tree.begin(); }
			const_iterator begin() const { return _tree.begin(); }

			iterator end() { return _tree.end(); }
			const_iterator end() const { return _tree.end(); }

			reverse_iterator rbegin() { return _tree.rbegin(); }
			const_reverse_iterator rbegin() const { return _tree.rbegin(); }

			reverse_iterator rend() { return _tree.rend(); }
			const_reverse_iterator rend() const { return _tree.rend(); }

			// Capacity
			bool empty() const { return _tree.size() == 0; }
			size_type size() const { return _tree.size(); }
			size_type max_size() const
			{
				std::allocator<node_type> alloc;
				return alloc.max_size();
			}

			// Element access
			// If key matches a key in the map, a reference to the mapped value is returned.
			// Otherwise, a node is created with the key and a default-constructed value,
			mapped_type& operator[](const key_type& key)
			{
				return insert(ft::make_pair(key, mapped_type())).first->second;
			}

			// Modifiers
			// A pair of an iterator and a bool is returned.
			// The iterator points to the element, either it was inserted or already existed.
			// The bool is true if the element was inserted, false if it already existed.
			std::pair<iterator, bool> insert(const value_type& value)
			{
				bool	was_present = false;
				try
				{
					_tree.insert(value);
					was_present = true;
				}
				catch(...)
				{
				}
				return ft::make_pair(iterator(_tree.get(value)), was_present);
			}

			// This insert take a hint, which is an iterator to a position in the map.
			// It might be used to optimize the insertion.
			iterator insert(iterator hint, const value_type& value)
			{
				if (hint->_value.first == value.first)
					return hint;
				return insert(value).first;
			}

			// This insert will take a range of values.
			template <class InputIterator>
			void insert(InputIterator first, InputIterator last)
			{
				for (; first != last; ++first)
				{
					try
					{
						_tree.insert(*first);
					}
					catch(...)
					{
					}
				}
			}

			// Will erase the element pointer by the iterator.
			void erase(iterator position)
			{
				try
				{
					_tree.remove(position->_value);
				}
				catch(...)
				{
				}
			}

			// Will erase the element with the key.
			size_type	erase(const key_type& key)
			{
				try
				{
					_tree.remove(value_type(key, mapped_type()));
					return 1;
				}
				catch(...)
				{
				}
				return 0;
			}

			// Will erase the range of elements.
			void erase(iterator first, iterator last)
			{
				for (; first != last; ++first)
				{
					try
					{
						_tree.remove(first->_value);
					}
					catch(...)
					{
					}
				}
			}

			// Will swap the contents of the map with another map.
			void swap(map& other)
			{
				_tree.swap(other._tree);
			}

			// Will clear the map.
			void clear()
			{
				_tree.clear();
			}

			// Observers
			key_compare key_comp() const { return _comp; }
			value_compare value_comp() const { return value_compare(_comp); }

			// Operations
			// This will return an iterator to the element with the key.
			// If the key is not found, the end() iterator is returned.
			iterator find(const key_type& key)
			{
				return iterator(_tree.get(value_type(key, mapped_type())));
			}

			const_iterator find(const key_type& key) const
			{
				return const_iterator(_tree.get(value_type(key, mapped_type())));
			}

			// This will return the number of elements with the key.
			size_type count(const key_type& key) const
			{
				return _tree.get(value_type(key, mapped_type())) != _tree.limit();
			}

			// This will return an iterator to the first element not less than the key.
			// If the key is not found, the end() iterator is returned.
			iterator lower_bound(const key_type& key)
			{
				return iterator(_tree.lower_bound(value_type(key, mapped_type())));
			}

			const_iterator lower_bound(const key_type& key) const
			{
				return const_iterator(_tree.lower_bound(value_type(key, mapped_type())));
			}

			// This will return an iterator to the first element greater than the key.
			// If the key is not found, the end() iterator is returned.
			iterator upper_bound(const key_type& key)
			{
				return iterator(_tree.upper_bound(value_type(key, mapped_type())));
			}

			// Return a pair of iterators to the range of elements with the key.
			ft::pair<iterator, iterator> equal_range(const key_type& key)
			{
				iterator	it = find(key);
				return ft::make_pair(it, it);
			}

			ft::pair<const_iterator, const_iterator> equal_range(const key_type& key) const
			{
				const_iterator	it = find(key);
				return ft::make_pair(it, it);
			}

			// Allocator
			allocator_type get_allocator() const { return _tree.get_allocator(); }

			// Operations
			friend bool operator==(const map<Key, T, Compare, Alloc>& lhs,
							const map<Key, T, Compare, Alloc>& rhs)
			{
				return lhs._tree == rhs._tree;
			}

			friend bool operator<(const map<Key, T, Compare, Alloc>& lhs,
							const map<Key, T, Compare, Alloc>& rhs)
			{
				return lhs._tree < rhs._tree;
			}
	};
	template <class Key, class T, class Compare, class Allocator>
	bool operator!=(const map<Key, T, Compare, Allocator>& lhs,
					const map<Key, T, Compare, Allocator>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class Key, class T, class Compare, class Allocator>
	bool operator>(const map<Key, T, Compare, Allocator>& lhs,
					const map<Key, T, Compare, Allocator>& rhs)
	{
		return rhs < lhs;
	}

	template <class Key, class T, class Compare, class Allocator>
	bool operator<=(const map<Key, T, Compare, Allocator>& lhs,
					const map<Key, T, Compare, Allocator>& rhs)
	{
		return !(rhs < lhs);
	}

	template <class Key, class T, class Compare, class Allocator>
	bool operator>=(const map<Key, T, Compare, Allocator>& lhs,
					const map<Key, T, Compare, Allocator>& rhs)
	{
		return !(lhs < rhs);
	}

	template <class Key, class T, class Compare, class Allocator>
	void swap(map<Key, T, Compare, Allocator>& lhs,
				map<Key, T, Compare, Allocator>& rhs)
	{
		lhs.swap(rhs);
	}
}

#endif