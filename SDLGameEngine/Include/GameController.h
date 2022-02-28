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

enum class KeyCode {
    UNKNOWN = 0,
    RETURN = '\r',
    ESCAPE = '\x1B',
    BACKSPACE = '\b',
    TAB = '\t',
    SPACE = ' ',
    EXCLAIM = '!',
    QUOTEDBL = '"',
    HASH = '#',
    PERCENT = '%',
    DOLLAR = '$',
    AMPERSAND = '&',
    QUOTE = '\'',
    LEFTPAREN = '(',
    RIGHTPAREN = ')',
    ASTERISK = '*',
    PLUS = '+',
    COMMA = ',',
    MINUS = '-',
    PERIOD = '.',
    SLASH = '/',
    Alpha0 = '0',
    Alpha1 = '1',
    Alpha2 = '2',
    Alpha3 = '3',
    Alpha4 = '4',
    Alpha5 = '5',
    Alpha6 = '6',
    Alpha7 = '7',
    Alpha8 = '8',
    Alpha9 = '9',
    COLON = ':',
    SEMICOLON = ';',
    LESS = '<',
    EQUALS = '=',
    GREATER = '>',
    QUESTION = '?',
    AT = '@',
    LEFTBRACKET = '[',
    BACKSLASH = '\\',
    RIGHTBRACKET = ']',
    CARET = '^',
    UNDERSCORE = '_',
    BACKQUOTE = '`',
    A = 'a',
    B = 'b',
    C = 'c',
    D = 'd',
    E = 'e',
    F = 'f',
    G = 'g',
    H = 'h',
    I = 'i',
    J = 'j',
    K = 'k',
    L = 'l',
    M = 'm',
    N = 'n',
    O = 'o',
    P = 'p',
    Q = 'q',
    R = 'r',
    S = 's',
    T = 't',
    U = 'u',
    V = 'v',
    W = 'w',
    X = 'x',
    Y = 'y',
    Z = 'z',
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

    FORCEINLINE const ButtonState& GetKeyButton(KeyCode Key) const { return KeyBroad[static_cast<int>(Key)]; }

private:
    void ClearMouseState();

    FORCEINLINE void SetButtonState(int State, ButtonState& Button);
private:
    FVector2i MousePosition;
    ButtonState MouseButton[3];
    ButtonState KeyBroad[127];

    uint32 OldButton = 0;
};

extern Listener<void(IInputEvent*)> GInputObserver;


#endif //SDLGAMEENGINE_GAMECONTROLLER_H
