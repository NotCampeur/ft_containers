/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rectangle.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 17:56:23 by ldutriez          #+#    #+#             */
/*   Updated: 2021/11/25 20:24:42 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Rectangle.hpp"

lcppgl::tools::Rectangle::Rectangle(int x, int y, int width, int height)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;
}

lcppgl::tools::Rectangle::Rectangle(Rectangle const &src)
{
	*this = src;
}

lcppgl::tools::Rectangle::~Rectangle()
{}

lcppgl::tools::Rectangle &
lcppgl::tools::Rectangle::operator=(Rectangle const &rhs)
{
	if (this != &rhs)
	{
		_x = rhs._x;
		_y = rhs._y;
		_width = rhs._width;
		_height = rhs._height;
	}
	return (*this);
}

int
lcppgl::tools::Rectangle::x(void) const
{
	return (_x);
}

int
lcppgl::tools::Rectangle::y(void) const
{
	return (_y);
}

int
lcppgl::tools::Rectangle::width(void) const
{
	return (_width);
}

int
lcppgl::tools::Rectangle::height(void) const
{
	return (_height);
}

void
lcppgl::tools::Rectangle::set_x(int x)
{
	_x = x;
}

void
lcppgl::tools::Rectangle::set_y(int y)
{
	_y = y;
}

void
lcppgl::tools::Rectangle::set_width(int width)
{
	_width = width;
}

void
lcppgl::tools::Rectangle::set_height(int height)
{
	_height = height;
}

bool
lcppgl::tools::Rectangle::contains(int x, int y) const
{
	return (x >= _x && y >= _y && x < _x + _width && y < _y + _height);
}

bool
lcppgl::tools::Rectangle::contains(Rectangle const &rhs) const
{
	return (contains(rhs.x(), rhs.y()) && contains(rhs.x() + rhs.width(), rhs.y() + rhs.height()));
}

bool
lcppgl::tools::Rectangle::intersect(Rectangle const &rhs) const
{
	return (contains(rhs.x(), rhs.y()) || contains(rhs.x() + rhs.width(), rhs.y() + rhs.height())
		|| rhs.contains(x(), y()) || rhs.contains(x() + width(), y() + height()));
}

void
lcppgl::tools::Rectangle::move(int x, int y)
{
	_x += x;
	_y += y;
}

void
lcppgl::tools::Rectangle::move(Rectangle const &rhs)
{
	move(rhs.x(), rhs.y());
}

void
lcppgl::tools::Rectangle::resize(int width, int height)
{
	_width = width;
	_height = height;
}

void
lcppgl::tools::Rectangle::resize(Rectangle const &rhs)
{
	resize(rhs.width(), rhs.height());
}

void
lcppgl::tools::Rectangle::expand(int width, int height)
{
	_x -= width;
	_y -= height;
	_width += width * 2;
	_height += height * 2;
}

void
lcppgl::tools::Rectangle::expand(Rectangle const &rhs)
{
	expand(rhs.width(), rhs.height());
}

void
lcppgl::tools::Rectangle::shrink(int width, int height)
{
	_x += width;
	_y += height;
	_width -= width * 2;
	_height -= height * 2;
}

void
lcppgl::tools::Rectangle::shrink(Rectangle const &rhs)
{
	shrink(rhs.width(), rhs.height());
}

void
lcppgl::tools::Rectangle::reset(int x, int y, int width, int height)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;
}

void
lcppgl::tools::Rectangle::reset(Rectangle const &rhs)
{
	reset(rhs.x(), rhs.y(), rhs.width(), rhs.height());
}

void
lcppgl::tools::Rectangle::reset(void)
{
	reset(0, 0, 0, 0);
}

void
lcppgl::tools::Rectangle::print(void) const
{
	std::cout << "Rectangle(" << _x << ", " << _y << ", " << _width << ", " << _height << ")";
}