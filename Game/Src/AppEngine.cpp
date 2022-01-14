//
// Created by chenyifei on 2022/1/14.
//

#include "AppEngine.h"

bool AppEngine::bExit = false;

void AppEngine::ExitApp() {
    AppEngine::bExit = true;
}


void AppEngine::Construct() {
    OnStart();

    SWindowInfo Info{.Width = Width / 4, .Height = Height / 4, .Title = Title};
    RHI.InitRHI(Info);
    GAppObserver.Register(AppEngine::ExitApp);
}

void AppEngine::Start() {
    while(!bExit) {
        Controller.Tick();
        Timer.Tick();

        RHIRendererRALL RHIScope(&RHI);
        RHI.ClearColor(ClearColor);

        OnUpdate();

        RHI.Render();
        RHI.SetTitleText(Timer.GetFPS());
    }
    OnExit();
}

