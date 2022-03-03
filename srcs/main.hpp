/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 20:13:05 by notcampeur        #+#    #+#             */
/*   Updated: 2022/03/03 22:56:14 by ldutriez         ###   ########.fr       */
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

# ifdef TREE_VISUALIZER
#  include "lcppgl.hpp"
int	input_nbr_box(lcppgl::Context & context, const char *text
					, std::vector<std::string> &proposition
					, unsigned long max_size_entry);
# endif

# ifdef FT
	#  include <map.hpp>
	#  include <stack.hpp>
	#  include <vector.hpp>
	#  include <set.hpp>
# else
	#  include <map>
	#  include <stack>
	#  include <vector>
	#  include <set>
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
void	vector_string_test();
void	vector_inception_test();

void	stack_test(void);
void	stack_capacity_test(void);
void	stack_element_access_test(void);
void	stack_modifiers_test(void);
void	stack_relational_operators_test(void);
void	stack_mutant_test(void);

void	pair_basic_test(void);

void	map_test(void);
void	map_allocator_test(void);
void	map_capacity_test(void);
void	map_element_access_test(void);
void	map_iterators_test(void);
void	map_limit_test(void);
void	map_modifiers_test(void);
void	map_observers_test(void);
void	map_operations_test(void);
void	map_relational_operators_test(void);

void	set_test(void);
void	set_allocator_test(void);
void	set_capacity_test(void);
void	set_iterators_test(void);
void	set_limit_test(void);
void	set_modifiers_test(void);
void	set_observers_test(void);
void	set_operations_test(void);
void	set_relational_operators_test(void);

# ifdef TREE_VISUALIZER
void	visualize_b_tree(void);
# endif

long	get_elapsed_time(struct timeval	start_time);

int		getting_seed(char *argv[]);
void	getting_started(int argc, char *argv[]);

#endif