#ifndef _SCENE_COMPONENT_H_
#define _SCENE_COMPONENT_H_

#include <memory>
#include <vector>

#include "ActorComponent.h"
#include "Math/Transform.h"

class SceneCompoent : public ActorComponent
{
public:
    SceneCompoent();
    virtual ~SceneCompoent();

public:
    /**
     * @brief 将这个组件附加在其他组件上
     * 这里会判断是否是构造环境，如果不是会有其他操作 TODO
     * 
     * @param Parent 父组件
     * @return true 成功
     * @return false 失败
     */
    bool AttachToComponent(const std::shared_ptr<SceneCompoent> &Parent);

    /**
     * @brief 组件注册，会在构造的时候执行
     * 
     * @param InParent 
     */
    void SetupAttachment(const std::shared_ptr<SceneCompoent> &InParent);

public:
    const std::vector<std::shared_ptr<SceneCompoent>> &GetAttachChildren() const;
    const Transform &GetTransform() const;

private:
    /**
     * 设置 AttachParent 的值
     * TODO 可能其他系统需要这个值改变的通知
     */
    void SetAttachParent(const std::shared_ptr<SceneCompoent> &NewAttachParent);

private:
    /** 子场景组件 */
    std::vector<std::shared_ptr<SceneCompoent>> AttachChildren;

    /** 指向正在 Attach 的组件 */
    std::shared_ptr<SceneCompoent> AttachParent;

    /** 当前组件的 Transform */
    Transform ComponentToWorld;
};

#endif // _SCENE_COMPONENT_H_