#ifndef _WORLD_H_
#define _WORLD_H_
#include <vector>
#include <memory>

#include "Level.h"
#include "GameFramework/WorldSettings.h"
#include "Engine/EngineTypes.h"

class UWorld
{
public:
    std::shared_ptr<WorldSettings> GetWorldSetting();

public:
    /** 目前世界中的所有关卡 */
    std::vector<std::shared_ptr<Level>> Levels;

public:
    static std::shared_ptr<UWorld> CreateWorld(const EWorldType::Type& InWorldType);

public:
    void SetGameInstance(const std::shared_ptr<class UGameInstance>& NewGI);

    void CleanupWorld(UWorld* NewWorld = nullptr);

    void ClearWorldComponents();
public:
    EWorldType::Type WorldType;

private:
    /** 主关卡，表示一开始就加载进来的关卡 */
    std::shared_ptr<Level> PersistentLevel;

    /** Game 模式下指向 PersistentLevel， Editor 模式下可能指向不同的关卡 */
    std::shared_ptr<Level> CurrentLevel;

    std::shared_ptr<class UGameInstance> OwningGameInstance;
};

#endif //  _WORLD_H_