/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_element_access_test.cpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 03:02:05 by ldutriez          #+#    #+#             */
/*   Updated: 2022/02/26 04:53:16 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

void	map_access_operator_test(void)
{
	struct timeval	start_time;

	Logger() << "__________[map_access_operator_test]__________";
	ft::map<int, int> mymap;
	gettimeofday(&start_time, NULL);
	Logger() << "Key and value : " << 1 << " " << mymap[1];
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";

	for (int i=1; i<=5; i++) mymap.insert(ft::pair<int, int>(i, i));

	Logger() << "mymap contains:";
	for (ft::map<int, int>::iterator it = mymap.begin() ; it != mymap.end(); ++it)
		Logger() << it->first << " => " << it->second;
	gettimeofday(&start_time, NULL);
	Logger() << "Key and value : " << 1 << " " << mymap[1];
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	Logger();
}

void	map_element_access_test(void)
{
	Logger() << "\n----------(map_element_access_test)----------";
	
	map_access_operator_test();
}