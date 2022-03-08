/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Singleton.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 20:51:07 by ldutriez          #+#    #+#             */
/*   Updated: 2021/11/13 17:47:01 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LCPPGL_SINGLETON_HPP
# define LCPPGL_SINGLETON_HPP

namespace lcppgl
{
	// The Singleton class is a template class that implements the Singleton design
	class Singleton
	{
		public:
			static Singleton &instance()
			{
				static Singleton instance;
				return instance;
			}
			~Singleton() {}
			Singleton(Singleton const &src)
			{
				*this = src;
			}
			Singleton &operator=(Singleton const &rhs)
			{
				if (this != &rhs)
					;
				return *this;
			}

		protected:
			Singleton() {}
	};
}

#endif