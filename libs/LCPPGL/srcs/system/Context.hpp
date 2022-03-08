/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Context.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 18:22:08 by ldutriez          #+#    #+#             */
/*   Updated: 2021/11/13 18:29:30 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LCPPGL_CONTEXT_HPP
# define LCPPGL_CONTEXT_HPP

# include "lcppgl.hpp"
# include <vector>

namespace lcppgl
{
	// This class is used to manage the SDL context (window, renderer, etc.)
	class Context
	{
		private:
			SDL_Window		*_window;
			SDL_Renderer	*_renderer;

			unsigned char 	_id;

			bool			_is_running;

			unsigned int	_fps_limit;
			// Functor to call in the event_manager
			std::vector<void (*)(lcppgl::Context &)>	_event_functors;

			// Functor to call in the render_manager
			std::vector<void (*)(lcppgl::Context &)>	_render_functors;

			void	event_manager(void);
			void	render_manager(void);

		public:
			Context(unsigned char id, const char * title, int width, int height);
			Context(const Context &src);
			~Context(void);

			SDL_Window		*window(void) const;
			SDL_Renderer	*renderer(void) const;

			int		width(void) const;
			int		height(void) const;

			unsigned char	id(void) const;
			bool			is_running(void) const;
			
			std::string	title(void) const;

			bool	is_fullscreen(void) const;
			bool	is_resizable(void) const;
			bool	is_borderless(void) const;

			void	set_id(const unsigned char id);

			void	set_title(const std::string & title);
			void	set_size(const int width, const int height);
			void	set_fullscreen(const bool fullscreen);
			void	set_resizable(const bool resizable);
			void	set_borderless(const bool borderless);

			// If the fps is set to 0 the fps are not limited.
			void	set_fps_limit(const unsigned int fps);

			void	update(void);
			void	stop(void);

			// Return the index of the function in the functor.
			int		add_event_functor(void (*functor)(lcppgl::Context &));
			void	remove_event_functor(int index);
			// Return the index of the function in the functor.
			int		add_render_functor(void (*functor)(lcppgl::Context &));
			void	remove_render_functor(int index);

			Context				&operator=(const Context &rhs);
	};
}

#endif