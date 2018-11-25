#include "Ship.h"

#include <plog/Log.h>

#include "Math.h"

namespace Game
{

void Ship::move(sf::Vector2i movement)
{
	if (m_acted == false)
	{
		movement.x = Math::clamp(movement.x, -1, 1);
		movement.y = Math::clamp(movement.y, -1, 1);
		m_position += movement;
		m_sprite.setPosition(m_position.x * 32.0f, m_position.y * 32.0f);
		setActed();
	}
}

void Ship::setPosition(sf::Vector2i position)
{
	m_position = position;
}

sf::Vector2i Ship::getPosition()
{
	return m_position;
}

void Ship::setActed()
{
	m_acted = true;
}

void Ship::resetActed()
{
	m_acted = false;
}

Ship::Ship(const unsigned& id)
{
	m_ctx = duk_create_heap_default();
	//JSSetupContext(m_ctx, id);
	duk_peval_string(m_ctx, "function update() {x = Math.floor(Math.random() * 3) - 1; y = Math.floor(Math.random() * 3) - 1;move(x,y);while(1);}");

	//m_sprite.setTexture(textures["debug_32"]);
}

void Ship::update()
{
	duk_get_global_string(m_ctx, "update");
	duk_pcall(m_ctx, 0);

	duk_pop(m_ctx);
}

Ship::~Ship()
{
	duk_destroy_heap(m_ctx);
}

void Ship::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	target.draw(m_sprite);
}


} /* namespace game */
