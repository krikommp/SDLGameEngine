//
// Created by chenyifei on 2022/1/14.
//

#ifndef SDLGAMEENGINE_GAMECONTROLLER_H
#define SDLGAMEENGINE_GAMECONTROLLER_H

#include "SoftWarePCH.h"
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

struct ButtonState {
    bool bPressed = false;
    bool bReleased = false;
    bool bHold = false;
};

class GameController : public ITickEngine {
public:
    void Tick() override;

public:
    FORCEINLINE const FVector2i& GetMousePosition() const { return MousePosition; }

    FORCEINLINE const ButtonState& GetMouse(MouseType Type) const { return MouseButton[static_cast<int>(Type)]; }

private:
    FORCEINLINE void ClearMouseState();

    FORCEINLINE void SetButtonState(int State, ButtonState& Button);
private:
    FVector2i MousePosition;
    ButtonState MouseButton[3];

    uint32 OldButton;
};

extern Listener<void(IInputEvent*)> GInputObserver;


#endif //SDLGAMEENGINE_GAMECONTROLLER_H
