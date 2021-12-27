#ifndef _ACTOR_H_
#define _ACTOR_H_

#include <vector>
#include <memory>

#include "Components/SceneComponent.h"

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
    /** 这个 */
    std::shared_ptr<SceneCompoent> RootComponent;
};

#endif //  _ACTOR_H_
