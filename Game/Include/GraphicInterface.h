//
// Created by chenyifei on 2022/1/14.
//

#ifndef SDLGAMEENGINE_GRAPHICINTERFACE_H
#define SDLGAMEENGINE_GRAPHICINTERFACE_H

#include "SortWarePCH.h"
#include "GraphicMath.h"

class SWindowInfo{
public:
    SWindowInfo() {
        Title = nullptr;
        Pixel = 1;
        Width = 1;
        Height = 1;
        PixelWidth = 1;
        PixelHeight = 1;
    }
    SWindowInfo(uint32 InWidth, uint32 InHeight, const char* InTitle, uint32 InPixel = 1) {
        Title = InTitle;
        Pixel = InPixel;

        Width = InWidth;
        Height = InHeight;

        PixelWidth = Width / Pixel;
        PixelHeight = Height / Pixel;
    }
public:
    uint32 Width;
    uint32 Height;
    uint32 Pixel;

    const char* Title;

    uint32 PixelWidth;
    uint32 PixelHeight;
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

public:
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
void DrawEllipse(SoftWareRHI& RHI, int MX, int MY, int A, int B, const FColor& Color);

#endif //SDLGAMEENGINE_GRAPHICINTERFACE_H
