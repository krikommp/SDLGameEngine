#include "Engine/World.h"

std::shared_ptr<WorldSettings> World::GetWorldSetting()
{
    if (PersistentLevel)
    {
        return PersistentLevel->GetWorldSettings();
    }
    return nullptr;
}