//
// Created by chenyifei on 2022/1/14.
//

#include "GameController.h"

Listener<void(IInputEvent*)> GInputObserver;

void GameController::Tick() {
    SDL_Event Event;
    while (SDL_PollEvent(&Event)) {
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
	                int X, Y;
					uint32 Button = SDL_GetMouseState(&X, &Y);
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
    }
}