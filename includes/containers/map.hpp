/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 17:23:00 by notcampeur        #+#    #+#             */
/*   Updated: 2022/02/02 17:03:21 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINERS_MAP_HPP
# define CONTAINERS_MAP_HPP

# include <memory>
# include "pair.hpp"

namespace ft
{
	template < class Key, // map::key_type
		class T, // map::mapped_type
		class Compare = std::less<Key>, // map::key_compare
		class Alloc = std::allocator<std::pair<const Key,T> > > // map::allocator_type
	class map;
}

#endif