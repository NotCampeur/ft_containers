/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_modifiers_test.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 16:23:42 by ldutriez          #+#    #+#             */
/*   Updated: 2022/02/04 15:42:48 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "main.hpp"

void	stack_pop_method_test(void)
{
	struct timeval	start_time;
	ft::stack<int> s;
 
	Logger() << "__________[stack_pop_method_test]__________";
 
	Logger() << s.size() << " elements on stack";
	for (int i(0); i < rand() % 100; ++i)
		s.push(rand() % INT32_MAX);
	gettimeofday(&start_time, NULL);
	for (std::size_t i(0); i < s.size(); ++i)
		s.pop();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs\n";
	Logger() << "Top element: " << s.top();
	Logger() << s.size() << " elements on stack";
}

void	stack_push_method_test(void)
{
	struct timeval	start_time;
	ft::stack<int> s;
 
	Logger() << "__________[stack_top_method_test]__________";
 
	Logger() << s.size() << " elements on stack";
	gettimeofday(&start_time, NULL);
	for (int i(0); i < rand() % 100; ++i)
		s.push(rand() % INT32_MAX);
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs\n";
	Logger() << "Top element: " << s.top();
	Logger() << s.size() << " elements on stack";
}

void	stack_modifiers_test(void)
{
	Logger() << "\n----------(stack_modifiers_test)----------";
	stack_push_method_test();
	stack_pop_method_test();
}