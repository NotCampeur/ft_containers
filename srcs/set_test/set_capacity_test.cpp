/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_capacity_test.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 02:58:38 by ldutriez          #+#    #+#             */
/*   Updated: 2022/02/28 05:47:25 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

void	set_max_size_method_test(void)
{
	struct timeval	start_time;

	Logger() << "__________[set_max_size_method_test]__________";
	ft::set<int> myset;
	gettimeofday(&start_time, NULL);
	Logger() << "Max size : " << myset.max_size();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";

	for (int i=1; i<=5; i++) myset.insert(i);

	Logger() << "myset contains:";
	for (ft::set<int>::iterator it = myset.begin() ; it != myset.end(); ++it)
		Logger() << *it;
	gettimeofday(&start_time, NULL);
	Logger() << "Max size : " << myset.max_size();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	Logger();
}

void	set_size_method_test(void)
{
	struct timeval	start_time;

	Logger() << "__________[set_size_method_test]__________";
	ft::set<int> myset;
	gettimeofday(&start_time, NULL);
	Logger() << "Size : " << myset.size();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";

	for (int i=1; i<=5; i++) myset.insert(i);

	Logger() << "myset contains:";
	for (ft::set<int>::iterator it = myset.begin() ; it != myset.end(); ++it)
		Logger() << *it;
	gettimeofday(&start_time, NULL);
	Logger() << "Size : " << myset.size();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	Logger();
}

void	set_empty_method_test(void)
{
	struct timeval	start_time;

	Logger() << "__________[set_empty_method_test]__________";
	ft::set<int> myset;
	gettimeofday(&start_time, NULL);
	Logger() << "Is empty : " << myset.empty();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";

	for (int i=1; i<=5; i++) myset.insert(i);

	Logger() << "myset contains:";
	for (ft::set<int>::iterator it = myset.begin() ; it != myset.end(); ++it)
		Logger() << *it;
	gettimeofday(&start_time, NULL);
	Logger() << "Is empty : " << myset.empty();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	Logger();
}

void	set_capacity_test(void)
{
	Logger() << "\n----------(set_capacity_test)----------";
	
	set_empty_method_test();
	set_size_method_test();
	set_max_size_method_test();
}