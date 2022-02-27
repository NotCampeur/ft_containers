/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_modifiers_test.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 03:05:49 by ldutriez          #+#    #+#             */
/*   Updated: 2022/02/27 22:26:58 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

void	map_clear_method_test(void)
{
	struct timeval	start_time;
	
	Logger() << "__________(map_clear_method_test)__________";
	
	ft::map<int, int> mymap;
	
	for (int i=1; i<=5; i++) mymap.insert(ft::pair<int, int>(i, i));
	
	Logger() << "mymap contains:";
	for (ft::map<int, int>::iterator it = mymap.begin() ; it != mymap.end(); ++it)
		Logger() << it->first << " => " << it->second;
	
	gettimeofday(&start_time, NULL);
	mymap.clear();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";

	Logger() << "mymap contains:";
	for (ft::map<int, int>::iterator it = mymap.begin() ; it != mymap.end(); ++it)
		Logger() << it->first << " => " << it->second;
	Logger();
}

void	map_swap_method_test(void)
{
	struct timeval	start_time;

	Logger() << "__________[map_swap_method_test]__________";
	
	ft::map<char,int, std::greater<int> > foo,bar;

	foo['x']=100;
	foo['y']=200;

	bar['a']=11;
	bar['b']=22;
	bar['c']=33;

	Logger() << "foo contains:\n";
	for (ft::map<char,int, std::greater<int> >::iterator it=foo.begin(); it!=foo.end(); ++it)
		Logger() << it->first << " => " << it->second;

	Logger() << "bar contains:\n";
	for (ft::map<char,int, std::greater<int> >::iterator it=bar.begin(); it!=bar.end(); ++it)
		Logger() << it->first << " => " << it->second;
		
	gettimeofday(&start_time, NULL);
	foo.swap(bar);
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";

	Logger() << "foo contains:\n";
	for (ft::map<char,int, std::greater<int> >::iterator it=foo.begin(); it!=foo.end(); ++it)
		Logger() << it->first << " => " << it->second;

	Logger() << "bar contains:\n";
	for (ft::map<char,int, std::greater<int> >::iterator it=bar.begin(); it!=bar.end(); ++it)
		Logger() << it->first << " => " << it->second;
}

void	map_erase_method_test(void)
{
	struct timeval	start_time;

	Logger() << "__________[map_erase_method_test]__________";
	ft::map<int, int> mymap;
	gettimeofday(&start_time, NULL);
	mymap.erase(1);
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";

	for (int i=1; i<=5; i++) mymap.insert(ft::pair<int, int>(i, i));

	Logger() << "mymap contains:";
	for (ft::map<int, int>::iterator it = mymap.begin() ; it != mymap.end(); ++it)
		Logger() << it->first << " => " << it->second;
	gettimeofday(&start_time, NULL);
	mymap.erase(1);
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	Logger();
}

void	map_insert_method_test(void)
{
	struct timeval	start_time;

	Logger() << "__________[map_insert_method_test]__________";
	ft::map<int, int> mymap;
	gettimeofday(&start_time, NULL);
	mymap.insert(ft::pair<int, int>(1, 1));
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";

	for (int i=1; i<=5; i++) mymap.insert(ft::pair<int, int>(i, i));

	Logger() << "mymap contains:";
	for (ft::map<int, int>::iterator it = mymap.begin() ; it != mymap.end(); ++it)
		Logger() << it->first << " => " << it->second;
	gettimeofday(&start_time, NULL);
	mymap.insert(ft::pair<int, int>(1, 1));
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	Logger();
}

void	map_modifiers_test(void)
{
	Logger() << "\n----------(map_modifiers_test)----------";
	
	map_insert_method_test();
	map_erase_method_test();
	map_swap_method_test();
	map_clear_method_test();
}