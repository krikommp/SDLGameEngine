//
// Created by chenyifei on 2022/1/14.
//

#include "GameTimer.h"

void GameTimer::Tick() {
    TimePoint2 = std::chrono::system_clock::now();
    ElapsedTime = TimePoint2 - TimePoint1;
    TimePoint1 = TimePoint2;
    fElapsedTime = ElapsedTime.count();
}

