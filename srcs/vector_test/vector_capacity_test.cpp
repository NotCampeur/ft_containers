/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_capacity_test.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notcampeur <notcampeur@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 20:10:54 by notcampeur        #+#    #+#             */
/*   Updated: 2021/11/03 11:15:46 by notcampeur       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "main.hpp"

void	vector_size_method_test(void)
{
	std::cout << GREEN << "vector_size_method_test" << RESET << std::endl;
	ft::vector<int> myints;
	std::cout << "0. size: " << myints.size() << '\n';

	for (int i=0; i<10; i++) myints.push_back(i);
	std::cout << "1. size: " << myints.size() << '\n';

	myints.insert (myints.end(),10,100);
	std::cout << "2. size: " << myints.size() << '\n';

	myints.pop_back();
	std::cout << "3. size: " << myints.size() << '\n';
}

void	vector_max_size_method_test(void)
{
	std::cout << GREEN << "vector_max_size_test" << RESET << std::endl;
	ft::vector<int> myvector;

	for (int i=0; i<100; i++) myvector.push_back(i);

	std::cout << "size: " << myvector.size() << "\n";
	std::cout << "capacity: " << myvector.capacity() << "\n";
	std::cout << "max_size: " << myvector.max_size() << "\n";
}

void	vector_resize_method_test(void)
{
	std::cout << GREEN << "vector_resize_method_test" << RESET << std::endl;
	ft::vector<int> myvector;

	// set some initial content:
	for (int i=1;i<10;i++) myvector.push_back(i);

	myvector.resize(5);
	myvector.resize(8,100);
	myvector.resize(12);

	std::cout << "myvector contains:";
	for (std::size_t i=0;i<myvector.size();i++)
	std::cout << ' ' << myvector[i];
	std::cout << '\n';
}

void	vector_capacity_method_test(void)
{
	std::cout << GREEN << "vector_capacity_method_test" << RESET << std::endl;
	ft::vector<int> myvector;

	// set some content in the vector:
	for (int i=0; i<100; i++) myvector.push_back(i);

	std::cout << "size: " << (int) myvector.size() << '\n';
	std::cout << "capacity: " << (int) myvector.capacity() << '\n';
	std::cout << "max_size: " << (int) myvector.max_size() << '\n';
}

void	vector_empty_method_test(void)
{
	std::cout << GREEN << "vector_empty_method_capacity_test" << RESET << std::endl;
	ft::vector<int> myvector;
	int sum (0);

	for (int i=1;i<=10;i++) myvector.push_back(i);

	while (!myvector.empty())
	{
	sum += myvector.back();
	myvector.pop_back();
	}

	std::cout << "total: " << sum << '\n';
}

void	vector_reserve_method_test(void)
{
	std::cout << GREEN << "vector_reserve_method_test" << RESET << std::endl;
	ft::vector<int>::size_type sz;

	ft::vector<int> foo;
	sz = foo.capacity();
	std::cout << "making foo grow:\n";
	for (int i=0; i<100; ++i)
	{
		foo.push_back(i);
		if (sz!=foo.capacity())
		{
			sz = foo.capacity();
			std::cout << "capacity changed: " << sz << '\n';
		}
	}

	ft::vector<int> bar;
	sz = bar.capacity();
	bar.reserve(100);   // this is the only difference with foo above
	std::cout << "making bar grow:\n";
	for (int i=0; i<100; ++i)
	{
		bar.push_back(i);
		if (sz!=bar.capacity())
		{
			sz = bar.capacity();
			std::cout << "capacity changed: " << sz << '\n';
		}
	}
}

void	vector_capacity_test(void)
{
	std::cout << BOLDBLUE << "vector_capacity_test" << RESET << std::endl;
	vector_size_method_test();
	wait_for_enter();
	vector_max_size_method_test();
	wait_for_enter();
	vector_resize_method_test();
	wait_for_enter();
	vector_capacity_method_test();
	wait_for_enter();
	vector_empty_method_test();
	wait_for_enter();
	vector_reserve_method_test();
	
	// ft::vector<int> myvector;

	// myvector.push_back(10);
	// myvector.push_back(20);
	// myvector.push_back(30);
	// ft::vector<int>::iterator it = myvector.begin();
	// for (ft::vector<int>::size_type i=0; i<myvector.size(); i++)
	// {
	// 	std::cout << *(it + i) << ' ';
	// }
}
