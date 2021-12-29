#ifndef _GAMEENGINE_H_
#define _GAMEENGINE_H_
#include <memory>

#include "Engine.h"
#include "GameInstance.h"

class GameEngine : public Engine
{
public:
    std::shared_ptr<GameInstance> GameInstance;
};

#endif //  _GAMEENGINE_H_