/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:14:53 by ldutriez          #+#    #+#             */
/*   Updated: 2022/02/01 17:26:10 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINERS_EQUAL_HPP
# define CONTAINERS_EQUAL_HPP

namespace ft
{
	template< class InputIt1, class InputIt2 >
	bool	equal( InputIt1 first1, InputIt1 last1,
					InputIt2 first2 )
	{
		while ( first1 != last1 )
		{
			if ( *first1 == *first2 )
			{
				first1++;
				first2++;
			}
			else
				return false;
		}
		return true;
	}

	template< class InputIt1, class InputIt2, class BinaryPredicate >
	bool	equal( InputIt1 first1, InputIt1 last1,
					InputIt2 first2, BinaryPredicate p )
	{
		while ( first1 != last1 )
		{
			if ( p( first1, first2 ) == true )
			{
				first1++;
				first2++;
			}
			else
				return false;
		}
		return true;
	}
}

#endif