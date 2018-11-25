#include "JSMethods.h"

#include <string>

#include "Application.h"
#include "GlobalObjects.h"

[[deprecated]]
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

[[deprecated]]
static duk_ret_t native_err(duk_context* ctx)
{
	return duk_error(ctx, DUK_ERR_RANGE_ERROR, "argument out of range:");
}

[[deprecated]]
static duk_ret_t native_sleep(duk_context* ctx)
{
	sf::sleep(sf::milliseconds(duk_to_int(ctx, 0)));
	return 0;
}

[[deprecated]]
static duk_ret_t move_ship(duk_context* ctx)
{
	if (duk_get_global_literal(ctx, DUK_HIDDEN_SYMBOL("ID")) == false)
	{
		duk_pop(ctx);
		LOG_ERROR << "Non-ID ES called";
		throw std::runtime_error("Non-ID ES called");
	}
	unsigned id = duk_to_int(ctx, 2);
	duk_pop(ctx);

	if (ships.find(id) == ships.end())
	{
		LOG_ERROR << "Ship object deleted, but script still running?";
		throw std::runtime_error("Ship object deleted, but script still running?");
	}

	sf::Vector2i mov;
	mov.x = duk_to_int(ctx, 0);
	mov.y = duk_to_int(ctx, 1);

	LOG_INFO << mov.x << ":" << mov.y;
	ships[id]->move(mov);

	return 0;
}

[[deprecated]]
void JSSetupContext(duk_context* ctx, const unsigned& id)
{
	duk_push_global_object(ctx);
	duk_push_string(ctx, std::to_string(id).c_str());
	duk_put_global_literal(ctx, DUK_HIDDEN_SYMBOL("ID"));

	duk_push_c_function(ctx, native_log, 1);
	duk_put_global_string(ctx, "log");

	duk_push_c_function(ctx, native_sleep, 1);
	duk_put_global_string(ctx, "sleep");

	duk_push_c_function(ctx, native_err, 0);
	duk_put_global_string(ctx, "err");

	duk_push_c_function(ctx, move_ship, 2);
	duk_put_global_string(ctx, "move");
}
