//
// Created by chenyifei on 2021/12/29.
//

#include "LaunchEngineLoop.h"

EngineLoop::EngineLoop() {

}

EngineLoop::~EngineLoop() {
}

int EngineLoop::PreInit() {
    const int rv1 = PreInitPreStartupScreen();
    if (rv1 != 0) {
        return rv1;
    }
    const int rv2 = PreInitPostStartupScreen();
    if (rv2 != 0) {
        return rv2;
    }
    return 0;
}

int EngineLoop::PreInitPreStartupScreen() {
    return 0;
}

int EngineLoop::PreInitPostStartupScreen() {
    return 0;
}


int EngineLoop::Init() {
    return 0;
}

void EngineLoop::InitTime() {

}

void EngineLoop::Exit() {

}

void EngineLoop::Tick() {

}
