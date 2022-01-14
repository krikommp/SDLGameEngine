//
// Created by chenyifei on 2022/1/14.
//

#ifndef SDLGAMEENGINE_GAMECONTROLLER_H
#define SDLGAMEENGINE_GAMECONTROLLER_H

#include "SortWarePCH.h"
#include "TickEngine.h"

class GameController : public ITickEngine {
public:
    void Tick() override {
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
};

#endif //SDLGAMEENGINE_GAMECONTROLLER_H
