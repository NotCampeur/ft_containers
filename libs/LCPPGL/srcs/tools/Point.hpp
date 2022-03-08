/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 03:25:28 by ldutriez          #+#    #+#             */
/*   Updated: 2022/02/06 03:35:00 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LCPPGL_POINT_HPP
# define LCPPGL_POINT_HPP

namespace lcppgl
{
	namespace tools
	{
		class Point
		{
			public:
				int		x;
				int		y;

				Point(void) {};
				Point(const int new_x, const int new_y) : x(new_x), y(new_y) {};
				Point(const Point & point) : x(point.x), y(point.y) {};
				~Point(void) {};

				Point	& operator=(const Point & point)
				{
					if (this != &point)
					{
						x = point.x;
						y = point.y;
					}
					return (*this);
				}
				Point	& operator+=(const Point & point)
				{
					x += point.x;
					y += point.y;
					return (*this);
				}
				Point	& operator-=(const Point & point)
				{
					x -= point.x;
					y -= point.y;
					return (*this);
				}
				Point	& operator*=(const Point & point)
				{
					x *= point.x;
					y *= point.y;
					return (*this);
				}
				Point	& operator/=(const Point & point)
				{
					x /= point.x;
					y /= point.y;
					return (*this);
				}

				Point	& operator+=(const int n)
				{
					x += n;
					y += n;
					return (*this);
				}
				Point	& operator-=(const int n)
				{
					x -= n;
					y -= n;
					return (*this);
				}
				Point	& operator*=(const int n)
				{
					x *= n;
					y *= n;
					return (*this);
				}
				Point	& operator/=(const int n)
				{
					x /= n;
					y /= n;
					return (*this);
				}

				Point	& operator++(void)
				{
					x++;
					y++;
					return (*this);
				}
				Point	& operator--(void)
				{
					x--;
					y--;
					return (*this);
				}

				Point	operator+(const Point & point) const
				{
					return (Point(*this) += point);
				}
				Point	operator-(const Point & point) const
				{
					return (Point(*this) -= point);
				}
				Point	operator*(const Point & point) const
				{
					return (Point(*this) *= point);
				}
				Point	operator/(const Point & point) const
				{
					return (Point(*this) /= point);
				}

				Point	operator+(const int n) const
				{
					return (Point(*this) += n);
				}
				Point	operator-(const int n) const
				{
					return (Point(*this) -= n);
				}
				Point	operator*(const int n) const
				{
					return (Point(*this) *= n);
				}
				Point	operator/(const int n) const
				{
					return (Point(*this) /= n);
				}

				bool	operator==(const Point & point) const
				{
					return (x == point.x && y == point.y);
				}
				bool	operator!=(const Point & point) const
				{
					return (!(*this == point));
				}
		};
		
	}
}

#endif