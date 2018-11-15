#ifndef GLOBAL_OBJECTS_H_
#define GLOBAL_OBJECTS_H_

#include <map>

#include "ship.h"
#include <memory>

extern std::map<unsigned, std::shared_ptr<game::ship>> ships;


#endif /* GLOBAL_OBJECTS_H_ */
