/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_allocator_test.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notcampeur <notcampeur@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 17:56:52 by notcampeur        #+#    #+#             */
/*   Updated: 2021/11/11 20:48:06 by notcampeur       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

void	vector_get_allocator_method_test(void)
{
	struct timeval	start_time;
	ft::vector<int> myvector;
	Logger() << "__________[vector_get_allocator_method_test]__________";
	int * p;
	unsigned int i;

	// allocate an array with space for 5 elements using vector's allocator:
	gettimeofday(&start_time, NULL);
	p = myvector.get_allocator().allocate(5);
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";

	// construct values in-place on the array:
	for (i=0; i<5; i++)
	{
		gettimeofday(&start_time, NULL);
		myvector.get_allocator().construct(&p[i],i);
		Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	}

	Logger() << "The allocated array contains:";
	for (i=0; i<5; i++) Logger() << p[i];
	Logger();

	// destroy and deallocate:
	for (i=0; i<5; i++)
	{
		gettimeofday(&start_time, NULL);
		myvector.get_allocator().destroy(&p[i]);
		Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	}
	gettimeofday(&start_time, NULL);
	myvector.get_allocator().deallocate(p,5);
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
}

void	vector_allocator_test(void)
{
	Logger() << "\n----------(vector_allocator_test)----------";
	vector_get_allocator_method_test();
}