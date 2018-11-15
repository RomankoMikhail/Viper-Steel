#include "ship.h"

#include "js_methods.h"
#include "templates.h"
#include "thread.h"
#include "thread_pool.h"
#include "global_objects.h"

#include <plog/Log.h>

namespace game
{

void ship::move(sf::Vector2i movement)
{
	if (m_acted == false)
	{
		movement.x = clamp(movement.x, -1, 1);
		movement.y = clamp(movement.y, -1, 1);
		m_position += movement;
		m_sprite.setPosition(m_position.x * 32.0f, m_position.y * 32.0f);
		set_acted();
	}
}

void ship::set_position(sf::Vector2i position)
{
	m_position = position;
}

sf::Vector2i ship::get_position()
{
	return m_position;
}

void ship::set_acted()
{
	m_acted = true;
}

void ship::reset_acted()
{
	m_acted = false;
}

ship::ship(const unsigned& id)
{
	m_ctx = duk_create_heap_default();
	js_setup_context(m_ctx, id);
	duk_peval_string(m_ctx, "function update() {x = Math.floor(Math.random() * 3) - 1; y = Math.floor(Math.random() * 3) - 1;move(x,y);while(1);log();}");

	m_sprite.setTexture(textures["debug_32"]);
}

void ship::update()
{
	duk_get_global_string(m_ctx, "update");
	duk_pcall(m_ctx, 0);
	duk_pop(m_ctx);
}

ship::~ship()
{
	duk_destroy_heap(m_ctx);
}

void ship::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	target.draw(m_sprite);
}


} /* namespace game */
