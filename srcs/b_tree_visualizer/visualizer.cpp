/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 02:29:57 by ldutriez          #+#    #+#             */
/*   Updated: 2022/02/19 01:46:36 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

bool	g_delete_node = false;
bool	g_insert_node = false;
bool	g_insert_random = false;

int		cam_x = 0;
int		cam_y = 0;

void	input_manager(lcppgl::Context & context)
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
				// else if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_SPACE)
					// carry_on = true;
				else if (event.key.keysym.sym == SDLK_d)
					g_delete_node = true;
				else if (event.key.keysym.sym == SDLK_i)
					g_insert_node = true;
				else if (event.key.keysym.sym == SDLK_RETURN)
					g_insert_random = true;
				else if	(event.key.keysym.sym == SDLK_LEFT)
					cam_x += 20;
				else if	(event.key.keysym.sym == SDLK_RIGHT)
					cam_x -= 20;
				else if	(event.key.keysym.sym == SDLK_UP)
					cam_y += 20;
				else if	(event.key.keysym.sym == SDLK_DOWN)
					cam_y -= 20;
				break;
			default:
				break;
		}
	}
}

// Will calcul the offset between the root nodes and his children.
// The offset will be used to space out the nodes.
// behavior: will return the offset between the root and the leftmost node.
int		calcul_offset(const RedBlackTreeNode<int> * tree)
{
	int		offset(0);

	while (tree->_left != NULL)
	{
		offset++;
		tree = tree->_left;
	}
	return (offset);
}

#include <sstream>

std::string	to_string(int nb)
{
	std::stringstream	ss;

	ss << nb;
	return (ss.str());
}

int		to_int(const std::string & str)
{
	int					nb(0);
	std::stringstream	ss;

	ss << str;
	ss >> nb;
	return (nb);
}

// Calcul the how much nodes separate the node from the farthest leave.
int		deepest(const RedBlackTreeNode<int> * node)
{
	int		result(0);

	if (node == NULL)
		return (0);
	if (node->_left != NULL)
		result = std::max(result, deepest(node->_left));
	if (node->_right != NULL)
		result = std::max(result, deepest(node->_right));
	return (result + 1);
}

void	draw_node(lcppgl::Context & context, const RedBlackTreeNode<int> *node
				, int depth, int offset)
{
	// lcppgl::Writer writer(context, "/Users/ldutriez/.brew/Library/Homebrew/vendor/portable-ruby/2.6.8/lib/ruby/2.6.0/rdoc/generator/template/darkfish/fonts/Lato-Regular.ttf", 20);
	lcppgl::Printer drawer(context);
	lcppgl::tools::Color		node_color;
	// lcppgl::tools::Color		writing_color(255, 255, 255, 255);
	// std::string					s_value = to_string(node->_value);
	// int							nb_width(12 * s_value.size());
	lcppgl::tools::Rectangle	pos(cam_x + offset * 26
								, cam_y + depth * 100
								, 50, 25);
								// , nb_width, 25);

	if (node->_color == red)
		node_color = lcppgl::tools::Color(255, 0, 0, 255);
	else if (node->_color == black)
		node_color = lcppgl::tools::Color(0, 0, 0, 255);
	// writer.put_text_and_bg(s_value, pos, writing_color, node_color);
	drawer.put_filled_rect(pos, node_color);
}

// Will print the tree to the screen.
// behavior: will print the tree to the screen.
//			the offset will be used to space out the nodes.
//			the tree will be printed from the leftmost to the rightmost node.
//			the leftmost node will be at x = 0.
void	draw_tree(lcppgl::Context & context, const RedBlackTreeNode<int> *node, bool first_call)
{
	static int	offset(1);
	static int	depth(1);
	static lcppgl::Printer printer(context);
	
	if (first_call)
	{
		offset = 1;
		depth = 1;
	}

	if (node != NULL)
	{
		if (node->_left != NULL)
		{
			depth++;
			draw_tree(context, node->_left, false);
		}
		
		{
			lcppgl::tools::Point	p1(cam_x + offset * 26 + 25, cam_y + depth * 100);
			lcppgl::tools::Point	p2(p1.x, p1.y - 75);

			if (node->_parent && node == node->_parent->_left)
				p2.x = (cam_x + (offset + deepest(node)) * 26) + 25;
			else if (node->_parent && node == node->_parent->_right)
				p2.x = (cam_x + (offset - deepest(node)) * 26) + 25;
			else if (node->_parent == NULL)
				p2 = p1;
			printer.put_line(p1, p2, lcppgl::tools::Color(255, 255, 255, 255));
		}

		draw_node(context, node, depth, offset);
		if (node->_right != NULL)
		{
			offset++;
			depth++;
			draw_tree(context, node->_right, false);
			offset--;
		}
		depth--;
		offset++;
	}
}

void	welcome_message(lcppgl::Context & context)
{
	static bool	printed(false);

	if (printed == false)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "WELCOME",
		"You launch ldutriez's Red Black Tree Visualizer   \n"
		"                      Have fun\n"
		"  return = random insertion                       \n"
		"  i = input insertion           d = input deletion\n"
		"  arrow keys = camera movements                   \n"
		"  escape = quit                   F11 = fullscreen\n",
		context.window());
		printed = true;
	}
}

void	tree_rendering(lcppgl::Context & context)
{
	lcppgl::Printer render(context);
	static rbtree<int> test;
	static std::vector<std::string> proposition;

	// context.set_fps_limit(1);
	
	render.set_draw_color(lcppgl::tools::Color(70, 70, 70, 255));
	render.clear();
	welcome_message(context);
	try
	{
		if (g_insert_random == true)
		{
			g_insert_random = false;
			test.insert(rand() % 999);
		}
		else if (g_insert_node == true)
		{
			g_insert_node = false;
			test.insert(input_nbr_box(context, "Number to insert:", proposition, 4));
		}
		else if (g_delete_node == true)
		{
			g_delete_node = false;
			test.remove(input_nbr_box(context, "Number to remove:", proposition, 4));
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	draw_tree(context, test.root(), true);
	render.present();
}

void	visualize_b_tree(void)
{
	Logger() << "======================={Visualize B-Tree test}=======================";
	try
	{
		lcppgl::Context & main_context = lcppgl::Application::instance().create_context("RB-Tree Visualizer", 1920, 1080);
		main_context.add_event_functor(input_manager);
		main_context.add_render_functor(tree_rendering);
		lcppgl::Application::instance().run();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}