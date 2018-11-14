#include "ship.h"
#include "jsmethods.h"
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

	setup_js_context(m_ctx, id);
}

ship::~ship()
{
}

} /* namespace game */


