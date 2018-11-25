#ifndef SHIP_H_
#define SHIP_H_

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <duktape.h>

namespace Game
{

class Ship: public sf::Drawable
{
	duk_context* m_ctx = NULL;
	bool m_acted = false;
	sf::Vector2i m_position;

	sf::Sprite m_sprite;
protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
	void move(sf::Vector2i movement);
	void setPosition(sf::Vector2i position);
	sf::Vector2i getPosition();

	void setActed();
	void resetActed();

	void update();

	Ship(const unsigned& id);
	~Ship();
};

} /* namespace game */

#endif /* SHIP_H_ */
