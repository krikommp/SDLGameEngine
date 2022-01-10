//
// Created by chenyifei on 2022/1/10.
//

#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "Engine/GameEngine.h"

#include <cassert>

extern std::shared_ptr<Engine> GEngine;

void UGameInstance::InitializeStandalone() {
    assert(GEngine != nullptr && "GEngine is nullptr");
    WorldContext = GEngine->CreateNewWorldContext(WorldType::Game);
    WorldContext->OwningGameInstance = this;
    std::shared_ptr<World> DummyWorld = World::CreateWorld(WorldType::Type::Game);
    DummyWorld->SetGameInstance(this);
    WorldContext->SetCurrentWorld(DummyWorld);

    Init();
}

void UGameInstance::Init() {

}

void UGameInstance::StartGameInstance() {

}
