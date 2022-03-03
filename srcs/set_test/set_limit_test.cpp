/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_limit_test.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 04:28:22 by ldutriez          #+#    #+#             */
/*   Updated: 2022/03/03 23:42:13 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

void	set_limit_test(void)
{
	Logger() << "\n----------(set_limit_test)----------";
	ft::set<int, std::greater<int>, std::allocator<int> > set_int;
	struct timeval	start_time;
	
	Logger() << "Inserting elements : " << COUNT;

	gettimeofday(&start_time, NULL);
	for (int i = 0; i < COUNT; ++i)
	{
		set_int.insert(rand());
	}
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	
	Logger() << "set_int.size() = " << set_int.size();
	
	unsigned long long sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		int access = rand();
		sum += *set_int.find(access);
	}
	Logger() << "should be constant with the same seed: " << sum;
	{
		ft::set<int, std::greater<int>, std::allocator<int> > copy = set_int;
		Logger() << "copy.size() = " << copy.size();
	}
}