#include <fstream>
#include <sstream>
#include "Script.h"

/*!
 * \brief Duktape callback function for execution termination by timeout
 *
 * \param udata pointer to user data
 * \return 1 if duktape script execution needs to be terminated, 0 otherwise
 */
int duk_exec_timeout(void* udata)
{
	Game::Scripting::ScriptData* data = static_cast<Game::Scripting::ScriptData*>(udata);

	if (data != nullptr && data->terminate)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

static void scriptFatalHandler(void *udata, const char *msg)
{
	LOG_ERROR << msg;
}

namespace Game
{
namespace Scripting
{
Script::Script()
{
	// Allocating duktape heap
	m_ctx = duk_create_heap(nullptr, nullptr, nullptr, &m_data, scriptFatalHandler);
}

void Script::requestTermination()
{
	m_data.terminate = true;
}

void Script::loadFile(std::string path)
{
	std::ifstream in(path);
	std::ostringstream content;
	content << in.rdbuf();
	in.close();
	loadSrc(content.str());
}

void Script::loadSrc(std::string src)
{
	duk_push_string(m_ctx, src.c_str());
	if (duk_peval(m_ctx) != 0)
	{
		std::string errorMsg("Compilation error");
		errorMsg += duk_safe_to_string(m_ctx, -1);

		LOG_ERROR << errorMsg;
		throw std::runtime_error(errorMsg);
	}
	duk_pop(m_ctx);
}

void Script::bindFunction(duk_c_function callback, std::string name, int args)
{
	duk_push_c_function(m_ctx, callback, args);
	duk_put_global_string(m_ctx, name.c_str());
}

void Script::call(std::string func)
{
	duk_get_global_string(m_ctx, func.c_str());
	duk_pcall(m_ctx, 0);
}

void Script::setProperty(std::string key, std::string value)
{
	setProperty(m_ctx, key, value);
}

std::string Script::getProperty(std::string key)
{
	return getProperty(m_ctx, key);
}

void Script::setProperty(duk_context* ctx, std::string key, std::string value)
{
	duk_push_string(ctx, value.c_str());
	duk_put_global_string(ctx, ("\xFF" + key).c_str());
}

std::string Script::getProperty(duk_context* ctx, std::string key)
{
	duk_get_global_string(ctx, ("\xFF" + key).c_str());
	std::string value(duk_safe_to_string(ctx, 0));
	duk_pop(ctx);
	return value;
}

Script::~Script()
{
	duk_destroy_heap(m_ctx);
}

}
} /* namespace Game */

