//
// Created by chenyifei on 2022/1/14.
//

#ifndef SDLGAMEENGINE_MYAPPENGINE_H
#define SDLGAMEENGINE_MYAPPENGINE_H

#include <AppEngine.h>

class MyAppEngine : public AppEngine {
protected:
    void OnStart() override;

    void OnUpdate() override;

    void OnExit() override;
};

#endif //SDLGAMEENGINE_MYAPPENGINE_H