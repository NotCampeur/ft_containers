/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notcampeur <notcampeur@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 17:14:44 by notcampeur        #+#    #+#             */
/*   Updated: 2021/11/02 15:21:44 by notcampeur       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <deque>
#include <sys/time.h>

#ifdef DIY
	# include <map.hpp>
	# include <stack.hpp>
	# include <vector.hpp>
#else
	# include <map>
	# include <stack>
	# include <vector>
	namespace ft = std;
#endif

#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};

// #define COUNT 500
#define COUNT (MAX_RAM / (int)sizeof(Buffer))

#ifndef DIY
	template<typename T>
	class MutantStack : public ft::stack<T>
	{
		public:
			MutantStack() {}
			MutantStack(const MutantStack<T>& src) { *this = src; }
			MutantStack<T>& operator=(const MutantStack<T>& rhs) 
			{
				this->c = rhs.c;
				return *this;
			}
			~MutantStack() {}

			typedef typename ft::stack<T>::container_type::iterator iterator;

			iterator begin() { return this->c.begin(); }
			iterator end() { return this->c.end(); }
	};
#endif

long	get_elapsed_time(struct timeval	start_time)
{
	struct timeval	act_time;

	gettimeofday(&act_time, NULL);
	return ((act_time.tv_sec - start_time.tv_sec) * 1000L
			+ (act_time.tv_usec - start_time.tv_usec) / 1000L);
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
		std::cerr << "Usage: " << argv[0] << " seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		throw std::exception();
	}
	try
	{
		seed = getting_seed(argv);
	}
	catch(const std::exception& e)
	{
		std::cerr << "The seed need to be a number." << std::endl;
		throw ;
	}
	srand(seed);
	#ifdef DIY
		std::cout << "DIY testing with seed : " << seed << std::endl;
	#else
		std::cout << "STL testing with seed : " << seed << std::endl;
	#endif

}

void	vector_test(void)
{
	ft::vector<std::string> vector_str;
	ft::vector<int> vector_int;
	ft::vector<Buffer> vector_buffer;

	struct timeval	start_time;
	long			elapsed_time;
	
	gettimeofday(&start_time, NULL);
	for (size_t i = 0; i < COUNT; i++)
	{
		vector_buffer.push_back(Buffer());
	}
	elapsed_time = get_elapsed_time(start_time);
	std::cout << "[Size / Capacity]:[" << vector_buffer.size() << " / " << vector_buffer.capacity()
	<< "] Elapsed time : " << elapsed_time << std::endl;
	for (size_t i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		vector_buffer[i].idx = idx;
	}
	std::cout << vector_buffer[rand() % COUNT].idx << std::endl;
	ft::vector<Buffer>().swap(vector_buffer);
	
	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		//NORMAL ! :P
	}
	#ifndef DIY
	#endif
}

void	stack_test(void)
{
	#ifndef DIY
	ft::stack<int> stack_int;
	ft::stack<Buffer, std::deque<int> > stack_deq_buffer;
	MutantStack<char> iterable_stack;

	for (char letter = 'a'; letter <= 'z'; letter++)
		iterable_stack.push(letter);
	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	{
		std::cout << *it;
	}
	std::cout << std::endl;
	#endif
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
	std::cout << "should be constant with the same seed: " << sum << std::endl;

	{
		ft::map<int, int> copy = map_int;
	}
	#endif
}

int main(int argc, char** argv)
{
	try
	{
		getting_started(argc, argv);
	}
	catch(const std::exception& e)
	{
		return EXIT_FAILURE;
	}
	
	vector_test();
	stack_test();
	map_test();
	return EXIT_SUCCESS;
}