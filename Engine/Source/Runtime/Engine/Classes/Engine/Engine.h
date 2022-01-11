#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <vector>
#include <memory>
#include <string>

#include "World.h"
#include "EngineTypes.h"
#include "World.h"

/**
 * @brief 当需要切换不同世界的时候
 * 需要传递这个类型
 * 对于独立运行的游戏（无编辑器），只存在一个 WorldContext
 * 
 */
struct FWorldContext
{
public:
    void SetCurrentWorld(std::unique_ptr<UWorld>&& InWorld);

    inline const std::unique_ptr<UWorld>& GetWorld() const { return CurrentWorld; }

public:
    std::unique_ptr<UWorld> CurrentWorld;

    /** 指向拥有的 GameInstance */
    std::weak_ptr<class UGameInstance> OwningGameInstance;

    /** 当前世界类型 */
    EWorldType::Type ThisWorldType;

    std::string ContextHandle;
};

/**
 * @brief 所有引擎对象的父类
 * 一些引擎默认需要的类会在这里
 * 
 */
class IEngineLoop;

class Engine
{

public:
    /** 初始化 */
    virtual void Init(IEngineLoop* InEngineLoop) = 0;

    /** 与初始化不同的逻辑，可以进行游戏开始前的初始化操作 */
    virtual void Start() = 0;

    /** 更新 */
    virtual void Tick(float DeltaSeconds) = 0;

    /** 被 Shutdown 调用，执行退出前的逻辑 */
    virtual void PreExit() = 0;

    virtual  EBrowseReturnVal::Type Browse(FWorldContext& WorldContext);

    virtual bool LoadMap(FWorldContext& WorldContext);

public:
    virtual void WorldAdded(const UWorld& InWorld);

    std::shared_ptr<FWorldContext> CreateNewWorldContext(const EWorldType::Type& WorldType);
protected:
    /** 保存了所有世界对象 */
    std::vector<std::weak_ptr<FWorldContext>> WorldList;
};

#endif //  _ENGINE_H_