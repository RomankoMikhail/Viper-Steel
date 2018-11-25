#ifndef GLOBALOBJECTS_H_
#define GLOBALOBJECTS_H_

#include <map>

#include <memory>
#include <SFML/Graphics.hpp>
#include "Ship.h"

extern std::map<unsigned, std::shared_ptr<Game::Ship>> ships;
extern std::map<std::string, sf::Texture> textures;

#endif /* GLOBALOBJECTS_H_ */
