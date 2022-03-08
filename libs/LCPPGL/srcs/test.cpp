/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 19:59:07 by ldutriez          #+#    #+#             */
/*   Updated: 2022/01/12 15:38:20 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lcppgl.hpp"
#include <cmath>

void	exit_input(lcppgl::Context & context)
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				context.stop();
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
					context.stop();
				else if (event.key.keysym.sym == SDLK_F11)
					context.set_fullscreen(!context.is_fullscreen());
				break;
			default:
				break;
		}
	}
}

// Put a rectangle on the screen with random position and color.
void	random_rectangle(lcppgl::Context & context)
{
	context.set_fps_limit(5);
	lcppgl::Printer render(context);
	lcppgl::tools::Rectangle rect_one(0, 0, rand() % 100 + 50, rand() % 100 + 50);
	lcppgl::tools::Rectangle rect_two(0, 0, rand() % 100 + 50, rand() % 100 + 50);
	
	rect_one.move(rand() % (context.width() - rect_one.width()), rand() % (context.height() - rect_one.height()));
	rect_two.move(rand() % (context.width() - rect_two.width()), rand() % (context.height() - rect_two.height()));
	render.clear();
	render.set_draw_color(rand() % 255, rand() % 255, rand() % 255, 255);
	render.put_filled_rect(rect_one);
	render.set_draw_color(rand() % 255, rand() % 255, rand() % 255, 255);
	render.put_filled_rect(rect_two);
	render.set_draw_color(0, 0, 0, 255);
	render.present();
}

// Put two overlapping rectangles on the screen to test color blending.
void	overlapping_rectangles(lcppgl::Context & context)
{
	lcppgl::Printer render(context);
	// lcppgl::Writer writer(context, "/usr/share/fonts/truetype/freefont/FreeSans.ttf", 25);
	lcppgl::tools::Color red;
	lcppgl::tools::Color green;
	
	red = lcppgl::tools::Color(255, 0, 0, 120);
	green = lcppgl::tools::Color(0, 255, 0, 255);
	render.clear();
	SDL_SetRenderDrawBlendMode(context.renderer(), SDL_BLENDMODE_ADD);

	render.put_filled_rect(lcppgl::tools::Rectangle(400, 0, 400, 400),
		red);
	render.put_filled_rect(lcppgl::tools::Rectangle(400, 200, 400, 400),
		green);
	
	render.put_filled_rect(lcppgl::tools::Rectangle(0, 200, 400, 200),
		red + green);
		
	render.put_outlined_rect(lcppgl::tools::Rectangle(0, 200, 400, 200),
		lcppgl::tools::Color(255, 255, 255, 255));
	render.put_outlined_rect(lcppgl::tools::Rectangle(400, 200, 400, 200),
		lcppgl::tools::Color(255, 255, 255, 255));
		
	// writer.put_text("Actual", lcppgl::tools::Rectangle(150, 300, 100, 25),
		// lcppgl::tools::Color(0, 0, 0, 255));
	// writer.put_text("Expected", lcppgl::tools::Rectangle(550, 300, 100, 25),
		// lcppgl::tools::Color(0, 0, 0, 255));
	render.present();
}

#include <sstream> // Needed since you can't use to_string() in C++98.
// Put random text on the screen at rendom position to test text rendering.
// Put text on the screen in the three different ways.
void	text_rendering(lcppgl::Context & context)
{
	lcppgl::Printer render(context);
	// lcppgl::Writer writer(context, "/usr/share/fonts/truetype/freefont/FreeSans.ttf", 40);
	context.set_fps_limit(2);
	
	render.clear();
	// writer.put_text("Hello World!", lcppgl::tools::Rectangle(20, 50, 480, 80),
		// lcppgl::tools::Color(255, 255, 255, 255));
	// writer.put_text_and_bg("Hello World!", lcppgl::tools::Rectangle(20, 150, 480, 80),
		// lcppgl::tools::Color(255, 255, 255, 255), lcppgl::tools::Color(100, 100, 100, 255));
	// writer.put_pretty_text("Hello World!", lcppgl::tools::Rectangle(20, 250, 480, 80),
		// lcppgl::tools::Color(255, 255, 255, 255));

	std::ostringstream nb;

	nb << rand() % 100;
	// writer.put_text(nb.str(), lcppgl::tools::Rectangle(rand() % (context.width() - 40), rand() % (context.height() - 80) + 40, 40, 40),
		// lcppgl::tools::Color(rand() % 255, rand() % 255, rand() % 255, 255));
	render.present();
}

int	main(void)
{
	try
	{
		lcppgl::Context & main_context = lcppgl::Application::instance().create_context();
		main_context.add_event_functor(exit_input);
		main_context.add_render_functor(overlapping_rectangles);

		lcppgl::Application::instance().run();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return EXIT_SUCCESS;
}