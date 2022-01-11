#include "Engine/World.h"
#include "Engine/GameEngine.h"

extern std::shared_ptr<Engine> GEngine;

std::shared_ptr<WorldSettings> World::GetWorldSetting()
{
    if (PersistentLevel)
    {
        return PersistentLevel->GetWorldSettings();
    }
    return nullptr;
}

std::shared_ptr<World> World::CreateWorld(const WorldType::Type& InWorldType) {
    auto NewWorld = std::make_shared<World>();
    // NewWorld->WorldType = InWorldType;
    if (GEngine != nullptr) {
        GEngine->WorldAdded(NewWorld);
    }

    return NewWorld;
}

void World::SetGameInstance(const std::shared_ptr<UGameInstance>& NewGI) {
    OwningGameInstance = NewGI;
}
