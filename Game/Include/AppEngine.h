//
// Created by chenyifei on 2022/1/14.
//

#ifndef SDLGAMEENGINE_APPENGINE_H
#define SDLGAMEENGINE_APPENGINE_H

#include "GraphicInterface.h"
#include "GameTimer.h"
#include "GameController.h"

class AppEngine {
protected:
    virtual void OnStart() = 0;

    virtual void OnUpdate() = 0;

    virtual void OnExit() = 0;

public:
    void Construct();

    void Start();

private:
    static bool bExit;

    static void OnExitApp(IInputEvent* pEvent);

protected:
    void SetWidthAndHeight(const FVector2i& Size) { Width = Size[0]; Height = Size[1]; }
    void SetWidth(uint32 InWidth) { Width = InWidth; }
    void SetHeight(uint32 InHeight) { Height = InHeight; }
    void SetTitle(const char* InTitle) { Title = InTitle; }
    void SetClearColor(const FColor& Color) { ClearColor = Color; }
    void SetPixelSize(uint32 InPiexl) { Pixel = InPiexl; }

    void SetPixel(uint32 X, uint32 Y, const FColor& Color) { RHI.SetPixel(X, Y, Color); }

protected:
    uint32 GetWindowWidth() const { return RHI.WindowInfo.Width; }
    uint32 GetWindowHeight() const { return RHI.WindowInfo.Height; }
    FVector2ui GetWindowsWidthAndHeight() const { return FVector2ui(RHI.WindowInfo.Width, RHI.WindowInfo.Height); }
    uint32 GetPixelWidth() const { return RHI.WindowInfo.PixelWidth; }
    uint32 GetPixelHeight() const { return RHI.WindowInfo.PixelHeight; }
    FVector2ui GetPixelWidthAndHeight() const { return  FVector2ui(RHI.WindowInfo.PixelWidth, RHI.WindowInfo.PixelHeight); }
    uint32 GetPixelSize() const { return RHI.WindowInfo.Pixel; }

private:
    uint32 Width = 100;
    uint32 Height = 100;
    const char* Title = "Blank";
    uint32 Pixel = 1;

protected:
    SoftWareRHI RHI;
    GameTimer Timer;
    GameController Controller;

private:
    FColor ClearColor;
};

#endif //SDLGAMEENGINE_APPENGINE_H
