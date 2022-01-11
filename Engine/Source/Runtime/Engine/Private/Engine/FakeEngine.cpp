#include "FakeEngine.h"
#include "Engine/Engine.h"
#include "Engine/World.h"

#include <iostream>

std::shared_ptr<Engine> GEngine = nullptr;


void FWorldContext::SetCurrentWorld(std::unique_ptr<UWorld>&&InWorld)
{
    CurrentWorld = std::move(InWorld);
}

void Engine::WorldAdded(const UWorld &InWorld) {
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

    // 卸载当前世界
    if (WorldContext.GetWorld()) {
        // 分离玩家控制器
        auto GameInstance = WorldContext.OwningGameInstance.lock();
        if (GameInstance) {
            // TODO 遍历玩家 执行清除操作
        }

        // 在销毁 Pawn 和 PlayerControllers 之后进行 防止新的东西产生（例如 掉落物）
        WorldContext.GetWorld()->CleanupWorld();

        WorldContext.SetCurrentWorld(nullptr);
    }

    std::unique_ptr<UWorld> NewWorld = nullptr;

    // 加载一个 map
    // 从 内存 硬盘
    if (NewWorld == nullptr) {
        NewWorld = std::move(UWorld::CreateWorld(EWorldType::Type::Game));
    }
    auto GameInstance = WorldContext.OwningGameInstance.lock();
    if (GameInstance)
        NewWorld->SetGameInstance(GameInstance);

    WorldContext.SetCurrentWorld(std::forward<decltype(NewWorld)>(NewWorld));
    WorldContext.GetWorld()->WorldType = WorldContext.ThisWorldType;

    WorldContext.GetWorld()->SetGameMode();

    WorldContext.GetWorld()->BeginPlay();
    return false;
}

EBrowseReturnVal::Type Engine::Browse(FWorldContext &WorldContext) {
    LoadMap(WorldContext);
    return EBrowseReturnVal::Success;
}
