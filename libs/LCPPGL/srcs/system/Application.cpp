/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Application.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 20:48:15 by ldutriez          #+#    #+#             */
/*   Updated: 2021/11/23 10:04:35 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Application.hpp"

lcppgl::Application::Application(void) : lcppgl::Singleton()
, _context(), _is_running(false)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		throw std::invalid_argument(SDL_GetError());
	// if (TTF_Init() == -1)
		// throw std::invalid_argument(TTF_GetError());
	// if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0)
		// throw std::invalid_argument(IMG_GetError());
}

lcppgl::Application::~Application(void)
{
	for (size_t i = 0; i < _context.size(); i++)
		delete _context[i];
	_context.clear();
	// TTF_Quit();
	// IMG_Quit();
	SDL_Quit();
}

lcppgl::Application &
lcppgl::Application::instance(void)
{
	static Application instance;
	return instance;
}
lcppgl::Context &
lcppgl::Application::create_context(const char *title, int width, int height)
{
	_context.push_back(new lcppgl::Context(_context.size(), title, width, height));
	return *_context.back();
}

lcppgl::Context &
lcppgl::Application::context(size_t index) const
{
	return *_context.at(index);
}

void
lcppgl::Application::destroy_context(size_t index)
{
	for (size_t i = index + 1; i < _context.size(); i++)
		_context[i]->set_id(_context[i]->id() - 1);
	delete _context.at(index);
	_context.erase(_context.begin() + index);
	if (_context.empty() == true)
		_is_running = false;
}

void
lcppgl::Application::destroy_context(lcppgl::Context & context)
{
	unsigned char index = context.id();
	for (size_t i = index + 1; i < _context.size(); i++)
		_context[i]->set_id(_context[i]->id() - 1);
	delete _context.at(index);
	_context.erase(_context.begin() + index);
	if (_context.empty() == true)
		_is_running = false;
}

void
lcppgl::Application::run(void)
{
	_is_running = true;
	while (_is_running == true)
	{
		for (size_t i = 0; i < _context.size(); i++)
		{
			_context[i]->update();
		}
		for (size_t i = 0; i < _context.size(); i++)
		{
			if (_context[i]->is_running() == false)
			{
				destroy_context(*_context[i]);
				i--;
			}
		}
	}
}

void
lcppgl::Application::stop(void)
{
	_is_running = false;
}

void
lcppgl::Application::quit(void)
{
	this->~Application();
}