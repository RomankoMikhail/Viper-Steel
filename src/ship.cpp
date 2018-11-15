#include "ship.h"

#include "js_methods.h"
#include "templates.h"

namespace game
{

void ship::move(sf::Vector2i movement)
{
	if(m_acted == false)
	{
		movement.x = clamp(movement.x, -1, 1);
		movement.y = clamp(movement.y, -1, 1);
		m_position += movement;
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
}

void ship::update()
{

}

ship::~ship()
{
	duk_destroy_heap(m_ctx);
}

} /* namespace game */


