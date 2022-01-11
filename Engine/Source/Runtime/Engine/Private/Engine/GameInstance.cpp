//
// Created by chenyifei on 2022/1/10.
//

#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "Engine/GameEngine.h"

#include "GameMapsSetting.h"

#include <cassert>
#include <iostream>

extern std::shared_ptr<Engine> GEngine;

void UGameInstance::InitializeStandalone() {
    assert(GEngine != nullptr && "GEngine is nullptr");
    WorldContext = GEngine->CreateNewWorldContext(EWorldType::Game);
    WorldContext->OwningGameInstance = shared_from_this();
    std::shared_ptr<World> DummyWorld = World::CreateWorld(EWorldType::Type::Game);
    DummyWorld->SetGameInstance(shared_from_this());
    WorldContext->SetCurrentWorld(DummyWorld);

    Init();
}

void UGameInstance::Init() {

}

void UGameInstance::StartGameInstance() {
    const std::unique_ptr<GameMapsSettings> GameMapSettings = std::make_unique<GameMapsSettings>();
    const std::string DefaultMap = GameMapSettings->GetGameDefaultMap();

}
