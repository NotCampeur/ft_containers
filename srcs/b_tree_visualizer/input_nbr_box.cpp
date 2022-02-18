/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_nbr_box.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 19:18:41 by ldutriez          #+#    #+#             */
/*   Updated: 2022/02/17 20:03:43 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

void	insert_typed_input(SDL_Event e, std::string &string
							, unsigned long &index, int &proposition_index
							, unsigned long max_size_entry)
{
	const Uint8		*keystates = SDL_GetKeyboardState(NULL);

	if ((keystates[SDL_SCANCODE_RSHIFT] || keystates[SDL_SCANCODE_LSHIFT])
			&& (e.key.keysym.sym >= SDLK_a && e.key.keysym.sym <= SDLK_z))
		e.key.keysym.sym = e.key.keysym.sym - 32;
	else if ((keystates[SDL_SCANCODE_RSHIFT] || keystates[SDL_SCANCODE_LSHIFT])
			&& (e.key.keysym.sym == SDLK_MINUS))
		e.key.keysym.sym = '_';
	if (string.size() < max_size_entry + 1)
	{
		string.insert(index, 1, e.key.keysym.sym);
		(index)++;
		proposition_index = 0;
	}
}

void	backspace_typed_input(std::string &string, unsigned long &index
								, int &proposition_index)
{
	if (index > 0)
	{
		string.erase(index - 1, 1);
		index--;
		proposition_index = 0;
	}
}

void	delete_typed_input(std::string &string, unsigned long &index
							, int &proposition_index)
{
	if (index + 1 < string.size())
	{
		string.erase(index + 1, 1);
		proposition_index = 0;
	}
}

void	move_left_in_input(std::string &string, unsigned long &index)
{
	if (index > 0)
	{
		std::swap(string[index], string[index - 1]);
		index--;
	}
}

void	move_right_in_input(std::string &string, unsigned long &index)
{
	if (index + 1 < string.size())
	{
		std::swap(string[index], string[index + 1]);
		index++;
	}
}

void		move_down_in_proposition(std::string &string, unsigned long &index
								, std::vector<std::string> &proposition
								, int &proposition_index)
{
	if (proposition_index > 0)
	{
		proposition_index--;
		string = proposition[proposition.size() - proposition_index - 1];
		index = string.size();
		string += '|';
	}
}

void		move_up_in_proposition(std::string &string, unsigned long &index
								, std::vector<std::string> &proposition
								, int &proposition_index)
{
	if (proposition_index < static_cast<int>(proposition.size()) - 1)
	{
		proposition_index++;
		string = proposition[proposition.size() - proposition_index - 1];
		index = string.size();
		string += '|';
	}
}

void	catch_input(SDL_Event e, std::string &string, unsigned long &index
					, SDL_bool &done, std::vector<std::string> &proposition
					, int &proposition_index, unsigned long max_size_entry)
{
	if (e.key.keysym.sym == SDLK_RETURN && string.size() >= 2)
		done = SDL_TRUE;
	else if (e.key.keysym.sym == SDLK_ESCAPE)
	{
		string = "|";
		done = SDL_TRUE;
	}
	else if ((e.key.keysym.sym >= SDLK_a && e.key.keysym.sym <= SDLK_z)
			|| (e.key.keysym.sym >= SDLK_0 && e.key.keysym.sym <= SDLK_9)
			|| (e.key.keysym.sym >= SDLK_KP_1 && e.key.keysym.sym <= SDLK_KP_0) // Take care of the define depending the OS
			|| e.key.keysym.sym == SDLK_MINUS)
		insert_typed_input(e, string, index, proposition_index, max_size_entry);
	else if (e.key.keysym.sym == SDLK_BACKSPACE)
		backspace_typed_input(string, index, proposition_index);
	else if (e.key.keysym.sym == SDLK_DELETE)
		delete_typed_input(string, index, proposition_index);
	else if (e.key.keysym.sym == SDLK_LEFT)
		move_left_in_input(string, index);
	else if (e.key.keysym.sym == SDLK_RIGHT)
		move_right_in_input(string, index);
	else if (e.key.keysym.sym == SDLK_UP)
		move_up_in_proposition(string, index, proposition, proposition_index);
	else if (e.key.keysym.sym == SDLK_DOWN)
		move_down_in_proposition(string, index, proposition, proposition_index);
}

void	insert_typed_nbr_input(SDL_Event e, std::string &string
							, unsigned long &index, int &proposition_index
							, unsigned long max_size_entry)
{
	if (string.size() < max_size_entry + 1)
	{
		string.insert(index, 1, e.key.keysym.sym);
		(index)++;
		proposition_index = 0;
	}
}

void	catch_nbr_input(SDL_Event e, std::string &string, unsigned long &index
					, SDL_bool &done, std::vector<std::string> &proposition
					, int &proposition_index, unsigned long max_size_entry)
{
	if (e.key.keysym.sym == SDLK_RETURN && string.size() >= 2)
		done = SDL_TRUE;
	else if (e.key.keysym.sym == SDLK_ESCAPE)
	{
		string = "|";
		done = SDL_TRUE;
	}
	else if ((e.key.keysym.sym >= SDLK_0 && e.key.keysym.sym <= SDLK_9)
			|| (e.key.keysym.sym >= SDLK_KP_1 && e.key.keysym.sym <= SDLK_KP_0)) //Take care of the define depending the OS
		insert_typed_nbr_input(e, string, index, proposition_index, max_size_entry);
	else if (e.key.keysym.sym == SDLK_BACKSPACE)
		backspace_typed_input(string, index, proposition_index);
	else if (e.key.keysym.sym == SDLK_DELETE)
		delete_typed_input(string, index, proposition_index);
	else if (e.key.keysym.sym == SDLK_LEFT)
		move_left_in_input(string, index);
	else if (e.key.keysym.sym == SDLK_RIGHT)
		move_right_in_input(string, index);
	else if (e.key.keysym.sym == SDLK_UP)
		move_up_in_proposition(string, index, proposition, proposition_index);
	else if (e.key.keysym.sym == SDLK_DOWN)
		move_down_in_proposition(string, index, proposition, proposition_index);
}

int	input_nbr_box(lcppgl::Context & context, const char *text
					, std::vector<std::string> &proposition
					, unsigned long max_size_entry)
{
	lcppgl::Printer	render(context);
	(void)text;
	// lcppgl::Writer	writer(context, "/Users/ldutriez/.brew/Library/Homebrew/vendor/portable-ruby/2.6.8/lib/ruby/2.6.0/rdoc/generator/template/darkfish/fonts/Lato-Regular.ttf", 20);
	std::string		result("|");
	SDL_Event		e;
	SDL_bool		done(SDL_FALSE);
	unsigned long	index(0);
	int				proposition_index(0);

	// system_get_window_size();
	while (done == SDL_FALSE)
	{
		while (SDL_PollEvent(&e) == 1)
		{
			if (e.type == SDL_KEYDOWN)
				catch_nbr_input(e, result, index, done, proposition, proposition_index, max_size_entry);
			render.put_filled_rect(lcppgl::tools::Rectangle(context.width() / 2 - 150, context.height() /2 - 50, 300, 100), lcppgl::tools::Color(10, 70, 160, 255));
			render.put_filled_rect(lcppgl::tools::Rectangle(context.width() / 2 - 140, context.height() /2, 280, 45), lcppgl::tools::Color(50, 50, 50, 255));
			// writer.put_pretty_text(text, lcppgl::tools::Rectangle(context.width() / 2 - 100, context.height() /2 - 45, 200, 50), lcppgl::tools::Color(0, 0, 0, 255));
			// writer.put_pretty_text(result, lcppgl::tools::Rectangle(context.width() / 2 - 135, context.height() /2 - 5, result.length() * 9, 50), lcppgl::tools::Color(0, 0, 0, 255));
			render.present();
		}
	}
	result.erase(result.find("|"), 1);
	render.clear();
	return atoi(result.c_str());
}