/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_relational_operators_test.cpp                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 04:38:03 by ldutriez          #+#    #+#             */
/*   Updated: 2022/02/26 04:40:00 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

void	map_relational_operators_test(void)
{
	Logger() << "\n----------(map_relational_operators_test)----------";
	ft::map<char,int> foo,bar;
	foo['a']=100;
	foo['b']=200;
	bar['a']=10;
	bar['z']=1000;

	// foo ({{a,100},{b,200}}) vs bar ({a,10},{z,1000}}):
	if (foo==bar) Logger() << "foo and bar are equal";
	if (foo!=bar) Logger() << "foo and bar are not equal";
	if (foo< bar) Logger() << "foo is less than bar";
	if (foo> bar) Logger() << "foo is greater than bar";
	if (foo<=bar) Logger() << "foo is less than or equal to bar";
	if (foo>=bar) Logger() << "foo is greater than or equal to bar";
}