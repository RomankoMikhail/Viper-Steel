#include "GridDrawer.h"
#include <plog/Log.h>

namespace Game {
GridDrawer::GridDrawer(const sf::Texture& texture, const sf::Vector2u size) :
		mTexture(texture), mSize(size) {
	mVertices.setPrimitiveType(sf::Quads);
	mVertices.resize(size.x * size.y * 4);

	for (unsigned int x = 0; x < size.x; ++x) {
		for (unsigned int y = 0; y < size.y; ++y) {

			// get a pointer to the current tile's quad
			sf::Vertex* quad = &mVertices[(x + y * size.x) * 4];

			// define its 4 corners
			quad[0].position = sf::Vector2f(x * mTexture.getSize().x, y * mTexture.getSize().y);
			quad[1].position = sf::Vector2f((x + 1) * mTexture.getSize().x, y * mTexture.getSize().y);
			quad[2].position = sf::Vector2f((x + 1) * mTexture.getSize().x, (y + 1) * mTexture.getSize().y);
			quad[3].position = sf::Vector2f(x * mTexture.getSize().x, (y + 1) * mTexture.getSize().y);

			// define its 4 texture coordinates
			quad[0].texCoords = sf::Vector2f(0, 0);
			quad[1].texCoords = sf::Vector2f(mTexture.getSize().x, 0);
			quad[2].texCoords = sf::Vector2f(mTexture.getSize());
			quad[3].texCoords = sf::Vector2f(0, mTexture.getSize().y);
		}
	}
	LOGD << mTexture.getSize().x << " " << mTexture.getSize().y;
}

void GridDrawer::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	states.transform *= getTransform();
	states.texture = &mTexture;
	target.draw(mVertices, states);
}
} /* namespace Game */
