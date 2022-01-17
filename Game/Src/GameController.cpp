//
// Created by chenyifei on 2022/1/14.
//

#include "GameController.h"

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
	            }
                break;
			case SDL_MOUSEBUTTONDOWN:
				{
                    if (Button & SDL_BUTTON_LMASK) {
                        MouseButton[0].bPressed = true;
                        MouseButton[0].bHold = true;
                        MouseButton[0].bReleased = false;
                    }
                    if (Button & SDL_BUTTON_MMASK) {
                        MouseButton[1].bPressed = true;
                        MouseButton[1].bHold = true;
                        MouseButton[1].bReleased = false;
                    }
                    if (Button & SDL_BUTTON_RMASK) {
                        MouseButton[2].bPressed = true;
                        MouseButton[2].bHold = true;
                        MouseButton[2].bReleased = false;
                    }
				}
				break;
            case SDL_MOUSEBUTTONUP:
                {
                    if ((OldButton ^ Button) & SDL_BUTTON_LMASK) {
                        MouseButton[0].bPressed = false;
                        MouseButton[0].bHold = false;
                        MouseButton[0].bReleased = true;
                    }
                    if ((OldButton ^ Button) & SDL_BUTTON_MMASK) {
                        MouseButton[1].bPressed = false;
                        MouseButton[1].bHold = false;
                        MouseButton[1].bReleased = true;
                    }
                    if ((OldButton ^ Button) & SDL_BUTTON_RMASK) {
                        MouseButton[2].bPressed = false;
                        MouseButton[2].bHold = false;
                        MouseButton[2].bReleased = true;
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