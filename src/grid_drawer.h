#ifndef GRID_DRAWER_H_
#define GRID_DRAWER_H_

#include <SFML/Graphics.hpp>

namespace game
{

class grid_drawer: public sf::Drawable, public sf::Transformable, sf::NonCopyable
{
	const sf::Texture& m_texture;
	sf::VertexArray m_vertices;
	const sf::Vector2u m_size;

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
			override;
public:
	/*!
	 * game::grid_drawer constructor
	 * @param texture grid texture
	 * @param size grid size
	 */
	explicit grid_drawer(const sf::Texture& texture, const sf::Vector2u size);
};
/*!
 * \class game::grid_drawer
 * \ingroup graphics
 *
 * game::grid_drawer is a class, that draws grid of images on
 * the screen.
 *
 */


} /* namespace game */

#endif /* GRID_DRAWER_H_ */
