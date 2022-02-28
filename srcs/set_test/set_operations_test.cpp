/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_operations_test.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 03:46:59 by ldutriez          #+#    #+#             */
/*   Updated: 2022/02/28 05:55:43 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

void	set_equal_range_method_test(void)
{
	struct timeval	start_time;

	Logger() << "__________[set_equal_range_method_test]__________";
	ft::set<int> myset;
	gettimeofday(&start_time, NULL);
	myset.equal_range(1);
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	Logger() << "Equal range key | value : " << *myset.equal_range(1).first << " | " << *myset.equal_range(1).first;

	for (int i=1; i<=5; i++) myset.insert(i);

	Logger() << "myset contains:";
	for (ft::set<int>::iterator it = myset.begin() ; it != myset.end(); ++it)
	Logger() << *it;
	gettimeofday(&start_time, NULL);
	myset.equal_range(1);
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	Logger() << "Equal range key | value : " << *myset.equal_range(1).first << " | " << *myset.equal_range(1).first;
	Logger();
}

void	set_upper_bound_method_test(void)
{
	struct timeval	start_time;

	Logger() << "__________[set_upper_bound_method_test]__________";
	ft::set<int> myset;
	gettimeofday(&start_time, NULL);
	myset.upper_bound(1);
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	Logger() << "Upper bound key : " << *myset.upper_bound(1);

	for (int i=1; i<=5; i++) myset.insert(i);

	Logger() << "myset contains:";
	for (ft::set<int>::iterator it = myset.begin() ; it != myset.end(); ++it)
		Logger() << *it;
	gettimeofday(&start_time, NULL);
	myset.upper_bound(1);
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	Logger() << "Upper bound key : " << *myset.upper_bound(1);
	Logger();
}

void	set_lower_bound_method_test(void)
{
	struct timeval	start_time;

	Logger() << "__________[set_lower_bound_method_test]__________";
	ft::set<int> myset;
	gettimeofday(&start_time, NULL);
	myset.lower_bound(0);
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	Logger() << "Lower bound key : " << *myset.lower_bound(0);

	for (int i=1; i<=5; i++) myset.insert(i);

	Logger() << "myset contains:";
	for (ft::set<int>::iterator it = myset.begin() ; it != myset.end(); ++it)
	Logger() << *it;
	gettimeofday(&start_time, NULL);
	myset.lower_bound(0);
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	Logger() << "Lower bound key : " << *myset.lower_bound(0);
	Logger();
}

void	set_count_method_test(void)
{
	struct timeval	start_time;
	
	Logger() << "__________[set_count_method_test]__________";
	ft::set<int> myset;
	gettimeofday(&start_time, NULL);
	myset.count(1);
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	Logger() << "Set count : " << myset.count(1);
	
	for (int i=1; i<=5; i++) myset.insert(i);
	
	Logger() << "myset contains:";
	for (ft::set<int>::iterator it = myset.begin() ; it != myset.end(); ++it)
		Logger() << *it;
	
	gettimeofday(&start_time, NULL);
	myset.count(1);
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	Logger() << "Set count : " << myset.count(1);
	
	Logger();
}

void	set_find_method_test(void)
{
	struct timeval	start_time;

	Logger() << "__________[set_find_method_test]__________";
	ft::set<int> myset;
	gettimeofday(&start_time, NULL);
	myset.find(1);
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	Logger() << "Set find : " << *myset.find(1) << " | " << *myset.find(1);

	for (int i=1; i<=5; i++) myset.insert(i);

	Logger() << "myset contains:";
	for (ft::set<int>::iterator it = myset.begin() ; it != myset.end(); ++it)
		Logger() << *it;
	gettimeofday(&start_time, NULL);
	myset.find(1);
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	Logger() << "Set find : " << *myset.find(1) << " | " << *myset.find(1);
	Logger();
}

void	set_operations_test(void)
{
	Logger() << "\n----------(set_operations_test)----------";

	set_find_method_test();
	set_count_method_test();
	set_lower_bound_method_test();
	set_upper_bound_method_test();
	set_equal_range_method_test();
}