//
// Created by chenyifei on 2022/1/14.
//

#include "GameController.h"

Listener<void(void)> GAppObserver;

void GameController::Tick() {
    SDL_Event Event;
    while (SDL_PollEvent(&Event)) {
        switch (Event.type) {
            case SDL_KEYDOWN:
                if (Event.key.keysym.sym == SDLK_SPACE) {
                    GAppObserver.NotifyAll();
                }
                break;
            case SDL_QUIT:
                GAppObserver.NotifyAll();
                break;
        }
    }
}