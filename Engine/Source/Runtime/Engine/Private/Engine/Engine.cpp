#include "Engine/Engine.h"

#include <iostream>

void WorldContext::SetWorld(const std::shared_ptr<World> &InWorld)
{
    CurrentWorld = InWorld;
}

void Engine::WorldAdded(const std::shared_ptr<struct World> &InWorld) {
    std::cout << "New World Added" << std::endl;
}
