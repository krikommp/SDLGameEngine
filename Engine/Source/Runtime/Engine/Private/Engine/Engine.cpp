#include "Engine/Engine.h"

void WorldContext::SetWorld(const std::shared_ptr<World> &InWorld)
{
    CurrentWorld = InWorld;
}