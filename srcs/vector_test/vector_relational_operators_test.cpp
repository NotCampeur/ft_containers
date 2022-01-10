/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_relational_operators_test.cpp               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:04:47 by notcampeur        #+#    #+#             */
/*   Updated: 2022/01/05 16:51:17 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "main.hpp"

void	vector_relational_operators_test(void)
{
	Logger() << "\n----------(vector_relational_operators_test)----------";
	ft::vector<int> foo (3,100);   // three ints with a value of 100
	ft::vector<int> bar (2,200);   // two ints with a value of 200

	if (foo==bar) Logger() << "foo and bar are equal";
	if (foo!=bar) Logger() << "foo and bar are not equal";
	if (foo< bar) Logger() << "foo is less than bar";
	if (foo> bar) Logger() << "foo is greater than bar";
	if (foo<=bar) Logger() << "foo is less than or equal to bar";
	if (foo>=bar) Logger() << "foo is greater than or equal to bar";
}