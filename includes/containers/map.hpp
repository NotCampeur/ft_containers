/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 17:23:00 by notcampeur        #+#    #+#             */
/*   Updated: 2022/02/04 18:24:18 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINERS_MAP_HPP
# define CONTAINERS_MAP_HPP

# include <memory>
# include "pair.hpp"
# include "../tools/iterators/bidirectional_iterator.hpp"
# include "binary_search_tree.hpp"

namespace ft
{
	template < class Key,
		class T,
		class Compare = std::less<Key>,
		class Alloc = std::allocator<std::pair<const Key,T> > >
	class map
	{
		public:
			typedef Key key_type;
			typedef T mapped_type;
			typedef std::pair<const Key,T> value_type;
			typedef std::size_t	size_type;
			typedef std::ptrdiff_t difference_type;
			typedef Compare key_compare;
			typedef Alloc allocator_type;

			typedef value_type& reference;
			typedef const value_type& const_reference;

			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;

			typedef ft::bidirectional_iterator<value_type> iterator;
			typedef ft::bidirectional_iterator<const value_type> const_iterator;
		
			typedef std::reverse_iterator<iterator> reverse_iterator;
			typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
	};
}

#endif