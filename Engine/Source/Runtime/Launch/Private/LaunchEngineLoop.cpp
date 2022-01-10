//
// Created by chenyifei on 2021/12/29.
//
#include <iostream>

#include "LaunchEngineLoop.h"
#include "Engine/GameEngine.h"

extern std::shared_ptr<Engine> GEngine;

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
    std::cout << "EngineLoop::Init" << std::endl;

    GEngine = std::make_shared<GameEngine>();

    {
        std::cout << "GEngine->Init" << std::endl;
        GEngine->Init(this);
    }

    {
        std::cout << "GEngine->Start" << std::endl;
        GEngine->Start();
    }
    return 0;
}

void EngineLoop::InitTime() {

}

void EngineLoop::Exit() {
    if (GEngine != nullptr) {
        GEngine->PreExit();
    }
}

void EngineLoop::Tick() {

}

