/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Texture.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:13:39 by ldutriez          #+#    #+#             */
/*   Updated: 2021/12/07 14:34:20 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Texture.hpp"

lcppgl::tools::Texture::Texture(Context & context, SDL_Surface *surface, bool free_surface)
: _context(context), _texture(NULL)
{
	if(surface == NULL)
		throw std::runtime_error("Can not create texture from NULL surface");
	_texture = SDL_CreateTextureFromSurface(_context.renderer(), surface);
	if (_texture == NULL)
		throw std::runtime_error(std::string("Can not create texture from surface: ") + SDL_GetError());
	if (free_surface == true)
		SDL_FreeSurface(surface);
}

lcppgl::tools::Texture::~Texture(void)
{
	if (_texture)
		SDL_DestroyTexture(_texture);
}

void
lcppgl::tools::Texture::render(const Rectangle *src, const Rectangle *dst)
{
	if (SDL_RenderCopy(_context.renderer(), _texture, (const SDL_Rect *)src, (const SDL_Rect *)dst) == -1)
		throw std::runtime_error(std::string("SDL_RenderCopy: ") + SDL_GetError());
}
