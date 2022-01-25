/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_capacity_test.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 20:10:54 by notcampeur        #+#    #+#             */
/*   Updated: 2022/01/25 17:48:12 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "main.hpp"

void	vector_size_method_test(void)
{
	struct timeval	start_time;
	
	Logger() << "__________[vector_size_method_test]__________";
	ft::vector<int> myints;
	
	gettimeofday(&start_time, NULL);
	Logger() << "0. size: " << myints.size();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs\n";

	for (int i=0; i<10; i++) myints.push_back(i);
	gettimeofday(&start_time, NULL);
	Logger() << "1. size: " << myints.size();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs\n";

	myints.insert (myints.end(),10,100);
	gettimeofday(&start_time, NULL);
	Logger() << "2. size: " << myints.size();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs\n";

	for (ft::vector<int>::iterator it=myints.begin(); it!=myints.end(); ++it)
		Logger() << *it;
	myints.pop_back();
	gettimeofday(&start_time, NULL);
	Logger() << "3. size: " << myints.size();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs\n";
}

void	vector_max_size_method_test(void)
{
	struct timeval	start_time;
	
	Logger() << "__________[vector_max_size_test]__________";
	ft::vector<int> myvector;

	for (int i=0; i<100; i++) myvector.push_back(i);

	gettimeofday(&start_time, NULL);
	Logger() << "size: " << myvector.size();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs\n";
	gettimeofday(&start_time, NULL);
	Logger() << "capacity: " << myvector.capacity();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs\n";
	gettimeofday(&start_time, NULL);
	Logger() << "max_size: " << myvector.max_size();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs\n";
}

void	vector_resize_method_test(void)
{
	struct timeval	start_time;
	
	Logger() << "__________[vector_resize_method_test]__________";
	ft::vector<int> myvector;
	// set some initial content:
	for (int i=1;i<10;i++) myvector.push_back(i);

	gettimeofday(&start_time, NULL);
	myvector.resize(5);
	Logger() << "vector size : " << myvector.size() 
	<< "\nTime elapsed : " << get_elapsed_time(start_time) << "µs\n";
	gettimeofday(&start_time, NULL);
	myvector.resize(8,100);
	Logger() << "vector size : " << myvector.size() 
	<< "\nTime elapsed : " << get_elapsed_time(start_time) << "µs\n";
	gettimeofday(&start_time, NULL);
	myvector.resize(12);
	Logger() << "vector size : " << myvector.size() 
	<< "\nTime elapsed : " << get_elapsed_time(start_time) << "µs\n";

	Logger() << "myvector contains:";
	for (std::size_t i=0;i<myvector.size();i++)
		Logger() << myvector[i];
	Logger();
}

void	vector_capacity_method_test(void)
{
	struct timeval	start_time;
	Logger() << "__________[vector_capacity_method_test]__________";
	ft::vector<int> myvector;

	// set some content in the vector:
	for (int i=0; i<100; i++) myvector.push_back(i);

	gettimeofday(&start_time, NULL);
	Logger() << "size: " << (int) myvector.size();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs\n";
	gettimeofday(&start_time, NULL);
	Logger() << "capacity: " << (int) myvector.capacity();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs\n";
	gettimeofday(&start_time, NULL);
	Logger() << "max_size: " << (int) myvector.max_size();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs\n";
}

void	vector_empty_method_test(void)
{
	struct timeval	start_time;
	Logger() << "__________[vector_empty_method_capacity_test]__________";
	ft::vector<int> myvector;
	int sum (0);

	for (int i=1;i<=10;i++) myvector.push_back(i);

	gettimeofday(&start_time, NULL);
	Logger() << "is empty : " << myvector.empty()
	<< "\nTime elapsed : " << get_elapsed_time(start_time) << "µs\n";
	while (!myvector.empty())
	{
		sum += myvector.back();
		myvector.pop_back();
	}
	gettimeofday(&start_time, NULL);
	Logger() << "is empty : " << myvector.empty()
	<< "\nTime elapsed : " << get_elapsed_time(start_time) << "µs\n";
	Logger() << "total: " << sum << '\n';
}

void	vector_reserve_method_test(void)
{
	struct timeval	start_time;
	Logger() << "__________[vector_reserve_method_test]__________";
	ft::vector<int>::size_type sz;

	ft::vector<int> foo;
	sz = foo.capacity();
	Logger() << "making foo grow:";
	for (int i=0; i<100; ++i)
	{
		foo.push_back(i);
		if (sz!=foo.capacity())
		{
			sz = foo.capacity();
			Logger() << "capacity changed: " << sz;
		}
	}

	ft::vector<int> bar;
	sz = bar.capacity();
	gettimeofday(&start_time, NULL);
	bar.reserve(100);   // this is the only difference with foo above
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs\n";
	Logger() << "making bar grow:";
	for (int i=0; i<100; ++i)
	{
		bar.push_back(i);
		if (sz!=bar.capacity())
		{
			sz = bar.capacity();
			Logger() << "capacity changed: " << sz;
		}
	}
}

void	vector_capacity_test(void)
{
	Logger() << "\n----------(vector_capacity_test)----------";
	vector_size_method_test();
	vector_max_size_method_test();
	vector_resize_method_test();
	vector_capacity_method_test();
	vector_empty_method_test();
	vector_reserve_method_test();
}
