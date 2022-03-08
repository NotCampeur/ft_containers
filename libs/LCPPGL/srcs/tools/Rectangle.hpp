/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rectangle.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 17:51:32 by ldutriez          #+#    #+#             */
/*   Updated: 2021/12/05 20:26:57 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LCPPGL_RECTANGLE_HPP
# define LCPPGL_RECTANGLE_HPP

# include "lcppgl.hpp"

namespace lcppgl
{
	namespace tools
	{
		class Rectangle
		{
			private:
				int	_x;
				int	_y;
				int	_width;
				int	_height;

			public:
				Rectangle(int x = 0, int y = 0, int width = 0, int height = 0);
				Rectangle(Rectangle const & src);
				~Rectangle(void);

				Rectangle &	operator=(Rectangle const & rhs);

				operator SDL_Rect() const
				{
					SDL_Rect rect;

					rect.x = this->_x;
					rect.y = this->_y;
					rect.w = this->_width;
					rect.h = this->_height;

					return (rect);
				}

				int					x(void) const;
				int					y(void) const;
				int					width(void) const;
				int					height(void) const;

				void				set_x(int x);
				void				set_y(int y);
				void				set_width(int width);
				void				set_height(int height);

				bool				contains(int x, int y) const;
				bool				contains(Rectangle const & rhs) const;
				bool				intersect(Rectangle const &rhs) const;
				void				move(int x, int y);
				void				move(Rectangle const &rhs);
				void				resize(int width, int height);
				void				resize(Rectangle const &rhs);
				void				expand(int width, int height);
				void				expand(Rectangle const &rhs);
				void				shrink(int width, int height);
				void				shrink(Rectangle const &rhs);
				void				reset(int x, int y, int width, int height);
				void				reset(Rectangle const &rhs);
				void				reset(void);

				void				print(void) const;
		};
	}
}


#endif