//
// Created by chenyifei on 2022/1/14.
//

#ifndef SDLGAMEENGINE_GAMETIMER_H
#define SDLGAMEENGINE_GAMETIMER_H

#include "SoftWarePCH.h"
#include "TickEngine.h"

class GameTimer : public ITickEngine {
public:
     GameTimer() : TimePoint1(std::chrono::system_clock::now()), TimePoint2(std::chrono::system_clock::now()) {}

public:
    void Tick() override;

    float GetFPS() const { return 1.0f / fElapsedTime; }

public:
    float fElapsedTime;
private:
    std::chrono::system_clock::time_point TimePoint1;
    std::chrono::system_clock::time_point TimePoint2;

    std::chrono::duration<float> ElapsedTime;
};

#endif //SDLGAMEENGINE_GAMETIMER_H
