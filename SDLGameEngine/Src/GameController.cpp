//
// Created by chenyifei on 2022/1/14.
//

#include "GameController.h"
#include <iostream>

Listener<void(IInputEvent*)> GInputObserver;

void GameController::Tick() {
    ClearMouseState();
    SDL_Event Event;
    while (SDL_PollEvent(&Event)) {
        int X, Y;
        // left     0001
        // mid      0010
        // right    0100
        uint32 Button = SDL_GetMouseState(&X, &Y);
        MousePosition = FVector2i(X, Y);
        switch (Event.type) {
            case SDL_KEYDOWN:
	            {
	                if (Event.key.keysym.sym == SDLK_SPACE) {
						AppExitEvent Event;
						GInputObserver.NotifyAll(&Event);
	                }
                    if (Event.key.keysym.sym == SDLK_ESCAPE) {
                        AppExitEvent Event;
                        GInputObserver.NotifyAll(&Event);
                    }
                    uint32 key = Event.key.keysym.sym;
                    if (KeyBroad[key].bHold) SetButtonState(2, KeyBroad[key]);
                    else SetButtonState(1, KeyBroad[key]);
	            }
                break;
            case SDL_KEYUP:
                {
                    uint32 key = Event.key.keysym.sym;
                    SetButtonState(0, KeyBroad[key]);
                }
                break;
			case SDL_MOUSEBUTTONDOWN:
				{
                    if (Button & SDL_BUTTON_LMASK) {
                        SetButtonState(1, MouseButton[0]);
                    }
                    if (Button & SDL_BUTTON_MMASK) {
                        SetButtonState(1, MouseButton[1]);
                    }
                    if (Button & SDL_BUTTON_RMASK) {
                        SetButtonState(1, MouseButton[2]);
                    }
				}
				break;
            case SDL_MOUSEBUTTONUP:
                {
                    if ((OldButton ^ Button) & SDL_BUTTON_LMASK) {
                        SetButtonState(0, MouseButton[0]);
                    }
                    if ((OldButton ^ Button) & SDL_BUTTON_MMASK) {
                        SetButtonState(0, MouseButton[1]);
                    }
                    if ((OldButton ^ Button) & SDL_BUTTON_RMASK) {
                        SetButtonState(0, MouseButton[2]);
                    }
                }
                break;
            case SDL_QUIT:
	            {
					AppExitEvent Event;
					GInputObserver.NotifyAll(&Event);
	            }
                break;
            default:
                break;
        }
        OldButton = Button;
    }
}

void GameController::ClearMouseState() {
    for (auto & Index : MouseButton) {
        Index.bReleased = false;
        Index.bPressed = false;
    }
}

void GameController::SetButtonState(int State, ButtonState &Button) {
    switch (State) {
        case 0:
            Button.bPressed = false;
            Button.bReleased = true;
            Button.bHold = false;
            break;
        case 1:
            Button.bPressed = true;
            Button.bReleased = false;
            Button.bHold = true;
            break;
        case 2:
            Button.bPressed = false;
            Button.bReleased = false;
            Button.bHold = true;
            break;
        default:
            break;
    }
}
