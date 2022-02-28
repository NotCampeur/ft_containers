/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_limit_test.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 04:28:22 by ldutriez          #+#    #+#             */
/*   Updated: 2022/02/28 02:08:38 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

void	map_limit_test(void)
{
	Logger() << "\n----------(map_limit_test)----------";
	ft::map<int, int, std::greater<int>, std::allocator<ft::pair<const int, int> > > map_int;
	
	Logger() << "Inserting elements : " << COUNT;

	for (int i = 0; i < COUNT; ++i)
	{
		map_int.insert(ft::make_pair(rand(), rand()));
	}
	
	Logger() << "map_int.size() = " << map_int.size();
	
	unsigned long long sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		int access = rand();
		sum += map_int[access];
	}
	Logger() << "should be constant with the same seed: " << sum;
	{
		ft::map<int, int, std::greater<int> > copy = map_int;
	}
}