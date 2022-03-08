/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Writer.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 17:14:24 by ldutriez          #+#    #+#             */
/*   Updated: 2021/12/07 14:33:59 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Writer.hpp"

lcppgl::Writer::Writer(lcppgl::Context & context, const std::string &path,
	 int size)
: _context(context), _font(NULL)
, _font_path(path), _font_size(size)
{
	_font = TTF_OpenFont(path.c_str(), size);
	if (_font == NULL)
		throw std::runtime_error(std::string("TTF_OpenFont: ") + TTF_GetError());
}

lcppgl::Writer::Writer(const Writer &other)
: _context(other._context)
{
	*this = other;
}

lcppgl::Writer::~Writer()
{
	if (_font != NULL)
		TTF_CloseFont(_font);
}

lcppgl::Writer &
lcppgl::Writer::operator=(const Writer &other)
{
	if (this != &other)
	{
		_context = other._context;
		if (_font != NULL)
			TTF_CloseFont(_font);
		_font = TTF_OpenFont(other._font_path.c_str(), other._font_size);
		if (_font == NULL)
			throw std::runtime_error(std::string("TTF_OpenFont: ") + TTF_GetError());
		_font_path = other._font_path;
		_font_size = other._font_size;
	}
	return (*this);
}

void
lcppgl::Writer::put_text(const std::string &text, const tools::Rectangle &rect, const tools::Color &color)
{
	tools::Texture		texture(_context, TTF_RenderUTF8_Solid(_font, text.c_str(), color), true);	

	texture.render(NULL, &rect);
}
void
lcppgl::Writer::put_text_and_bg(const std::string &text, const tools::Rectangle &rect,
					const tools::Color &color, const tools::Color &bg_color)
{
	tools::Texture		texture(_context, TTF_RenderUTF8_Shaded(_font, text.c_str(), color, bg_color), true);	

	texture.render(NULL, &rect);
}

void
lcppgl::Writer::put_pretty_text(const std::string &text, const tools::Rectangle &rect,
					const tools::Color &color)
{
	tools::Texture		texture(_context, TTF_RenderUTF8_Blended(_font, text.c_str(), color), true);	

	texture.render(NULL, &rect);
}

void
lcppgl::Writer::change_font(const std::string &path, int size)
{
	if (_font != NULL)
		TTF_CloseFont(_font);
	_font = TTF_OpenFont(path.c_str(), size);
	if (_font == NULL)
		throw std::runtime_error(std::string("TTF_OpenFont: ") + TTF_GetError());
	_font_path = path;
	_font_size = size;
}