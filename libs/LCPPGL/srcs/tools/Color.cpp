/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Color.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 20:58:02 by ldutriez          #+#    #+#             */
/*   Updated: 2021/12/05 20:35:18 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Color.hpp"

lcppgl::tools::Color::Color(void)
{
	_r = 0;
	_g = 0;
	_b = 0;
	_a = 0;
}

lcppgl::tools::Color::Color(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a)
: _r(r), _g(g), _b(b), _a(a)
{}

lcppgl::tools::Color::Color(const Color & color)
{
	*this = color;
}

lcppgl::tools::Color::~Color(void)
{}

lcppgl::tools::Color	&
lcppgl::tools::Color::operator=(const Color & color)
{
	if (this != &color)
	{
		_r = color._r;
		_g = color._g;
		_b = color._b;
		_a = color._a;
	}
	return (*this);
}

lcppgl::tools::Color
lcppgl::tools::operator+(const Color & color_a, const Color & color_b)
{
	// RGB = srcRGB * SDL_BLENDFACTOR_SRC_ALPHA + dstRGB * SDL_BLENDFACTOR_ONE
	// A = srcA * SDL_BLENDFACTOR_ZERO + dstA * SDL_BLENDFACTOR_ONE
	// lcppgl::tools::Color	result(color_b.r() * SDL_BLENDFACTOR_SRC_ALPHA + color_a.r() * SDL_BLENDFACTOR_ONE,
	// 			  color_b.g() * SDL_BLENDFACTOR_SRC_ALPHA + color_a.g() * SDL_BLENDFACTOR_ONE,
	// 			  color_b.b() * SDL_BLENDFACTOR_SRC_ALPHA + color_a.b() * SDL_BLENDFACTOR_ONE,
	// 			  color_b.a() * SDL_BLENDFACTOR_ZERO + color_a.a() * SDL_BLENDFACTOR_ONE);
	float	base_alpha = color_b.a() / 255.0f;
	float	inv_alpha = color_a.a() / 255.0f;
	// float   inv_alpha = 1.0f - base_alpha;
	tools::Color	result(static_cast<Uint8>(color_b.r() * base_alpha + color_a.r() * inv_alpha),
				  static_cast<Uint8>(color_b.g() * base_alpha + color_a.g() * inv_alpha),
				  static_cast<Uint8>(color_b.b() * base_alpha + color_a.b() * inv_alpha),
				  color_b.a());
	
	return result;
}

lcppgl::tools::Color
lcppgl::tools::operator-(const Color & color_a, const Color & color_b)
{
	// lcppgl::tools::Color	result(color_b.r() * SDL_BLENDFACTOR_SRC_ALPHA - color_a.r() * SDL_BLENDFACTOR_ONE,
	// 			  color_b.g() * SDL_BLENDFACTOR_SRC_ALPHA - color_a.g() * SDL_BLENDFACTOR_ONE,
	// 			  color_b.b() * SDL_BLENDFACTOR_SRC_ALPHA - color_a.b() * SDL_BLENDFACTOR_ONE,
	// 			  color_b.a() * SDL_BLENDFACTOR_ZERO - color_a.a() * SDL_BLENDFACTOR_ONE);
	float	base_alpha = color_b.a() / 255.0f;
	float   inv_alpha = 1.0f - base_alpha;
	tools::Color	result(static_cast<Uint8>(color_b.r() * base_alpha - color_a.r() * inv_alpha),
				  static_cast<Uint8>(color_b.g() * base_alpha - color_a.g() * inv_alpha),
				  static_cast<Uint8>(color_b.b() * base_alpha - color_a.b() * inv_alpha),
				  color_b.a());
	return result;
}

bool
lcppgl::tools::Color::operator==(const Color & color)
{
	return (_r == color._r && _g == color._g && _b == color._b && _a == color._a);
}

bool
lcppgl::tools::Color::operator!=(const Color & color)
{
	return !(*this == color);
}

Uint8
lcppgl::tools::Color::r(void) const
{
	return (_r);
}

Uint8
lcppgl::tools::Color::g(void) const
{
	return (_g);
}

Uint8
lcppgl::tools::Color::b(void) const
{
	return (_b);
}

Uint8
lcppgl::tools::Color::a(void) const
{
	return (_a);
}

void
lcppgl::tools::Color::set_r(const Uint8 r)
{
	_r = r;
}

void
lcppgl::tools::Color::set_g(const Uint8 g)
{
	_g = g;
}

void
lcppgl::tools::Color::set_b(const Uint8 b)
{
	_b = b;
}

void
lcppgl::tools::Color::set_a(const Uint8 a)
{
	_a = a;
}