// PLOG library
#include <plog/Log.h>
#include <plog/Appenders/ConsoleAppender.h>

// Standard C++ Library
#include <iostream>


int main()
{
	// Initialize logging library for both text and console logging
	static plog::ConsoleAppender<plog::TxtFormatter> consoleAppender;
	plog::init(plog::debug, "log.txt").addAppender(&consoleAppender);

	// Main code begins here
	LOG_INFO << "Application started";

	LOG_INFO << "Application shuting down";
	return 0;
}
