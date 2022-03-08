/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Color.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 20:47:37 by ldutriez          #+#    #+#             */
/*   Updated: 2021/12/04 19:55:54 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LCPPGL_COLOR_HPP
# define LCPPGL_COLOR_HPP

# include "lcppgl.hpp"

namespace lcppgl
{
	namespace tools
	{
		class Color
		{
			private:
				Uint8	_r;
				Uint8	_g;
				Uint8	_b;
				Uint8	_a;

			public:
				Color(void);
				Color(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a);
				Color(const Color & color);
				~Color(void);

				Color	& operator=(const Color & color);
				bool	operator==(const Color & color);
				bool	operator!=(const Color & color);
				operator SDL_Color() const
				{
					SDL_Color	color;

					color.r = this->_r;
					color.g = this->_g;
					color.b = this->_b;
					color.a = this->_a;
					return (color);
				}

				Uint8	r(void) const;
				Uint8	g(void) const;
				Uint8	b(void) const;
				Uint8	a(void) const;

				void	set_r(const Uint8 r);
				void	set_g(const Uint8 g);
				void	set_b(const Uint8 b);
				void	set_a(const Uint8 a);
		};
		Color	operator+(const Color & color_a, const Color & color_b);
		Color	operator-(const Color & color_a, const Color & color_b);
	}
}

#endif