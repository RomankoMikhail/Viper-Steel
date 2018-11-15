#ifndef SHIP_H_
#define SHIP_H_

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <duktape.h>

namespace game
{

class ship: public sf::Drawable
{
	duk_context* m_ctx = NULL;
	bool m_acted = false;
	sf::Vector2i m_position;

	sf::Sprite m_sprite;
protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
	void move(sf::Vector2i movement);
	void set_position(sf::Vector2i position);
	sf::Vector2i get_position();

	void set_acted();
	void reset_acted();

	void update();

	ship(const unsigned& id);
	~ship();
};

} /* namespace game */

#endif /* SHIP_H_ */
