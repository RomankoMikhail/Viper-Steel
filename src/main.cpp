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

#include "GridDrawer.h"
#include "Templates.h"
#include "Application.h"

#include "Script.h"

#include "GlobalObjects.h"

static duk_ret_t native_log(duk_context* ctx)
{
	if (duk_get_global_literal(ctx, DUK_HIDDEN_SYMBOL("ID")) == false)
	{
		duk_pop(ctx);
		LOG_ERROR << "Script with no ID called";
		throw std::runtime_error("Script with no ID called");
	}
	unsigned id = duk_to_int(ctx, 1);
	duk_pop(ctx);

	LOG_DEBUG << "(id:" << id << "):" << duk_to_string(ctx, 0);

	return 0;
}

int main(int argc, char* argv[])
{

	char* ptr = nullptr;

	static plog::ConsoleAppender<plog::TxtFormatter> consoleAppender;
	plog::init(plog::debug, "log.txt").addAppender(&consoleAppender);

	Game::Script myScript;
	myScript.bindFunction(native_log, "print", 1);
	myScript.setProperty("ID", "1");
	LOG_INFO << myScript.getProperty("ID");
	myScript.loadSrc("print('program code'); function updater() {print('updater function');}");
	//myScript.call("updater");

	double d1 = 0.1 + 0.2;
	double d2 = 0.3;

	if(d1 != d2) {
		LOG_WARNING << "d1 != d2";
		LOG_WARNING << d1;
		LOG_WARNING << d2;
	}
	LOG_WARNING << approx(d1, d2, 1);
	return 0;

	LOG_DEBUG << ptr;
	ptr = NULL;
	LOG_DEBUG << ptr;

	textures["debug_16"].loadFromFile("images/debug_16.png");
	textures["debug_32"].loadFromFile("images/debug_32.png");
	textures["debug_64"].loadFromFile("images/debug_64.png");
	textures["debug_128"].loadFromFile("images/debug_128.png");

	return 0;
}
