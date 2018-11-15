#ifndef GLOBAL_OBJECTS_H_
#define GLOBAL_OBJECTS_H_

#include <map>

#include "ship.h"
#include <memory>
#include <SFML/Graphics.hpp>

extern std::map<unsigned, std::shared_ptr<game::ship>> ships;
extern std::map<std::string, sf::Texture> textures;

#endif /* GLOBAL_OBJECTS_H_ */
