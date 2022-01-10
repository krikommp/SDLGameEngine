#ifndef _GAMEENGINE_H_
#define _GAMEENGINE_H_
#include <memory>

#include "Engine.h"
#include "GameInstance.h"

class GameEngine : public Engine
{
public:
    void Init() override {

    }

    void Start() override {

    }

    void Tick(float DeltaSeconds) override {

    }

    void PreExit() override {

    }

public:
    std::shared_ptr<GameInstance> GameInstance;
};

#endif //  _GAMEENGINE_H_