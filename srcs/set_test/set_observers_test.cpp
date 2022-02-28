/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_observers_test.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 03:43:25 by ldutriez          #+#    #+#             */
/*   Updated: 2022/02/28 05:47:25 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

void	set_value_comp_method_test(void)
{
	struct timeval	start_time;

	Logger() << "__________[set_value_comp_method_test]__________";
	ft::set<int> myset;
	gettimeofday(&start_time, NULL);
	myset.value_comp();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";

	for (int i=1; i<=5; i++) myset.insert(i);

	Logger() << "myset contains:";
	for (ft::set<int>::iterator it = myset.begin() ; it != myset.end(); ++it)
		Logger() << *it;
	Logger();
}

void	set_key_comp_method_test(void)
{
	struct timeval	start_time;

	Logger() << "__________[set_key_comp_method_test]__________";
	ft::set<int> myset;
	gettimeofday(&start_time, NULL);
	myset.key_comp();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";

	for (int i=1; i<=5; i++) myset.insert(i);

	Logger() << "myset contains:";
	for (ft::set<int>::iterator it = myset.begin() ; it != myset.end(); ++it)
		Logger() << *it;
	Logger();
}

void	set_observers_test(void)
{
	Logger() << "\n----------(set_observers_test)----------";
	
	set_key_comp_method_test();
	set_value_comp_method_test();
}