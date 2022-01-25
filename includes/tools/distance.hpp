/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 18:52:12 by ldutriez          #+#    #+#             */
/*   Updated: 2022/01/25 17:46:10 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINERS_DISTANCE_HPP
# define CONTAINERS_DISTANCE_HPP  

#include "iterator_traits.hpp"
#include "iterator_tags.hpp"
#include <iterator>

namespace ft
{
	template<class InputIterator>
	std::ptrdiff_t do_distance (InputIterator first, InputIterator last, std::random_access_iterator_tag)
	{
		return (last - first);
	}

	template<class InputIterator>
	std::ptrdiff_t do_distance (InputIterator first, InputIterator last, ft::random_access_iterator_tag)
	{
		return (last - first);
	}

	template<class InputIterator>
	std::ptrdiff_t do_distance (InputIterator first, InputIterator last, std::input_iterator_tag)
	{
		int sum(0);
		while (first != last)
		{
			first++;
			sum++;
		}
		return (sum);
	}

	template<class InputIterator>
	std::ptrdiff_t do_distance (InputIterator first, InputIterator last, ft::input_iterator_tag)
	{
		int sum(0);
		while (first != last)
		{
			first++;
			sum++;
		}
		return (sum);
	}

	template<class InputIterator>
	std::ptrdiff_t distance (InputIterator first, InputIterator last)
	{
		return (do_distance(first, last, typename ft::iterator_traits<InputIterator>::iterator_category()));
	};
}

#endif