#include "Engine/World.h"
#include "Engine/GameEngine.h"

#include <iostream>

extern std::shared_ptr<Engine> GEngine;

std::shared_ptr<WorldSettings> UWorld::GetWorldSetting()
{
    if (PersistentLevel)
    {
        return PersistentLevel->GetWorldSettings();
    }
    return nullptr;
}

std::unique_ptr<UWorld> UWorld::CreateWorld(const EWorldType::Type& InWorldType) {
    auto NewWorld = std::make_unique<UWorld>();
    NewWorld->WorldType = InWorldType;
    if (GEngine != nullptr) {
        GEngine->WorldAdded(*NewWorld);
    }

    return NewWorld;
}

void UWorld::SetGameInstance(const std::shared_ptr<UGameInstance>& NewGI) {
    OwningGameInstance = NewGI;
}

void UWorld::CleanupWorld(UWorld *NewWorld) {
    const bool bWorldChanged = NewWorld != this;
    ClearWorldComponents();
}

void UWorld::ClearWorldComponents() {
    using SizeType = std::vector<std::shared_ptr<Level>>::size_type;
    for ( SizeType i = 0; i < Levels.size(); ++i ) {
        auto Level = Levels[i];
        Level->ClearLevelComponents();
    }
}

UWorld::~UWorld() {
    
}
