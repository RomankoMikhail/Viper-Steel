// PLOG library
#include <plog/Log.h>

#ifdef _WIN32
#define _fileno(F) ((F)->_file)
#endif
#include <plog/Appenders/ConsoleAppender.h>

// Standard C++ library
#include <iostream>

// SFML library
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <duktape.h>
#include <array>

#include "grid_drawer.h"
#include "templates.h"
#include "application.h"
#include "thread.h"
#include "thread_pool.h"

#include "global_objects.h"

class testA
{
public:
	void call()
	{
		LOG_INFO << "Call";
	}
};

int main(int argc, char* argv[])
{
	static plog::ConsoleAppender<plog::TxtFormatter> consoleAppender;
	plog::init(plog::debug, "log.txt").addAppender(&consoleAppender);

	game::thread_ptr app_thread(new game::thread([&argc, &argv](){game::application app(argc, argv);app.run();}));

	textures["debug_16"].loadFromFile("images/debug_16.png");
	textures["debug_32"].loadFromFile("images/debug_32.png");
	textures["debug_64"].loadFromFile("images/debug_64.png");
	textures["debug_128"].loadFromFile("images/debug_128.png");

	thread_pool_add(app_thread);
	while(thread_pool_process())
	{
		sf::sleep(sf::milliseconds(10));
	}

	return 0;
}
