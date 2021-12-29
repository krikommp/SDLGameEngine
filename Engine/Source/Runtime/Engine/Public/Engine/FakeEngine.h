#ifndef _FAKEENGINE_H_
#define _FAKEENGINE_H_

#include <memory>

#include "Engine/Engine.h"

/**
 * 是所有 EngineLoop 的接口
 * 方便在代码中使用
 */
class IEngineLoop{
public:
    virtual int Init() = 0;

    virtual void Tick() = 0;
};

#endif //  _FAKEENGINE_H_