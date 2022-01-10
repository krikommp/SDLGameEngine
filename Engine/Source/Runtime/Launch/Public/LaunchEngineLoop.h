//
// Created by chenyifei on 2021/12/29.
//

#ifndef SDLGAMEENGINE_LAUNCHENGINELOOP_H
#define SDLGAMEENGINE_LAUNCHENGINELOOP_H

#include "FakeEngine.h"

class EngineLoop : IEngineLoop {
public:
    EngineLoop();
    virtual ~EngineLoop();

public:
    int PreInit();

    int PreInitPreStartupScreen();

    int PreInitPostStartupScreen();

public:
    /**
     * 游戏循环的开始
     * @return
     */
    virtual int Init() override;

    void InitTime();

    void Exit();

    virtual void Tick() override;
};

#endif //SDLGAMEENGINE_LAUNCHENGINELOOP_H
