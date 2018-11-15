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

#include "grid_drawer.h"
#include "templates.h"
#include "application.h"

#include <duktape.h>

#include "thread.h"

#include <array>

#include "thread_pool.h"

int main(int argc, char* argv[])
{
	// Initialize logging library for both text and console logging
	static plog::ConsoleAppender<plog::TxtFormatter> consoleAppender;
	plog::init(plog::debug, "log.txt").addAppender(&consoleAppender);

	std::shared_ptr<game::thread> task1(new game::thread([]()
	{
		LOG_WARNING << "Hello from thread #1";
		std::shared_ptr<game::thread> task2(new game::thread([]()
		{
			LOG_WARNING << "Hello from thread #2";
			for(int t = 0; t < 10; t++)
			{

				sf::sleep(sf::milliseconds(100));
			}
			LOG_WARNING << "Bye from thread #2";
		}));

		thread_pool_add(task2);

		for(int i = 0; i < 10; i++)
		{

			sf::sleep(sf::milliseconds(500));

		}

		std::shared_ptr<game::thread> task3(new game::thread([]()
		{
			LOG_WARNING << "Hello from thread #3";
			for(int t = 0; t < 10; t++)
			{
				sf::sleep(sf::milliseconds(100));
			}
			LOG_WARNING << "Bye from thread #3";
		}));
		thread_pool_add(task3);
		LOG_WARNING << "Bye from thread #1";
	}));

	thread_pool_add(task1, sf::seconds(10));

	while (thread_pool_process())
	{
		sf::sleep(sf::milliseconds(10));
	}

	//game::application app(argc, argv);
	//app.run();

	return 0;
}
