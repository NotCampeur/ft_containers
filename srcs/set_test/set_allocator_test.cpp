/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_allocator_test.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 04:06:43 by ldutriez          #+#    #+#             */
/*   Updated: 2022/02/28 05:43:44 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

void	set_allocator_test(void)
{
	struct timeval	start_time;
	Logger() << "\n----------(set_allocator_test)----------";

	Logger() << "__________[set_get_allocator_method_test]__________";
	ft::set<int> myset;
	gettimeofday(&start_time, NULL);
	myset.get_allocator();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";

}