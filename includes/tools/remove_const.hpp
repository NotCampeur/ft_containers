/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_const.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 05:29:05 by ldutriez          #+#    #+#             */
/*   Updated: 2022/02/26 05:29:41 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINERS_REMOVE_CONST_HPP
# define CONTAINERS_REMOVE_CONST_HPP

namespace ft
{
	template< class T >
	struct remove_const
	{
		typedef T type;
	};

	template< class T >
	struct remove_const< const T >
	{
		typedef T type;
	};
}

#endif