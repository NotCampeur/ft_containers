/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_limit_test.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 04:28:22 by ldutriez          #+#    #+#             */
/*   Updated: 2022/02/28 06:33:07 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

void	set_limit_test(void)
{
	Logger() << "\n----------(set_limit_test)----------";
	ft::set<int, std::greater<int>, std::allocator<int> > set_int; // WHEN YOU ADD AN ALLOCATOR IT DOESN'T COMPILE ANYMORE
	
	Logger() << "Inserting elements : " << COUNT;

	for (int i = 0; i < COUNT; ++i)
	{
		set_int.insert(rand());
	}
	
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