/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_element_access_test.cpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notcampeur <notcampeur@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:04:47 by notcampeur        #+#    #+#             */
/*   Updated: 2021/11/11 20:47:32 by notcampeur       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "main.hpp"

void	vector_access_operator_test(void)
{
	struct timeval	start_time;
	
	Logger() << "__________[vector_access_operator_test]__________";
	ft::vector<int> myvector (10);   // 10 zero-initialized elements

	ft::vector<int>::size_type sz = myvector.size();

	// assign some values:
	for (unsigned i=0; i<sz; i++) myvector[i]=i;

	// reverse vector using operator[]:
	for (unsigned i=0; i<sz/2; i++)
	{
		int temp;
		gettimeofday(&start_time, NULL);
		temp = myvector[sz-1-i];
		Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
		gettimeofday(&start_time, NULL);
		myvector[sz-1-i]=myvector[i];
		Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
		gettimeofday(&start_time, NULL);
		myvector[i]=temp;
		Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	}

	Logger() << "\nmyvector contains:";
	for (unsigned i=0; i<sz; i++)
	{
		gettimeofday(&start_time, NULL);
		Logger() << myvector[i] << "\nTime elapsed : " << get_elapsed_time(start_time) << "µs";
	}
	Logger();
}

void	vector_at_method_test(void)
{
	struct timeval	start_time;
	
	Logger() << "__________[vector_at_method_test]__________";
	ft::vector<int> myvector (10);   // 10 zero-initialized ints

	// assign some values:
	for (unsigned i=0; i<myvector.size(); i++)
	{
		gettimeofday(&start_time, NULL);
		myvector.at(i)=i;
		Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	}

	Logger() << "\nmyvector contains:";
	for (unsigned i=0; i<myvector.size(); i++)
	{
		gettimeofday(&start_time, NULL);
		Logger() << myvector.at(i)
		<< "\nTime elapsed : " << get_elapsed_time(start_time) << "µs";
	}
	Logger();
}

void	vector_front_method_test(void)
{
	struct timeval	start_time;

	Logger() << "__________[vector_front_method_test]__________";
	ft::vector<int> myvector;

	myvector.push_back(78);
	myvector.push_back(16);

	// now front equals 78, and back 16

	gettimeofday(&start_time, NULL);
	Logger() << "Front value : " << myvector.front()
	<< "\nTime elapsed : " << get_elapsed_time(start_time) << "µs";
}

void	vector_back_method_test(void)
{
	struct timeval	start_time;

	Logger() << "__________[vector_back_method_test]__________";
	ft::vector<int> myvector;

	myvector.push_back(78);
	myvector.push_back(16);

	// now front equals 78, and back 16

	gettimeofday(&start_time, NULL);
	Logger() << "Back value : " << myvector.back()
	<< "\nTime elapsed : " << get_elapsed_time(start_time) << "µs";
}

void	vector_element_access_test(void)
{
	Logger() << "\n----------(vector_element_access_test)----------";
	vector_access_operator_test();
	vector_at_method_test();
	vector_front_method_test();
	vector_back_method_test();
}