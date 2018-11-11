#ifndef GRIDDRAWER_H_
#define GRIDDRAWER_H_

#include <SFML/Graphics.hpp>

namespace Game
{

class GridDrawer: public sf::Drawable, public sf::Transformable, sf::NonCopyable
{
	const sf::Texture& mTexture;
	const sf::Vector2u mSize;

	sf::VertexArray mVertices;

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
			override;
public:
	explicit GridDrawer(const sf::Texture& texture, const sf::Vector2u size);
};

} /* namespace Game */

#endif /* GRIDDRAWER_H_ */
