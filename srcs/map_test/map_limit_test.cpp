/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_limit_test.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 04:28:22 by ldutriez          #+#    #+#             */
/*   Updated: 2022/03/03 23:18:05 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

void	map_limit_test(void)
{
	Logger() << "\n----------(map_limit_test)----------";
	ft::map<int, int, std::greater<int>, std::allocator<ft::pair<const int, int> > > map_int;
	struct timeval	start_time;
	
	Logger() << "Inserting elements : " << COUNT;

	gettimeofday(&start_time, NULL);
	for (int i = 0; i < COUNT; ++i)
	{
		map_int.insert(ft::make_pair(rand(), rand()));
	}
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	
	Logger() << "map_int.size() = " << map_int.size();
	
	unsigned long long sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		int access = rand();
		sum += map_int[access];
	}
	Logger() << "should be constant with the same seed: " << sum;
	{
		ft::map<int, int, std::greater<int>, std::allocator<ft::pair<const int, int> > > copy = map_int;
	}
}