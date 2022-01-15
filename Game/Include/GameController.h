//
// Created by chenyifei on 2022/1/14.
//

#ifndef SDLGAMEENGINE_GAMECONTROLLER_H
#define SDLGAMEENGINE_GAMECONTROLLER_H

#include "SortWarePCH.h"
#include "TickEngine.h"
#include "GraphicMath.h"

class IInputEvent
{
public:
    IInputEvent(const char* InName) : Name(InName) {}

    virtual ~IInputEvent() {}
public:
    const char* Name;
};

class AppExitEvent : public IInputEvent
{
public:
    AppExitEvent() : IInputEvent("AppExit") {}
};

extern Listener<void(IInputEvent*)> GInputObserver;

class GameController : public ITickEngine {
public:
    void Tick() override;
};

#endif //SDLGAMEENGINE_GAMECONTROLLER_H
