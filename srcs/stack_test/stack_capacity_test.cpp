/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_capacity_test.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 16:14:52 by ldutriez          #+#    #+#             */
/*   Updated: 2022/02/01 17:09:28 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "main.hpp"

void	stack_empty_method_test(void)
{
	struct timeval	start_time;
	ft::stack<int> container;
 
	Logger() << "__________[stack_empty_method_test]__________";
 
	gettimeofday(&start_time, NULL);
	Logger() << "Initially, container.empty(): " << container.empty();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs\n";
 
	container.push(42);
	gettimeofday(&start_time, NULL);
	Logger() << "After adding elements, container.empty(): " << container.empty();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs\n";

	container.pop();
	gettimeofday(&start_time, NULL);
	Logger() << "After removing elements, container.empty(): " << container.empty();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs\n";
}

void	stack_size_method_test(void)
{
	struct timeval	start_time;
	ft::stack<int> container;

	Logger() << "__________[stack_size_method_test]__________";
 
	gettimeofday(&start_time, NULL);
	Logger() << "Initially, container.size(): " << container.size();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs\n";

	for (int i = 0; i < 7; ++i)
		container.push(i);

	gettimeofday(&start_time, NULL);
	Logger() << "After adding elements, container.size(): " << container.size();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs\n";
}

void	stack_capacity_test(void)
{
	Logger() << "\n----------(stack_capacity_test)----------";
	stack_empty_method_test();
	stack_size_method_test();
}