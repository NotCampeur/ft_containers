/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterators_test.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notcampeur <notcampeur@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 18:06:17 by notcampeur        #+#    #+#             */
/*   Updated: 2021/11/11 21:04:20 by notcampeur       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

void	vector_begin_method_test(void)
{
	struct timeval	start_time;

	Logger() << "__________[vector_begin_method_test]__________";
	ft::vector<int> myvector;
	gettimeofday(&start_time, NULL);
	myvector.begin();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	for (int i=1; i<=5; i++) myvector.push_back(i);

	Logger() << "myvector contains:";
	for (ft::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
	Logger() << *it;
	Logger();
}

void	vector_end_method_test(void)
{
	struct timeval	start_time;

	Logger() << "__________[vector_end_method_test]__________";
	ft::vector<int> myvector;
	gettimeofday(&start_time, NULL);
	myvector.end();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";

	for (int i=1; i<=5; i++) myvector.push_back(i);

	Logger() << "myvector contains:";
	for (ft::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
	Logger() << *it;
	Logger();
}

void	vector_rbegin_method_test(void)
{
	struct timeval	start_time;
	
	Logger() << "__________[vector_rbegin_method_test]__________";
	ft::vector<int> myvector (5);  // 5 default-constructed ints
	gettimeofday(&start_time, NULL);
	myvector.rbegin();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";

	int i=0;

	ft::vector<int>::reverse_iterator rit = myvector.rbegin();
	for (; rit!= myvector.rend(); ++rit)
	*rit = ++i;

	Logger() << "myvector contains:";
	for (ft::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
	Logger() << *it;
	Logger();
}

void	vector_rend_method_test(void)
{
	struct timeval	start_time;

	Logger() << "__________[vector_rend_method_test]__________";
	ft::vector<int> myvector (5);  // 5 default-constructed ints
	gettimeofday(&start_time, NULL);
	myvector.rend();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";

	int i=0;

	ft::vector<int>::reverse_iterator rit = myvector.rbegin();
	for (; rit!= myvector.rend(); ++rit)
	*rit = ++i;

	Logger() << "myvector contains:";
	for (ft::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
	Logger() << *it;
	Logger();
}

void	vector_iterators_test(void)
{
	Logger() << "\n----------(vector_iterators_test)----------";
	vector_begin_method_test();
	vector_end_method_test();
	vector_rbegin_method_test();
	vector_rend_method_test();
}