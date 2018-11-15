#ifndef SHIP_H_
#define SHIP_H_

#include <SFML/System.hpp>
#include <duktape.h>

namespace game
{

class ship
{
	duk_context* m_ctx = NULL;
	bool m_acted = false;
	sf::Vector2i m_position;
public:
	void move(sf::Vector2i movement);
	void set_position(sf::Vector2i position);
	sf::Vector2i get_position();

	void set_acted();
	void reset_acted();

	void update();

	ship() = default;
	ship(const unsigned& id);
	~ship();
};

} /* namespace game */

#endif /* SHIP_H_ */
