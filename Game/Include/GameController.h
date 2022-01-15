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

enum class MouseType
{
	MOUSE_LEFT = 0,
    MOUSE_MIDDLE = 1,
    MOUSE_RIGHT = 2
};

class GameController : public ITickEngine {
public:
    void Tick() override;

public:
    bool GetMouseButtonDown(MouseType Type) const { return MouseButtonDown[static_cast<int>(Type)]; }

private:
    uint32 MouseButtonDown[3] = { 0 };
};

extern Listener<void(IInputEvent*)> GInputObserver;


#endif //SDLGAMEENGINE_GAMECONTROLLER_H
