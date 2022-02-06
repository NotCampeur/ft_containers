/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 20:13:05 by notcampeur        #+#    #+#             */
/*   Updated: 2022/02/06 02:30:57 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINERS_MAIN_HPP
# define CONTAINERS_MAIN_HPP

# include <iostream>
# include <string>
# include <deque>
# include <sys/time.h>
# include <stdlib.h>
# include <limits>
# include <stdint.h>
# include "Logger.hpp"
# include "lcppgl.hpp"

# ifdef DIY
	#  include <map.hpp>
	#  include <stack.hpp>
	#  include <vector.hpp>
# else
	#  include <map>
	#  include <stack>
	#  include <vector>
	namespace ft = std;
# endif

# define MAX_RAM 4294967296
# define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};

# define COUNT (MAX_RAM / (int)sizeof(Buffer))

void	vector_test(void);
void	vector_iterators_test(void);
void	vector_capacity_test(void);
void	vector_element_access_test(void);
void	vector_modifiers_test(void);
void	vector_allocator_test(void);
void	vector_relational_operators_test(void);

void	stack_test(void);
void	stack_capacity_test(void);
void	stack_element_access_test(void);
void	stack_modifiers_test(void);
void	stack_relational_operators_test(void);
void	stack_mutant_test(void);

void	pair_basic_test(void);

void	map_test(void);

void	visualize_b_tree(void);

long	get_elapsed_time(struct timeval	start_time);

int		getting_seed(char *argv[]);
void	getting_started(int argc, char *argv[]);

#endif