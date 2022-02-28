/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_modifiers_test.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 03:05:49 by ldutriez          #+#    #+#             */
/*   Updated: 2022/02/28 05:53:08 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

void	set_clear_method_test(void)
{
	struct timeval	start_time;
	
	Logger() << "__________(set_clear_method_test)__________";
	
	ft::set<int> myset;
	
	for (int i=1; i<=5; i++) myset.insert(i);
	
	Logger() << "myset contains:";
	for (ft::set<int>::iterator it = myset.begin() ; it != myset.end(); ++it)
		Logger() << *it;
	
	gettimeofday(&start_time, NULL);
	myset.clear();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";

	Logger() << "myset contains:";
	for (ft::set<int>::iterator it = myset.begin() ; it != myset.end(); ++it)
		Logger() << *it;
	Logger();
}

void	set_swap_method_test(void)
{
	struct timeval	start_time;

	Logger() << "__________[set_swap_method_test]__________";
	
	ft::set<char, std::greater<char> > foo,bar;

	foo.insert('x');
	foo.insert('y');

	bar.insert('a');
	bar.insert('b');
	bar.insert('c');

	Logger() << "foo contains:\n";
	for (ft::set<char, std::greater<char> >::iterator it=foo.begin(); it!=foo.end(); ++it)
		Logger() << *it;

	Logger() << "bar contains:\n";
	for (ft::set<char, std::greater<char> >::iterator it=bar.begin(); it!=bar.end(); ++it)
		Logger() << *it;
		
	gettimeofday(&start_time, NULL);
	foo.swap(bar);
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";

	Logger() << "foo contains:\n";
	for (ft::set<char, std::greater<char> >::iterator it=foo.begin(); it!=foo.end(); ++it)
		Logger() << *it;

	Logger() << "bar contains:\n";
	for (ft::set<char, std::greater<char> >::iterator it=bar.begin(); it!=bar.end(); ++it)
		Logger() << *it;
}

void	set_erase_method_test(void)
{
	struct timeval	start_time;

	Logger() << "__________[set_erase_method_test]__________";
	ft::set<int> myset;
	gettimeofday(&start_time, NULL);
	myset.erase(1);
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";

	for (int i=1; i<=5; i++) myset.insert(i);

	Logger() << "myset contains:";
	for (ft::set<int>::iterator it = myset.begin() ; it != myset.end(); ++it)
		Logger() << *it;
	gettimeofday(&start_time, NULL);
	myset.erase(1);
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	Logger();
}

void	set_insert_method_test(void)
{
	struct timeval	start_time;

	Logger() << "__________[set_insert_method_test]__________";
	ft::set<int> myset;
	gettimeofday(&start_time, NULL);
	myset.insert(1);
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";

	for (int i=1; i<=5; i++) myset.insert(i);

	Logger() << "myset contains:";
	for (ft::set<int>::iterator it = myset.begin() ; it != myset.end(); ++it)
		Logger() << *it;
	gettimeofday(&start_time, NULL);
	myset.insert(1);
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	Logger();
}

void	set_modifiers_test(void)
{
	Logger() << "\n----------(set_modifiers_test)----------";
	
	set_insert_method_test();
	set_erase_method_test();
	set_swap_method_test();
	set_clear_method_test();
}