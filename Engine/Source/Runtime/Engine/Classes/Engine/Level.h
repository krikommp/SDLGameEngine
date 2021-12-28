#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <vector>
#include <memory>

#include "GameFramework/Actor.h"
#include "GameFramework/WorldSettings.h"
#include "Engine/LevelScriptActor.h"
/**
 * @brief Level 对象包含了 Actor
 * World 包含了多个 Level
 */
class Level
{
public:
    std::shared_ptr<WorldSettings> GetWorldSettings() const;

public:
    std::vector<std::shared_ptr<Actor>> Actors;

private:
    std::shared_ptr<WorldSettings> WorldSettings;

    std::shared_ptr<LevelScriptActor> LevelScriptActor;
};

#endif //  _LEVEL_H_