#include "Engine/World.h"
#include "Engine/GameEngine.h"

extern std::shared_ptr<Engine> GEngine;

std::shared_ptr<WorldSettings> UWorld::GetWorldSetting()
{
    if (PersistentLevel)
    {
        return PersistentLevel->GetWorldSettings();
    }
    return nullptr;
}

std::shared_ptr<UWorld> UWorld::CreateWorld(const EWorldType::Type& InWorldType) {
    auto NewWorld = std::make_shared<UWorld>();
    // NewWorld->WorldType = InWorldType;
    if (GEngine != nullptr) {
        GEngine->WorldAdded(NewWorld);
    }

    return NewWorld;
}

void UWorld::SetGameInstance(const std::shared_ptr<UGameInstance>& NewGI) {
    OwningGameInstance = NewGI;
}
