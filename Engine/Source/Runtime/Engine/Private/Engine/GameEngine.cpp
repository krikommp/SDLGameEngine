//
// Created by chenyifei on 2022/1/10.
//
#include "FakeEngine.h"
#include "Engine/GameEngine.h"
#include "Engine/GameInstance.h"

#include <iostream>

void GameEngine::Init(IEngineLoop *InEngineLoop) {
    std::cout << "GameEngine Init" << std::endl;
    GameInstance = std::make_shared<UGameInstance>();

    GameInstance->InitializeStandalone();
}

void GameEngine::Start() {

}

void GameEngine::Tick(float DeltaSeconds) {

}

void GameEngine::PreExit() {

}
