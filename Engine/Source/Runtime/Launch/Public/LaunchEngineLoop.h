//
// Created by chenyifei on 2021/12/29.
//

#ifndef SDLGAMEENGINE_LAUNCHENGINELOOP_H
#define SDLGAMEENGINE_LAUNCHENGINELOOP_H

#include "Engine/FakeEngine.h"

class EngineLoop : IEngineLoop {
public:
    EngineLoop();
    virtual ~EngineLoop();

public:
    int PreInit();

    int PreInitPreStartupScreen();

    int PreInitPostStartupScreen();

public:
    virtual int Init() override;

    void InitTime();

    void Exit();

    virtual void Tick() override;
};

#endif //SDLGAMEENGINE_LAUNCHENGINELOOP_H
