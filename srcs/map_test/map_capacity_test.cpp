/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_capacity_test.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 02:58:38 by ldutriez          #+#    #+#             */
/*   Updated: 2022/02/26 04:51:07 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

void	map_max_size_method_test(void)
{
	struct timeval	start_time;

	Logger() << "__________[map_max_size_method_test]__________";
	ft::map<int, int> mymap;
	gettimeofday(&start_time, NULL);
	Logger() << "Max size : " << mymap.max_size();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";

	for (int i=1; i<=5; i++) mymap.insert(ft::pair<int, int>(i, i));

	Logger() << "mymap contains:";
	for (ft::map<int, int>::iterator it = mymap.begin() ; it != mymap.end(); ++it)
		Logger() << it->first << " => " << it->second;
	gettimeofday(&start_time, NULL);
	Logger() << "Max size : " << mymap.max_size();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	Logger();
}

void	map_size_method_test(void)
{
	struct timeval	start_time;

	Logger() << "__________[map_size_method_test]__________";
	ft::map<int, int> mymap;
	gettimeofday(&start_time, NULL);
	Logger() << "Size : " << mymap.size();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";

	for (int i=1; i<=5; i++) mymap.insert(ft::pair<int, int>(i, i));

	Logger() << "mymap contains:";
	for (ft::map<int, int>::iterator it = mymap.begin() ; it != mymap.end(); ++it)
		Logger() << it->first << " => " << it->second;
	gettimeofday(&start_time, NULL);
	Logger() << "Size : " << mymap.size();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	Logger();
}

void	map_empty_method_test(void)
{
	struct timeval	start_time;

	Logger() << "__________[map_empty_method_test]__________";
	ft::map<int, int> mymap;
	gettimeofday(&start_time, NULL);
	Logger() << "Is empty : " << mymap.empty();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";

	for (int i=1; i<=5; i++) mymap.insert(ft::pair<int, int>(i, i));

	Logger() << "mymap contains:";
	for (ft::map<int, int>::iterator it = mymap.begin() ; it != mymap.end(); ++it)
		Logger() << it->first << " => " << it->second;
	gettimeofday(&start_time, NULL);
	Logger() << "Is empty : " << mymap.empty();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	Logger();
}

void	map_capacity_test(void)
{
	Logger() << "\n----------(map_capacity_test)----------";
	
	map_empty_method_test();
	map_size_method_test();
	map_max_size_method_test();
}