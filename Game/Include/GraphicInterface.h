//
// Created by chenyifei on 2022/1/14.
//

#ifndef SDLGAMEENGINE_GRAPHICINTERFACE_H
#define SDLGAMEENGINE_GRAPHICINTERFACE_H

#include "SortWarePCH.h"
#include "GraphicMath.h"

struct SWindowInfo{
    uint32 Width;
    uint32 Height;

    const char* Title;
};

class SoftWareRHI : public NonCopyable{
public:
    ~SoftWareRHI();

public:
    bool InitRHI(const SWindowInfo& InWindowInfo);

    bool ClearColor(const FColor& Color);

    bool BeginRHI();

    void SetPixel(uint32 X, uint32 Y, const FColor& Color);

    void EndRHI();

    bool Render();

public:
    void SetTitleText(float FPS);

private:
    SDL_Window* Window;
    SDL_Renderer* Renderer;
    SDL_Texture* Buffer;

    SWindowInfo WindowInfo;

private:
    void* Pixels;
    int Pitch;
};

class RHIRendererRALL : public NonCopyable{
public:
    explicit RHIRendererRALL(SoftWareRHI* InRHI) : RHI(InRHI) {
        RHI -> BeginRHI();
    }
    ~RHIRendererRALL() {
        RHI -> EndRHI();
    }

private:
    SoftWareRHI* RHI;
};

void DrawLine(SoftWareRHI& RHI, const FVector2i& A, const FVector2i& B, const FColor& Color);
void DrawLine(SoftWareRHI& RHI, int AX, int AY, int BX, int BY, const FColor& Color);

#endif //SDLGAMEENGINE_GRAPHICINTERFACE_H
