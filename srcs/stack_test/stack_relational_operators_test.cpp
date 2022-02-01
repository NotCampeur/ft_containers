/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_relational_operators_test.cpp                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 16:23:42 by ldutriez          #+#    #+#             */
/*   Updated: 2022/02/01 17:09:03 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "main.hpp"

template < class T >
void	cmp(const ft::stack<T, ft::vector<int> > &lhs, const ft::stack<T, ft::vector<int> > &rhs)
{
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	Logger() << "eq: " << (lhs == rhs) << " | ne: " << (lhs != rhs);
	Logger() << "lt: " << (lhs <  rhs) << " | le: " << (lhs <= rhs);
	Logger() << "gt: " << (lhs >  rhs) << " | ge: " << (lhs >= rhs);
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs\n";
}

void	stack_comparison_test(void)
{
	ft::vector<int>	vec;

	vec.push_back(21);
	vec.push_back(42);
	vec.push_back(1337);
	vec.push_back(19);
	vec.push_back(0);
	vec.push_back(183792);

	ft::stack<int, ft::vector<int> >	stck(vec);
	ft::stack<int, ft::vector<int> >	stck2(vec);
 
	Logger() << "__________[stack_comparison_test]__________";

	cmp(stck, stck);
	cmp(stck, stck2);

	stck2.push(60);
	stck2.push(61);
	stck2.push(62);

	cmp(stck, stck2);
	cmp(stck2, stck);

	stck.push(42);

	cmp(stck, stck2);
	cmp(stck2, stck);

	stck.push(100);

	cmp(stck, stck2);
	cmp(stck2, stck);
	
	Logger() << "Top element: " << stck.top();
	Logger() << stck.size() << " elements on stack";
	Logger() << "Top element: " << stck2.top();
	Logger() << stck2.size() << " elements on stack";
}

void	stack_relational_operators_test(void)
{
	Logger() << "\n----------(stack_relational_operators_test)----------";
	stack_comparison_test();
}