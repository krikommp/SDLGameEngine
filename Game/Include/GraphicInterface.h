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
    ~SoftWareRHI() {
        SDL_DestroyRenderer(Renderer);
        SDL_DestroyWindow(Window);
        SDL_Quit();
    }

public:
    bool InitRHI(const SWindowInfo& InWindowInfo) {
        WindowInfo = InWindowInfo;
        SDL_Init(SDL_INIT_VIDEO);
        Pixels = nullptr;
        Pitch = 0;

        Window = SDL_CreateWindow(WindowInfo.Title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WindowInfo.Width * 4, WindowInfo.Height * 4, SDL_WINDOW_RESIZABLE);
        if (Window == nullptr) return false;
        Renderer = SDL_CreateRenderer(Window, -1,  SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
        if (Renderer == nullptr) return false;
        Buffer = SDL_CreateTexture(Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, WindowInfo.Width, WindowInfo.Height);
        if (Buffer == nullptr) return false;
        return true;
    }

    bool ClearColor(const FColor& Color) {
        uint32* Dst;
        for (uint32 Row = 0; Row < WindowInfo.Height; ++Row) {
            Dst = (uint32*)((uint8 *)Pixels + Row * Pitch);
            for (uint32 Col = 0; Col < WindowInfo.Width; ++Col) {
                *Dst++ = ConvertColorToHEX(Color);
            }
        }
        return true;
    }

    inline bool BeginRHI() {
        return SDL_LockTexture(Buffer, nullptr, &Pixels, &Pitch) >= 0;
    }

    void SetPixel(uint32 X, uint32 Y, const FColor& Color) {
        uint32* Dst = (uint32*)((uint8*)Pixels + X * Pitch);
        *(Dst + Y) = ConvertColorToHEX(Color);
    }

    inline void EndRHI() {
        SDL_UnlockTexture(Buffer);
        Pixels = nullptr;
        Pitch = 0;
    }

    bool Render() {
        SDL_RenderClear(Renderer);
        SDL_RenderCopy(Renderer, Buffer, nullptr, nullptr);
        SDL_RenderPresent(Renderer);
        return true;
    }

public:
    void SetTitleText(float FPS) {
        char NewTitle[1024];
        sprintf(NewTitle ,"%s - FPS: %3.2f", WindowInfo.Title, FPS);
        SDL_SetWindowTitle(Window, NewTitle);
    }

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

#endif //SDLGAMEENGINE_GRAPHICINTERFACE_H
