/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integral_constant.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:03:24 by ldutriez          #+#    #+#             */
/*   Updated: 2022/01/21 17:03:28 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINERS_INTEGRAL_CONSTANT_HPP
# define CONTAINERS_INTEGRAL_CONSTANT_HPP

namespace ft
{
	template <class T, T v>
	struct integral_constant {
		static const T					value = v;
		
		typedef T						value_type;
		typedef integral_constant<T,v>	type;
		
		operator T() { return v; }
	};
	
	typedef integral_constant<bool,true> true_type;
	typedef integral_constant<bool,false> false_type;
}

#endif