/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 17:14:44 by notcampeur        #+#    #+#             */
/*   Updated: 2022/03/03 22:56:14 by ldutriez         ###   ########.fr       */
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
	int seed(0);

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
	#ifdef FT
		Logger() << "FT testing with seed : " << seed << "\n";
	#else
		Logger() << "STL testing with seed : " << seed << "\n";
	#endif

}

#ifndef TREE_VISUALIZER
void	vector_test(void)
{
	Logger() << "======================={Vector test}=======================";
	vector_iterators_test();
	vector_capacity_test();
	vector_element_access_test();
	vector_modifiers_test();
	vector_allocator_test();
	vector_relational_operators_test();
	vector_string_test();
	vector_inception_test();
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
	Logger() << "======================={Map test}=======================";
	map_allocator_test();
	map_capacity_test();
	map_element_access_test();
	map_iterators_test();
	map_limit_test();
	map_modifiers_test();
	map_observers_test();
	map_operations_test();
	map_relational_operators_test();
}

void	set_test(void)
{
	Logger() << "======================={Set test}=======================";
	set_allocator_test();
	set_capacity_test();
	set_iterators_test();
	set_limit_test();
	set_modifiers_test();
	set_observers_test();
	set_operations_test();
	set_relational_operators_test();
}
#endif

void	tree_test(void)
{
	Logger() << "======================={Tree test}=======================";
	#ifdef FT
	ft::rbtree<int> tree;
	
	try
	{
		tree.insert(rand() % INT32_MAX);
		tree.insert(rand() % INT32_MAX);
		tree.insert(rand() % INT32_MAX);
		tree.insert(rand() % INT32_MAX);
		tree.insert(rand() % INT32_MAX);
		tree.insert(rand() % INT32_MAX);
		tree.insert(rand() % INT32_MAX);
		tree.insert(rand() % INT32_MAX);
		tree.insert(rand() % INT32_MAX);
		tree.insert(rand() % INT32_MAX);
		tree.insert(rand() % INT32_MAX);
		tree.insert(rand() % INT32_MAX);
		tree.insert(rand() % INT32_MAX);
		tree.insert(rand() % INT32_MAX);
		tree.insert(rand() % INT32_MAX);
		tree.insert(rand() % INT32_MAX);
		tree.insert(rand() % INT32_MAX);
		tree.insert(rand() % INT32_MAX);
		tree.insert(rand() % INT32_MAX);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	ft::rbtree<int>::iterator it = tree.begin();
	ft::rbtree<int>::iterator ite = tree.end();
	Logger() << "inorder: " << tree.size();
	// print address of it and ite
	for (int i(0); it != ite; it++)
	{
		Logger() << "[" << i << "] :" << *it;
		i++;
	}
		
	ft::rbtree<int>::reverse_iterator rit = tree.rbegin();
	ft::rbtree<int>::reverse_iterator rite = tree.rend();
	Logger() << "reverse inorder: " << tree.size();
	// print address of rit and rite
	for (int i(0); rit != rite; rit++)
	{
		Logger() << "[" << i << "] :" << *rit;
		i++;
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
	
	#ifndef TREE_VISUALIZER
		vector_test();
		stack_test();
		pair_test();
		map_test();
		set_test();
	#elif TREE_VISUALIZER
		tree_test();
		visualize_b_tree();
	#endif
	Logger::quit();
	return EXIT_SUCCESS;
}