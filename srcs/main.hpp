/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notcampeur <notcampeur@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 20:13:05 by notcampeur        #+#    #+#             */
/*   Updated: 2021/11/03 10:47:08 by notcampeur       ###   ########.fr       */
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

// The following are UBUNTU/LINUX, and MacOS ONLY terminal color codes.
# define RESET			"\033[0m"
# define BLACK			"\033[30m"
# define RED			"\033[31m"
# define GREEN			"\033[32m"
# define YELLOW			"\033[33m"
# define BLUE			"\033[34m"
# define MAGENTA		"\033[35m"
# define CYAN			"\033[36m"
# define WHITE			"\033[37m"
# define BOLDBLACK		"\033[1m\033[30m"
# define BOLDRED		"\033[1m\033[31m"
# define BOLDGREEN		"\033[1m\033[32m"
# define BOLDYELLOW		"\033[1m\033[33m"
# define BOLDBLUE		"\033[1m\033[34m"
# define BOLDMAGENTA	"\033[1m\033[35m"
# define BOLDCYAN		"\033[1m\033[36m"
# define BOLDWHITE		"\033[1m\033[37m"

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

// Wait for the user to press enter and ignore other input
void	wait_for_enter();

void	vector_capacity_test(void);

#endif