//
// Created by chenyifei on 2022/1/14.
//

#ifndef SDLGAMEENGINE_APPENGINE_H
#define SDLGAMEENGINE_APPENGINE_H

#include "GraphicInterface.h"
#include "GameTimer.h"
#include "GameController.h"

static bool bExit = false;

void OnExit() {
    bExit = true;
}

class AppEngine {
protected:
    virtual void OnStart() {}

    virtual void OnUpdate() {}

    virtual void OnExit() {}

public:
    void Construct() {
        SWindowInfo Info{.Width = Width, .Height = Height, .Title = Title};
        RHI.InitRHI(Info);
        GAppObserver.Register(::OnExit);
    }

    void Start() {
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

protected:
    void SetWidth(uint32 InWidth) { Width = InWidth; }
    void SetHeight(uint32 InHeight) { Height = InHeight; }
    void SetTitle(const char* InTitle) { Title = InTitle; }
    void SetClearColor(const FColor& Color) { ClearColor = Color; }
protected:
    uint32 Width = 100;
    uint32 Height = 100;
    const char* Title = "Blank";

private:
    SoftWareRHI RHI;
    GameTimer Timer;
    GameController Controller;

private:
    FColor ClearColor;
};

#endif //SDLGAMEENGINE_APPENGINE_H
