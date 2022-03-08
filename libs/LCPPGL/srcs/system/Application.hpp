/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Application.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 20:48:23 by ldutriez          #+#    #+#             */
/*   Updated: 2021/11/13 20:45:56 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LCPPGL_APPLICATION_HPP
# define LCPPGL_APPLICATION_HPP

# include "lcppgl.hpp"
# include "Singleton.hpp"
# include "Context.hpp"
# include <vector>

// TODO : The application should be able to handle multiple windows
// TODO : The application should be able to handle multiple contexts
// TODO : The renderer should be a class.


namespace lcppgl
{
	class Context;
	// This class is a singleton used to create a window and manage it.
	// The application is created by the first call to the get_instance() method.
	// The application is automatically destroyed. (The method quit() is deprecated)
	class Application : public lcppgl::Singleton
	{
		private:
			std::vector<lcppgl::Context *>	_context;
			
			// Tell if the application is running
			bool			_is_running;
			
			Application(void);
			
		public:
			~Application(void);
			
			static Application &	instance(void);

			lcppgl::Context &	create_context(const char *title = "LCppGL", int width = 800, int height = 600);
			lcppgl::Context &	context(size_t index = 0) const;
			void				destroy_context(size_t index);
			void				destroy_context(lcppgl::Context & context);

			void	run(void);
			void	stop(void);

			__attribute__ ((deprecated)) void	quit(void);
	};
}

#endif