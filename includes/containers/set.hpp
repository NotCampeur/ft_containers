/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 17:23:00 by notcampeur        #+#    #+#             */
/*   Updated: 2022/03/08 03:43:22 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINERS_SET_HPP
# define CONTAINERS_SET_HPP

# include <memory>
# include "pair.hpp"
# include "vector.hpp"
# include "../tools/iterators/bidirectional_iterator.hpp"
# include "binary_tree/new_red_black_tree.hpp"

namespace ft
{
	template < class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
	class set
	{
		public:
			typedef T												key_type;
			typedef T				 								value_type;
			typedef Compare 										key_compare;
			typedef Compare 										value_compare;
			typedef Alloc											allocator_type;
			

			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;

			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;

		private:
			typedef ft::rbtree<value_type, key_compare, allocator_type>	rbtree_type;
			typedef typename rbtree_type::node_type					node_type;
			
		public:
			typedef typename rbtree_type::const_iterator			iterator;
			typedef typename rbtree_type::const_iterator			const_iterator;

			typedef rb_reverse_iterator< const_iterator >			reverse_iterator;
			typedef rb_reverse_iterator< const_iterator >			const_reverse_iterator;

			typedef std::ptrdiff_t									difference_type;
			typedef std::size_t										size_type;
			
		private:

			rbtree_type												_tree;
			key_compare												_comp;
			allocator_type											_alloc;
			
		public:

			explicit set(const Compare& comp = Compare(), const allocator_type& alloc = allocator_type())
			: _tree(), _comp(comp), _alloc(alloc)
			{}

			template <class InputIterator>
			set(InputIterator first, InputIterator last,
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

			// The copy constructor will call the copy constructor of the ft::rbtree.
			// Which will do a deep copy of the tree.
			set(const set& other)
			: _tree(), _comp(other._comp), _alloc(other._alloc)
			{
				insert(other.begin(), other.end());
			}

			~set()
			{}

			set& operator=(const set& other)
			{
				if (this != &other)
				{
					_tree.clear();
					insert(other.begin(), other.end());
				}
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
				std::allocator<node_type> tree_alloc;
				return tree_alloc.max_size();
			}

			// Modifiers
			// A pair of an iterator and a bool is returned.
			// The iterator points to the element, either it was inserted or already existed.
			// The bool is true if the element was inserted, false if it already existed.
			ft::pair<iterator, bool> insert(const value_type& value)
			{
				size_type	size_before = _tree.size();
				
				return ft::make_pair(iterator(_tree.insert(value), _tree.limit()), size_before != _tree.size());
			}

			// This insert take a hint, which is an iterator to a position in the set.
			// It might be used to optimize the insertion.
			iterator insert(iterator hint, const value_type& value)
			{
				if (hint != end())
				{
					iterator next = hint;
					++next;
					if (*hint < value && (next == end() || *next > value))
					{
						if (hint.base()->_parent == next.base() || next == end())
							_tree.insert(hint, value, 0); // Insert the value to right of hint
						else
							_tree.insert(next, value, 1); // Insert the value to left of next
						return (--next);
					}
				}
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
					_tree.remove(*position);
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
					_tree.remove(key);
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
				iterator temp;

				for (; first != last;)
				{
					temp = first;
					++temp;
					erase(first);
					first = temp;
				}
			}

			// Will swap the contents of the set with another set.
			void swap(set& other)
			{
				_tree.swap(other._tree);
			}

			// Will clear the set.
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
				return iterator(_tree.get(key), _tree.limit());
			}

			const_iterator find(const key_type& key) const
			{
				return const_iterator(_tree.get(key), _tree.limit());
			}

			// This will return the number of elements with the key.
			size_type count(const key_type& key) const
			{
				return _tree.get(key) != _tree.limit();
			}

			// This will return an iterator to the first element not less than the key.
			// If the key is not found, the end() iterator is returned.
			iterator lower_bound(const key_type& key)
			{
				return iterator(const_cast<typename rbtree_type::node_type *>(_tree.lower_bound(key).base()), _tree.limit());
			}

			const_iterator lower_bound(const key_type& key) const
			{
				return const_iterator(_tree.lower_bound(key));
			}

			// This will return an iterator to the first element greater than the key.
			// If the key is not found, the end() iterator is returned.
			iterator upper_bound(const key_type& key)
			{
				return iterator(const_cast<typename rbtree_type::node_type *>(_tree.upper_bound(key).base()), _tree.limit());
			}

			const_iterator upper_bound(const key_type& key) const
			{
				return const_iterator(_tree.upper_bound(key));
			}
			
			// Return a pair of iterators to the range of elements with the key.
			// The first refer to the lower bound, the second to the upper bound.
			ft::pair<iterator, iterator> equal_range(const key_type& key)
			{
				return ft::make_pair(lower_bound(key), upper_bound(key));
			}

			ft::pair<const_iterator, const_iterator> equal_range(const key_type& key) const
			{
				return ft::make_pair(lower_bound(key), upper_bound(key));
			}

			// Allocator
			allocator_type get_allocator() const { return _alloc; }

			// Operations
			friend bool operator==(const set<T, Compare, Alloc>& lhs,
							const set<T, Compare, Alloc>& rhs)
			{
				if (lhs.size() != rhs.size())
					return false;
				return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
			}

			friend bool operator<(const set<T, Compare, Alloc>& lhs,
							const set<T, Compare, Alloc>& rhs)
			{
				return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
			}
	};
	template <class T, class Compare, class Allocator>
	bool operator!=(const set<T, Compare, Allocator>& lhs,
					const set<T, Compare, Allocator>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class T, class Compare, class Allocator>
	bool operator>(const set<T, Compare, Allocator>& lhs,
					const set<T, Compare, Allocator>& rhs)
	{
		return rhs < lhs;
	}

	template <class T, class Compare, class Allocator>
	bool operator<=(const set<T, Compare, Allocator>& lhs,
					const set<T, Compare, Allocator>& rhs)
	{
		return !(rhs < lhs);
	}

	template <class T, class Compare, class Allocator>
	bool operator>=(const set<T, Compare, Allocator>& lhs,
					const set<T, Compare, Allocator>& rhs)
	{
		return !(lhs < rhs);
	}

	template <class T, class Compare, class Allocator>
	void swap(set<T, Compare, Allocator>& lhs,
				set<T, Compare, Allocator>& rhs)
	{
		lhs.swap(rhs);
	}
}

#endif