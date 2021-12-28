#ifndef _WORLD_H_
#define _WORLD_H_
#include <vector>
#include <memory>

#include "Level.h"
#include "GameFramework/WorldSettings.h"

class World
{
public:
    std::shared_ptr<WorldSettings> GetWorldSetting();

public:
    std::vector<std::shared_ptr<Level>> Levels;

private:
    /** 主关卡，表示一开始就加载进来的关卡 */
    std::shared_ptr<Level> PersistentLevel;

    /** Game 模式下指向 PersistentLevel， Editor 模式下可能指向不同的关卡 */
    std::shared_ptr<Level> CurrentLevel;
};

#endif //  _WORLD_H_