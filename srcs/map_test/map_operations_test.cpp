/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_operations_test.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 03:46:59 by ldutriez          #+#    #+#             */
/*   Updated: 2022/03/06 14:34:55 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

void	map_equal_range_method_test(void)
{
	struct timeval	start_time;

	Logger() << "__________[map_equal_range_method_test]__________";
	ft::map<int, int> mymap;
	gettimeofday(&start_time, NULL);
	mymap.equal_range(1);
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	Logger() << "Equal range key | value : " << mymap.equal_range(1).first->first << " | " << mymap.equal_range(1).first->second;

	for (int i=1; i<=5; i++) mymap.insert(ft::pair<int, int>(i, i));

	Logger() << "mymap contains:";
	for (ft::map<int, int>::iterator it = mymap.begin() ; it != mymap.end(); ++it)
	Logger() << it->first << " => " << it->second;
	gettimeofday(&start_time, NULL);
	mymap.equal_range(1);
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	Logger() << "Equal range key | value : " << mymap.equal_range(1).first->first << " | " << mymap.equal_range(1).first->second;
	Logger();
}

void	map_upper_bound_method_test(void)
{
	struct timeval	start_time;

	Logger() << "__________[map_upper_bound_method_test]__________";
	ft::map<int, int> mymap;
	gettimeofday(&start_time, NULL);
	mymap.upper_bound(1);
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	Logger() << "Upper bound key : " << mymap.upper_bound(1)->first;

	for (int i=1; i<=5; i++) mymap.insert(ft::pair<int, int>(i, i));

	Logger() << "mymap contains:";
	for (ft::map<int, int>::iterator it = mymap.begin() ; it != mymap.end(); ++it)
		Logger() << it->first << " => " << it->second;
	gettimeofday(&start_time, NULL);
	mymap.upper_bound(1);
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	Logger() << "Upper bound key : " << mymap.upper_bound(1)->first;
	Logger();
}

void	map_lower_bound_method_test(void)
{
	struct timeval	start_time;

	Logger() << "__________[map_lower_bound_method_test]__________";
	ft::map<int, int> mymap;
	gettimeofday(&start_time, NULL);
	mymap.lower_bound(0);
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	Logger() << "Lower bound key : " << mymap.lower_bound(0)->first;

	for (int i=1; i<=5; i++) mymap.insert(ft::pair<int, int>(i, i));

	Logger() << "mymap contains:";
	for (ft::map<int, int>::iterator it = mymap.begin() ; it != mymap.end(); ++it)
	Logger() << it->first << " => " << it->second;
	gettimeofday(&start_time, NULL);
	mymap.lower_bound(0);
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	Logger() << "Lower bound key : " << mymap.lower_bound(0)->first;
	Logger();
}

void	map_count_method_test(void)
{
	struct timeval	start_time;
	
	Logger() << "__________[map_count_method_test]__________";
	ft::map<int, int> mymap;
	gettimeofday(&start_time, NULL);
	mymap.count(1);
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	Logger() << "Map count : " << mymap.count(1);
	
	for (int i=1; i<=5; i++) mymap.insert(ft::pair<int, int>(i, i));
	
	Logger() << "mymap contains:";
	for (ft::map<int, int>::iterator it = mymap.begin() ; it != mymap.end(); ++it)
		Logger() << it->first << " => " << it->second;
	
	gettimeofday(&start_time, NULL);
	mymap.count(1);
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	Logger() << "Map count : " << mymap.count(1);
	
	Logger();
}

void	map_find_method_test(void)
{
	struct timeval	start_time;

	Logger() << "__________[map_find_method_test]__________";
	ft::map<int, int> mymap;
	gettimeofday(&start_time, NULL);
	mymap.find(1);
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	Logger() << "Map find : " << mymap.find(1)->first << " | " << mymap.find(1)->second;

	for (int i=1; i<=5; i++) mymap.insert(ft::pair<int, int>(i, i));

	Logger() << "mymap contains:";
	for (ft::map<int, int>::iterator it = mymap.begin() ; it != mymap.end(); ++it)
		Logger() << it->first << " => " << it->second;
	gettimeofday(&start_time, NULL);
	mymap.find(1);
	Logger() << "Time elapsed : " << get_elapsed_time(start_time) << "µs";
	Logger() << "Map find : " << mymap.find(1)->first << " | " << mymap.find(1)->second;
	Logger();
}

template <typename T>
std::string	printPair(const T &iterator, bool nl = true)
{
	Logger() << "key: " << iterator->first << " | value: " << iterator->second;
	if (nl)
		Logger();
	return ("");
}

template <typename T_MAP>
void	printSize(T_MAP const &mp, bool print_content = 1)
{
	Logger() << "size: " << mp.size();
	Logger() << "max_size: " << mp.max_size();
	if (print_content)
	{
		typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
		Logger() << "Content is:";
		for (; it != ite; ++it)
			Logger() << "- " << printPair(it, false);
	}
	Logger() << "###############################################";
}

void	map_operations_test(void)
{
	Logger() << "\n----------(map_operations_test)----------";

	map_find_method_test();
	map_count_method_test();
	map_lower_bound_method_test();
	map_upper_bound_method_test();
	map_equal_range_method_test();
	
	Logger() << "__________[map_MLI_find_count_test]__________";
	ft::map<int, std::string> mp;
	ft::map<int, std::string>::iterator it = mp.end();

	mp[42] = "fgzgxfn";
	mp[25] = "funny";
	mp[80] = "hey";
	mp[12] = "no";
	mp[27] = "bee";
	mp[90] = "8";
	printSize(mp);

	Logger() << "\t-- FIND --";
	ft::map<int, std::string>::iterator ret;
	
	ret = mp.find(12);
	if (ret != it)
		printPair(ret);
	else
		Logger() << "map::find(" << 12 << ") returned end()";

	ret = mp.find(3);
	if (ret != it)
		printPair(ret);
	else
		Logger() << "map::find(" << 3 << ") returned end()";

	ret = mp.find(35);
	if (ret != it)
		printPair(ret);
	else
		Logger() << "map::find(" << 35 << ") returned end()";

	ret = mp.find(90);
	if (ret != it)
		printPair(ret);
	else
		Logger() << "map::find(" << 90 << ") returned end()";

	ret = mp.find(100);
	if (ret != it)
		printPair(ret);
	else
		Logger() << "map::find(" << 100 << ") returned end()";

	Logger() << "\t-- COUNT --";
	Logger() << "map::count(" << -3 << ")\treturned [" << mp.count(-3) << "]";
	Logger() << "map::count(" << 12 << ")\treturned [" << mp.count(12) << "]";
	Logger() << "map::count(" << 3 << ")\treturned [" << mp.count(3) << "]";
	Logger() << "map::count(" << 35 << ")\treturned [" << mp.count(35) << "]";
	Logger() << "map::count(" << 90 << ")\treturned [" << mp.count(90) << "]";
	Logger() << "map::count(" << 100 << ")\treturned [" << mp.count(100) << "]";

	mp.find(27)->second = "newly inserted mapped_value";

	printSize(mp);

	ft::map<int, std::string> const c_map(mp.begin(), mp.end());
	Logger() << "const map.find(" << 42 << ")->second: [" << c_map.find(42)->second << "]";
	Logger() << "const map.count(" << 80 << "): [" << c_map.count(80) << "]";
}
