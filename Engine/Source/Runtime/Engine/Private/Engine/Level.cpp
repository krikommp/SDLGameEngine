#include "Engine/Level.h"

std::shared_ptr<WorldSettings> Level::GetWorldSettings() const
{
    return WorldSettings;
}