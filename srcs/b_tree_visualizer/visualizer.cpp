/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 02:29:57 by ldutriez          #+#    #+#             */
/*   Updated: 2022/02/06 03:49:47 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"


void	exit_input(lcppgl::Context & context)
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				context.stop();
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
					context.stop();
				else if (event.key.keysym.sym == SDLK_F11)
					context.set_fullscreen(!context.is_fullscreen());
				break;
			default:
				break;
		}
	}
}

#include <sstream>

void	print_node(lcppgl::Writer & writer, lcppgl::Printer & render, lcppgl::Context & context, ft::binary_search_tree<int> &node)
{
	static int	depth(0);
	static int	offset(0);
	static lcppgl::tools::Point	p1;
	static lcppgl::tools::Point	p2;
	
	if (node._left)
	{
		offset--;
		depth++;
		print_node(writer, render, context, *node._left);
		offset++;
		depth--;
	}
	std::ostringstream nb;
	nb << node._value;
	int	nb_width(20 * nb.str().size());
	writer.put_text(nb.str(),
		lcppgl::tools::Rectangle(context.width() / 2 - (nb_width / 2) + (offset * nb_width),
								50 + (depth * 50),
								nb_width,
								40),
		lcppgl::tools::Color(255, 255, 255, 255));
	if (node._right)
	{
		offset++;
		depth++;
		print_node(writer, render, context, *node._right);
		offset--;
		depth--;
	}
	p1 = lcppgl::tools::Point(context.width() / 2 - (nb_width / 2) + (offset * nb_width),
								50 + (depth * 50));
	int	parent_offset(offset);
	if (node._parent && node._parent->_left == &node)
		parent_offset++;
	else if (node._parent && node._parent->_right == &node)
		parent_offset--;
	else
		parent_offset = 0;
	p2 = lcppgl::tools::Point(context.width() / 2 + (nb_width / 2) + (parent_offset * nb_width),
								50 + (depth - 1 * 50));
	render.put_line(p1, p2, lcppgl::tools::Color(255, 200, 200, 255));
}

void	tree_rendering(lcppgl::Context & context)
{
	lcppgl::Printer render(context);
	lcppgl::Writer writer(context, "/usr/share/fonts/truetype/freefont/FreeSans.ttf", 40);
	context.set_fps_limit(2);
	
	render.clear();
	// writer.put_pretty_text("Hello World!", lcppgl::tools::Rectangle(20, 250, 480, 80),
	// 	lcppgl::tools::Color(255, 255, 255, 255));
	ft::binary_search_tree<int> test(42);

	// int rand_nb = rand() % INT32_MAX;
	// test.insert(rand_nb);
	test.insert(12);
	test.insert(-728);
	test.insert(0);
	test.insert(15678);
	test.insert(-683155);
	test.insert(99);

	print_node(writer, render, context, test);	
	render.present();
}

void	visualize_b_tree(void)
{
	Logger() << "======================={Visualize B-Tree test}=======================";
	try
	{
		lcppgl::Context & main_context = lcppgl::Application::instance().create_context();
		main_context.add_event_functor(exit_input);
		main_context.add_render_functor(tree_rendering);
		lcppgl::Application::instance().run();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}