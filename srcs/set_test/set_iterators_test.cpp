/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_iterators_test.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 02:53:11 by ldutriez          #+#    #+#             */
/*   Updated: 2022/02/28 06:00:00 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

void	set_rend_method_test(void)
{
	struct timeval	start_time;
	
	Logger() << "__________[set_rend_method_test]__________";
	ft::set<int> myset;
	gettimeofday(&start_time, NULL);
	myset.rend();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	
	for (int i=1; i<=5; i++) myset.insert(i);
	
	Logger() << "myset contains:";
	ft::set<int>::reverse_iterator it = myset.rbegin();
	for (; it != myset.rend(); ++it)
		Logger() << *it;
	++it;
	Logger() << *it;
	gettimeofday(&start_time, NULL);
	myset.rend();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	Logger();
}

void	set_rbegin_method_test(void)
{
	struct timeval	start_time;
	
	Logger() << "__________[set_rbegin_method_test]__________";
	ft::set<int> myset;
	gettimeofday(&start_time, NULL);
	myset.rbegin();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	
	for (int i=1; i<=5; i++) myset.insert(i);
	
	Logger() << "myset contains:";
	for (ft::set<int>::reverse_iterator it = myset.rbegin() ; it != myset.rend(); ++it)
		Logger() << *it;
	gettimeofday(&start_time, NULL);
	myset.rbegin();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	Logger();
}

void	set_end_method_test(void)
{
	struct timeval	start_time;

	Logger() << "__________[set_end_method_test]__________";
	ft::set<int> myset;
	gettimeofday(&start_time, NULL);
	myset.end();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";

	for (int i=1; i<=5; i++) myset.insert(i);

	Logger() << "myset contains:";
	ft::set<int>::iterator it = myset.begin();
	for (; it != myset.end(); ++it)
		Logger() << *it;
	it++;
	Logger() << *it;
	gettimeofday(&start_time, NULL);
	myset.end();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	Logger();
}

void	set_begin_method_test(void)
{
	struct timeval	start_time;

	Logger() << "__________[set_begin_method_test]__________";
	ft::set<int> myset;
	gettimeofday(&start_time, NULL);
	myset.begin();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	for (int i=1; i<=5; i++) myset.insert(i);

	Logger() << "myset contains:";
	for (ft::set<int>::iterator it = myset.begin() ; it != myset.end(); ++it)
		Logger() << *it;
	gettimeofday(&start_time, NULL);
	myset.begin();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	Logger();
}

void	set_iterators_test(void)
{
	Logger() << "\n----------(set_iterators_test)----------";

	set_begin_method_test();
	set_end_method_test();
	set_rbegin_method_test();
	set_rend_method_test();	
}