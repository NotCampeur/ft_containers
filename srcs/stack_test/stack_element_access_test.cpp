/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_element_access_test.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 16:23:42 by ldutriez          #+#    #+#             */
/*   Updated: 2022/02/01 16:29:04 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "main.hpp"

void	stack_top_method_test(void)
{
	struct timeval	start_time;
	ft::stack<int> s;
 
	Logger() << "__________[stack_top_method_test]__________";
 
    s.push(2);
    s.push(6);
    s.push(51);

    Logger() << s.size() << " elements on stack";
	gettimeofday(&start_time, NULL);
    Logger() << "Top element: " << s.top();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs\n";
 
    Logger() << s.size() << " elements on stack";
    s.pop();
 
    Logger() << s.size() << " elements on stack";
	gettimeofday(&start_time, NULL);
    Logger() << "Top element: " << s.top();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs\n";
}

void	stack_element_access_test(void)
{
	Logger() << "\n----------(stack_element_access_test)----------";
	stack_top_method_test();
}