//
// Created by chenyifei on 2022/1/14.
//

#ifndef SDLGAMEENGINE_GRAPHICINTERFACE_H
#define SDLGAMEENGINE_GRAPHICINTERFACE_H

#include "SortWarePCH.h"

struct SWindowInfo{
    uint32 Width;
    uint32 Height;

    const char* Title;
};

class SoftWareRHI : public NonCopyable{
    friend class RHITexture;
public:
    SoftWareRHI(const SWindowInfo& InWindowInfo) : WindowInfo(InWindowInfo) {
        SDL_Init(SDL_INIT_VIDEO);
    }

    ~SoftWareRHI() {
        SDL_DestroyRenderer(Renderer);
        SDL_DestroyWindow(Window);
        SDL_Quit();
    }

public:
    bool InitRHI() {
        Window = SDL_CreateWindow(WindowInfo.Title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WindowInfo.Width, WindowInfo.Height, SDL_WINDOW_RESIZABLE);
        if (Window == nullptr) return false;
        Renderer = SDL_CreateRenderer(Window, -1,  SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
        if (Renderer == nullptr) return false;
        Buffer = SDL_CreateTexture(Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, WindowInfo.Width, WindowInfo.Height);
        if (Buffer == nullptr) return false;
        return true;
    }

    bool ClearColor() {
        void* Pixels;
        int Pitch;
        if (SDL_LockTexture(Buffer, nullptr, &Pixels, &Pitch) < 0) return false;

        SDL_PixelFormat* Format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
        // uint32 Color = SDL_MapRGBA(Format, 0xff, 0, 0, 0xff / 3);
        SDL_memset(Pixels, 0, WindowInfo.Height * Pitch);

        SDL_UnlockTexture(Buffer);
        return true;
    }

    bool Render() {
        SDL_RenderClear(Renderer);
        SDL_RenderCopy(Renderer, Buffer, nullptr, nullptr);
        SDL_RenderPresent(Renderer);
        return true;
    }

private:
    SDL_Window* Window;
    SDL_Renderer* Renderer;
    SDL_Texture* Buffer;

    SWindowInfo WindowInfo;
};

#endif //SDLGAMEENGINE_GRAPHICINTERFACE_H
