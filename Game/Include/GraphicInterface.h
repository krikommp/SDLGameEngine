//
// Created by chenyifei on 2022/1/14.
//

#ifndef SDLGAMEENGINE_GRAPHICINTERFACE_H
#define SDLGAMEENGINE_GRAPHICINTERFACE_H

#include "SoftWarePCH.h"
#include "GraphicMath.h"
#include "tgaimage.h"

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

struct Vertice {
    FVector2i pos;
    FVector2f uv;
};

class SoftWareRHI : public NonCopyable{
public:
    ~SoftWareRHI();

public:
    bool InitRHI(const SWindowInfo& InWindowInfo);

    bool SetImage(const char* ImageName);

    bool ClearColor(const FColor& Color);

    bool BeginRHI();

    void SetPixel(uint32 X, uint32 Y, const FColor& Color);

    void EndRHI();

    bool Render();

public:
    void SetTitleText(float FPS);

public:
    uint32 GetPixelWidth() const { return WindowInfo.PixelWidth; }
    uint32 GetPixelHeight() const { return WindowInfo.PixelHeight; }
private:
    SDL_Window* Window;
    SDL_Renderer* Renderer;
    SDL_Texture* Buffer;
public:
    SWindowInfo WindowInfo;
    int* ZBuffer = nullptr;
    TGAImage Image;
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

FORCEINLINE bool CheckPixelInScope(const SoftWareRHI& RHI ,int X, int Y) { return X >= 0 && X < static_cast<int>(RHI.GetPixelWidth()) && Y >= 0 &&  Y < static_cast<int>(RHI.GetPixelHeight());  }
void DrawLine(SoftWareRHI& RHI, const FVector2i& A, const FVector2i& B, const FColor& Color);
void DrawLine(SoftWareRHI& RHI, int AX, int AY, int BX, int BY, const FColor& Color);
void DrawTriangleTwo(SoftWareRHI &RHI, FVector2i &T0, FVector2i &T1,  FVector2i &T2, const FColor& Color);
void DrawTriangle(SoftWareRHI& RHI, Vertice* Pts , const FColor& Color);
void DrawEllipse(SoftWareRHI& RHI, int MX, int MY, int A, int B, const FColor& Color);

#endif //SDLGAMEENGINE_GRAPHICINTERFACE_H
