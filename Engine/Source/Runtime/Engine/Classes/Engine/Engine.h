#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <memory>

#include "World.h"

struct WorldContext
{
public:
    std::shared_ptr<World> CurrentWorld;
};

#endif //  _ENGINE_H_