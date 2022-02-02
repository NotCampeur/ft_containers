/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 17:14:44 by notcampeur        #+#    #+#             */
/*   Updated: 2022/02/02 16:04:17 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

long	get_elapsed_time(struct timeval	start_time)
{
	struct timeval	act_time;

	gettimeofday(&act_time, NULL);
	return ((act_time.tv_sec - start_time.tv_sec) * 1000000L
		+ (act_time.tv_usec - start_time.tv_usec));
}

int	getting_seed(char *argv[])
{
	if (atoi(argv[1]) == 0
		&& (argv[1][0] != '0' && (argv[1][0] != '-' && argv[1][1] != '0')))
	{
		throw std::exception();
	}
	return atoi(argv[1]);
}

void	getting_started(int argc, char *argv[])
{
	int seed;

	if (argc != 2)
	{
		Logger(error_type) << "Usage: " << argv[0] << " seed\n"
			<< "Provide a seed please\n"
			<< "Count value:" << COUNT;
		throw std::exception();
	}
	try
	{
		seed = getting_seed(argv);
	}
	catch(const std::exception& e)
	{
		Logger(error_type) << "The seed need to be a number.";
		throw ;
	}
	srand(seed);
	#ifdef DIY
		Logger() << "DIY testing with seed : " << seed << "\n";
	#else
		Logger() << "STL testing with seed : " << seed << "\n";
	#endif

}

void	vector_test(void)
{
	Logger() << "======================={Vector test}=======================";
	vector_iterators_test();
	vector_capacity_test();
	vector_element_access_test();
	vector_modifiers_test();
	vector_allocator_test();
	vector_relational_operators_test();
}

void	stack_test(void)
{
	Logger() << "======================={Stack test}=======================";
	stack_capacity_test();
	stack_element_access_test();
	stack_modifiers_test();
	stack_relational_operators_test();
	stack_mutant_test();
}

void	pair_test(void)
{
	Logger() << "======================={Pair test}=======================";
	pair_basic_test();
}

void	map_test(void)
{
	#ifndef DIY
	ft::map<int, int> map_int;
	
	for (int i = 0; i < COUNT; ++i)
	{
		map_int.insert(ft::make_pair(rand(), rand()));
	}
	
	int sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		int access = rand();
		sum += map_int[access];
	}
	Logger() << "should be constant with the same seed: " << sum;
	{
		ft::map<int, int> copy = map_int;
	}
	#endif
}

int main(int argc, char** argv)
{
	std::string	log_name(argv[0]);

	// Only keep the binary name without the path
	log_name = log_name.substr(log_name.find_last_of("/") + 1);
	log_name += ".log";
	log_name = "logs/" + log_name;
	Logger::open_log_file(log_name);
	Logger::enable_time(false);
	Logger::put_timestamp();
	Logger() << "Starting " << argv[0];
	try
	{
		getting_started(argc, argv);
	}
	catch(const std::exception& e)
	{
		Logger::quit();
		return EXIT_FAILURE;
	}
	
	vector_test();
	stack_test();
	pair_test();
	// map_test();
	Logger::quit();
	return EXIT_SUCCESS;
}