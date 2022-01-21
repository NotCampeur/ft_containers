/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 17:23:57 by ldutriez          #+#    #+#             */
/*   Updated: 2022/01/21 17:24:56 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINERS_ENABLE_IF_HPP
# define CONTAINERS_ENABLE_IF_HPP

namespace ft
{
	template <bool B, class T = void>
	struct enable_if
	{
		typedef T type;
	};

	template <class T>
	struct enable_if<false, T>
	{
	};
}

#endif