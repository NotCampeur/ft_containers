/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 14:55:57 by ldutriez          #+#    #+#             */
/*   Updated: 2022/01/21 17:04:52 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINERS_IS_INTEGRAL_HPP
# define CONTAINERS_IS_INTEGRAL_HPP

# include "integral_constant.hpp"

namespace ft
{
	template <class T>
	struct is_integral : public false_type {};

	template <class T>
	struct is_integral<const T> : is_integral<T> {};

	template <class T>
	struct is_integral<volatile T> : is_integral<T> {};

	template <class T>
	struct is_integral<const volatile T> : is_integral<T> {};

	template <>
	struct is_integral<bool> : true_type {};
	template <>
	struct is_integral<char> : true_type {};
	template <>
	struct is_integral<wchar_t> : true_type {};
	template <>
	struct is_integral<signed char> : true_type {};
	template <>
	struct is_integral<short int> : true_type {};
	template <>
	struct is_integral<int> : true_type {};
	template <>
	struct is_integral<long int> : true_type {};
	template <>
	struct is_integral<long long int> : true_type {};
	template <>
	struct is_integral<unsigned char> : true_type {};
	template <>
	struct is_integral<unsigned short int> : true_type {};
	template <>
	struct is_integral<unsigned int> : true_type {};
	template <>
	struct is_integral<unsigned long int> : true_type {};
	template <>
	struct is_integral<unsigned long long int> : true_type {};
}

#endif