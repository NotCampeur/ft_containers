/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_modifiers_test.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:38:29 by notcampeur        #+#    #+#             */
/*   Updated: 2022/03/04 01:21:33 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

void	vector_assign_method_test(void)
{
	struct timeval	start_time;

	Logger() << "__________[vector_assign_method_test]__________";
	ft::vector<int> first;
	ft::vector<int> second;
	ft::vector<int> third;

	gettimeofday(&start_time, NULL);
	first.assign (7,100);             // 7 ints with a value of 100
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	first[1] = 200;
	first[5] = 200;
	ft::vector<int>::iterator it;
	it=first.begin()+1;

	gettimeofday(&start_time, NULL);
	second.assign (it,first.end()-1); // the 5 central values of first
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";

	int myints[] = {1776,7,4};
	gettimeofday(&start_time, NULL);
	third.assign (myints,myints+3);   // assigning from array.
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";

	Logger() << "1. Capacity: " << first.capacity() << " Size: " << int (first.size());
	for (ft::vector<int>::size_type i = 0; i < first.size(); i++)
		Logger() << "first[" << i << "] = " << first[i];
	Logger() << "2. Capacity: " << second.capacity() << " Size: " << int (second.size());
	for (ft::vector<int>::size_type i = 0; i < second.size(); i++)
		Logger() << "second[" << i << "] = " << second[i];
	Logger() << "3. Capacity: " << third.capacity() << " Size: " << int (third.size());
	for (ft::vector<int>::size_type i = 0; i < third.size(); i++)
		Logger() << "third[" << i << "] = " << third[i];
}

void	vector_push_back_method_test(void)
{
	struct timeval	start_time;
	ft::vector<int> myvector;

	Logger() << "__________[vector_push_back_method_test]__________";
	for (int i(0); i < 10; i++)
	{
		gettimeofday(&start_time, NULL);
		myvector.push_back (i);
		Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	}
	Logger() << "myvector stores " << int(myvector.size()) << " numbers.";
}

void	vector_pop_back_method_test(void)
{
	struct timeval	start_time;
	ft::vector<int> myvector;

	Logger() << "__________[vector_pop_back_method_test]__________";
	for (int i(0); i < 10; i++)
		myvector.push_back (i);
	Logger() << "myvector stores " << int(myvector.size()) << " numbers.";

	for (int i(0); i < 10; i++)
	{
		gettimeofday(&start_time, NULL);
		myvector.pop_back();
		Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	}
	Logger() << "myvector stores " << int(myvector.size()) << " numbers.";
}

void	vector_insert_method_test(void)
{
	struct timeval	start_time;
	ft::vector<int> myvector (3,100);
	ft::vector<int>::iterator it;

	Logger() << "__________[vector_insert_method_test]__________";
	Logger() << "Vector capacity: " << myvector.capacity() << " Vector size: " << int (myvector.size());

	it = myvector.begin();
	gettimeofday(&start_time, NULL);
	it = myvector.insert ( it , 200 );
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	for (ft::vector<int>::size_type i = 0; i < myvector.size(); i++)
		Logger() << "myvector[" << i << "] = " << myvector[i];
	Logger() << "Vector capacity: " << myvector.capacity() << " Vector size: " << int (myvector.size());
	
	gettimeofday(&start_time, NULL);
	it = myvector.insert ( myvector.end() - 2 , 200 );
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	for (ft::vector<int>::size_type i = 0; i < myvector.size(); i++)
		Logger() << "myvector[" << i << "] = " << myvector[i];
	Logger() << "Vector capacity: " << myvector.capacity() << " Vector size: " << int (myvector.size());
		
	gettimeofday(&start_time, NULL);
	myvector.insert (it,2,300);
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	for (ft::vector<int>::size_type i = 0; i < myvector.size(); i++)
		Logger() << "myvector[" << i << "] = " << myvector[i];
	Logger() << "Vector capacity: " << myvector.capacity() << " Vector size: " << int (myvector.size());
	it = myvector.begin();

	ft::vector<int> anothervector (2,400);
	gettimeofday(&start_time, NULL);
	myvector.insert (it+2,anothervector.begin(),anothervector.end());
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	for (it=myvector.begin(); it<myvector.end(); it++)
		Logger() << *it;
	Logger() << "Vector capacity: " << myvector.capacity() << " Vector size: " << int (myvector.size());

	int myarray [] = { 501,502,503 };
	gettimeofday(&start_time, NULL);
	myvector.insert (myvector.begin(), myarray, myarray+3);
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";

	Logger() << "myvector contains:";
	for (it=myvector.begin(); it<myvector.end(); it++)
		Logger() << *it;
	Logger() << "Vector capacity: " << myvector.capacity() << " Vector size: " << int (myvector.size());

	gettimeofday(&start_time, NULL);
	myvector.insert (myvector.begin(), 50, 42);
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";

	Logger() << "myvector contains:";
	for (it=myvector.begin(); it<myvector.end(); it++)
		Logger() << *it;
	Logger() << "Vector capacity: " << myvector.capacity() << " Vector size: " << int (myvector.size());
	
	Logger();
}

void	vector_erase_method_test(void)
{
	struct timeval	start_time;
	ft::vector<int> myvector;

	Logger() << "__________[vector_erase_method_test]__________";
	// set some values (from 1 to 10)
	for (int i=1; i<=10; i++) myvector.push_back(i);

	// erase the 6th element
	gettimeofday(&start_time, NULL);
	myvector.erase (myvector.begin()+5);
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";

	// erase the first 3 elements:
	gettimeofday(&start_time, NULL);
	myvector.erase (myvector.begin(),myvector.begin()+3);
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";

	Logger() << "myvector contains:";
	for (unsigned i=0; i<myvector.size(); ++i)
		Logger() << myvector[i];
	Logger();
}

void	vector_swap_method_test(void)
{
	struct timeval	start_time;

	Logger() << "__________[vector_swap_method_test]__________";
	ft::vector<int> foo (3,100);   // three ints with a value of 100
	ft::vector<int> bar (5,200);   // five ints with a value of 200

	gettimeofday(&start_time, NULL);
	foo.swap(bar);
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";

	Logger() << "foo contains:";
	for (unsigned i=0; i<foo.size(); i++)
		Logger() << foo[i];
	Logger();

	Logger() << "bar contains:";
	for (unsigned i=0; i<bar.size(); i++)
		Logger() << bar[i];
	Logger();

	Logger() << "__________[vector_specialized_swap_test]__________";

	gettimeofday(&start_time, NULL);
	ft::swap(foo, bar);
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";

	Logger() << "foo contains:";
	for (unsigned i=0; i<foo.size(); i++)
		Logger() << foo[i];
	Logger();

	Logger() << "bar contains:";
	for (unsigned i=0; i<bar.size(); i++)
		Logger() << bar[i];
	Logger();
}

void	vector_clear_method_test(void)
{
	struct timeval	start_time;
	ft::vector<int> myvector;
	
	Logger() << "__________[vector_clear_method_test]__________";
	myvector.push_back (100);
	myvector.push_back (200);
	myvector.push_back (300);

	Logger() << "myvector contains:";
	for (unsigned i=0; i<myvector.size(); i++)
		Logger() << myvector[i];
	Logger();

	gettimeofday(&start_time, NULL);
	myvector.clear();
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	myvector.push_back (1101);
	myvector.push_back (2202);

	Logger() << "myvector contains:";
	for (unsigned i=0; i<myvector.size(); i++)
		Logger() << myvector[i];
	Logger();
}

void	vector_modifiers_test(void)
{
	Logger() << "\n----------(vector_modifiers_test)----------";
	vector_assign_method_test();
	vector_push_back_method_test();
	vector_pop_back_method_test();
	vector_insert_method_test();
	vector_erase_method_test();
	vector_swap_method_test();
	vector_clear_method_test();
	
	Logger() << "__________[vector_special_leaks_test]__________";
	
	ft::vector<std::string *> p_vector;
	for (int i = 0; i < 10; i++)
	{
		std::string *str = new std::string("Hello");
		p_vector.push_back(str);
	}
	std::string *str = new std::string("Bye");
	p_vector.insert(p_vector.begin() + 2, str);
	Logger() << "Capacity: " << p_vector.capacity() << " Size: " << int (p_vector.size());
	for (ft::vector<int>::size_type i = 0; i < p_vector.size(); i++)
		Logger() << "p_vector[" << i << "] = " << p_vector[i];
	for (ft::vector<int>::size_type i = 0; i < p_vector.size(); i++)
		delete p_vector[i];
}