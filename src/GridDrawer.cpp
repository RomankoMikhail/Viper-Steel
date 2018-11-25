#include "GridDrawer.h"

#include <plog/Log.h>


namespace Game {
GridDrawer::GridDrawer(const sf::Texture& texture, const sf::Vector2u size) :
		m_texture(texture), m_size(size) {
	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(size.x * size.y * 4);

	for (unsigned int x = 0; x < size.x; ++x) {
		for (unsigned int y = 0; y < size.y; ++y) {

			// get a pointer to the current tile's quad
			sf::Vertex* quad = &m_vertices[(x + y * size.x) * 4];

			// define its 4 corners
			quad[0].position = sf::Vector2f(x * m_texture.getSize().x, y * m_texture.getSize().y);
			quad[1].position = sf::Vector2f((x + 1) * m_texture.getSize().x, y * m_texture.getSize().y);
			quad[2].position = sf::Vector2f((x + 1) * m_texture.getSize().x, (y + 1) * m_texture.getSize().y);
			quad[3].position = sf::Vector2f(x * m_texture.getSize().x, (y + 1) * m_texture.getSize().y);

			// define its 4 texture coordinates
			quad[0].texCoords = sf::Vector2f(0, 0);
			quad[1].texCoords = sf::Vector2f(m_texture.getSize().x, 0);
			quad[2].texCoords = sf::Vector2f(m_texture.getSize());
			quad[3].texCoords = sf::Vector2f(0, m_texture.getSize().y);
		}
	}
	LOGD << m_texture.getSize().x << " " << m_texture.getSize().y;
}

void GridDrawer::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	states.transform *= getTransform();
	states.texture = &m_texture;
	target.draw(m_vertices, states);
}

} /* namespace Game */
