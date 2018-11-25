#ifndef GRIDDRAWER_H_
#define GRIDDRAWER_H_

#include <SFML/Graphics.hpp>

namespace Game
{
/*!
 * \deprecated
 */
class [[deprecated]] GridDrawer: public sf::Drawable, public sf::Transformable, sf::NonCopyable
{
	const sf::Texture& m_texture;
	sf::VertexArray m_vertices;
	const sf::Vector2u m_size;

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
			override;
public:
	explicit GridDrawer(const sf::Texture& texture, const sf::Vector2u size);
};


} /* namespace game */

#endif /* GRIDDRAWER_H_ */
