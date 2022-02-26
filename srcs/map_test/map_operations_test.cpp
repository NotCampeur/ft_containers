/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_operations_test.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 03:46:59 by ldutriez          #+#    #+#             */
/*   Updated: 2022/02/26 04:53:16 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

void	map_equal_range_method_test(void)
{
	struct timeval	start_time;

	Logger() << "__________[map_equal_range_method_test]__________";
	ft::map<int, int> mymap;
	gettimeofday(&start_time, NULL);
	mymap.equal_range(1);
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	Logger() << "Equal range key | value : " << mymap.equal_range(1).first->first << " | " << mymap.equal_range(1).first->second;

	for (int i=1; i<=5; i++) mymap.insert(ft::pair<int, int>(i, i));

	Logger() << "mymap contains:";
	for (ft::map<int, int>::iterator it = mymap.begin() ; it != mymap.end(); ++it)
	Logger() << it->first << " => " << it->second;
	gettimeofday(&start_time, NULL);
	mymap.equal_range(1);
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	Logger() << "Equal range key | value : " << mymap.equal_range(1).first->first << " | " << mymap.equal_range(1).first->second;
	Logger();
}

void	map_upper_bound_method_test(void)
{
	struct timeval	start_time;

	Logger() << "__________[map_upper_bound_method_test]__________";
	ft::map<int, int> mymap;
	gettimeofday(&start_time, NULL);
	mymap.upper_bound(1);
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	Logger() << "Upper bound key : " << mymap.upper_bound(1)->first;

	for (int i=1; i<=5; i++) mymap.insert(ft::pair<int, int>(i, i));

	Logger() << "mymap contains:";
	for (ft::map<int, int>::iterator it = mymap.begin() ; it != mymap.end(); ++it)
		Logger() << it->first << " => " << it->second;
	gettimeofday(&start_time, NULL);
	mymap.upper_bound(1);
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	Logger() << "Upper bound key : " << mymap.upper_bound(1)->first;
	Logger();
}

void	map_lower_bound_method_test(void)
{
	struct timeval	start_time;

	Logger() << "__________[map_lower_bound_method_test]__________";
	ft::map<int, int> mymap;
	gettimeofday(&start_time, NULL);
	mymap.lower_bound(0);
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	Logger() << "Lower bound key : " << mymap.lower_bound(0)->first;

	for (int i=1; i<=5; i++) mymap.insert(ft::pair<int, int>(i, i));

	Logger() << "mymap contains:";
	for (ft::map<int, int>::iterator it = mymap.begin() ; it != mymap.end(); ++it)
	Logger() << it->first << " => " << it->second;
	gettimeofday(&start_time, NULL);
	mymap.lower_bound(0);
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	Logger() << "Lower bound key : " << mymap.lower_bound(0)->first;
	Logger();
}

void	map_count_method_test(void)
{
	struct timeval	start_time;
	
	Logger() << "__________[map_count_method_test]__________";
	ft::map<int, int> mymap;
	gettimeofday(&start_time, NULL);
	mymap.count(1);
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	Logger() << "Map count : " << mymap.count(1);
	
	for (int i=1; i<=5; i++) mymap.insert(ft::pair<int, int>(i, i));
	
	Logger() << "mymap contains:";
	for (ft::map<int, int>::iterator it = mymap.begin() ; it != mymap.end(); ++it)
		Logger() << it->first << " => " << it->second;
	
	gettimeofday(&start_time, NULL);
	mymap.count(1);
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	Logger() << "Map count : " << mymap.count(1);
	
	Logger();
}

void	map_find_method_test(void)
{
	struct timeval	start_time;

	Logger() << "__________[map_find_method_test]__________";
	ft::map<int, int> mymap;
	gettimeofday(&start_time, NULL);
	mymap.find(1);
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	Logger() << "Map find : " << mymap.find(1)->first << " | " << mymap.find(1)->second;

	for (int i=1; i<=5; i++) mymap.insert(ft::pair<int, int>(i, i));

	Logger() << "mymap contains:";
	for (ft::map<int, int>::iterator it = mymap.begin() ; it != mymap.end(); ++it)
		Logger() << it->first << " => " << it->second;
	gettimeofday(&start_time, NULL);
	mymap.find(1);
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	Logger() << "Map find : " << mymap.find(1)->first << " | " << mymap.find(1)->second;
	Logger();
}

void	map_operations_test(void)
{
	Logger() << "\n----------(map_operations_test)----------";

	map_find_method_test();
	map_count_method_test();
	map_lower_bound_method_test();
	map_upper_bound_method_test();
	map_equal_range_method_test();
}