#include "Engine/Level.h"

#include <iostream>

std::shared_ptr<WorldSettings> Level::GetWorldSettings() const
{
    return WorldSettings;
}

void Level::ClearLevelComponents() {
    std::cout << "ClearLevelComponents" << std::endl;
}
