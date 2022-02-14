/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair_basic_test.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 15:44:38 by ldutriez          #+#    #+#             */
/*   Updated: 2022/02/14 11:26:08 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "main.hpp"
# include <algorithm>

void	pair_basic_test(void)
{
	Logger() << "\n----------(pair_basic_test)----------";
	
	ft::pair<int, float> p1;
	Logger() << "(" << p1.first << ", " << p1.second << ")";
 
    ft::pair<int, double> p2(42, 3.1415);
	Logger() << "(" << p2.first << ", " << p2.second << ")";

	ft::pair<int, float> p3(p1);
	Logger() << "(" << p3.first << ", " << p3.second << ")";

	ft::pair<int, float> p4(p2);
	Logger() << "(" << p4.first << ", " << p4.second << ")";

	p3 = p4;  
	Logger() << "(" << p3.first << ", " << p3.second << ")";

	Logger() << "(" << ft::make_pair(42, 3.1415).first << ", " << ft::make_pair(42, 3.1415).second << ")";

	ft::vector<ft::pair<int, std::string> > v;

	v.push_back(ft::make_pair(2, "baz"));
	v.push_back(ft::make_pair(2, "bar"));
	v.push_back(ft::make_pair(1, "foo"));
	#ifdef LINUX
    std::sort(v.begin(), v.end());
	#endif
    for(ft::vector<ft::pair<int, std::string> >::iterator it = v.begin(); it != v.end(); ++it)
	{
        Logger() << "{" << it->first << ", " << it->second << "}";
    }
}