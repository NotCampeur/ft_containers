/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_allocator_test.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 04:06:43 by ldutriez          #+#    #+#             */
/*   Updated: 2022/02/26 04:10:19 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

void	map_allocator_test(void)
{
	struct timeval	start_time;
	Logger() << "\n----------(map_operations_test)----------";

	Logger() << "__________[map_get_allocator_method_test]__________";
	ft::map<int, int> mymap;
	gettimeofday(&start_time, NULL);
	mymap.get_allocator();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";

}