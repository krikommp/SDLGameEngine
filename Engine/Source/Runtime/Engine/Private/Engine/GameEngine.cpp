//
// Created by chenyifei on 2022/1/10.
//
#include "FakeEngine.h"
#include "Engine/GameEngine.h"
#include "Engine/GameInstance.h"

#include <iostream>
#include <memory>

void GameEngine::Init(IEngineLoop *InEngineLoop) {
    std::cout << "GameEngine Init" << std::endl;
    GameInstance = std::make_shared<UGameInstance>();

    // 产生一个 GameInstance
    // 包含 WorldContext
    GameInstance->InitializeStandalone();
}

void GameEngine::Start() {
    std::cout << "Start Game." << std::endl;

    // 具体流程是打开地图 加载世界 加载Actor 调用 begin play
    GameInstance->StartGameInstance();
}

void GameEngine::Tick(float DeltaSeconds) {
    
}

void GameEngine::PreExit() {

}
