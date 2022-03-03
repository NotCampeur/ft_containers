/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_inception_test.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 13:07:06 by hbaudet           #+#    #+#             */
/*   Updated: 2022/03/03 06:44:00 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.hpp>

void vector_inception_test()
{
	ft::vector<int>			test(3, 3);

	Logger() << "self assignation test\n";
	ft::vector<ft::vector<int> >	self_assign;
	ft::vector<ft::vector<int> >	*ptr = &self_assign;
	ft::vector<ft::vector<int> >	*ptr2 = &self_assign;

	self_assign.assign(4, test);
	*ptr = *ptr2;

	Logger() << std::boolalpha << (*ptr == *ptr2) << '\n';
//	self_assign = self_assign; //compiler doesn't like it!



	ft::vector<ft::vector<int> > JOHN;
	ft::vector<ft::vector<int> > BOB(5, test);
	Logger() << "BOB(5, test(test, 5)) : \n";
	for (size_t i = 0; i < BOB.size(); i++)
	{
		for (size_t j = 0; j < BOB[i].size(); j++)
			Logger() << BOB[i][j] << ' ';
		Logger() << '\n';
	}
	ft::vector<ft::vector<int> > MIKE(BOB);

	// CTORs
	Logger() << "\nCTORS\n";
	Logger() << "Empty is empty ? " << std::boolalpha << JOHN.empty() << '\n';
	Logger() << "BOB is empty? " << BOB.empty() << '\n';

	Logger() << "Size of JOHN " << JOHN.size();
	Logger() << "Size of BOB " << BOB.size();
	Logger() << "Size of MIKE " << MIKE.size();

	// RESIZE
	size_t	bob_resize = 2;
	Logger() << "\nRESIZE\n";
	BOB.resize(bob_resize);
	Logger() << "Size of JOHN " << JOHN.size();
	if (JOHN.capacity() >= JOHN.size())
		Logger() << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 53\n";
	Logger() << "Size of BOB " << BOB.size();
	if (BOB.capacity() >= bob_resize)
		Logger() << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 58\n";
	Logger() << "Size of MIKE " << MIKE.size();
	if (MIKE.capacity() >= MIKE.size())
		Logger() << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 63\n";

	size_t	mike_resize = 9;
	bob_resize = 0;
	
	BOB.resize(bob_resize);
	Logger() << "BOB is empty now ? " << BOB.empty() << '\n';
	MIKE.resize(mike_resize, test);
	Logger() << "Size of JOHN " << JOHN.size();
	if (JOHN.capacity() >= JOHN.size())
		Logger() << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 86\n";
	Logger() << "Size of BOB " << BOB.size();
	if (BOB.capacity() >= bob_resize)
		Logger() << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 91\n";
	Logger() << "Size of MIKE " << MIKE.size();
	if (MIKE.capacity() >= mike_resize)
		Logger() << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 96\n";
	for (size_t i = 0; i < MIKE.size(); i++)
	{
		for (size_t j = 0; j < MIKE[i].size(); j++)
		{
			Logger() << MIKE[i][j] << ' ';
		}
	Logger();
	}
	// RESERVE
	Logger() << "\nRESERVE\n";

	size_t	john_reserve = 0;
	size_t	bob_reserve = 3;
	size_t	mike_reserve = 4;

	JOHN.reserve(john_reserve);
	BOB.reserve(bob_reserve);
	MIKE.reserve(mike_reserve);
	Logger() << "Size of JOHN " << JOHN.size();
	if (JOHN.capacity() >= john_reserve)
		Logger() << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 120\n";
	Logger() << "Size of BOB " << BOB.size();
	if (BOB.capacity() >= bob_reserve)
		Logger() << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 125\n";
	Logger() << "Size of MIKE " << MIKE.size();
	if (MIKE.capacity() >= mike_reserve)
		Logger() << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 130\n";
	for (size_t i = 0; i < MIKE.size(); i++)
	{
		for (size_t j = 0; j < MIKE[i].size(); j++)
			Logger() << MIKE[i][j] << ' ';
	Logger();
	}

	//AT
	Logger() << "\nAT\n";
	try
	{
		Logger() << MIKE.at(2).front() << '\n';
		Logger() << MIKE.at(87).back() << '\n';
	}
	catch (std::out_of_range& oor)
	{
		(void)oor;
		Logger() << "OOR error caught\n";
	}

	// FRONT / BACK
	Logger() << "\nFRONT / BACK\n";
	Logger() << "front() of MIKE : " << MIKE.front().front() << '\n';
	Logger() << "back() of MIKE : " << MIKE.back().back() << '\n';

	//ASSIGN
	Logger() << "\nASSIGN\n";
	test.assign(3, 17);
	BOB.assign(3, test);

	//ASSIGN RANGE
	Logger() << "\nASSIGN RANGE\n";
	ft::vector<ft::vector<int> >	assign_range;
	assign_range.assign(8, test);
	assign_range.assign(BOB.begin() + 1, BOB.end() - 2);

	//EMPTY
	Logger() << "\nEMPTY\n";
	Logger() << "BOB is empty ? " << BOB.empty() << '\n';
	Logger() << "BOB at(1) : " << BOB.at(1).front() << '\n';

	//PUSH/POP_BACK
	Logger() << "\nPUSH/POP_BACK\n";
	test.assign(2, 42);
	BOB.push_back(test);
	Logger() << "last elem of BOB : " << BOB.back().back() << '\n';
	BOB.pop_back();
	Logger() << "last elem of BOB : " << BOB.back().back() << '\n';

	//INSERT
	Logger() << "\nINSERT\n";
	ft::vector<ft::vector<int> >	insert_in_me;
	for (int i = 0; i < 15; i++)
	{
		ft::vector<int>	j(2, i);
		insert_in_me.push_back(j);
	}
	for (size_t i = 0; i < insert_in_me.size(); i++)
	{
		for (size_t j = 0; j < insert_in_me.at(i).size(); j++)
			Logger() << insert_in_me.at(i).at(j) << ' ';
		Logger() << '\n';
	}

	ft::vector<ft::vector<int> >::iterator	tmp;
	test.assign(23, 19);
	tmp = insert_in_me.begin() + 4;
	insert_in_me.insert(tmp, 8, test);
	for (size_t i = 0; i < insert_in_me.size(); i++)
	{
		for (size_t j = 0; j < insert_in_me.at(i).size(); j++)
			Logger() << insert_in_me.at(i).at(j) << ' ';
		Logger() << '\n';
	}

	ft::vector<ft::vector<int> >::const_iterator const_it(insert_in_me.begin());
	Logger() << "Const it.front() : ";
	Logger() << (*const_it).front() << '\n';


	//INSERT
	Logger() << "\nINSERT\n";
	ft::vector<ft::vector<int> >	std_insert_in_me;
	for (int i = 0; i < 15; i++)
		std_insert_in_me.push_back(test);
	for (size_t i = 0; i < std_insert_in_me.size(); i++)
		Logger() << std_insert_in_me.at(i).front() << ' ';
	Logger() << '\n';

	ft::vector<ft::vector<int> >::iterator	std_tmp;
	std_tmp = std_insert_in_me.begin() + 4;
	std_insert_in_me.insert(std_tmp, 8, test);
	for (size_t i = 0; i < std_insert_in_me.size(); i++)
		Logger() << std_insert_in_me.at(i).back() << ' ';
	Logger() << '\n';


	//INSERT RANGE
	Logger() << "\nINSERT RANGE\n";
	ft::vector<ft::vector<int> >	insert_bis;
	for (int i = 0; i < 7; i++)
	{
		ft::vector<int>	j(2, i * 3);
		insert_bis.push_back(j);
	}
	for (size_t i = 0; i < insert_bis.size(); i++)
		Logger() << insert_bis[i].back() << ' ';
	Logger() << '\n';

	insert_bis.insert(insert_bis.begin() + 5, insert_in_me.begin(), insert_in_me.end());
	for (size_t i = 0; i < insert_bis.size(); i++)
		Logger() << insert_bis[i].back() << ' ';
	Logger() << '\n';


	//ERASE
	Logger() << "\nERASE\n";
	ft::vector<ft::vector<int> >	erase_in_me;
	for (int i = 0; i < 15; i++)
	{
		ft::vector<int>	j(1, i);
		erase_in_me.push_back(j);
	}
	for (size_t i = 0; i < erase_in_me.size(); i++)
		Logger() << erase_in_me.at(i).front() << ' ';
	Logger() << '\n';

	erase_in_me.erase(erase_in_me.begin() + 7);
	for (size_t i = 0; i < erase_in_me.size(); i++)
		Logger() << erase_in_me.at(i).front() << ' ';
	Logger() << '\n';
	erase_in_me.erase(erase_in_me.begin() + 2, erase_in_me.begin() + 6);
	for (size_t i = 0; i < erase_in_me.size(); i++)
		Logger() << erase_in_me.at(i).front() << ' ';
	Logger() << '\n';

	//SWAP
	Logger() << "\nSWAP\n";
	john_reserve = 4;
	JOHN.reserve(john_reserve);
	BOB.swap(MIKE);
	Logger() << "Size of JOHN " << JOHN.size();
	if (JOHN.capacity() >= JOHN.size())
		Logger() << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 272\n";
	Logger() << "Size of BOB " << BOB.size();
	if (BOB.capacity() >= BOB.size())
		Logger() << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 277\n";
	Logger() << "Size of MIKE " << MIKE.size();
	if (MIKE.capacity() >= MIKE.size())
		Logger() << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 282\n";
	for (size_t i = 0; i < MIKE.size(); i++)
	{
		for (size_t j = 0; j < MIKE[i].size(); j++)
			Logger() << MIKE[i][j] << ' ';
	Logger();
	}

	MIKE.swap(JOHN);
	Logger() << "Size of JOHN " << JOHN.size();
	if (JOHN.capacity() >= JOHN.size())
		Logger() << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 298\n";
	Logger() << "Size of BOB " << BOB.size();
	if (BOB.capacity() >= BOB.size())
		Logger() << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 303\n";
	Logger() << "Size of MIKE " << MIKE.size();
	if (MIKE.capacity() >= MIKE.size())
		Logger() << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 308\n";
	for (size_t i = 0; i < MIKE.size(); i++)
	{
		for (size_t j = 0; j < MIKE[i].size(); j++)
			Logger() << MIKE[i][j] << ' ';
	Logger();
	}

	//CLEAR
	Logger() << "\nCLEAR\n";
	JOHN.clear();
	MIKE.clear();
	Logger() << "Size of JOHN " << JOHN.size();
	if (JOHN.capacity() >= JOHN.size())
		Logger() << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 327\n";
	Logger() << "Size of BOB " << BOB.size();
	if (BOB.capacity() >= BOB.size())
		Logger() << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 332\n";
	Logger() << "Size of MIKE " << MIKE.size();
	if (MIKE.capacity() >= MIKE.size())
		Logger() << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 337\n";
	for (size_t i = 0; i < MIKE.size(); i++)
	{
		for (size_t j = 0; j < MIKE[i].size(); j++)
			Logger() << MIKE[i][j] << ' ';
	Logger();
	}

	//NON MEMBER Functions
	Logger() << "\nNON MEMBER functions\n";
	swap(BOB, MIKE);
	Logger() << "Size of JOHN " << JOHN.size();
	if (JOHN.capacity() >= JOHN.size())
		Logger() << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 355\n";
	Logger() << "Size of BOB " << BOB.size();
	if (BOB.capacity() >= BOB.size())
		Logger() << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 360\n";
	Logger() << "Size of MIKE " << MIKE.size();
	if (MIKE.capacity() >= MIKE.size())
		Logger() << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 365\n";
	for (size_t i = 0; i < MIKE.size(); i++)
	{
		for (size_t j = 0; j < MIKE[i].size(); j++)
			Logger() << MIKE[i][j] << ' ';
	Logger();
	}
	
	//RELATIONAL OPERATORS
	Logger() << "\nRELATIONAL OPERATORS\n";
	ft::vector<ft::vector<int> > MIKE_2(MIKE);
	Logger() << "MIKE and BOB are equal ? " << (MIKE == BOB) << '\n';
	Logger() << "MIKE and MIKE_2 are equal ? " << (MIKE == MIKE_2) << '\n';

	Logger() << "\nReal ft::Vector\n";
	ft::vector<ft::vector<int> > real;
	real.assign(5, test);
	for (ft::vector<ft::vector<int> >::iterator it = real.begin(); it != real.end(); it++)
		Logger() << (*it).front() << " ";
	Logger() << '\n';

	Logger();
}

