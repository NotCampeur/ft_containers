/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexicographical_compare.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:29:43 by ldutriez          #+#    #+#             */
/*   Updated: 2022/02/01 12:58:59 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINERS_LEXICOGRAPHICAL_COMPARE_HPP
# define CONTAINERS_LEXICOGRAPHICAL_COMPARE_HPP

namespace ft
{
	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
								InputIterator2 first2, InputIterator2 last2)
		
	{
		while (first1 != last1)
		{
			if (*first1 > *first2 || first2 == last2)
				return false;
			else if (*first1 < *first2)
				return true;
			++first2;
			++first1;
		}
		if (first2 == last2)
			return false;
		return true;
	}

	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
								InputIterator2 first2, InputIterator2 last2,
								Compare comp)
	{
		while (first1 != last1)
		{
			if (first2 == last2 && comp(*first2, *first1) == true)
				return false;
			else if (comp(*first1, *first2) == true)
				return true;
			first1++;
			first2++;
		}
		if (first2 == last2)
			return false;
		return true;
	}
}

#endif