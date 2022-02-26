/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterators_test.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 02:53:11 by ldutriez          #+#    #+#             */
/*   Updated: 2022/02/26 04:53:16 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

void	map_rend_method_test(void)
{
	struct timeval	start_time;
	
	Logger() << "__________[map_rend_method_test]__________";
	ft::map<int, int> mymap;
	gettimeofday(&start_time, NULL);
	mymap.rend();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	
	for (int i=1; i<=5; i++) mymap[i] = i;
	
	Logger() << "mymap contains:";
	ft::map<int, int>::reverse_iterator it = mymap.rbegin();
	for (; it != mymap.rend(); ++it)
		Logger() << it->first << " => " << it->second;
	++it;
	Logger() << it->first << " => " << it->second;
	gettimeofday(&start_time, NULL);
	mymap.rend();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	Logger();
}

void	map_rbegin_method_test(void)
{
	struct timeval	start_time;
	
	Logger() << "__________[map_rbegin_method_test]__________";
	ft::map<int, int> mymap;
	gettimeofday(&start_time, NULL);
	mymap.rbegin();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	
	for (int i=1; i<=5; i++) mymap.insert(ft::pair<int, int>(i, i));
	
	Logger() << "mymap contains:";
	for (ft::map<int, int>::reverse_iterator it = mymap.rbegin() ; it != mymap.rend(); ++it)
		Logger() << it->first << " => " << it->second;
	gettimeofday(&start_time, NULL);
	mymap.rbegin();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	Logger();
}

void	map_end_method_test(void)
{
	struct timeval	start_time;

	Logger() << "__________[map_end_method_test]__________";
	ft::map<int, int> mymap;
	gettimeofday(&start_time, NULL);
	mymap.end();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";

	for (int i=1; i<=5; i++) mymap[i] = i;

	Logger() << "mymap contains:";
	ft::map<int, int>::iterator it = mymap.begin();
	for (; it != mymap.end(); ++it)
		Logger() << it->first << " => " << it->second;
	it++;
	Logger() << it->first << " => " << it->second;
	gettimeofday(&start_time, NULL);
	mymap.end();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	Logger();
}

void	map_begin_method_test(void)
{
	struct timeval	start_time;

	Logger() << "__________[map_begin_method_test]__________";
	ft::map<int, int> mymap;
	gettimeofday(&start_time, NULL);
	mymap.begin();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	for (int i=1; i<=5; i++) mymap.insert(ft::pair<int, int>(i, i));

	Logger() << "mymap contains:";
	for (ft::map<int, int>::iterator it = mymap.begin() ; it != mymap.end(); ++it)
		Logger() << it->first << " => " << it->second;
	gettimeofday(&start_time, NULL);
	mymap.begin();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	Logger();
}

void	map_iterators_test(void)
{
	Logger() << "\n----------(map_iterators_test)----------";

	map_begin_method_test();
	map_end_method_test();
	map_rbegin_method_test();
	map_rend_method_test();	
}