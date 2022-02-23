/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 17:23:00 by notcampeur        #+#    #+#             */
/*   Updated: 2022/02/23 08:16:40 by ldutriez         ###   ########.fr       */
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
					_tree.insert(*first);
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
			mapped_type& operator[](const key_type& key)
			{
				node_type* node = _tree.get(value_type(key, mapped_type()));

				if (node == NULL)
					throw std::out_of_range("ft::map::operator[]");
				return node->value.second;
			}
	};
}

#endif