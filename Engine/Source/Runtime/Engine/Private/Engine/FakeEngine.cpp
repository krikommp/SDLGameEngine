#include "FakeEngine.h"
#include "Engine/Engine.h"


#include <iostream>

std::shared_ptr<Engine> GEngine = nullptr;


void WorldContext::SetCurrentWorld(const std::shared_ptr<World> &InWorld)
{
    CurrentWorld = InWorld;
}

void Engine::WorldAdded(const std::shared_ptr<class World> &InWorld) {
    std::cout << "New World Added" << std::endl;
}

std::shared_ptr<WorldContext> Engine::CreateNewWorldContext(const EWorldType::Type &WorldType) {
    std::shared_ptr<WorldContext> NewWorldContext = std::make_shared<WorldContext>();
    WorldList.push_back(NewWorldContext);
    NewWorldContext->ThisWorldType = WorldType;
    NewWorldContext->ContextHandle = "Context_1";
    return NewWorldContext;
}
