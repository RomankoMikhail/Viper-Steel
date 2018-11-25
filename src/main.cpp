#include <plog/Log.h>
#ifdef _WIN32
#define _fileno(F) ((F)->_file)
#endif
#include <plog/Appenders/ConsoleAppender.h>

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <duktape.h>
#include <array>

#include "Application.h"

int main(int argc, char* argv[])
{
	static plog::ConsoleAppender<plog::TxtFormatter> consoleAppender;
	plog::init(plog::debug, "log.txt").addAppender(&consoleAppender);

	Game::Core::Application app(argc, argv);
	app.run();

	return 0;
}
