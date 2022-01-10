//
// Created by chenyifei on 2022/1/10.
//

#include "Engine/GameInstance.h"
#include "Engine/World.h"

void UGameInstance::InitializeStandalone() {
    auto DummyWorld = World::CreateWorld(WorldType::Type::Game);
}
