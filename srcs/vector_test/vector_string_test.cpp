/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_string_test.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 13:07:06 by hbaudet           #+#    #+#             */
/*   Updated: 2022/03/03 22:42:31 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.hpp>

#include <sstream>

std::string	to_string(int nb)
{
	std::stringstream	ss;

	ss << nb;
	return (ss.str());
}

void vector_string_test()
{
	Logger() << "\n----------(mazoise_vector_string_test)----------";
	
	ft::vector<std::string> JOHN;
	ft::vector<std::string> BOB(5, "Hello");
	Logger() << "BOB(5, 8) : ";
	for (size_t i = 0; i < BOB.size(); i++)
		Logger() << BOB[i] << ' ';
	Logger() << '\n';
	ft::vector<std::string> MIKE(BOB);

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
	MIKE.resize(mike_resize, "juste some random string");
	/*
	Logger() << "Size of JOHN " << JOHN.size();
	Logger() << "Capacity of JOHN " << JOHN.capacity();
	Logger() << "Size of BOB " << BOB.size();
	Logger() << "Capacity of BOB " << BOB.capacity();
	Logger() << "Size of MIKE " << MIKE.size();
	Logger() << "Capacity of MIKE " << MIKE.capacity();
	*/
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
		Logger() << MIKE[i] << ' ';
	Logger();

	// RESERVE
	Logger() << "\nRESERVE\n";

	size_t	john_reserve = 5;
	size_t	bob_reserve = 3;
	size_t	mike_reserve = 83;

	JOHN.reserve(john_reserve);
	BOB.reserve(bob_reserve);
	MIKE.reserve(mike_reserve);
	/*
	Logger() << "Size of JOHN " << JOHN.size();
	Logger() << "Capacity of JOHN " << JOHN.capacity();
	Logger() << "Size of BOB " << BOB.size();
	Logger() << "Capacity of BOB " << BOB.capacity();
	Logger() << "Size of MIKE " << MIKE.size();
	Logger() << "Capacity of MIKE " << MIKE.capacity();
	*/
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
		Logger() << MIKE[i] << ' ';
	Logger();

	//AT
	Logger() << "\nAT\n";
	try
	{
		Logger() << MIKE.at(2) << '\n';
		Logger() << MIKE.at(87) << '\n';
	}
	catch (std::out_of_range& oor)
	{
		(void)oor;
		Logger() << "OOR error caught\n";
	}

	// FRONT / BACK
	Logger() << "\nFRONT / BACK\n";
	Logger() << "front() of MIKE : " << MIKE.front() << '\n';
	Logger() << "back() of MIKE : " << MIKE.back() << '\n';

	//ASSIGN
	Logger() << "\nASSIGN\n";
	BOB.assign(42, "James BOND");

	//ASSIGN RANGE
	Logger() << "\nASSIGN RANGE\n";
	ft::vector<std::string>	assign_range;
	assign_range.assign(8, "Covfefe");
	assign_range.assign(BOB.begin() + 1, BOB.end() - 2);

	//EMPTY
	Logger() << "\nEMPTY\n";
	Logger() << "BOB is empty ? " << BOB.empty() << '\n';
	Logger() << "BOB at(41) : " << BOB.at(41) << '\n';

	//PUSH/POP_BACK
	Logger() << "\nPUSH/POP_BACK\n";
	BOB.push_back("My name is Bond");
	Logger() << "last elem of BOB : " << BOB.back() << '\n';
	BOB.pop_back();
	Logger() << "last elem of BOB : " << BOB.back() << '\n';

	//INSERT
	Logger() << "\nINSERT\n";
	ft::vector<std::string>	insert_in_me;
	for (size_t i = 0; i < 15; i++)
		insert_in_me.push_back(to_string(i) + " I love hbaudet\n");
	Logger() << "after push_back, before at\n";
	for (size_t i = 0; i < insert_in_me.size(); i++)
		Logger() << insert_in_me.at(i) << ' ';
	Logger() << '\n';

	ft::vector<std::string>::iterator	tmp;
	tmp = insert_in_me.begin() + 4;
	insert_in_me.insert(tmp, 8, "Norminet");
	for (size_t i = 0; i < insert_in_me.size(); i++)
		Logger() << insert_in_me.at(i) << ' ';
	Logger() << '\n';

	ft::vector<std::string>::const_iterator const_it(insert_in_me.begin());
	Logger() << "Const it : ";
	Logger() << *const_it << '\n';
//	*const_it = 89; // Does not compile because it's a const_iterator


	//INSERT
	Logger() << "\nINSERT\n";
	ft::vector<std::string>	std_insert_in_me;
	for (size_t i = 0; i < 15; i++)
		std_insert_in_me.push_back(to_string(i) + " 42 ");
	for (size_t i = 0; i < std_insert_in_me.size(); i++)
		Logger() << std_insert_in_me.at(i) << ' ';
	Logger() << '\n';

	ft::vector<std::string>::iterator	std_tmp;
	std_tmp = std_insert_in_me.begin() + 4;
	std_insert_in_me.insert(std_tmp, 8, "Why are you reading this!?");
	for (size_t i = 0; i < std_insert_in_me.size(); i++)
		Logger() << std_insert_in_me.at(i) << ' ';
	Logger() << '\n';


	//INSERT RANGE
	Logger() << "\nINSERT RANGE\n";
	ft::vector<std::string>	insert_bis;
	for (size_t i = 0; i < 7; i++)
		insert_bis.push_back(to_string(3 * i));
	for (size_t i = 0; i < insert_bis.size(); i++)
		Logger() << insert_bis[i] << ' ';
	Logger() << '\n';

	insert_bis.insert(insert_bis.begin() + 5, insert_in_me.begin(), insert_in_me.end());
	for (size_t i = 0; i < insert_bis.size(); i++)
		Logger() << insert_bis[i] << ' ';
	Logger() << '\n';


	//ERASE
	Logger() << "\nERASE\n";
	ft::vector<std::string>	erase_in_me;
	for (size_t i = 0; i < 15; i++)
		erase_in_me.push_back(to_string(2 * i));
	for (size_t i = 0; i < erase_in_me.size(); i++)
	{
//		if (erase_in_me[i] < 10)
//			Logger() << ' ';
		Logger() << erase_in_me.at(i) << ' ';
	}
	Logger() << '\n';

	erase_in_me.erase(erase_in_me.begin() + 7);
	for (size_t i = 0; i < erase_in_me.size(); i++)
	{
//		if (erase_in_me[i] < 10)
//			Logger() << ' ';
		Logger() << erase_in_me.at(i) << ' ';
	}
	Logger() << '\n';

	erase_in_me.erase(erase_in_me.begin() + 2, erase_in_me.begin() + 6);
	for (size_t i = 0; i < erase_in_me.size(); i++)
	{
//		if (erase_in_me[i] < 10)
//			Logger() << ' ';
		Logger() << erase_in_me.at(i) << ' ';
	}
	Logger() << '\n';

	//SWAP
	Logger() << "\nSWAP\n";
	BOB.swap(MIKE);
	/*
	Logger() << "Size of BOB " << BOB.size();
	Logger() << "Capacity of BOB " << BOB.capacity();
	Logger() << "Size of MIKE " << MIKE.size();
	Logger() << "Capacity of MIKE " << MIKE.capacity();
	*/
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
		Logger() << MIKE[i] << ' ';
	Logger();

	MIKE.swap(JOHN);
	/*
	Logger() << "Size of JOHN " << JOHN.size();
	Logger() << "Capacity of JOHN " << JOHN.capacity();
	Logger() << "Size of MIKE " << MIKE.size();
	Logger() << "Capacity of MIKE " << MIKE.capacity();
	*/
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
		Logger() << MIKE[i] << ' ';
	Logger();

	//CLEAR
	Logger() << "\nCLEAR\n";
	JOHN.clear();
	MIKE.clear();
	/*
	Logger() << "Size of JOHN " << JOHN.size();
	Logger() << "Capacity of JOHN " << JOHN.capacity();
	Logger() << "Size of MIKE " << MIKE.size();
	Logger() << "Capacity of MIKE " << MIKE.capacity();
	*/
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
		Logger() << MIKE[i] << ' ';
	Logger();

	//NON MEMBER Functions
	Logger() << "\nNON MEMBER functions\n";
	swap(BOB, MIKE);
	/*
	Logger() << "Size of BOB " << BOB.size();
	Logger() << "Capacity of BOB " << BOB.capacity();
	Logger() << "Size of MIKE " << MIKE.size();
	Logger() << "Capacity of MIKE " << MIKE.capacity();
	*/
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
		Logger() << MIKE[i] << ' ';
	Logger();
	
	//RELATIONAL OPERATORS
	Logger() << "\nRELATIONAL OPERATORS\n";
	ft::vector<std::string> MIKE_2(MIKE);
	Logger() << "MIKE and BOB are equal ? " << (MIKE == BOB) << '\n';
	Logger() << "MIKE and MIKE_2 are equal ? " << (MIKE == MIKE_2) << '\n';

	ft::vector<std::string> real;
	real.assign(5, "foo");
	for (ft::vector<std::string>::iterator it = real.begin(); it != real.end(); it++)
		Logger() << *it << " ";
	Logger() << '\n';

	Logger();
}
