#ifndef _ACTOR_H_
#define _ACTOR_H_

#include <set>
#include <vector>
#include <memory>

class ActorComponent;
class SceneCompoent;

class Actor
{
public:
    Actor();
    ~Actor();

public:
    /**
     * @brief Actor 每帧调用
     * 
     * @param DeltaSeconds 上一帧到这一帧花费的时间
     */
    virtual void Tick(float DeltaSeconds);

public:
    /** Array of all actors whose Owner is this Actor */
    std::vector<std::weak_ptr<Actor>> Children;


protected:
    /** 根组件 如果需要显示在关卡中需要使用 SceneComponent */
    std::shared_ptr<SceneCompoent> RootComponent;

    /** Actor 持有的所有 Component */
    std::set<std::shared_ptr<ActorComponent>> OwnedComponents;
};

#endif //  _ACTOR_H_
