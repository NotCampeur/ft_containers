/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_relational_operators_test.cpp                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 04:38:03 by ldutriez          #+#    #+#             */
/*   Updated: 2022/02/28 05:56:39 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

void	set_relational_operators_test(void)
{
	Logger() << "\n----------(set_relational_operators_test)----------";
	ft::set<char> foo,bar;

	foo.insert('a');
	foo.insert('b');
	bar.insert('a');
	bar.insert('z');

	// foo ({{a,100},{b,200}}) vs bar ({a,10},{z,1000}}):
	if (foo==bar) Logger() << "foo and bar are equal";
	if (foo!=bar) Logger() << "foo and bar are not equal";
	if (foo< bar) Logger() << "foo is less than bar";
	if (foo> bar) Logger() << "foo is greater than bar";
	if (foo<=bar) Logger() << "foo is less than or equal to bar";
	if (foo>=bar) Logger() << "foo is greater than or equal to bar";
}