#ifndef _ACTOR_COMPONENT_H_
#define _ACTOR_COMPONENT_H_
#include <memory>

class Actor;
class ActorComponent : public std::enable_shared_from_this<ActorComponent>
{
public:
    ActorComponent();
    virtual ~ActorComponent();

public:
    /**
     * @brief 组件每帧调用函数，重写这个函数来实现不同组件每帧调用逻辑
     * 只有当组件被注册了才会调用
     * 
     * @param DeltaTime 上一帧到这一帧花费的时间
     */
    virtual void TickComponent(float DeltaTime);

private:
    /** 缓存正在持有的 Actor */
    std::shared_ptr<Actor> OwnerPrivate;
};

#endif // _ACTOR_COMPONENT_H_