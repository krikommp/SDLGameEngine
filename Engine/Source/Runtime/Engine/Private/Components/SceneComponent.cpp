#include <algorithm>

#include "Misc/CoreMiscDefines.h"
#include "Components/SceneComponent.h"

SceneCompoent::SceneCompoent()
{
}

SceneCompoent::~SceneCompoent()
{
}

bool SceneCompoent::AttachToComponent(const std::shared_ptr<SceneCompoent> &Parent)
{
    if (Parent == nullptr)
    {
        SetupAttachment(Parent);
        return true;
    }
    if (Parent != nullptr)
    {
        if (Parent == std::static_pointer_cast<SceneCompoent>(shared_from_this()))
        {
            return false;
        }

        // 判断是否已经加入在父组件中
        int LastAttachIndex = INDEX_NONE;
        auto ParentAttachChildren = Parent->GetAttachChildren();
        for (std::vector<std::shared_ptr<SceneCompoent>>::size_type i = 0; i < ParentAttachChildren.size(); ++i)
        {
            if (ParentAttachChildren[i] == std::static_pointer_cast<SceneCompoent>(shared_from_this()))
            {
                LastAttachIndex = i;
                break;
            }
        }

        // 保存子组件(这个组件)指向父组件
        SetAttachParent(Parent);

        if (LastAttachIndex != INDEX_NONE)
        {
            Parent->AttachChildren.insert(ParentAttachChildren.begin() + LastAttachIndex, std::static_pointer_cast<SceneCompoent>(shared_from_this()));
        }
        else
        {
            auto ThisPtr = std::static_pointer_cast<SceneCompoent>(shared_from_this());
            Parent->AttachChildren.push_back(ThisPtr);
        }
        return true;
    }
    return false;
}

void SceneCompoent::SetupAttachment(const std::shared_ptr<SceneCompoent> &InParent)
{
    if (InParent != std::static_pointer_cast<SceneCompoent>(shared_from_this()))
    {
        if (InParent != nullptr)
        {
            if (AttachParent != nullptr)
            {
                SetAttachParent(InParent);
            }
        }
    }
}

const std::vector<std::shared_ptr<SceneCompoent>> &SceneCompoent::GetAttachChildren() const
{
    return AttachChildren;
}

const Transform &SceneCompoent::GetTransform() const
{
    return ComponentToWorld;
}

void SceneCompoent::SetAttachParent(const std::shared_ptr<SceneCompoent> &NewAttachParent)
{
    this->AttachParent = NewAttachParent;
}