//
// Created by chenyifei on 2022/1/14.
//

#ifndef SDLGAMEENGINE_GAMECONTROLLER_H
#define SDLGAMEENGINE_GAMECONTROLLER_H

#include "SortWarePCH.h"
#include "TickEngine.h"

class GameController : public ITickEngine {
public:
    void Tick() override;
};

#endif //SDLGAMEENGINE_GAMECONTROLLER_H