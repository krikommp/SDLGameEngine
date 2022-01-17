//
// Created by chenyifei on 2022/1/14.
//

#include "AppEngine.h"

bool AppEngine::bExit = false;

void AppEngine::OnExitApp(IInputEvent* pEvent) {
    AppExitEvent* Event = dynamic_cast<AppExitEvent*>(pEvent);
    if (Event != nullptr)
    {
    	AppEngine::bExit = true;
    }
}


void AppEngine::Construct() {
    OnStart();

    SWindowInfo Info(Width, Height, Title, Pixel);
    RHI.InitRHI(Info);
    srand(static_cast<uint32>(time(nullptr)));
    GInputObserver.Register(AppEngine::OnExitApp);
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

