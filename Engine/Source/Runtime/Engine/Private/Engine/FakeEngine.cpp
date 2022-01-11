#include "FakeEngine.h"
#include "Engine/Engine.h"


#include <iostream>

std::shared_ptr<Engine> GEngine = nullptr;


void FWorldContext::SetCurrentWorld(const std::shared_ptr<UWorld> &InWorld)
{
    CurrentWorld = InWorld;
}

void Engine::WorldAdded(const std::shared_ptr<class UWorld> &InWorld) {
    std::cout << "New World Added" << std::endl;
}

std::shared_ptr<FWorldContext> Engine::CreateNewWorldContext(const EWorldType::Type &WorldType) {
    std::shared_ptr<FWorldContext> NewWorldContext = std::make_shared<FWorldContext>();
    WorldList.push_back(NewWorldContext);
    NewWorldContext->ThisWorldType = WorldType;
    NewWorldContext->ContextHandle = "Context_1";
    return NewWorldContext;
}

bool Engine::LoadMap(FWorldContext &WorldContext) {
    std::cout << "Load Map" << std::endl;

    if (WorldContext.GetWorld()) {
        WorldContext.GetWorld()->CleanupWorld();
    }
    return false;
}

EBrowseReturnVal::Type Engine::Browse(FWorldContext &WorldContext) {
    LoadMap(WorldContext);
    return EBrowseReturnVal::Success;
}
